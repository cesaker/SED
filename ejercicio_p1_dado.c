#include <16F84.h>
#use fast_io(a)
#use fast_io(b)
void main() {
   int count;
   set_tris_b(0b00000000);
   output_b(0);
   
   while (TRUE) {
     while ( input(PIN_A0) ) {count++}
     output_b(count%6 + 1);
     while ( !input(PIN_A0) ) {}
   }
}
