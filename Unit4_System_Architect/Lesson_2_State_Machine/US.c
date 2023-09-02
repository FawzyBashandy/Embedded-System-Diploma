#include "US.h"

extern void (* P_US_State) ();

//Module Variables
unsigned int US_Distance;

int Generate_Random_Distance(int min, int max) {
    return min + rand() % (max - min + 1);
}

Define_State(US_Busy)
{
    //State Action
    US_State_Id = US_Busy;
    US_Distance = Generate_Random_Distance(45 , 55 );
    printf("US Busy State : Distance = %d \n",US_Distance);

    US_Distance_Signal(US_Distance);
    P_US_State = State(US_Busy);
}