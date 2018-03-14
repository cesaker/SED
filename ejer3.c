////////////// Programa básico de test del RTC PCF8583
////////////// Fija fecha y hora iniciales
////////////// y visualiza en el LCD cada segundo (aproximadamente)
#include "18F4520.H"
#device ADC=10
#fuses HS, NOWDT, WDT2048, NOPROTECT, BROWNOUT, PUT, NOLVP, NOXINST
#use delay(clock=8000000, restart_wdt)
#include <ctype.h>
#include "PCF8583.c"
#include "LCDeasy.c"
#use i2c(master,sda=PIN_C4, scl=PIN_C3, force_Hw)
#include "2432.c"
#include "FLOATEE.C" 
#use fast_io(B)

//=================================

int16 direccion=0;

void graba_int(int dato){
      
   WRITE_EXT_EEPROM(0x0FFF&direccion, dato);
   if (direccion++==4096) direccion=0;
   delay_ms(10);
}


void graba_float(float dato){
      
   WRITE_FLOAT_EXT_EEPROM(0x0FFF&direccion, dato);
   if (direccion+4==4096) direccion=0;
   delay_ms(10);
}


void main()
{
   float analog1, analog2; // para resultados de conversiones A / D,
   
   setup_adc_ports (AN0_TO_AN3); //RA0 a RA3 entradas analógicas (ver 18F4520.h)
   setup_adc (adc_clock_div_8);  //Ajusta tiempo de conversión de cada bit a 1us,
                                  //como múltiplo del periodo de reloj del PIC (ver datasheet del PIC)
   CHAR weekday[10];
   date_time_t dt; //////// El tipo de estructura date_time_t
                           // está definido en PCF8583.c
   PCF8583_init (); ////////////////-----------------INICIALIZACIÓN
   dt.month = 12; // December
   dt.day = 31; // 31
   dt.year = 14; // 2014
   dt.hours = 23; // 23 hours (11pm in 24 - hour time)
   dt.minutes = 59; // 59 minutes
   dt.seconds = 50; // 50 seconds
   dt.weekday = 0; // 0 = Sunday, 1 = Monday, etc.
   PCF8583_set_datetime (&dt); ////------------Puesta en fecha - hora
   lcd_init ();
   lcd_send_byte (0, 1); //Borra LCD
   
   WHILE (TRUE)
   {
      delay_ms (1000);
      lcd_send_byte (0, 2) ;
      PCF8583_read_datetime (&dt); ////-------------Lectura de fecha y hora del RTC
      strcpy (weekday, weekday_names[dt.weekday]); // ptr = strncpy (s1, s2, n)
      // Copy up to n characters s2 - > s1
      /*setup_wdt (wdt_on) ;
      sleep () ;
      setup_wdt (wdt_off) ;*/

      printf (lcd_putc, " %s, %2u / %2u / %2u \nHora: %u: %2u: %2u ",weekday, dt.day, dt.month, dt.year, dt.hours, dt.minutes, dt.seconds);
      
      delay_ms (1000);
      lcd_send_byte (0, 1);
      set_adc_channel (2); //Selección del canal 2 (pin RA2)
      delay_us (10); //retardo añadido para muestreo del canal
      //para carga del condensador de 'hold'
      analog1 = read_adc (); //Inicia la conversión y devuelve el resultado
      set_adc_channel (3); //Selección del canal 3 (pin RA3)
      delay_us (10);
      analog2 = read_adc (); //Inicia la conversión y devuelve el resultado
      
      analog1 = ( (analog1 * 5) / 1023) ;
      analog2 = ( (analog2 * 5) / 1023) ;
      
      printf (lcd_putc, "ANALOG1: %.2f \nANALOG2: %.2f ", analog1, analog2);
      
      graba_int(dt.hours);
      graba_int(dt.minutes);
      graba_int(dt.seconds);
      graba_int(dt.day);
      graba_int(dt.month);
      graba_int(dt.year);
      graba_float(analog1);
      graba_float(analog2);
      
   }
}

