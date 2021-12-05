#include "DHT.h"
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#define PWM 9
byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.createChar(1,degree);
  lcd.clear();
  lcd.print("   Fan Speed  ");
 lcd.setCursor(0,1);
 lcd.print("  Controlling ");
 
 analogWrite(PWM, 255);
 delay(5000);
 
 
  Serial.begin(9600); 
  Serial.println("Temperature controlled fan ");
  dht.begin();
}  


void loop() {
  // put your main code here, to run repeatedly:
float h=dht.readHumidity();
float t=dht.readTemperature();
float f=dht.readTemperature(true);
  if(isnan(h)||isnan(t)||isnan(f)){
    Serial.println(F("Failed to read"));
    return;
    }
Serial.print(F(" Humidity: "));
Serial.print(h);
Serial.println(F("%  Temperature: "));
Serial.print(t);
Serial.println(F("°C "));
Serial.print(f);
Serial.println(F("°F "));
lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(t);  
  lcd.write(1);
  lcd.print(" C");
  lcd.setCursor(0,1);
   if(t <26)
    { 
      analogWrite(PWM,0);
      lcd.print("Fan OFF            ");
      delay(100);
    }
    
    else if(t<26.5)
    {             
      analogWrite(PWM, 64);
      lcd.print("Fan Speed: 25%   ");
      delay(100);
    }
    
     else if(t<27)
    {
      analogWrite(PWM, 128);
      lcd.print("Fan Speed: 50%   ");
      delay(100);
    }
    
     else if(t<27.5)
    {
      analogWrite(PWM, 192);
      lcd.print("Fan Speed: 75%   ");
      delay(100);
    }
    
    else 
    {
      analogWrite(PWM, 255);
      
      lcd.print("Fan Speed: 100%    ");
      delay(100);
    }
     
  delay(3000);
}
