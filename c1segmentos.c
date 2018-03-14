#include <16F84.h>
#use fast_io(a) 
#use fast_io(b) 

void main() {
   set_tris_b(0b00000000);
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ) {}
     output_b(input_b()+1);
     while ( !input(PIN_A0) ) {}
   }
}

//Si tienes una caida de tesion de 5V-1.5V(que es el minimo que necesita el
//display para funcionar), luego el 3.5V lo divides entre los 500 ohm que tiene
//la resistencia y te sale el amperaje minimo que necesita cada segmento para
//para funcionar, por ultimo multiplicamos por 7 para conseguir el amperaje 
//total que es 47.2mA cuando están todos encendidos, para canda segmento es 6.7mA
// que es algo menor que los 10 mA teóricos que debería tener cada segmento.
