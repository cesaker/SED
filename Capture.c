//Módulo CCP en modo de Captura. Medida de la duración de pulsos.
//
//El ejemplo emplea el módulo CCP1 para capturar el valor del TMR1 cada vez que lleguen
//un flanco ascendente  y otro descendente por la línea RC2/CCP1.
//Conocida la velocidad con la que evoluciona el TMR1, se puede determinar el lapsus de 
//tiempo transcurrido entre  flancos (la duración del pulso).
//Este programa emite pulsos de disparo de 10us cada 300ms, que se supone provocan los pulsos de respuesta
// que se capturan con el CCP. Podrían tratarse por ejemplo de los pulsos de ECO de un sensor de ultrasonidos del
//modelo SRF04 o SRF05, con el que quisiéramos realizar una medida de distancia cada 0,3 segundos (aprox.).
//En el terminal virtual conectado al módulo USART visualizamos el tiempo en alta del pulso capturado.

#include "18F4520.h"
#use delay(clock=4000000,RESTART_WDT)
#fuses NOPROTECT,NOCPD,NOLVP,NOWDT,XT,NOXINST
#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8) //hay que comprobar 
                  //concordancia con propiedades del terminal en proteus
#use fast_io (C)

   INT captura=1;         //Contiene nº de captura realizada
   LONG T_subida, T_bajada;   //se actualizan en la rutina de interrupción
   float T_alta;            //se calcula en el main
  
   
   #INT_ccp1      // interrupción del CCP1
   void RSI_tratamiento()   //Rutina de tratamiento del CCP1
   {
      output_bit(PIN_C3, ~input(PIN_C3));//para ver en osciloscopio
      IF (captura < 2) //Si es la primera de las dos capturas
                        // se ha detectado el flanco ascendente
       { 
         T_subida=CCP_1;
         captura ++; //Para la siguiente captura:
         setup_ccp1 (ccp_capture_fe); //siguiente captura en el flanco descendente
       }

   ELSE   //Se trata de la segunda de las capturas (flanco descendente)
   {
      set_timer1(0); //Repone el TMR1 con 0  
      T_bajada = CCP_1; //Lee valor capturado (el valor de TIMER1 cargado en CCP_1)
      captura = 1;  //Restablecer 1ª captura
      setup_ccp1 (ccp_capture_re); //Siguiente captura en el flanco ascendente
   }
   }

void main()
{
   set_tris_c (0b10110110);  //Puerto C entrada, salvo:
                        //pin RC7 (salida TX del USART),
                        //RC0 que se usa para dar pulsos de disparo del generador 'monostable'
                        //RC3 que se emplea para visualizar los instantes en que realmente empieza
                        //a ejecutarse la RSI
   
   //El TMR1 actúa en el modo temporizador con reloj interno y un preescaler 1:8 evoluciona 
   //cada 8uS (con un cuarzo de 4MHz).
   //Según esto, el periodo de tiempo que se puede medir sería superior a 0,5 segundos (8us*2^16).
   //Para otro rango se debe seleccionar un preescaler diferente.
   setup_timer_1 (T1_INTERNAL|T1_DIV_BY_8); //TMR1 Interno y preescaler de 1:8
   //El módulo CCP1 actúa en modo de captura, inicialmente por flanco de subida:
   setup_ccp1 (ccp_capture_re); //1ª Captura en el flanco ascendente
   enable_interrupts (INT_ccp1); //habilita interrupción del CCP1
   enable_interrupts (global); //Habilita interrupciones
   
   WHILE (TRUE) //el bucle emite pulsos en RC0 y visualiza medidas con una separacíón mínima de 300ms
   {
    output_high(PIN_C0);
    delay_us(10);
    output_low(pin_C0);
    delay_ms(300);
    T_alta=8.0*(T_bajada-T_subida); //multiplicamos por 8*4Tosc para visualizarlo en microsegundos
    printf ("%5lu-%5lu --> T_alta: %6.1g us \r  ", T_bajada,T_subida, T_alta); //Visualiza resultado
   }
}

