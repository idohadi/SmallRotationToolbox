/** 
 * Calcualte the distance between two rotations in quaternion represntation.
 * This is a wrapper function for 
 *  calculate_rotation_distance
 * from utility_functions.c.
 * 
 * MATLAB call form:
 *      distance = calculateRotationDistance(rotation1, rotation2)
 *  where
 *      rotation1 and rotation2 are 4d MATLAB arrays and distance is a double scalar.
 * 
 * NOTE:
 *  Code performs no input checks.
  */

#include <stdint.h>
#include <stdlib.h>
#include "../c/utility_functions.h"
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Process input
    double *rotation1 = mxGetDoubles(prhs[0]);
    double *rotation2 = mxGetDoubles(prhs[1]);
    
    // Measure the distance
    double distance;
    calculate_rotation_distance(rotation1, rotation2, &distance);

    // Create output
    plhs[0] = mxCreateDoubleScalar(distance);
}
