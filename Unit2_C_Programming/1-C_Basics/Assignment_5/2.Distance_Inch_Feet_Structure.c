#include <stdio.h>
struct Sdistance
{
    float feet;
    float inch;
};

int main()
{
    struct Sdistance distance1,distance2,result;
    printf("Enter information for 1st distance : \n");
    printf("Enter Feet: ");
    scanf("%f",&distance1.feet);
    printf("Enter Inch: ");
    scanf("%f",&distance1.inch);

    printf("Enter information for 2st distance : \n");
    printf("Enter Feet: ");
    scanf("%f",&distance2.feet);
    printf("Enter Inch: ");
    scanf("%f",&distance2.inch);

    result.feet=distance1.feet+distance2.feet;
    result.inch=distance1.inch+distance2.inch;
    if(result.inch>=12)
    {
        result.inch-=12;
        result.feet++;
    }
    
    printf("Sum of distances=%g'-%g\"",result.feet,result.inch);
}
