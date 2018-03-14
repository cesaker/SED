/*
 Para ello, el programa deberá dar la opción de cambiar la clave cuando lo desee el usuario
*/
#include <18F4520.h>
#use delay(clock=8000000) 
#use fast_io(B) 
#include "LCDeasy.c"
#include "KBD2.c" //Control del teclado matricial 
#INT_RB
char tecla;
int8 i,j,a,c,Salida;
const int Intro[]={50,52,49,48};
int digitos[];
int entrada[];
char f[];
int Clave(){
   lcd_send_byte(0, 1); //Borra LCD
   lcd_send_byte(0, 2); //Posición inicial
   printf(lcd_putc,"ENTER PASSWORD:\n");
   for(i=0;i<=3;i++){
   f=0;
   while (f==0)
   f=kbd_getc();
   //printf(lcd_putc,"%u ",f); 
   write_eeprom(i+4,f);
   //entrada[i]=read_eeprom
   printf(lcd_putc,"%c ",read_eeprom(i+4));
   if(i==3){
      delay_ms(200);
      lcd_send_byte(0, 1); //Borra LCD
      lcd_send_byte(0, 2); //Posición inicial
      printf(lcd_putc,"Comprobacion:");
      delay_ms(100);
      j=0;
      a=0;
       printf(lcd_putc,"\n");
      while(j<4){
      //printf(lcd_putc,"%u ",read_eeprom(j+4));
        //if(entrada[j]==Intro[j]){
        if(read_eeprom(j)==read_eeprom(j+4)){
          a=a+1;
         }
         j++;
      }
     
     //printf(lcd_putc,"\n");
     if(a==4){
         printf(lcd_putc,"Clave correcta");
         Salida=1;
     }
      else {
         printf(lcd_putc,"Clave Incorrecta");
         Salida=0;
     }
      
   }//if
   }//For
   delay_ms(500);
   return Salida;
}
void Nueva_Clave(void){
   lcd_send_byte(0, 1); //Borra LCD
   lcd_send_byte(0, 2); //Posición inicial
   printf(lcd_putc,"Nueva Clave\n");
   for(i=0;i<=3;i++){
   f=0;
   while (f==0)
   f=kbd_getc();
   //printf(lcd_putc,"%u ",f); 
   write_eeprom(i,f);
   //entrada[i]=read_eeprom
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
//printf(lcd_putc,"Clave inicial\n");
   for(i=0;i<=3;i++){
      digitos[i]=read_eeprom(i);
   //printf(lcd_putc,"%d ",digitos[i]);
   }
//lcd_init();// printf(lcd_putc,"Pulsa teclas…");
   while(TRUE){
      c=0;
      lcd_send_byte(0, 1); //Borra LCD
      lcd_send_byte(0, 2); //Posición inicial
      do{
         printf(lcd_putc,"Tecla'+'->No cambiar\nTecla'-'->Cambiar");
         c=kbd_getc();
      }while(c==0);;
      if(c==43){ //Cambiar
         Clave();
         if (Salida==1)
         sleep();
      }
      else if(c==45){
         Nueva_Clave();
      }
      else{
         lcd_send_byte(0, 1); //Borra LCD
         lcd_send_byte(0, 2); //Posición inicial
         printf(lcd_putc,"Marca una opcion\nvalida");
         delay_ms(500);
      }
   } //True
} //Main
