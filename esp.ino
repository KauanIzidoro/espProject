#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);
int bt_blue_NEXT = 33;
int bt_green_YES = 34;
int bt_yellow_BACK = 32;
int bt_red_CANCEL = 35;
int clicks2 = 0;
int x = 0;
int h = 0, m = 0, s = 0;
int time_setup = 1000;
int count = 0;
int layer = 0;

void setup() {
  Serial.begin(115200);
  for(int i=32;i<36;i++)
    pinMode(i,INPUT);
  LCD.init();
  LCD.backlight();
  welcome();
}
void welcome() {
  LCD.setCursor(4, 0);
  LCD.print("WELCOME!");
  delay(1000);
  LCD.clear();
  displayMenu();
  LCD.noBlink();
}
void displayMenu() {
  LCD.setCursor(0, 0);
  LCD.print("1.Count Clicks");
  LCD.setCursor(0, 1);
  LCD.print("2.Clock");
  LCD.setCursor(8, 1);
  LCD.print("3.Clear");
}
void countClick() {
  LCD.clear();
  LCD.noBlink();
  LCD.setCursor(0, 0);
  LCD.print("Count Clicks");
  LCD.setCursor(0, 1);
  while (true) {
    if (digitalRead(bt_blue_NEXT) == HIGH) {
      count++;
      LCD.setCursor(0,1);
      LCD.print("Clicks: ");
      LCD.print(count);
      delay(200);
      while (digitalRead(bt_blue_NEXT) == HIGH) {} 
    }
    if (digitalRead(bt_yellow_BACK) == HIGH) {
      count=0;
      LCD.setCursor(0, 1);
      LCD.print("Clicks: ");
      LCD.print(count);
      delay(200);
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {
      exit(0);
      LCD.clear();
      welcome();
    }
  }
}
void Clock() {
  LCD.clear();
  LCD.noBlink();
  LCD.setCursor(1, 0);
  LCD.print("Clock");
  while (true) {
    LCD.setCursor(0, 1);
    LCD.print(h < 10 ? "0" : "");
    LCD.print(h);
    LCD.print(":");
    LCD.print(m < 10 ? "0" : "");
    LCD.print(m);
    LCD.print(":");
    LCD.print(s < 10 ? "0" : "");
    LCD.print(s);
    delay(time_setup);
    s++;
    if (s == 60) {
      s = 0;
      m++;
      if (m == 60) {
        m = 0;
        h++;
        if (h == 24) {
          h = 0;
        }
      }
    }
    if (digitalRead(bt_blue_NEXT) == HIGH) {
      time_setup = 250;
    }
    if (digitalRead(bt_yellow_BACK) == HIGH) {
      time_setup = 1000;
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {
      LCD.clear();
      welcome();
      break;
    }
  }
}
void Clear() {
  LCD.clear();
  LCD.noBlink();
  LCD.setCursor(1, 0);
  LCD.print("Clear all data?");
  unsigned long startTime = millis();
  while (millis() - startTime <= 3000) {
    if (digitalRead(bt_green_YES) == HIGH) {
      LCD.clear();
      LCD.print("Dados zerados!");
      delay(1000);
      LCD.clear();
      welcome();
    }
    if (digitalRead(bt_red_CANCEL) == HIGH) {
      LCD.clear();
      welcome();
    }
  }
}
void loop() {
  while (true) {
    if (digitalRead(bt_blue_NEXT) == HIGH) {
      delay(100); 
      layer++;
      if (layer > 3) 
        layer = 1; 
      LCD.clear();
      displayMenu();
      if(layer<3){
        LCD.setCursor(0, layer - 1);
        LCD.blink(); 
      }
      if(layer==3){
        LCD.setCursor(8,1);
        LCD.blink();
      }
    } 
    else if (digitalRead(bt_green_YES) == HIGH) {
      delay(100); 
      if(layer == 1)  countClick();
      else if(layer == 2) Clock();
      else if(layer == 3) Clear();
    } 
    else if (digitalRead(bt_yellow_BACK) == HIGH) {
      LCD.clear();
      LCD.noBlink();
      welcome();
      displayMenu();
      layer = 0; 
    } 
    else if (digitalRead(bt_red_CANCEL) == HIGH) {
      delay(100);
      exit(0);
      LCD.noBlink();
      welcome();
    }
  }
}

