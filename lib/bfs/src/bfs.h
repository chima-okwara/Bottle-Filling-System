#ifndef __BFS__
#define __BFS__
#include <LiquidCrystal.h>

enum direction_t { backwards, forwards};

#define MAX 50
#define STEPS 30


//Connections:
extern LiquidCrystal lcd;
extern uint8_t dirPin, stepperPin, pump, sw1, sw2, sw3, buzzer;

//Variables:
extern uint8_t bottleNo;
extern bool start;

//Functions:
extern void setup(void);
extern void loop(void);
extern void step(direction_t, int);
extern void fillBottles(uint8_t &num);               //To fill bottles
extern void getNoBottles(void);

#endif // __BFS__