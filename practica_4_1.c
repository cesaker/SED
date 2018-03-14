#include <18F4520.h>
#use delay(clock=8000000)
#include "lcdeasy.c"
#define LCD_DATO 1
#define LCD_COMANDO 0
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02

int i;

main(){
   lcd_init();
   while(1)
   {
       
      lcd_send_byte(LCD_COMANDO, LCD_CLEAR);
      lcd_send_byte(LCD_COMANDO, LCD_HOME);
      
      lcd_putc("Practicas de SED sesion 4 xdxdxdxdxdxdxd");
      delay_ms(2000);
      lcd_putc("\n");
      lcd_putc("jajjjjajjjajjjjajjajajajajajajajajajaaxd");
      delay_ms(2000);
      
      for(i=0; i<26;i++){  
      lcd_send_byte(0,0b00011100);
      delay_ms(100);
      }
      
      for(i=0; i<26;i++){
      lcd_send_byte(0,0b00011000);
      delay_ms(100);
      }
      }
   }


//Lo que hemos hecho para poder desplazar el LCD tanto para la izquierda como
//para la derecha ha sido realizar un bucle for que recorra las posiciones requeridas
//y utilizar el comando "send_byte" con las variantes necesarias para la realización
//del movimiento.
