#include <max6675.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display

// #include <LiquidCrystal_I2C.h>
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // 設定 LCD I2C 位址
int count = 0, sec = 0;
float ini_temp, temp = 0, scale = 0, target;
char st[20];
// ThermoCouple
int thermo_vcc_pin = 13;
int thermo_so_pin = 10;
int thermo_cs_pin = 11;
int thermo_sck_pin = 12;

MAX6675 thermocouple(thermo_sck_pin, thermo_cs_pin, thermo_so_pin);

String value;
void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // 設定游標位置在第一行行首
  // Debug console
  Serial.begin(9600);
  Serial.println("start");

  //ThermoCouple
  pinMode(thermo_vcc_pin, OUTPUT);
  digitalWrite(thermo_vcc_pin, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  delay(1000);

  ini_temp = thermocouple.readCelsius();
  lcd.setCursor(0, 1); // 設定游標位置在第一行行首
  value = String("") + "initial=" + ini_temp;
  lcd.print(value);
  scale = (150 - ini_temp) / 480;
  target = ini_temp;
  Serial.println(value);
  Serial.println(scale);
  Serial.println(target);
  delay(1000);
  digitalWrite(8, HIGH);
}

void loop()
{
  delay(250);
  temp = temp + thermocouple.readCelsius();

  count++;
  if (count == 4)
  {
    sec++;
    // temp=thermocouple.readCelsius();
    target = target + scale;
    value = String("") + "time=" + sec + "" + (int)target;
    lcd.clear();
    lcd.setCursor(0, 0); // 設定游標位置在第一行行首
    lcd.print(value);
    Serial.println(value);

    temp = temp / 4;
    value = String("") + "temp=" + temp;
    Serial.println(value);
    lcd.setCursor(0, 1); // 設定游標位置在第一行行首
    lcd.print(value);
    count = 0;
    if (sec < 840)
    {
      if (temp > target)
        digitalWrite(8, LOW);
      else
        digitalWrite(8, HIGH);
    }
    if (sec == 480)
      scale = (220.0 - 150.0) / 360;
    if (sec > 840)
    {

      if (temp > 220)

        digitalWrite(8, LOW);

      if (temp < 210)

        digitalWrite(8, HIGH);

    }
    temp = 0;
  }

}
