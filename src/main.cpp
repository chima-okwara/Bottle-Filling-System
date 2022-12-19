#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#define MAX 50
#define STEPS 30


//Connections:
LiquidCrystal lcd(PB12, PB13, PB14, PA8, PA11, PA12);
uint8_t dirPin(PB11), stepperPin(PB10), pump(PB0), sw1(PA7), sw2(PA6), sw3(PA5),
        buzzer(PA4);

//Variables:
uint8_t bottleNo (1);

bool start (false);
enum direction_t { backwards, forwards};


//Functions:
void setup(void);
void loop(void);
void step(direction_t, int);
void fillBottles(uint8_t &num);               //To fill bottles
void getNoBottles(void);                      //To get number of bottles

void setup()
{
  pinMode(dirPin, OUTPUT);
  pinMode(stepperPin, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(buzzer, INPUT);


  digitalWrite(pump, HIGH);         //Turns pump off
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

inline void step(direction_t dir, int steps)
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

inline void fillBottles(uint8_t &num)
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
  delay(1000);
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
