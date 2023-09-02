#include "US.h"
#include "Motor.h"
#include "CA.h"

void setup()
{
    // Init for all drivers
    //.................
    //Set State pointer for each block
    P_CA_State = State(CA_Waiting);
    P_Motor_State = State(Motor_Idle);
    P_US_State = State(US_Busy);
}

int main ()
{
    int delay;

    setup();

    while(1)
    {
        P_US_State();
        for(delay =1 ; delay > 0 ; delay++);
        P_CA_State();
        for(delay =1 ; delay > 0 ; delay++);
        P_Motor_State();
        for(delay =1 ; delay > 0 ; delay++);
    }
}
