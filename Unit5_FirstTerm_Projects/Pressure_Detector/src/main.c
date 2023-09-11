#include "../inc/Alarm_acutator.h"
#include "../inc/Main_Algo.h"
#include "../inc/Pressure_Sensor.h"

void setup();

int main()
{
    setup();

    while(1)
    {
        Pressure_Sensor_State();
        Main_Algo_State();
        Alarm_Acutator_State();
    }
}

void setup()
{
    GPIO_INITIALIZATION();
    Pressure_Sensor_State = State(Reading_Pval);
    Main_Algo_State = State(Get_Pval);
    Alarm_Acutator_State = State(Idle);
}