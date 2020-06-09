// TODO: write this mex function which returns quaternions representing the n elementsi n hte sequence

/** 
 * Generate the n-th point in the incremental sequence of rotations.
 * This is basically a wrapper function for 
 *  generate_incremental_rotation_grid_point
 * from rotation_grid.c.
 * 
 * MATLAB call form:
 *      rotation = generateUniformRotationSequencePoint(n)
 *  where
 *      n is the index of the rotation grid point
 * 
 * NOTE:
 *  (1) Code performs no input checks.
 *  (2) The sequence indices begin from 0.
  */

#include "rotation_grid.h"
#include "utility_functions.h"
#include "mex.h"

double initial_rotations_grid[288];
bool first_run = true;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Process input
    double n = mxGetScalar(prhs[0]);
    
    // Initialize the rotation grid
    if (first_run == true) // Initialize the rotation grid on first run, but otherwise used initialized rotation grid
    {
        initialize_incremental_rotation_grid(initial_rotations_grid);
        first_run = false;
    }

    // Create the output
    plhs[0] = mxCreateDoubleMatrix(4, 1, mxREAL);
    double *rotation = mxGetDoubles(plhs[0]);

    // Generate the rotation
    double hopf[3];
    generate_incremental_rotation_grid_point(n, initial_rotations_grid, hopf);
    hopf_to_quaternions(hopf, rotation);
}
