////////////// Programa básico de test del RTC PCF8583
////////////// Fija fecha y hora iniciales
////////////// y visualiza en el LCD cada segundo (aproximadamente)
////////////// Visualiza también en terminal virtual (salida RS232) desde que
////////////// pulsamos una tecla concreta  en el teclado del
////////////// PC (entrada RS232,) hasta que se pulse otra distinta. 

#include "18F4520.H"
#fuses HS, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP, NOXINST
#use delay(clock=8000000, restart_wdt)
#include <ctype.h>
#include "PCF8583.c"
#include "LCDeasy.c"

#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, bits=8) //hay que comprobar 
                  //concordancia con propiedades del terminal en proteus

#use fast_io(B)

//=================================
void main()
{

char weekday[10], tecla;
date_time_t dt; //////// El tipo de estructura date_time_t
                      // está definido en PCF8583.c

PCF8583_init(); ////////////////-----------------INICIALIZACIÓN

      dt.month   = 12;    // December
      dt.day     = 31;    // 31
      dt.year    = 12;    // 2006
      dt.hours   = 23;    // 23 hours (11pm in 24-hour time)
      dt.minutes = 59;    // 59 minutes
      dt.seconds = 50;    // 50 seconds
      dt.weekday = 0;     // 0 = Sunday, 1 = Monday, etc.

      PCF8583_set_datetime(&dt); ////------------Puesta en fecha-hora

   lcd_init();
   lcd_send_byte(0, 1); //Borra LCD

   printf("OPCIONES DEL TERMINAL: \n\r -Pulsando 'v' se activa la visualización 
           \n\r -Pulsando cualquier otra se desactiva\n\r");
           
while(TRUE)
  {
   delay_ms(1000);
   lcd_send_byte(0,2);
   PCF8583_read_datetime(&dt); ////-------------Lectura del RTC

   strcpy(weekday, weekday_names[dt.weekday]);  // ptr=strncpy (s1, s2,  n)
                                                // Copy up to n characters s2->s1

   printf(lcd_putc, "%s, %2u/%2u/%2u \nHora: %u:%2u:%2u       ",
           weekday, dt.day, dt.month, dt.year,
           dt.hours, dt.minutes, dt.seconds);

if(kbhit()) tecla=getchar();//nota: durante la simulación con proteus hay que 
                            //seleccionar con el cursor la ventana de
                           //visualización del terminal para que le lleguen 
                           //las pulsaciones del teclado del PC como entrada
        
if(tecla=='v')
 printf( "Fecha: %s, %2u/%2u/%2u  Hora: %u:%2u:%2u   \n\r    ",
           weekday, dt.day, dt.month, dt.year,
           dt.hours, dt.minutes, dt.seconds);
   }

}
