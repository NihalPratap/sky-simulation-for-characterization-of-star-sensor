#include <stdio.h>      /* printf */
#include <math.h>       /* modf */

double inpart(double param)
{
   double intpart;
  double frapart = modf (param , &intpart);
   //printf("func %lf\n",intpart);
  return intpart;
}

double frapart(double param)
{
    double intpart;
  double fracpart = modf (param , &intpart);
    //printf("func %lf\n",fracpart);
  return fracpart;
}
