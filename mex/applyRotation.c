/** 
 * Applies a rotation in quaternion representation to a 3 x N MATLAB array
 * 
 * MATLAB call form:
 *      output = applyRotation(rotation, vectors)
 *  where
 *      rotation is a quaternion representaiton of a rotation R and vectors is an 3 x N MATLAB array.
 *      output is a 3 x N MATLAB array such that
 *          output(:, n) = R * vectors(:, n)
 * 
 * NOTE:
 *  Code performs no input checks.
  */

#include <stdint.h>
#include "../c/utility_functions.h"
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Process input
    size_t N = mxGetN(prhs[1]); // Number of vectors to rotate
    double *vectors = mxGetDoubles(prhs[1]); // The vectors to apply the rotation to
    double *rotation = mxGetDoubles(prhs[0]); // The rotation in quaternion representation

    // Create output matrix
    plhs[0] = mxCreateDoubleMatrix(3, N, mxREAL);
    double *output = mxGetDoubles(plhs[0]);

    // Perform the calculations
    for (size_t i = 0; i < N; ++i)
    {
        apply_rotation(&vectors[3*i], rotation, &output[3*i]);
    }
}