#include "../inc/Pressure_Sensor.h"
uint32_t gPressure_Sensor_Pval = 0;

Define_State(Reading_Pval)
{   
    //Assign state id
    Pressure_Sensor_State_ID = Reading_Pval;
    //State Action
    gPressure_Sensor_Pval = getPressureVal();
    //Set Next State
    Pressure_Sensor_State = State(Sending_Pval);
}

Define_State(Sending_Pval)
{
    //Assign state id
    Pressure_Sensor_State_ID = Sending_Pval;
    //State Action
    Send_Pressure_Val(gPressure_Sensor_Pval);
    //Set Next State
    Pressure_Sensor_State = State(Waiting);
}

Define_State(Waiting)
{
    //Assign state id
    Pressure_Sensor_State_ID = Waiting;
    //State Action
    Delay(1000);
    //Set Next State
    Pressure_Sensor_State = State(Reading_Pval);
}