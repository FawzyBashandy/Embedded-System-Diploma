#ifndef CA_H_
#define CA_H_
#include "state.h"

enum
{
    CA_Waiting,
    CA_Driving
}CA_State_Id;

//prototypes
Define_State(CA_Waiting);
Define_State(CA_Driving);

//Global pointer to next state
void (* P_CA_State)();

#endif