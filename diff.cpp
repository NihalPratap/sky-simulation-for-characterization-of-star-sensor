#include<iostream>
#include<cmath>
using namespace std;
double difference(double x,double y)
{
    double z;
    if(x<6)
    {
        x=x+12;
        y=y+12;
        if(y>360)
            y=y-360;
        z=abs(x-y);
        x=x-12;
        y=y-12;
        if(y<0)
            y=y+360;
    }
    else if(x>354)
    {
        x=x-12;
        y=y-12;
        if(y<0)
            y=y+360;
        z=abs(x-y);
        x=x+12;
        y=y+12;
        if(y>360)
            y=y-360;
    }
    else
    {
        z=abs(x-y);
    }
    return z;
}
