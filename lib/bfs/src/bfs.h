#ifndef __BFS__
#define __BFS__
#include <LiquidCrystal.h>
#include <Wire.h>

#define MAX   6
#define STEPS 1000
#define CASE4 100
#define __DELAY__ 120
#define front LOW
#define back  HIGH
#define init_steps 1200 //TODO: Change after measuring
#define DEFAULTLEVEL 3
#define MAXPUMPDEL 9500u
#define MINPUMPDEL 4500u


//Connections:
extern LiquidCrystal lcd;
//extern uint8_t dirPin, stepperPin, pump, sw1, sw2, sw3, buzzer;
extern uint8_t sw1, sw2, sw3;
extern uint8_t pump, buzzer, dirPin, stepperPin;
extern uint32_t pumpDel, trickleDel;
extern uint32_t level;

//Variables:
extern uint8_t bottleNo;
extern bool start;

//Functions:
void step(const uint8_t&, const int&);
void fillBottles(uint8_t &num);               //To fill bottles
void getNoBottles(void);
void getPumpLevel(void);

#endif // __BFS__
