///////Conversi�n A/D,
///////visualiza en el LCD los valores captados de las entradas anal�gicas AN2 y AN3.

#include "18F4520.H"
#device ADC=10

#fuses HS, NOWDT
#use delay(clock=8000000, restart_wdt)

#include "LCDeasy.c"  //funcines para el LCD


//=================================
void main()
{

float analog1, analog2; // para resultados de conversiones A/D, 
                      
setup_adc_ports(AN0_TO_AN3);   //RA0 a RA3 entradas anal�gicas (ver 18F4520.h)
setup_adc(adc_clock_div_8);   //Ajusta tiempo de conversi�n de cada bit a 1us,
                              //como m�ltiplo del periodo de reloj del PIC (ver datasheet del PIC)
   lcd_init();
   lcd_send_byte(0, 1); //Borra LCD
  
while(TRUE)
  {
  lcd_send_byte(0, 1);
  set_adc_channel(2);      //Selecci�n del canal 2 (pin RA2)
  delay_us(10);            //retardo a�adido para muestreo del canal
                           //para carga del condensador de 'hold' 
  analog1=read_adc();   //Inicia la conversi�n y devuelve el resultado
  set_adc_channel(3);//Selecci�n del canal 3 (pin RA3)
  delay_us(10);
  analog2=read_adc();   //Inicia la conversi�n y devuelve el resultado
  
  analog1=(analog1*5)/1023;
  analog2=(analog2*5)/1023;
 
  printf(lcd_putc, "ANALOG1: %.2f  \nANALOG2: %.2f  ",analog1, analog2);
  delay_ms(1000);
 
   }
}

//Cuando ponemos la declaraci�n ADC=10 debemos dividir el analog entre 1023 debido
//a que nuestra resoluci�n llega hasta 1023 no hasta 255. Por �ltimo, colocamos 
// %.2f para poder tomar dos decimales de precisi�n.

