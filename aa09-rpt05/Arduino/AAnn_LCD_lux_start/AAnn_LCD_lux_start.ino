/*
 빛 입력 LCD 모니터링 및 제어
*/
 // LCD 라리브러리 설정
#include <LiquidCrystal_I2C.h>
#include<Wire.h>
// LCD 설정
LiquidCrystal_I2C lcd(0x3F,16,2); // 0x3F, 0x27

// 0번 아날로그핀을 CdS 셀 입력으로 설정한다.
const int CdSPin = 0;    // CdS => A0
const int ledPin = 13;   // LED pin => D13

// LED OFF above threshold
int threshold = 0;

void setup() { 
  pinMode(ledPin, OUTPUT);
// 16X2 LCD 모듈 설정하고 백라이트를 켠다.
  lcd.init();
  lcd.backlight();
// 모든 메세지를 삭체한 뒤
// 숫자를 제외한 부분들을 미리 출력시킨다.
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("AA00,ADC: ");
  lcd.setCursor(0,1);
  lcd.print("Light:  ");
  lcd.setCursor(13,1);
  lcd.print("lux");  // 
}

void loop(){
  int adcValue; // 실제 센서로부터 읽은 값 (0~1023)
  int illuminance; // 현재의 밝기. 0~100%
  int lux;         // 현재의 밝기. lux
    
  // CdS cell을 통하여 입력되는 전압을 읽는다.
  adcValue = analogRead(CdSPin);
  // luminosity() 함수를 이용해서 Lux 를 계산한다.
  lux = int(luminosity(adcValue));  

  // 전에 표시했던 내용을 지운다.  
  lcd.setCursor(12,0);
  lcd.print("    "); 
  // ADC 값을 표시한다  
  lcd.setCursor(12,0);
  lcd.print(adcValue);
  // 전에 표시했던 내용을 지운다.
  lcd.setCursor(9,1);  
  lcd.print("   ");
  // 밝기를 표시한다  
  lcd.setCursor(9,1);  
  lcd.print(lux);   

// On/Off LED by threshold)


    
  delay(1000);
}

//Voltage to Lux
double luminosity (int RawADC0){
  double Vout=RawADC0*5.0/1023;  // 5/1023 (Vin = 5 V)
  double lux=(2500/Vout-500)/10;  
  // lux = 500 / Rldr, Vout = Ildr*Rldr = (5/(10 + Rldr))*Rldr
  return lux;
}
