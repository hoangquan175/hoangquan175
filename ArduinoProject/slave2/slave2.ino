#include <Wire.h>
#define LED_PIN 13

int x;

char data[] = {'0','1','2','3','4','5'};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(2); 
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (x == 'b')
    digitalWrite(LED_PIN,HIGH);
  else if (x == 'a')
    digitalWrite(LED_PIN,LOW);
}

//----------------------------------------------------------------
void receiveEvent(int howMany)
{
  x = Wire.read();
}
void requestEvent()
{
  Wire.write(data);  
}
