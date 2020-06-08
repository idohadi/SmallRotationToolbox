/** 
 * Estimate the dispersion of a set of rotations in quaternion representation.
 * 
 * MATLAB call form:
 *      dispersion = estimateDispersionOfRotationsSet(rotations_set, sampled_points_no)
 *  where
 *      the approximation is based on sampled_points_no uniformly sampled rotations.
 *      rotations_set is a 4 x N MATLAB array. Every column is a quaternion representation of rotation.
 * 
 * NOTE:
 *  Code performs no input checks.
  */

#include <stdint.h>
#include "../c/utility_functions.h"
#include "../extern/SFMT-1.5.1/SFMT.h"
#include "mex.h"

#define PI 3.14159265358979323846

sfmt_t sfmt; 
bool first_run = true;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    if (first_run == true)
    {
        first_run = false;
        sfmt_init_gen_rand(&sfmt, 1000);
    }

    // Process input
    double *rotations_set = mxGetDoubles(prhs[0]);
    double N = mxGetN(prhs[0]);
    double sampled_rotations_no = mxGetScalar(prhs[1]);
    
    // Calculate dispersion
    double random_rotation[4];  
    double current_distance, distance_min, distance_max;
    distance_max = 0;

    for (size_t i = 0; i < sampled_rotations_no; ++i)
    {
        distance_min = PI;
        generate_uniformly_random_rotation(random_rotation, &sfmt);

        for (size_t i = 0; i < N; ++i)
        {
            calculate_rotation_distance(&rotations_set[4*i], random_rotation, &current_distance);
            
            if (current_distance < distance_min)
            {
                distance_min = current_distance;
            }
        }

        if (distance_min > distance_max)
        {
            distance_max = distance_min;
        }
    }

    // Create output
    plhs[0] = mxCreateDoubleScalar(distance_max);
}
