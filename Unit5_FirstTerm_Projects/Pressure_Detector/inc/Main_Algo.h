#ifndef MAIN_ALGO_H_
#define MAIN_ALGO_H_
#include "States.h"

enum 
{
    Get_Pval,
    Pressure_Comparing,
    HighPressure,
    NormalPressure
}Main_Algo_State_ID;

void (* Main_Algo_State) ();

Define_State(Get_Pval);
Define_State(Pressure_Comparing);
Define_State(HighPressure);
Define_State(NormalPressure);

#endif