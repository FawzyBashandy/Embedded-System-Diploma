#ifndef MOTOR_H_
#define MOTOR_H_
#include "state.h"

enum
{
    Motor_Idle,
    Motor_Busy
}Motor_State_Id;

//prototypes
Define_State(Motor_Idle);
Define_State(Motor_Busy);

//Global pointer to next state
void (* P_Motor_State)();

#endif