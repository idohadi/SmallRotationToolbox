// TODO: better docs
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>

#include "SFMT.h"
#include "utility_functions.h"
 
#define PI 3.14159265358979323846


void hopf_to_quaternions(double *hopf, double *quaternion)
{
    /* Converts Hopfs coordinates into quaternions. Result is saved in quaternion.
        Hopf has three elements: theta, phi, psi */
    quaternion[0] = cos(hopf[0]/2) * cos(hopf[2]/2);
    quaternion[1] = cos(hopf[0]/2) * sin(hopf[2]/2);
    quaternion[2] = sin(hopf[0]/2) * cos(hopf[1] + hopf[2]/2);
    quaternion[3] = sin(hopf[0]/2) * sin(hopf[1] + hopf[2]/2);
}

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
