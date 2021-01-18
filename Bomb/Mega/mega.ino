#include <Keypad.h>

const byte passwordLength = 7;
byte index = 0;
char password[passwordLength];
char input[passwordLength];
bool defused = 1;
int startTime;
int endTime;
int timeOut = 40;
byte stat = 0;

const byte ROWS = 4; //four rows
const byte COLS = 3; //four columns
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {34, 32, 30, 28}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 24, 22}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);    //Beep + Led + "Bomb has been planted"
  Serial2.begin(9600);    //LCD
  Serial3.begin(9600);    //CT / T Wins
}



void loop() {
  // put your main code here, to run repeatedly:
  while (index < passwordLength){
    bool gotkey = 0;
    char customKey;
    while (!gotkey)
    {
      customKey = customKeypad.getKey();
      if (customKey >= '0' && customKey <= '9') gotkey = 1;
    }
    Serial.println(customKey);
    password[index++] = customKey;
    Serial2.print(customKey);
  }

  Serial2.print('p'); //indicating plant mode
  while (Serial2.available())
  {
    if (Serial2.read() == 'o') break;
  }
  
  startTime = millis() / 1000;
  endTime = startTime + timeOut;
  
  while (defused && (millis() / 1000 < endTime)){
    defused = 1;
    while (index < passwordLength && (millis() / 1000 < endTime)){
      char customKey = customKeypad.getKey();
      Serial.println(customKey);
      input[index++] = customKey;
      Serial2.print(customKey);
    }
    for (int i = 0; i < 8; i++) if (password[i] != input[i]) defused = 0;
    Serial.print('z');
  }

  if (defused){
    Serial2.print('s');   //Success, LCD print "Defused"
  while (Serial2.available()){
    if (Serial2.read() == 'o') break;
    } 
    Serial3.print('c');   //"CT wins"
  }
  else {
    Serial2.print('f');   //Fail, LCD print "Bomb exploded"
    while (Serial2.available()){
      if (Serial2.read() == 'o') break;
    } 
    Serial3.print('t');   //"T wins"
  }

  delay(15000);
}
