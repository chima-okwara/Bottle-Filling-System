#include <bfs.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Arduino.h>

void step(const uint8_t& dir, const int &steps)
{
 digitalWrite(dirPin, dir);

 for(int i = 0; i < steps; i++)
 {
   digitalWrite(stepperPin, HIGH);
   delayMicroseconds(__DELAY__);//Adjust the speed of motor. Increase the value, motor speed become slower.
   digitalWrite(stepperPin, LOW);
   delayMicroseconds(__DELAY__);
 }
}

void fillBottles(uint8_t &num)
{
  for(int i = 0; (i < num); ++i)
  {
    switch (i)
    {
    case 0:
      {
        lcd.clear();
        lcd.noCursor();
        lcd.setCursor(0, 0);
        lcd.print("Filling bottle");
        lcd.print(i + 1);
        digitalWrite(buzzer, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);

        step(back, 230);
        delay(50);

        step(front, init_steps);
        digitalWrite(pump, HIGH);
        delay(pumpDel);
        digitalWrite(pump, LOW);
        delay(trickleDel);

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bottle ");
        lcd.print(i + 1);
        lcd.print(" filled.");
        delay(1000);
        break;
      }

    case 1:
    case 2:
    case 3:
    case 5:
    {
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(0, 0);
      lcd.print("Filling bottle");
      lcd.print(i + 1);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);

      step(front, STEPS);
      digitalWrite(pump, HIGH);
      delay(pumpDel);
      digitalWrite(pump, LOW);
      delay(trickleDel);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bottle ");
      lcd.print(i + 1);
      lcd.print(" filled.");
      delay(1000);
      break;
    }

    case 4:
    {
      lcd.clear();
      lcd.noCursor();
      lcd.setCursor(0, 0);
      lcd.print("Filling bottle");
      lcd.print(i + 1);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);

      step(front, STEPS + CASE4);
      digitalWrite(pump, HIGH);
      delay(pumpDel);
      digitalWrite(pump, LOW);
      delay(trickleDel);

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Bottle ");
      lcd.print(i + 1);
      lcd.print(" filled.");
      delay(1000);
      break;
    }

  }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Done filling");
  lcd.setCursor(0, 1);
  lcd.print(num);
  lcd.print(" Bottles.");
  delay(1500);
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  lcd.clear();
  step(back, (STEPS*num) + CASE4);
  digitalWrite(pump, LOW);
  num = 1;


}
void getNoBottles()
{
  lcd.setCursor(0, 0);
  lcd.print("No of bottles:       ");
  lcd.setCursor(0, 1);
  lcd.print("Press 'Start'...");
  lcd.setCursor(14, 0);
  if(!digitalRead(sw2))
    bottleNo++;
  if(!digitalRead(sw3))
    bottleNo--;
  bottleNo = constrain(bottleNo, 1, 6);
  lcd.print(bottleNo);

  start = (!digitalRead(sw1) ? true : false );
  delay(200);
}

void getPumpLevel()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Fill Level:    ");
  lcd.setCursor(0, 1);
  lcd.print("Press 'Start'...");
  lcd.setCursor(14, 0);
  if(!digitalRead(sw2))
    level++;
  if(!digitalRead(sw3))
    level--;
  level = constrain(level, 1, 5);
  lcd.print(level);

  switch(level)
  {
    case 1:
    {
      pumpDel = MINPUMPDEL;
      break;
    }

    case 2:
    {
      pumpDel = 3500;
      break;
    }

    case 3:
    {
      pumpDel = 4500;
      break;
    }

    case 4:
    {
      pumpDel = 5500;
      break;
    }

    case 5:
    {
      pumpDel = 6500;
      break;
    }
  }

  start = (!digitalRead(sw1) ? true : false );
  delay(200);
}
