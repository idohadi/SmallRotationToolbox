/** 
 * Generate the n-th point from a quasi-random, well-dispersed grid on the rotation
 * group SO(3). The returned rotation is representated in Hopf rotation.
 * 
 * MATLAB call form:
 *      rotation = quasiRandRotation_mex(n)
 *  where
 *      n>0 is an array of integers, the indices of the rotation grid point.
 * 
 * NOTES:
 *  (1) This code performs no input checks.
 *  (2) This is basically a wrapper function for generate_incremental_rotation_grid_point
 *      from rotation_grid.c.
 *  (3) This is an implementation of the algorithm of [1]. The main functions are written 
 *      in C. The C code is derived from the Authors' C++ code. Their original C++ code is 
 *      available at
 *          https://mitchell-web.ornl.gov/SOI/index.php
 *      under "ISOI_SO3_sequence.tgz".
 * 
 * REFERENCES:
 *  [1] Yershova, A., Jain, S., LaValle, S. M., & Mitchell, J. C. (2009). Generating Uniform
 *      Incremental Grids on SO(3) Using the Hopf Fibration. The International Journal of 
 *      Robotics Research, 29(7), 801–812. https://doi.org/10.1177/0278364909352700
 * 
  */

/**
 * ***********************************************************
 * Author    Ido Hadi
 * Email     idohadi@mail.tau.ac.il
 * Year      2020
 * ***********************************************************
 */


#include <math.h>
#include <float.h>
#include <stdlib.h>

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
