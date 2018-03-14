////////////// Programa básico del chip de memoria EEPROM 24C32 
////////////// Escribe y lee 10 bytes consecutivos en la EEPROM.
////////////// visualizando en la pantalla LCD 16x2

#include "18F4520.H"
#fuses HS, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP, NOXINST
#use delay(clock=8000000, restart_wdt)
#include "LCDeasy.c"
#use i2c(master,sda=PIN_C4, scl=PIN_C3, force_Hw)
#include "2432.c"

//=================================
void main()
{
int8 valor=0, dato;
int16 direccion, direccion_inicial=0;    //direccionamiento de posiciones de memoria entre 0 a 4095

lcd_init();

   for(direccion=0; direccion <= 9; direccion++) {
      WRITE_EXT_EEPROM(0x0FFF&direccion, valor); //AND con 0FFF para limitar a 4095
      lcd_gotoxy(1,1);
      printf(lcd_putc, "Escribe: %4u", valor);
      delay_ms(500);
      valor++;
   }

   for(direccion=0; direccion <= 9; direccion++) {
      dato=READ_EXT_EEPROM(0x0FFF&direccion);
      lcd_gotoxy(1,2);
      printf(lcd_putc, "Lee: %4u", dato);
      delay_ms(500);
   }
}
