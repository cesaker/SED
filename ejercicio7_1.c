//ADC_to_PWM con el m�dulo CCP.
//
//El programa realiza una modulaci�n de anchura de pulsos (PWM) mediante el m�dulo CCP1, con
//salida de se�al por la l�nea RC2/CCP1. Se establece un periodo fijo de 16,384ms. Para conseguir llegar a
//este periodo, debido a la limitaci�n del timer2 que usa el CCP en modo PWM, hemos rebajado la velocidad
//del reloj del micro a 1MHz.
//
//El TMR2 trabajando con un preescaler de 1:16 y una frecuencia de 1MHz incrementa en uno cada 16*4Tosc=64uS
//TMR2 se usa para fijar el periodo de la se�al.
//Un osciloscopio conectado en RC2/CCP1 permitir� visualizar las variaciones del ancho de pulso de la se�al
//de salida seg�n la tensi�n anal�gica en el pin RA2/AN2. Se utiliza tambi�n el terminal virtual para visualizar
//la consigna de tiempo en alta de la se�al PWM.

#include "18F4520.h"
#device ADC=8 
#fuses NOPROTECT,NOCPD,NOLVP,NOWDT,XT,NOXINST
#use delay(clock=1000000)

#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8) //hay que comprobar 
                  //concordancia con propiedades del terminal en proteus


int periodo_timer2=255;    //Fijamos el valor de PR2 para que el Timer tenga el m�ximo periodo

void main()
{

   int a, b;
 
   setup_adc_ports(AN0_TO_AN3);   //entradas anal�gicas

//El TMR2 trabaja con un preescaler 1:16 por lo que con una frecuencia de 1MHz evoluciona
//cada 64uS ((4*Tosc)*16)

   setup_timer_2(T2_DIV_BY_16, periodo_timer2 ,4);   //Carga el periodo (registro PR2 del CCP) y activa TMR2
                                             //El post-scaler (4 en este caso) podr�a usarse para
                                             //la generaci�n de interrupciones del TMR2 (en este ejemplo no se usa) 

//El m�dulo CCP1 se congigura en el modo PWM con salida de se�al por RC2/CCP:

   setup_ccp1(CCP_PWM);         //Configura el modo PWM para el CCP1
   

//Se activa el ADC y se selecciona el canal RA2/AN2:
   setup_adc(adc_clock_div_2);   //Ajusta tiempo de ciclo para el ADC
   set_adc_channel(2);
   delay_us(10);

   while(TRUE)
   {

     a=16;
     b=17;
     
     CCP_1_LOW=a + read_adc()/b;     //Inicia la conversi�n y carga la anchura del pulso
                              //en parte menos significativa de CCP_1 (declarada en
                              //18F4520.h. Cada vez que var�e su valor cambiar� el
                              //duty_cicle de la se�al PWM
    
           
      printf("Valor consigna: %4u \r", CCP_1_LOW);
      delay_ms(500);         //permitimos cambiar la consigna cada medio segundo
   }
}

//CCP_1_LOW = a + read_adc()/b

//15'62=a+0/b
//31'25=a+255/b

//a=15'625
//b=16'32
