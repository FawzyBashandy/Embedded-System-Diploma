#include "../inc/Alarm_acutator.h"
const uint32_t const_gAlarm_Timer = 60 ;
Define_State(Idle)
{
    //Assign state id
    Alarm_Acutator_State_ID = Idle;
    //Set Next State
    //Stay in Idle state until you receive a signal from Main_Algo
    Alarm_Acutator_State = State(Idle);

}
Define_State(Alarm_ON)
{
    //Assign state id
    Alarm_Acutator_State_ID = Alarm_ON;
    //State Action
    Set_Alarm_actuator(0);
    Delay(10000000);
    //Set Next State
    Alarm_Acutator_State = State(ALarm_OFF);
}
Define_State(ALarm_OFF)
{
    //Assign state id
    Alarm_Acutator_State_ID = ALarm_OFF;
    //State Action
    Set_Alarm_actuator(1);
    //Set Next State
    Alarm_Acutator_State = State(Idle);
}

void HighPressure_Detected()
{
    Alarm_Acutator_State = State(Alarm_ON);
}
void NormalPressure_Detected()
{
    Alarm_Acutator_State = State(ALarm_OFF);
}