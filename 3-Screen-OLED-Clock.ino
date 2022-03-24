#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Time.h>
#include <DS1307RTC.h>
Adafruit_SSD1306 display(128, 64, &Wire, 4);
const int buttonPinDate = 2;
int buttonStateDate = 0;

void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);
  Wire.write(1 << bus);
  Wire.endTransmission();
}

void setup() {

  TCA9548A(2);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay(); 
  
  TCA9548A(3);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  TCA9548A(4);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  
    buttonStateDate = digitalRead(buttonPinDate);
  
    TCA9548A(2);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(45,0); display.print("Hour");
    tmElements_t tm;
    if(RTC.read(tm)){
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(40,25);
    if (tm.Hour >= 0 && tm.Hour < 10) {
    display.write('0');}
    display.print(tm.Hour);
    display.display();
    }
  
    TCA9548A(3);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(30,0); display.print("Minute");
    if(RTC.read(tm)){
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(40,25);
    if (tm.Minute >= 0 && tm.Minute < 10) {
    display.write('0');}
    display.print(tm.Minute);
    display.display();
    }

    TCA9548A(4);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(30,0); display.print("Second");    
    if(RTC.read(tm)){
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(40,25);
    if (tm.Second >= 0 && tm.Second < 10) {
    display.write('0');}
    display.print(tm.Second);
    display.display();
    }

    if (buttonStateDate == HIGH) {

    TCA9548A(2);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(40,0); display.print("Month");
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(40,25);
    if (tm.Month >= 0 && tm.Month < 10) {
    display.write('0');}
    display.print(tm.Month);
    display.display();

    TCA9548A(3);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(50,0); display.print("Day");
    display.setTextSize(5);
    display.setTextColor(WHITE);
    display.setCursor(40,25);
    if (tm.Day >= 0 && tm.Day < 10) {
    display.write('0');}
    display.print(tm.Day);
    display.display();

    TCA9548A(4);
    display.setTextColor(WHITE); display.clearDisplay();
    display.setTextSize(2); display.setCursor(45,0); display.print("Year");    
    display.setTextSize(4);
    display.setTextColor(WHITE);
    display.setCursor(20,25);
    display.print(tmYearToCalendar(tm.Year));
    display.display();
    delay(3000);
          
    }

}
