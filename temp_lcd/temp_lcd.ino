#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 7
#define DHTTYPE DHT11
/**********************************************************/
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 20 chars and 4 line display

float humid;
float temp;
/*********************************************************/
void setup()
{
  lcd.begin(); // initialize the lcd
  lcd.backlight(); // open the backlight
  dht.begin();
  pinMode(LED_BUILTIN, OUTPUT);
}
/*********************************************************/
void loop()
{
  const char array1[] = "xenolabs    office";
  const char array2[] = "==================";

  char buffer_line1[20];
  char buffer_line2[20];

  float old_humid = humid;
  float old_temp = temp;

  humid = dht.readHumidity();
  temp = dht.readTemperature();
  delay(2000);

  char humidstr[7];
  dtostrf(humid, 4, 1, humidstr);

  char tempstr[7];
  dtostrf(temp, 4, 1, tempstr);

  snprintf(buffer_line1, sizeof(buffer_line1), "   Humid. %s%%", humidstr);
  snprintf(buffer_line2, sizeof(buffer_line2), "   Temp.  %sC", tempstr);

  if ( old_humid != humid || old_temp != temp) {
    digitalWrite(LED_BUILTIN, HIGH);
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print(array1);
    lcd.setCursor(1, 1);
    lcd.print(array2);
    lcd.setCursor(1, 2);
    lcd.print(buffer_line1);
    lcd.setCursor(1, 3);
    lcd.print(buffer_line2);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
}
/************************************************************/
