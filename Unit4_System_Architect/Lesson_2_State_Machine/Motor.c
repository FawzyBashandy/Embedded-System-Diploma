#include "Motor.h"

extern void (* P_Motor_State) ();

//Module Variables
unsigned int Motor_Speed;

void Motor_Speed_Signal (int s)
{
    Motor_Speed = s;
    P_Motor_State = State(Motor_Busy);
    printf("Motor : Motor Speed Signal Received From ==CA== and speed is : %d\n",Motor_Speed);
}

Define_State(Motor_Idle)
{
    Motor_State_Id = Motor_Idle;
    P_Motor_State = State(Motor_Idle);
    printf("DC_Idle State : Speed is :%d\n",Motor_Speed);
}

Define_State(Motor_Busy)
{
    Motor_State_Id = Motor_Busy;
    P_Motor_State = State(Motor_Idle);
    printf("DC_Busy State : Speed is :%d\n",Motor_Speed);
}