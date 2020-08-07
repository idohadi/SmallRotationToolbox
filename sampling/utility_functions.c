// TODO: better docs
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <time.h>

#include "SFMT.h"
#include "utility_functions.h"
 
#define PI 3.14159265358979323846

double random_double(sfmt_t *sfmt)
{
    return sfmt_genrand_real3(sfmt);
}

void generate_uniformly_random_rotation(double *rotation, sfmt_t *sfmt)
{
    /* Generates a uniformly random rotation in quaternion representation and saves it in rotation. */
    
    /* See details of algorithm here:
        http://planning.cs.uiuc.edu/node198.html */
    
    double u1, u2, u3;
    u1 = random_double(sfmt);
    u2 = random_double(sfmt);
    u3 = random_double(sfmt);

    if (cos(2*PI*u2) >= 0)
    {
        rotation[0] = sqrt(1-u1)*sin(2*PI*u2);
        rotation[1] = sqrt(1-u1)*cos(2*PI*u2);
        rotation[2] = sqrt(u1)*sin(2*PI*u3);
        rotation[3] = sqrt(u1)*cos(2*PI*u3);
    }
    else
    {
        rotation[0] = -sqrt(1-u1)*sin(2*PI*u2);
        rotation[1] = -sqrt(1-u1)*cos(2*PI*u2);
        rotation[2] = -sqrt(u1)*sin(2*PI*u3);
        rotation[3] = -sqrt(u1)*cos(2*PI*u3);
    }
}

void hopf_to_quaternions(double *hopf, double *quaternion)
{
    /* Converts Hopfs coordinates into quaternions. Result is saved in quaternion.
        Hopf has three elements: theta, phi, psi */
    quaternion[0] = cos(hopf[0]/2) * cos(hopf[2]/2);
    quaternion[1] = cos(hopf[0]/2) * sin(hopf[2]/2);
    quaternion[2] = sin(hopf[0]/2) * cos(hopf[1] + hopf[2]/2);
    quaternion[3] = sin(hopf[0]/2) * sin(hopf[1] + hopf[2]/2);
}

void apply_rotation(double *x, double *quaternion, double *result)
{
    /* Apply the rotation represented by quternion to x and save the result in result.  */
    cross_product(&quaternion[1], x, result);
    for (int i = 0; i < 3; ++i)
    {
        result[i] += quaternion[0]*x[i];
    }
    cross_product(&quaternion[1], result, result);
    for (int i = 0; i < 3; ++i)
    {
        result[i] *= 2;
        result[i] += x[i];
    }
}

void cross_product(double *a, double *b, double *result)
{
    /* Calculate the cross product a x b and save the reuslt in result.
        Code enables result to be identical to a or b. */
    double i = a[1]*b[2] - a[2]*b[1];
    double j = a[2]*b[0] - a[0]*b[2];
    double k = a[0]*b[1] - a[1]*b[0];
    result[0] = i;
    result[1] = j;
    result[2] = k;
}

void dot_product(double *a, double *b, size_t n, double *result)
{
    /* Calculates the dot product of a and b, both arrays with n elements, and saves the result in result. */
    *result = 0;
    for (size_t i = 0; i < n; ++i)
    {
        *result += a[i]*b[i];
    }
    
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

void calculate_rotation_distance(double *quaternion1, double *quaternion2, double *distance)
{
    /* Calculate the distance between quaternion1 and quaternion2 and saves the result in distance.
        quaternion1 and quaternion2 have 4 elements. distance has one. */
    
    dot_product(quaternion1, quaternion2, 4, distance);
    if ((*distance) >= 0)
    {
        *distance = acos(*distance);
    }
    else
    {
        *distance = acos(- (*distance));
    }
}