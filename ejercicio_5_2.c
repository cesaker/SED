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
#include <math.h>

float contador=0;

void main()
{

int8 salida_H, salida_L; // salida de datos al DAC (byte a byte)
int16 sine_wave_12; // para ampliar a 12 bits los valores de la tabla

setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_XMIT_L_TO_H | SPI_CLK_DIV_4);
output_high(PIN_C0); //Inicia en alta la señal chip-select de DAC


while(TRUE)
  {
   
   sine_wave_12=(sin(contador)+1)*127;
   sine_wave_12= sine_wave_12<<4;//para ampliar al rango dinámico de salida del convertidor, 
                                 //con los cuatro bits menos significativos a 0
   salida_L= sine_wave_12;//parte baja del valor de 12 bits
   salida_H=((sine_wave_12>>8)|0x30); //4 bits de control y los 4 MSb del dato 
   output_low(Pin_C0);
   spi_write(salida_H);
   spi_write(salida_L);
   output_high(Pin_C0);
   
   delay_ms(1);
   contador+=0.1;
   
   if (contador>=2*pi)
      contador=0;

   }

}

//Lo único que tenemos que hacer en este apartado es conseguir que se cree una 
//onda sinusoidal utilizando la librería math.h y la función sin(). Lo que hemos
//hecho ha sido ir tomando valores del seno hasta que el incremento del valor
//del contador alcance 2*pi, en cuyo caso sabemos que habrá dado una vuelta entera 
//y volverá a empezar de nuevo.

//En cuanto a comparación con respecto a tomar los datos de la tabla he de decir
//que en este caso la onda sale más pixelada, es decir, se toman menos valores y
//por lo tanto no es tan precisa como coger los valores de la tabla. Por otro
//lado he de decir que en mi caso la carga de la cpu con este programa es mucho
//menor que usando el programa con la tabla.
