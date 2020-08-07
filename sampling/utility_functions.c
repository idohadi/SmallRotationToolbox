// TODO: better docs
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>

#include "SFMT.h"
#include "utility_functions.h"
 
#define PI 3.14159265358979323846

void quaternion_to_angleaxis(double *quaternion, double *angleaxis)
{
    /* Converts the quaternion represntation of a rotation to its angel-axis representation. 
        angleaxis is an array with 4 elements: (theta, n1, n2, n3) where theta is the angle and (n1, n2, n3) is a unit vector. */
    angleaxis[0] = 2*acos(quaternion[0]);
    if (angleaxis[0] <= DBL_MIN)
    {
        for (int i = 1; i < 4; ++i)
        {
            angleaxis[i] = 0;
        }
    }
    else
    {
        double factor = sin(angleaxis[0]/2);
        for (int i = 1; i < 4; ++i)
        {
            angleaxis[i] = quaternion[i]/factor;
        }
    }
}
