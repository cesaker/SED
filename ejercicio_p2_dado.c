#include <16F84.h>
#use fast_io(a)
#use fast_io(b)
void main() {

   const int tabla[10]={0x3f,0x6,0x5b,0x4f,0x66,0x6d,0x7d,0x7,0x7f,0x6f};
   int contador;
   
   set_tris_b(0b00000000);
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ){contador++;}
     contador=contador%6+1;
     output_b(tabla[contador]);
     
 
     while ( !input(PIN_A0) ) {}
   }
}

//La diferencia principal que podemos observar al utilizar una variable constante
//de una entera es en el uso de la RAM y la ROM como vemos en el OUTPUT inferior,
//cuando utilizamos una variable entera (int) el uso de ambas es 
//ROM=7%
//RAM=24%-26%
//Mientas que si usamos una variable const int el uso de ambas es:
//ROM=6%
//RAM=9%-12%
//Por lo que podemos concluir con que utilizar una variable const int mejora la
//eficiencia del programa.


