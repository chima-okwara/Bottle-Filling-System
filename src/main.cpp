#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "bfs.h"

void setup(void);
void loop(void);

//Connections:
LiquidCrystal_I2C lcd (0x27, 16, 2);
uint8_t dirPin(12), stepperPin(11), pump(10), sw1(10), sw2(9), sw3(8),
        buzzer(13);

//Variables:
uint8_t bottleNo (1);
bool start (false);

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);


  digitalWrite(pump, LOW);         //Turns pump off
  delay(500);
  digitalWrite(buzzer, LOW);


  //Print startup message.
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("      UER       ");
  delay(300);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automatic Bottle");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("Filling System");
  lcd.blink();
  delay(500);
  lcd.clear();
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("Press 'Start' to");
  lcd.setCursor(0, 1);
  lcd.print("fill bottles...");


  lcd.cursor();

  while(!start)
    start = (!digitalRead(sw1) ? true : false );

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  lcd.noCursor();

  lcd.clear();
  delay(1000);
  start = false;

  while(!start)
    getNoBottles();

  delay(1000);
  fillBottles(bottleNo);
  start = false;
}
