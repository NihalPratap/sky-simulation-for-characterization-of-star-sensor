#include<stdlib.h>
#include<iostream>
#include"fractpart.c"
using namespace std;
double pixelcnt(double x)
{
    double count=0.0;
    count=inpart(x);
    count=count*100;
    x=frapart(x);
    while(x>0)
    {
        x=x-0.0001;
        count=count+0.01;
    }
    return count;
}
