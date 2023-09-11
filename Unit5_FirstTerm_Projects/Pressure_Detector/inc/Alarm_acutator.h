#ifndef ALARM_ACUTATOR_H_
#define ALARM_ACUTATOR_H_
#include "States.h"

enum 
{
    Idle,
    Alarm_ON,
    ALarm_OFF
}Alarm_Acutator_State_ID;

void (* Alarm_Acutator_State) ();

Define_State(Idle);
Define_State(Alarm_ON);
Define_State(ALarm_OFF);

#endif