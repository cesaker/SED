#include <18F4520.h>
#use delay(clock=8000000)
#include "lcdeasy.c"
#define LCD_DATO 1
#define LCD_COMANDO 0
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02

int min;
int seg;

#INT_TIMER0

void un_segundo(VOID) 
{
   set_timer0 (3036);
   if (++seg == 60)
   {
      seg = 0;
      if (++min == 60) min = 0;
   }
}


void main() 
{
    lcd_init();
   setup_timer_0 (T0_INTERNAL|T0_DIV_32); 
   enable_interrupts (INT_TIMER0) ;
   enable_interrupts (GLOBAL) ;
   
   while(1)
   {
   lcd_send_byte(0,0x02);
   lcd_putc("RELOJ con TIMER");
   lcd_putc("\n");
   printf(lcd_putc, "MIN:%2u SEG:%2u", min, seg);
   delay_ms(100);
   }
}

//Al comienzo del programa realizamos el set_timer0 para recargar el TMR1 para 
//el siguiente desbordamiento de manera que cada 100ms se desborde el TMR1 (aprox).
