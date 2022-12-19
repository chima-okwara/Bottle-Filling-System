#include <bfs.h>
#include <Arduino.h>

void step(direction_t dir, int steps)
{
 digitalWrite(dirPin, dir);
 delay(50);

 for(int i=0; i<steps; i++)
 {
   digitalWrite(stepperPin, HIGH);
   delayMicroseconds(600);//Adjust the speed of motor. Increase the value, motor speed become slower.
   digitalWrite(stepperPin, LOW);
   delayMicroseconds(600);
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

    step(forwards, STEPS);
    digitalWrite(pump, LOW);
    delay(5000);
    digitalWrite(pump, HIGH);

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
  step(backwards, (STEPS*num));
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
