#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "bfs.h"

//Connections:
LiquidCrystal lcd(PB12, PB13, PB14, PA8, PA11, PA12);
uint8_t dirPin(PB11), stepperPin(PB10), pump(PB0), sw1(PA7), sw2(PA6), sw3(PA5),
        buzzer(PA4);

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


  digitalWrite(pump, HIGH);         //Turns pump off
  delay(500);
  digitalWrite(buzzer, LOW);


  //Print startup message.
  lcd.begin(16, 2);
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
