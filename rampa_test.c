/*Generación de señal en forma de rampa periódica.
 Programa de prueba del convertidor DAC de 12 bits: MCP9421
 Se emplea el módulo SPI del PIC
 El DAC está conectado al puerto C con la configuración:
         SDI: RC5/SDO  del PIC
         SCK: RC3/SCK/SCL
         CS#: RC0   --Chip Select: Debe mantenerse a cero durante la escritura
         LDAC# = 0  --Por tanto la transferencia del dato a los registros
                        se produce con el flanco de subida de CS#
*/

#include "18F4520.H"
#fuses HS, NOWDT, NOPROTECT, BROWNOUT, PUT, NOLVP, NOXINST
#use delay(clock=8000000, restart_wdt)


//=================================
void main()
{
int16 cuenta;
int8 salida_H, salida_L; // salida de datos al DAC (byte a byte)

setup_spi(SPI_MASTER | SPI_L_TO_H | SPI_XMIT_L_TO_H | SPI_CLK_DIV_4);
output_high(PIN_C0); //Inicia en alta la señal chip-select de DAC
cuenta =0; //vamos autilizar un contador para general la señal en forma de rampa

while(TRUE)
  {
 
   salida_L= cuenta; //para enviar el byte menos significativo del dato
   salida_H=(((0x0FFF&cuenta)>>8)|0x30); //4 bits de control y los 4 bits más 
                                        //significativos del dato
   //Secuencia de envío de los 2 bytes y activación de CS# para inciar 
   //la conversión D/A:
   output_low(Pin_C0);
   spi_write(salida_H);
   spi_write(salida_L);
   output_high(Pin_C0);
   
   delay_ms(2);
   cuenta +=1;
   if(cuenta>=4096) cuenta=0;
   
   }

}

