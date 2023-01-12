//TODO:
//*******Measure steps for motion by required distance
//*******Adjust first iteration of bottle fill routine.


#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "bfs.h"

void setup(void);
void loop(void);

//Connections:
// LiquidCrystal lcd (PB11, PB10, PB1, PB0, PA7, PA6);
LiquidCrystal lcd (PA6, PA7, PB0, PB1, PB10, PB11);

uint8_t sw1 (PA15), sw2 (PB3), sw3 (PB4);
uint8_t pump (PA11), buzzer (PA12), dirPin (PB6), stepperPin (PB5);

uint8_t ms1 (PB9), ms2 (PB8), ms3 (PB7);

//Variables:
uint8_t bottleNo (1);
bool start (false);

void setup()
{
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);

  pinMode(pump, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);

  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(ms3, OUTPUT);


  digitalWrite(dirPin, LOW);
  digitalWrite(stepperPin, LOW);

  digitalWrite(ms1, LOW);
  digitalWrite(ms2, HIGH);
  digitalWrite(ms3, LOW);



  digitalWrite(pump, LOW);

  digitalWrite(buzzer, HIGH);
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
