#include <LiquidCrystal_I2C.h>

unsigned long startTime;
unsigned long endTime;
unsigned long timeOut = 40000;
byte b = 0;

int index = 0;

LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set password: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(b == 0)
  {
    
    char b = Serial.read();
    if (b == 'p') break;
    else if (b >= '0' && b <= '9'){}
    else continue;
    Serial.println(b);
    lcd.setCursor(index, 1);
    lcd.print(b);
    index++;
    b = 0;
  }

  index = 0;
  delay(500);

  Serial.print('o');

  startTime = millis();
  endTime = startTime + timeOut;

  while (millis() < endTime){
    lcd.setCursor(0,0);
    lcd.print(endTime - millis());
    lcd.setCursor(0,index);
    b = Serial.read();
    if (b == 's' || b == 'c') break;
    else if (b == 'z')
    {
      lcd.clear();
    }
    lcd.print(b);
    index++;
  }

  lcd.clear();
  
  if (b == 's')
  {
    lcd.setCursor(0,0);
    lcd.print("Defused!");
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("CT wins!");
    Serial.print('o');
  }
  if (b == 'c')
  {
    lcd.setCursor(0,0);
    lcd.print("Bomb exploded!");
    delay(2000);
    lcd.setCursor(0,1);
    lcd.print("Terrorists win!");
    Serial.print('o');
  }

  delay(15000);
  lcd.clear();
}
