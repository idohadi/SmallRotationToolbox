/** 
 * Generate a uniformly random rotations in quaternions representation
 * 
 * MATLAB call form:
 *      output = generateUniformlyRandomRotations(sampled_rotations_no)
 *  where
 *      sampled_rotations_no is the number of rotations to sample.
 *      output is a 4 x sampled_rotations_no MATLAB array. 
 *      Every column in output is a quaternion representation of a rotation.
 * 
 * NOTE:
 *  Code performs no input checks.
  */

#include <stdint.h>
#include "utility_functions.h"
#include "mex.h"

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
    double sampled_rotations_no = mxGetScalar(prhs[0]);
    
    // Create output 
    plhs[0] = mxCreateDoubleMatrix(4, sampled_rotations_no, mxREAL);
    double *output = mxGetDoubles(plhs[0]);

    // Perform the calculations
    for (size_t i = 0; i < sampled_rotations_no; ++i)
    {
        generate_uniformly_random_rotation(&output[4*i], &sfmt); 
    }
}
