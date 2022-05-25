#include <18f4520.h>
#device ADC = 10
#fuses nomclr,hs
#use delay(clock=20M)
#define switch_mode pin_a1
#define button pin_a2
const unsigned char led_number[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned int16 adc_result, lux;
int times, thousands, hundreds, tens, units;
int1 status = 0;

#int_ad
void interrupt_adc()
{
   times++;
   adc_result = adc_result + read_adc(adc_read_only);
}

void decode()
{
   thousands = led_number[lux/1000];
   hundreds  = led_number[(lux%1000)/100];
   tens      = led_number[(lux%100)/10];
   units     = led_number[lux%10];
   if (thousands == 0xC0) thousands = 0xff;
   if (lux<100) hundreds = 0xff;
   if (lux<10) tens = 0xff;
}

void display_lux()
{
   output_b(thousands); output_high(pin_d0); delay_ms(1); output_low(pin_d0);
   output_b(hundreds);  output_high(pin_d1); delay_ms(1); output_low(pin_d1);
   output_b(tens);      output_high(pin_d2); delay_ms(1); output_low(pin_d2);
   output_b(units);     output_high(pin_d3); delay_ms(1); output_low(pin_d3);
}

void display_on_off()
{
  output_bit(pin_d4, 0); // turn off all of led indicator
  output_bit(pin_d5, 0);
  output_bit(pin_d6, 0);
 if (status) //on
 {
   output_bit(pin_d7, 1);
   output_b(0xC0);  output_high(pin_d2); delay_ms(1); output_low(pin_d2);
   output_b(0xC8);  output_high(pin_d3); delay_ms(1); output_low(pin_d3);
 }
 else       //off
 {
   output_bit(pin_d7, 0); 
   output_b(0xC0);  output_high(pin_d1); delay_ms(1); output_low(pin_d1);
   output_b(0x8E);  output_high(pin_d2); delay_ms(1); output_low(pin_d2);
   output_b(0x8E);  output_high(pin_d3); delay_ms(1); output_low(pin_d3);
 }
}

void led_indicator()
{
   if (lux<50) //dark
   {
      output_bit(pin_d4, 1);
      output_bit(pin_d5, 0);
      output_bit(pin_d6, 0);
      output_bit(pin_d7, 1);
   }
   else if ((lux>=50) && (lux<200)) // medium
   {
      output_bit(pin_d4, 0);
      output_bit(pin_d5, 1);
      output_bit(pin_d6, 0); 
      output_bit(pin_d7, 1);
   }
    else if (lux>=200) // light
   {
      output_bit(pin_d4, 0);
      output_bit(pin_d5, 0);
      output_bit(pin_d6, 1);
      output_bit(pin_d7, 0);
   }
}

void main()
{
  set_tris_a(0x0f); set_tris_b(0x00); set_tris_d(0x00);
  setup_adc(adc_clock_div_2); setup_adc_ports(AN0); set_adc_channel(0);
  enable_interrupts(global); enable_interrupts(int_ad);
  times = 0;
  while(1)
  {
  if (input(switch_mode)) //auto
      {
      
         if (times<50)
         {
            display_lux();
            read_adc(adc_start_only);
         }
         else
         { 
            times = 0;
            adc_result = adc_result/50;
            lux = 500/((adc_result*48.88)/(5000-adc_result*4.88));
            decode();
            adc_result = 0;
         }
         led_indicator();
      }
   else  //manual
   {
      if (input(button)==0)
      {
         delay_ms(10);
         while (input(button)==0){}
         status = ~status ;
      }
      display_on_off();
   }  
  }
}
