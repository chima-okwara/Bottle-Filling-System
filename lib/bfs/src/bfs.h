#ifndef __BFS__
#define __BFS__
#include <LiquidCrystal.h>

#define MAX   50
#define STEPS 2000000
#define DELAY 30


//Connections:
extern LiquidCrystal lcd;
extern uint8_t dirPin, stepperPin, pump, sw1, sw2, sw3, buzzer;

//Variables:
extern uint8_t bottleNo;
extern bool start;

//Functions:
void setup(void);
void loop(void);
void step(const uint8_t&, const int&);
void fillBottles(uint8_t &num);               //To fill bottles
void getNoBottles(void);

#endif // __BFS__
