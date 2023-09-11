#ifndef STATES_H_
#define STATES_H_
#include "stdint.h"
#include "Led_Driver.h"

//States Function generator
#define Define_State(S_Name) void State_##S_Name ()
#define State(S_Name) State_##S_Name


//States Connection
void Send_Pressure_Val(uint32_t Pressure_Sensor_Pval);
void HighPressure_Detected();
void NormalPressure_Detected();
#endif