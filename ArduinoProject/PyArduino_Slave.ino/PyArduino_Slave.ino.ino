#include <SPI.h>
 #include "DHT.h"
 
 volatile boolean process_it;
 volatile byte Svalreceived,Svalsent;
 long jj=0,temp = 0,hum=0;
 int sta_motor = 0;
 long last_sta_motor = 0;
 long last_hum = 0;
 long last_temp = 0;
 const int DHTPIN = 2;
 const int DHTTYPE = DHT11;
boolean auto_mode = false;
 
// KHÁI BÁO DHT
 DHT dht(DHTPIN,DHTTYPE);

// KHAI BÁO BIẾN ĐIỀU KHIỂN MOTOR
  int DC = 8;

// KHAI BÁO THỜI GIAN DELAY
unsigned long time1 = 0;
 
 void setup(void){
  
  Serial.begin(115200);
  
  dht.begin();
  
  pinMode(MISO,OUTPUT);
  SPCR |= _BV(SPE);
  process_it = false;
  SPI.attachInterrupt();
  
  pinMode(DC,OUTPUT);

  }



 ISR (SPI_STC_vect)
 {
  Svalreceived = SPDR;
  process_it = true;
  }



  
 void loop(void){
  temp = int(dht.readTemperature());
  hum = int(dht.readHumidity());
  
  
  
  if(process_it and (Svalreceived != 5) and (Svalreceived != 6))
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
//    Serial.println(Svalreceived);
//    Serial.print(last_temp);
//    Serial.print(',');
//    Serial.print(last_hum);
//    Serial.print(',');
//    Serial.print(last_sta_motor);
//    Serial.println();
    if (jj>3) {
      last_temp = temp;
      last_hum = hum;
      last_sta_motor = sta_motor;
      jj=0;
      }
    process_it = false;
    }
   if (Svalreceived == 5){
    digitalWrite(DC,LOW);
    sta_motor = 0;
    auto_mode = false;
    }
    if (Svalreceived == 6){
      digitalWrite(DC,HIGH);
      sta_motor =1;
      }
    if (Svalreceived == 7){
      auto_mode = true ;
      }
    if (auto_mode){
       if (  (millis() - time1) > 3000 ){
        if (sta_motor == 1 ) {
          sta_motor = 0;
          digitalWrite(DC,LOW);
          }
        else if (sta_motor == 0 ) {
          sta_motor = 1;
          digitalWrite(DC,HIGH);
          }
        time1 = millis();
        }
      
      }
  }
