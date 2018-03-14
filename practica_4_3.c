#include <18F4520.h>
#use delay(clock=8000000) 
#use fast_io(b) 
#include "LCDeasy.c"
#include "KBD2.c" 
#INT_RB

int8 i,j,a,c,salida;
const int Intro[]={52,50,49,48};
int digitos[];
char f[];

int Clave(){
   lcd_send_byte(0, 1); //Borramos el LCD
   lcd_send_byte(0, 2); //Posición inicial
   printf(lcd_putc,"ENTER PASSWORD:\n");
   for(i=0;i<=3;i++){
   f=0;
      while (f==0)
      f=kbd_getc();
      write_eeprom(i+4,f);
      printf(lcd_putc,"%c ",read_eeprom(i+4));
   
      if(i==3){
      delay_ms(200);
      lcd_send_byte(0, 1); //Borramos el LCD
      lcd_send_byte(0, 2); //Posición inicial
      printf(lcd_putc,"Comprobacion:");
      delay_ms(100);
      j=0;
      a=0;
      printf(lcd_putc,"\n");
         while(j<4){
            if(read_eeprom(j)==read_eeprom(j+4)){
             a=a+1;
            }
         j++;
         }
         if(a==4){
            printf(lcd_putc,"Clave correcta");
            salida=1;
            output_high(PIN_C0); //Hacemos que se encienda el LED
            delay_ms(1000);
            output_low(PIN_C0);
         }
         else {
            printf(lcd_putc,"Clave Incorrecta");
            salida=0;
         }   
      }
   }
   delay_ms(500);
   return salida;
}

void Nueva_Clave(void){
   lcd_send_byte(0, 1); //Borramos el LCD
   lcd_send_byte(0, 2); //Posición inicial
   printf(lcd_putc,"Nueva Clave\n");
   for(i=0;i<=3;i++){
   f=0;
   while (f==0)
   f=kbd_getc();
   write_eeprom(i,f);
   printf(lcd_putc,"%c ",read_eeprom(i));
   delay_ms(200);
   }
}

void main(){
   
   enable_interrupts(INT_RB);
   enable_interrupts(GLOBAL);
   ext_int_edge(H_to_L);
   lcd_init();
   
   for(i=0;i<=3;i++){
      write_eeprom(i,Intro[i]);
   }
   
   for(i=0;i<=3;i++){
      digitos[i]=read_eeprom(i);
   }
   
   while(TRUE){
      c=0;
      lcd_send_byte(0, 1); //Borramos el LCD
      lcd_send_byte(0, 2); //Posición inicial
      
      do{
         printf(lcd_putc,"Tecla'+' No cambiar\nTecla'-' Cambiar");
         c=kbd_getc();
      }while(c==0);
      if(c==43){ //Cambiar (es el correspondiente al código ascii con +)
         Clave();
         if (salida==1)
         sleep();
      }
      else if(c==45){ //Equivalente con el - en el código ascii
         Nueva_Clave();
      }
   } 
}

//Voy a explicar cada parte de forma resumida:

//Clave: Lo primero que hacemos es borrar el LCD e inicializarlo en la posición
//inicial. Posteriormente vamos escribiendo en la eeprom los caracteres de 
//nuestra clave (lo hacemos de 0 a 3 debido a que solo vamos a tener 4 dígitos).
//Una vez estén escritos volvemos a borrar el LCD y hacemos una comprobación
//de que la clave introducida es correcta, comparanado los valores que vaya 
//tomando j con los que hay escritos en la eeprom. Si es correcto cada caracter
//incrementamos el valor de "a" y por último (si llega "a" a 4) decimos que la
//clave es correcta y encendemos el led, si el valor es incorrecto devolverá un 
//0 y no hará nada.

//Nueva_Clave: Este es el caso que deberemos seleccionar cuando encendamos por
//primera vez el programa o queramos cambiar la clave que habíamos grabado
//anteriormente. Para poder realizarlo lo que hacemos es ir esciribiendo en las
//posiciones de la eeprom los valores deseados (utlizamos un printf para mostrar
//por pantalla los valores escritos).

//Main: Por último el programa principal. Hacemos un foro que recorra las
//posiciones de escritura en la eeprom y hacemos un printf de las distintas
//opciones de las que disponemos (para introducir la clave ya escrita en la 
//eeprom o para escribir una clave nueva), con estas dos opciones, dependiendo
//de la que se elija vamos a utilizar o "Clave" o "Nueva_Clave".

//Por último tener en cuenta que una vez escrita la clave y detectada que dicha
//clave es correcta debemos pulsar el pulsador colocado debajo de la resistencia
//de PULLUP.
