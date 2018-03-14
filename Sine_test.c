/*
  Generación de señal sinusoidal
 Programa de prueba del convertidor DAC de 12 bits: MCP9421
 Se emplea el módulo SPI del PIC
 El DAC está conectado al puerto C con la configuración:
         SDI: RC5/SDO  del PIC
         SCK: RC3/SCK/SCL
         CS#: RC0   --Chip Select: Debe mantenerse a cero durante la escritura
         LDAC# = 0  --Por tanto la transferencia del dato a los registros
                        se produce con el flanco de salida de CS#
*/

#include "18F4520.H"
#fuses HS, NOWDT
#use delay(clock=8000000, restart_wdt)


BYTE CONST SINE_WAVE[200] = {
128,132,136,139,143,147,150,154,158,161,165,169,172,176,179,
182,186,189,192,195,199,202,204,207,210,213,215,218,220,223,
225,227,229,231,233,235,237,238,240,241,242,243,244,245,246,
247,247,247,248,248,248,248,248,247,247,247,246,245,244,243,
242,241,240,238,237,235,233,231,229,227,225,223,220,218,215,
213,210,207,204,202,199,195,192,189,186,182,179,176,172,169,
165,161,158,154,150,147,143,139,136,132,128,124,120,117,113,
109,106,102,98,95,91,87,84,80,77,74,70,67,64,61,57,54,52,49,
46,43,41,38,36,33,31,29,27,25,23,21,19,18,16,15,14,13,12,11,
10,9,9,9,8,8,8,8,8,9,9,9,10,11,12,13,14,15,16,18,19,21,23,
25,27,29,31,33,36,38,41,43,46,49,52,54,57,61,64,67,70,74,77,
80,84,87,91,95,98,102,106,109,113,117,120,124};

BYTE sine_index=0;

//=================================
void main()
{

int8 salida_H, salida_L; // salida de datos al DAC (byte a byte)
int16 sine_wave_12; // para ampliar a 12 bits los valores de la tabla

setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_XMIT_L_TO_H | SPI_CLK_DIV_4);
output_high(PIN_C0); //Inicia en alta la señal chip-select de DAC


while(TRUE)
  {
   
   sine_wave_12=SINE_WAVE[sine_index];
   sine_wave_12= sine_wave_12<<4;//para ampliar al rango dinámico de salida del convertidor, 
                                 //con los cuatro bits menos significativos a 0
   salida_L= sine_wave_12;//parte baja del valor de 12 bits
   salida_H=((sine_wave_12>>8)|0x30); //4 bits de control y los 4 MSb del dato 
   output_low(Pin_C0);
   spi_write(salida_H);
   spi_write(salida_L);
   output_high(Pin_C0);
   
  sine_index+=1;
   if(sine_index >=200)
      sine_index=0;
   delay_ms(1);

   }

}

