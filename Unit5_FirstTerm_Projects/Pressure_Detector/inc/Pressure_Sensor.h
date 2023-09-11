#ifndef PRESSURE_SENSOR_H_
#define PRESSURE_SENSOR_H_
#include "States.h"

enum 
{
    Reading_Pval,
    Sending_Pval,
    Waiting
}Pressure_Sensor_State_ID;

void (* Pressure_Sensor_State) ();

Define_State(Reading_Pval);
Define_State(Sending_Pval);
Define_State(Waiting);

#endif