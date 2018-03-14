/*
  Generación de señal sinusoidal mediante DAC_8 en puerto C

*/

#include "18F4520.H"
#device ADC=10

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
setup_adc_ports(AN0_TO_AN3);   //RA0 a RA3 entradas analógicas (ver 18F4520.h)
setup_adc(adc_clock_div_8);   //Ajusta tiempo de conversión de cada bit
set_adc_channel(2);           //Selección del canal 2 (pin RA2)
delay_us(10);    //para muestreo de la entrada analógica

while(TRUE)
  {
   output_c(SINE_WAVE[sine_index]);//salida a DAC_8 conectado en puerto C
   if(++sine_index==200)
   sine_index=0;
   delay_us(1000+read_adc());//retardo variable con el potenciómetro
                             //entre 1 y 2ms (aprox)
   }

}

