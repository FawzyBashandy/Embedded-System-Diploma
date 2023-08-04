#include <stdio.h>
#include <math.h>
double mySqrt(double x);

int main()
{
    int number;
    printf("Enter an Integer : ");
    scanf("%d",&number);
    printf("The square root of %d is : %.5f",number,mySqrt(number));
}

double mySqrt(double x) //Using binary search
{
    double left = 0;
    double right = x;
    double mid = (left + right) / 2;

    if (x < 2)
        return x;

    while (fabs(mid * mid - x) > 0.00001)
    {
        if (mid * mid > x)
            right = mid;
        else
            left = mid;

        mid = (left + right) / 2;
    }

    return mid;
}

