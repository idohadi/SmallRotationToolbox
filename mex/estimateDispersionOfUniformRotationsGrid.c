/** 
 * Estimate the dispersion of the incremental rotation grid sequence.
 * This is a wrapper function for 
 *  approximate_incremental_rotation_grid_dispersion
 * from rotation_grid.c.
 * 
 * MATLAB call form:
 *      dispersion = estimateDispersionOfUniformRotationsGrid(sampled_rotations_no, sequence_lower_bound, sequence_upper_bound)
 *  where
 *      sampled_rotations_no is the number of rotations to sample.
 *      dispersion is calculated for the sequence between sequence_lower_bound and sequence_upper_bound.
 *      dispersion is a scalar.
 * 
 * NOTE:
 *  (1) Code performs no input checks.
 *  (2) The sequence indices begin from 0.
  */

#include <stdint.h>
#include "rotation_grid.h"
#include "SFMT.h"
#include "mex.h"

double initial_rotations_grid[288];
sfmt_t sfmt;
bool first_run = true;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Process input
    double sampled_rotations_no = mxGetScalar(prhs[0]);
    double sequence_lower_bound = mxGetScalar(prhs[1]);
    double sequence_upper_bound = mxGetScalar(prhs[2]);
    
    // Generate output
    // Initialize the rotation grid
    if (first_run == true) // Initialize the rotation grid on first run, but otherwise used initialized rotation grid
    {
        first_run = false;
        initialize_incremental_rotation_grid(initial_rotations_grid);
        sfmt_init_gen_rand(&sfmt, 1000);
    }
    
    // Approximate the rotation
    double dispersion = 0;
    approximate_incremental_rotation_grid_dispersion(sampled_rotations_no, sequence_lower_bound, sequence_upper_bound, initial_rotations_grid, &sfmt, &dispersion);

    // Create output
    plhs[0] = mxCreateDoubleScalar(dispersion);
}
