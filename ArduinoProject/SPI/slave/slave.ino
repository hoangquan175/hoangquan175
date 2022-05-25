 #include <SPI.h>
 #include "DHT.h"
 
 volatile boolean process_it;
 volatile byte Svalreceived,Svalsent;
 long jj=0,temp = 0,hum=0,sta_motor =0;;
 long last_sta_motor = 0;
 long last_hum = 0;
 long last_temp = 0;
 const int DHTPIN = A0;
 const int DHTTYPE = DHT11;

 DHT dht(DHTPIN,DHTTYPE);


 
 void setup(void){
  
  Serial.begin(115200);
  dht.begin();
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  process_it = false;
  SPI.attachInterrupt();

  }



 ISR (SPI_STC_vect)
 {
  Svalreceived = SPDR;
  process_it = true;
  }





  
 void loop(void){
  temp = int(dht.readTemperature());
  hum = int(dht.readHumidity());
  sta_motor = random(0,2);
  
  
  if(process_it)
  {
    if (Svalreceived == 0){
      SPDR = last_temp;
      }
    if (Svalreceived == 1){
      SPDR = last_hum;
      }
    if (Svalreceived == 2){
      SPDR = last_sta_motor;
      }
    jj++;
    Serial.println(Svalreceived);
    Serial.print(last_temp);
    Serial.print(',');
    Serial.print(last_hum);
    Serial.print(',');
    Serial.print(last_sta_motor);
    Serial.println();
    if (jj>3) {
      last_temp = temp;
      last_hum = hum;
      last_sta_motor = sta_motor;
      jj=0;
      }
    process_it = false;
    }
  }
