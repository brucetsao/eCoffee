#include <Wire.h>
#include <LiquidCrystal_I2C.h>


/*-----( Declare objects )-----*/  
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  lcd.begin (16,2);  // initialize the lcd 
// Switch on the backlight
  lcd.backlight();  //Backlight ON if under program control
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Hello, world!");
}// END Setup

static int count=0;
void loop()   
{
  lcd.setCursor(0,1);
  lcd.print("Realtek: ");
  lcd.print(count++) ;
  delay(1000);
} // END Loop

