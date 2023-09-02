#include "CA.h"

extern void (* P_CA_State) ();

//Module Variables
unsigned int CA_Distance;
unsigned int CA_Speed;
const unsigned int CA_Threshold = 50;



Define_State(CA_Waiting)
{
    //State Action
    CA_State_Id = CA_Waiting;
    CA_Speed = 0;
    printf("CA Waiting State : Distance = %d , Speed = %d \n",CA_Distance,CA_Speed);
    //Send signal to DC_Motor Module
    Motor_Speed_Signal(CA_Speed);
}

Define_State(CA_Driving)
{
    //State Action
    CA_State_Id = CA_Driving;
    CA_Speed = 30;
    printf("CA Driving State : Distance = %d , Speed = %d \n",CA_Distance,CA_Speed);
    //Send signal to DC_Motor Module
    Motor_Speed_Signal(CA_Speed);
}

void US_Distance_Signal (int d)
{
    CA_Distance = d;
    //Determine the State of CA Based on the received signal(distance)
    (CA_Distance > CA_Threshold)?(P_CA_State = State(CA_Driving)):(P_CA_State = State(CA_Waiting));
    printf("CA :Signal Received from ==US== and Distance is : %d \n",CA_Distance);
}
