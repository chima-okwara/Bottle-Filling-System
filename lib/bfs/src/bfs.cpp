#include <bfs.h>
#include <Arduino.h>

void step(const uint8_t& dir, const int &steps)
{
 digitalWrite(dirPin, dir);

 for(int i = 0; i < steps; i++)
 {
   digitalWrite(stepperPin, HIGH);
   delayMicroseconds(DELAY);//Adjust the speed of motor. Increase the value, motor speed become slower.
   digitalWrite(stepperPin, LOW);
   delayMicroseconds(DELAY);
 }
}

void fillBottles(uint8_t &num)
{
  for(int i = 0; (i < num); ++i)
  {
    lcd.clear();
    lcd.noCursor();
    lcd.setCursor(0, 0);
    lcd.print("Filling bottle");
    lcd.print(i + 1);
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);

    step(front, STEPS);
    digitalWrite(pump, HIGH);
    delay(3000);
    digitalWrite(pump, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bottle ");
    lcd.print(i + 1);
    lcd.print(" filled.");
    delay(1000);
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
  step(back, (STEPS*num));
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
  if(bottleNo < 0 || bottleNo > MAX)
    bottleNo = 1;
  lcd.print(bottleNo);

  start = (!digitalRead(sw1) ? true : false );
  delay(200);
}
