#ifndef STATE_H_
#define STATE_H_
#include <stdio.h>
#include <stdlib.h>
#define Define_State(State_Name) void State_##State_Name()
#define State(State_Name) State_##State_Name



//States Connection
void US_Distance_Signal(int d);
void Motor_Speed_Signal(int s);

#endif