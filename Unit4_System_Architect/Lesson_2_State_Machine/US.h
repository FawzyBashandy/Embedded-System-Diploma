#ifndef US_H_
#define US_H_
#include "state.h"

enum
{
    US_Busy
}US_State_Id;

//prototypes
Define_State(US_Busy);

//Global pointer to next state
void (* P_US_State)();

#endif