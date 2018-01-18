#include <Keypad.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
double first = 0;
double second = 0;
double total = 0;

char customKey;
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {0, 1, 6, 7}; 
byte colPins[COLS] = {8, 9, 10, 13};


Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup(){
lcd.begin(16,2);
lcd.print("Start");
delay(1000);
lcd.clear();
}
void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey) 
  {
  case '0' ... '9': 
    lcd.setCursor(1,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    break;

  case '+':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("+");
    second = SecondNumber(); 
    total = first+second;
      lcd.setCursor(9,2);
    lcd.print("=");
    lcd.setCursor(10,2);
    lcd.print(total);
    first = 0, second = 0; 
    break;

  case '-':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("-");
    second = SecondNumber();
    total = first-second;
    lcd.setCursor(9,2);
    lcd.print("=");
    lcd.setCursor(10,2);
    lcd.print(total);
    first = 0, second = 0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    lcd.setCursor(1,1);
    lcd.print("*");
    second = SecondNumber();
    total = first*second;
    lcd.setCursor(4,2);
    lcd.print("=");
    lcd.setCursor(5,2);
    lcd.print(total);
    first = 0, second = 0;
    break;


case '/':
    first = (total != 0 ? total : first);
    lcd.setCursor(2,1);
    lcd.print("/");
    second = SecondNumber();
    if(second==0)
    {lcd.print("INVALID");
    break;}
    total = first/second;
    lcd.setCursor(7,2);
    lcd.print("=");
    lcd.setCursor(8,2);
    lcd.print(total);
    first = 0, second = 0;
    break;
    
  case 'C':
    total = 0;
    lcd.clear();
    break;
  }
}

long SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
    if(customKey >= '0' && customKey <= '9')
    {
      second = second * 10 + (customKey - '0');
      lcd.setCursor(1,2);
      lcd.print(second);
    }

    if(customKey == '=') break; 
  }
 return second; 
}
