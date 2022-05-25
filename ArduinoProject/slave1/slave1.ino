//#include <Wire.h>
//#define LED_PIN 13
//
//int x;
//
//char data[] = {'0','1','2','3','4','5'};
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Wire.begin(1); 
//  Wire.onReceive(receiveEvent);
//  Wire.onRequest(requestEvent);
//  pinMode(LED_PIN,OUTPUT);
//  digitalWrite(LED_PIN,LOW);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////  if (x == 'a')
////    digitalWrite(LED_PIN,HIGH);
////  else if (x == 'b')
////    digitalWrite(LED_PIN,LOW);
//   delay(100);
//}
//
////----------------------------------------------------------------
//void receiveEvent(int howMany)
//{
//  x = Wire.read();
//}
//void requestEvent()
//{
//  Wire.write(data, sizeof data);  
//}


#include <Wire.h>

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
