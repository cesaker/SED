#include <16F84.h>

void main() {
   set_tris_b(0b00000000);
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ) {}
     output_b(input_b()+1);
     while ( !input(PIN_A0) ) {}
   }
}

//El puerto al poder seleccionarse él solo al no tener la sentencia fastio cambia 
//el puerto de salida como uno de entrada, por eso cuando utilizamos el pulsador introduces 
//un 1 y a ese le sumas el 1 de la linea de codigo, dando como resultado un 2
