#include "../inc/Main_Algo.h"

uint32_t gMain_Algo_Pval = 0 ;
uint32_t const const_gPval_Threshold = 20;


Define_State(Get_Pval)
{
    //Assign state id
    Main_Algo_State_ID = Get_Pval;
    //Set Next State
    Main_Algo_State = State(Pressure_Comparing);
}
Define_State(Pressure_Comparing)
{
    //Assign state id
    Main_Algo_State_ID = Pressure_Comparing;
    //Set Next State
    (gMain_Algo_Pval > const_gPval_Threshold) ? (Main_Algo_State = State(HighPressure)) : (Main_Algo_State = State(NormalPressure)); 
}
Define_State(HighPressure)
{
    //Assign state id
    Main_Algo_State_ID = HighPressure;
    //State Action
    HighPressure_Detected();
    //Set Next State
    Main_Algo_State = State(Get_Pval);
}
Define_State(NormalPressure)
{
    //Assign state id
    Main_Algo_State_ID = NormalPressure;
    //State Action
    NormalPressure_Detected();
    //Set Next State
    Main_Algo_State = State(Get_Pval);
}

void Send_Pressure_Val(uint32_t Pressure_Sensor_Pval)
{
    gMain_Algo_Pval = Pressure_Sensor_Pval;
}