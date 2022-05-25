#include <SPI.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

void setup(void){
  Serial.begin(115200);
  digitalWrite(SS,HIGH);

  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  
  }
void loop(void){
  
  byte Mvalsent,Mvalreceived;
  byte data[10];

  digitalWrite(SS,LOW);
  for (int jj =0; jj<4;jj++){
    Mvalsent = jj;
    Mvalreceived = SPI.transfer(Mvalsent);
//    Serial.println("sent: ");
//    Serial.println(Mvalsent);
//    Serial.println("\t received: ");
//    Serial.println(Mvalreceived);
    data[jj]=Mvalreceived;
    delay(200);
    }
  digitalWrite(SS,HIGH);
  Serial.print("master: ");
  for (int jj =0; jj<4;jj++){
    Serial.print(data[jj]);
    Serial.print(",");
    }
  lcd.print(data[1]);
  lcd.print(',');
  lcd.print(data[2]);
  lcd.print(',');
  lcd.print(data[3]);
  Serial.println();
  delay(500);
  lcd.clear();
  }
