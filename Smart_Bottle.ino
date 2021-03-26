#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

char *ssid="Sanjeev";
char *pwd="dumbeldore";


LiquidCrystal_I2C lcd(0x27,16,2);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");

int sw = D6;
int i=0;

String weekDays[7]={"Sunday","Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};                                            //Days of the week
String months[12]={"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; // Months of the year
String currentTime;

void calcDateTime(){                                       //Calculating Date and Time from NTP Server
  timeClient.update();

  unsigned long epochTime = timeClient.getEpochTime();
 
  currentTime = timeClient.getFormattedTime();
  Serial.println("\nCurrent time is : ");
  Serial.print(currentTime);
  lcd.print("Time : ");
  lcd.print(currentTime);
  delay(5000);
  lcd.clear();

  String weekDay = weekDays[timeClient.getDay()];
  Serial.println("\nDay :   ");
  Serial.print(weekDay);

  struct tm *ptm = gmtime ((time_t *)&epochTime);

  int monthDay = ptm->tm_mday;
  int currentMonth = ptm->tm_mon+1;
  String currentMonthName = months[currentMonth-1];
  int currentYear = ptm->tm_year+1900;
  Serial.println("\nMonth:   ");
  Serial.print(currentMonthName);
  lcd.print("Month: ");
  lcd.print(currentMonthName);
  delay(1000);
  lcd.clear();

  String currentDate = String(monthDay) + "/" + String(currentMonth) + "/" + String(currentYear);
  Serial.println("\nDate:   ");
  Serial.print(currentDate);
  lcd.print("Date : ");
  lcd.print(currentDate);
  delay(1000);
  lcd.clear();


  Serial.println("\n\n");
  delay(2000);
 }


void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to WiFi : ");
  Serial.print(ssid);
  WiFi.begin(ssid,pwd);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi ");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();
  timeClient.setTimeOffset(19800);
  calcDateTime();
 
  String eepromTime=currentTime;
  EEPROM.put(i,eepromTime);
  Serial.println("Current time is : ");
  Serial.print(eepromTime);
 
  Wire.begin();
  lcd.begin();
  lcd.backlight();
 
  pinMode(sw,INPUT);
}

void loop() {
  int val = digitalRead(sw);
  calcDateTime();
  if (val==HIGH){
     String serverTime=EEPROM.put(i,currentTime);
      //send this value of servertime to server
     Serial.println("Updated time is : ");
     Serial.print(serverTime);
     lcd.print("Updated time :  ");
     lcd.print(serverTime);
     delay(1000);
     lcd.clear();
  }
 
}
