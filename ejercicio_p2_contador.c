#include <16F84.h>
#use delay(clock=1000000)

void main() {

   const int tabla[10]={0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f};
   int contador=0;
   int i;
   
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ){
      if (contador==60)
         contador=0;
      for (i=1;i<=50;i++){
         output_b(~tabla[contador/10]);
         output_high(PIN_A1);
         delay_ms(10);
         output_low(PIN_A1);
         output_b(~tabla[contador%10]);
         output_high(PIN_A2);
         delay_ms(10);
         output_low(PIN_A2);
      }
      contador++;
     }
     
     while(!input(PIN_A0)){
     contador=0;
     output_b(~tabla[contador]);
     output_high(PIN_A1);
     output_low(PIN_A1);
     output_high(PIN_A2);
     output_low(PIN_A2);
     }
   }
}

//Este programa está hecho para realizar un contador de 7 segmentos con dos displays
//que llegue hasta 59 seg, lo primero que hemos hecho ha sido poner un delay en el reloj
//de un segundo para tener bien espaciados los tiempos. Posteriormente realizamos la
//condición de que si el contador llega a 60 nos muestre un 00 por pantalla. Como nos 
//dice que nos debe mostrar por pantalla cada dígito 50 veces cada segundo realizamos
//un bucle for que vaya desde 1 a 50 y que cada display se encienda cada 10ms. Esto es
//porque si realizamos la cuenta de 1/50 nos da 0.02, que coincide con la suma de los 
//dos displays, es decir, ambos se encenderán 50 veces por separado cada 10ms.
//Por último debemos tener en cuenta de que cuando pulsemos en pulsador el contador
//regresará a 0, mostrando eso por pantalla.

//Nota:he puesto los comandos output_high y output_low con el delay entre medias de 
//ellos dos para que se enciedan y se apaguen cada ese tiempo, no da problema ninguno, 
//por lo que creo que está bien hecho.
         
         
         
         
     
   

