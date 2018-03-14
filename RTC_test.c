////////////// Programa básico de test del RTC PCF8583
////////////// Fija fecha y hora iniciales
////////////// y visualiza en el LCD cada segundo (aproximadamente)

#include "18F4520.H"
#fuses HS, NOWDT, WDT2048
#use delay(clock=8000000, restart_wdt)
#include <ctype.h>
#include "PCF8583.c"
#include "LCDeasy.c"


#use fast_io(B)

//=================================
void main()
{

char weekday[10];
date_time_t dt; //////// El tipo de estructura date_time_t
                      // está definido en PCF8583.c


PCF8583_init(); ////////////////-----------------INICIALIZACIÓN



      dt.month   = 12;    // December
      dt.day     = 31;    // 31
      dt.year    = 14;    // 2014
      dt.hours   = 23;    // 23 hours (11pm in 24-hour time)
      dt.minutes = 59;    // 59 minutes
      dt.seconds = 50;    // 50 seconds
      dt.weekday = 0;     // 0 = Sunday, 1 = Monday, etc.

      PCF8583_set_datetime(&dt); ////------------Puesta en fecha-hora

   lcd_init();
   lcd_send_byte(0, 1); //Borra LCD


while(TRUE)
  {

   delay_ms(1000);
   lcd_send_byte(0,2);
   PCF8583_read_datetime(&dt); ////-------------Lectura de fecha y hora del RTC

   strcpy(weekday, weekday_names[dt.weekday]);  // ptr=strncpy (s1, s2,  n)
                                               // Copy up to n characters s2->s1

   printf(lcd_putc, "%s, %2u/%2u/%2u \nHora: %u:%2u:%2u       ",
           weekday, dt.day, dt.month, dt.year,
           dt.hours, dt.minutes, dt.seconds);


   }

}

/*Activando el WDT comprobamos que aunque el pic esta dormido la fecha y hora
no dejan de avanzar y cada 8 segundos se actualiza en el display*/
