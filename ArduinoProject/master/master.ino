//#include <Wire.h>
//#include <LiquidCrystal.h>
//
//
//byte data[6];
//byte i ;
//char num = 6;
//LiquidCrystal lcd(12,11,5,4,3,2);
//
//void setup() {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  Wire.begin();
//  pinMode(A0, INPUT_PULLUP);
//  lcd.begin(16,2);
//}
//
//void loop() {
//  // put your main code here, to run repeatedly:
////  if(digitalRead(A0) == 0)
////  {
////    Wire.beginTransmission(1);
////    Wire.write('b');
////    Wire.endTransmission();
////    Wire.beginTransmission(2);
////    Wire.write('b');
////    Wire.endTransmission();
////  }
////  else
////  {
////    Wire.beginTransmission(1);
////    Wire.write('a');
////    Wire.endTransmission();
////    Wire.beginTransmission(2);
////    Wire.write('a');
////    Wire.endTransmission();
////  }
//  
//  String response = "";
//  int count = 0 ;
//  if (Wire.requestFrom (1,num)) {
//      for (byte b = 0; b<10;b++){
//        data[b] = Wire.read();
//        }
//  }else
//  {
//    count= count ++;
//    }
//  lcd.print(data[0]);
//  lcd.setCursor(1,1);
//  lcd.print(count);
//  delay(500);
//  lcd.clear();
//}
//
//


#include <Wire.h>

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.println(c);         // print the character
  }

  delay(500);
}








//
///*
//  I2C Master Demo
//  i2c-master-demo.ino
//  Demonstrate use of I2C bus
//  Master sends character and gets reply from Slave
//  DroneBot Workshop 2019
//  https://dronebotworkshop.com
//*/
//
//// Include Arduino Wire library for I2C
//#include <Wire.h>
//#include <LiquidCrystal.h>
//
//LiquidCrystal lcd(12,11,5,4,3,2);
//
//// Define Slave I2C Address
//#define SLAVE_ADDR 9
//
//// Define Slave answer size
//#define ANSWERSIZE 5
//
//void setup() {
//
//  // Initialize I2C communications as Master
//  Wire.begin();
//  lcd.begin(16,2);
//}
//
//void loop() {
//  delay(50);
//
//  Wire.requestFrom(SLAVE_ADDR,ANSWERSIZE,false);
//  
//  // Add characters to string
//  String response = "";
//  while (Wire.available()) {
//      char b = Wire.read();
//      response += b ;
//  } 
//  lcd.print(response);
//  delay(500);
//  lcd.clear();
//}
