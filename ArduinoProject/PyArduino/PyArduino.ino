#include <DHT.h>
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <SPI.h>


//Khởi tạo với các chân
//KHAI BÁO CÁC CHÂN CỦA LCD
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

//KHAI BÁO CÁC BIẾN LƯU GIÁ TRỊ NHIỆT ĐỘ , ĐỘ ẨM, GÓI DỮ LIỆU
String TempS,HumS,DC_STA,data1;
int data3;

//KHAI BÁO CÁC CHÂN CỦA DHT
const int DHTPIN = A0;
const int DHTTYPE = DHT11;
DHT dht(DHTPIN, DHTTYPE);

// KHAI BÁO THỜI GIAN DELAY
unsigned long time1 = 0;

//KHAI BÁO CHÂN ĐIỀU KHIỂN ĐỘNG CƠ VÀ SWITCH ĐIỀU KHIỂN ĐỘNG CƠ
int SW = 9;
int DC = 8;

//KHAI BÁO BIẾN CHẾ ĐỘ MODE
int mode =0,STA_DC = 0;


byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};

void setup() {
  // CẤU HÌNH SPI
  digitalWrite(SS,HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);
 // CẤU HÌNH SERIAL
  Serial.begin(9600);
  lcd.begin(16, 2);
 // CẤU HÌNH LCD
  lcd.print("Nhiet do: ");
  lcd.setCursor(0,1);
  lcd.print("Do am: ");
  lcd.createChar(1, degree);
//CẤU HÌNH DHT
  dht.begin();
    
//CẤU HÌNH CHÂN ĐIỀU KHIỂN DC VÀ SWITCH
  pinMode(SW, INPUT);  
  pinMode(DC,OUTPUT); 
}

void loop() {
//// ĐỌC GIÁ TRỊ CỦA NHIỆT ĐỘ VÀ ĐỘ ẨM
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
  byte Mvalsent,Mvalreceived;
  byte data[10];

  digitalWrite(SS,LOW);
  for (int jj =0; jj<4;jj++){
    Mvalsent = jj;
    Mvalreceived = SPI.transfer(Mvalsent);
    data[jj]=Mvalreceived;
    delay(5);
    }
  digitalWrite(SS,HIGH);
  
// NHẬN GÓI TIN TỪ SCADA
    int data2 = Serial.readString().toInt();
    if (data2 > 0){
      data3 = data2;
      }  
  
  
  
//BẬT TẮT ĐỘNG CƠ MODE = MANUAL
//  mode = int(data3[0]);
//  if (mode == 1){
    
//  int switchStatus = digitalRead(SW);
//    if (switchStatus == HIGH){
//      digitalWrite(DC,LOW);
//      STA_DC = 0;
//      }else{
//        digitalWrite(DC,HIGH);
//        STA_DC = 1;
//        }
      if (data3 == 2){
        digitalWrite(SS,LOW);
        SPI.transfer(5);
        digitalWrite(SS,HIGH);
        STA_DC = 0;
        }
      if (data3 == 1){
        digitalWrite(SS,LOW);
        SPI.transfer(6);
        digitalWrite(SS,HIGH);
        STA_DC = 1;
        }
      if (data3 == 3){
        digitalWrite(SS,LOW);
        SPI.transfer(7);
        digitalWrite(SS,HIGH);
        STA_DC = 1;
        }
    STA_DC = data[3];
   
//XÂY DỰNG GÓI TIN SERIAL
    TempS = String(int(data[1]));
    HumS = String(int(data[2]));
    DC_STA = String(STA_DC);
    data1 = TempS +'_' + HumS+'_'+DC_STA;

//GHI LÊN LCD
    lcd.setCursor(10,0);
    lcd.print(round(data[1]));
    lcd.print(" ");
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(10,1);
    lcd.print(round(data[2]));
    lcd.print(" %");
    
  
 // GỬI GÓI TIN SAU THỜI GIAN DELAY = TIME1 
    if ( (unsigned long) (millis() - time1) > 500 )
    {
        Serial.println(data1);
        time1 = millis();
    }

  

}
