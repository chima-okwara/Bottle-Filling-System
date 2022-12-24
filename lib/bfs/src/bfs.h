#ifndef __BFS__
#define __BFS__
#include <LiquidCrystal_I2C.h>

#define MAX   50
#define STEPS 900
#define DELAY 300
#define front HIGH
#define back  LOW


//Connections:
extern LiquidCrystal_I2C lcd;
extern uint8_t dirPin, stepperPin, pump, sw1, sw2, sw3, buzzer;

//Variables:
extern uint8_t bottleNo;
extern bool start;

//Functions:
void step(const uint8_t&, const int&);
void fillBottles(uint8_t &num);               //To fill bottles
void getNoBottles(void);

#endif // __BFS__
