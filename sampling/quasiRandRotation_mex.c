/** 
 * Generate the n-th point from a quasi-random, well-dispersed grid on the rotation
 * group SO(3). The returned rotation is representated in Hopf rotation.
 * 
 * MATLAB call form:
 *      rotation = quasiRandRotation_mex(n)
 *  where
 *      n>0 is an array of integers, the indices of the rotation grid point.
 * 
 * NOTE:
 *  (1) This code performs no input checks.
 *  (2) Due to the convention in C, the sequence index n begin from 0.
 *  (3) This is basically a wrapper function for generate_incremental_rotation_grid_point
 *      from rotation_grid.c.
 *  (4) This is an implementation of the algorithm of [1]. The main functions are written 
 *      in C. The C code is derived from the Authors' C++ code. Their original C++ code is 
 *      available at
%           https://mitchell-web.ornl.gov/SOI/index.php
%       under "ISOI_SO3_sequence.tgz".
 * 
 * REFERENCE:
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

#include "rotation_grid.h"
#include "mex.h"

double initial_rotations_grid[288];
bool first_run = true;

double *n;
double *hopf;
size_t N;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // Initialize the rotation grid
    if (first_run == true) // Initialize the rotation grid on first run, but otherwise used initialized rotation grid
    {
        initialize_incremental_rotation_grid(initial_rotations_grid);
        first_run = false;
        mexPrintf("Sequence initialized successfully.\n");
    }

    // Process input
    n = mxGetDoubles(prhs[0]);
    N = mxGetNumberOfElements(prhs[0]);

    // Create the output
    plhs[0] = mxCreateDoubleMatrix(3, N, mxREAL);
    hopf = mxGetDoubles(plhs[0]);

    // Generate the rotation
    for (size_t i = 0; i<N; ++i)
    {
        generate_incremental_rotation_grid_point(n[i], initial_rotations_grid, &hopf[3*i]);
    }
}
