#include <16F84.h>
#include <stdlib.h>
#use fast_io(a)
#use fast_io(b)
void main() {
   set_tris_b(0b00000000);
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ) {}
     output_b(rand()%6+1);
     while ( !input(PIN_A0) ) {}
   }
}
