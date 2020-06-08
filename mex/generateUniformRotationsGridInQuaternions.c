// TODO: write this mex function which returns quaternions representing the n elementsi n hte sequence

/** 
 * Generate all the points of the incremenetal sequence of rotations with indices between a lower and upper bound.
 * 
 * MATLAB call form:
 *      rotations = generateUniformRotationsGrid(lower_bound, upper_bound)
 *  where
 *      rotations is a 4 x (upper_boudn - lower_bound + 1) MATLAB array containing such that
 *          rotations(:, n+1) is the quaternion represetntation of the n-th rotation in the incremental sequence
 * 
 * NOTE:
 *  (1) Code performs no input checks.
 *  (2) The sequence indices begin from 0.
  */

#include "../c/rotation_grid.h"
#include "../c/utility_functions.h"
#include "mex.h"

double initial_rotations_grid[288];
bool first_run = true;
size_t ind;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Process input
    double lower_bound = mxGetScalar(prhs[0]);
    double upper_bound = mxGetScalar(prhs[1]);
    
    // Initialize the rotation grid
    if (first_run == true) // Initialize the rotation grid on first run, but otherwise used initialized rotation grid
    {
        initialize_incremental_rotation_grid(initial_rotations_grid);
        first_run = false;
    }

    // Create the output
    double hopf[3];
    plhs[0] = mxCreateDoubleMatrix(4, upper_bound - lower_bound + 1, mxREAL);
    double *rotations = mxGetDoubles(plhs[0]);

    // Generate the rotation
    ind = 0;
    for (size_t n = lower_bound; n < upper_bound + 1; ++n)
    {
        generate_incremental_rotation_grid_point(n, initial_rotations_grid, hopf);
        hopf_to_quaternions(hopf, &rotations[4*ind]);
        ++ind;
    }
}
