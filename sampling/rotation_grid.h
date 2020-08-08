/**
 * This is part of an implementation of the main algorithm of [1]. It generates an deterministic, 
 * incremental, well-dispersed sequence of rotations, represented in Hopf coordinates.
 * 
 * 
 * This header file declares all three main functions of the algorithm. The functions are documented, 
 * somewhat, in the corresponding source file.
 * 
 * It is recommended to read [1] before going over the code.
 * 
 * NOTES: 
 *  (1) [1] cites Jain (2009) as a reference to the source code, but Jain (2009) is no longer 
 *      available online. My C code is derived from the Authors' C++ code. Their original C++ 
 *      code is available at
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


#include <stdint.h>

// Initial ordering of grid points
extern const size_t rotation_grid_initial_ordering[144];

extern const size_t initial_rotations_no;


void initialize_incremental_rotation_grid(double *initial_rotation_grid);

void generate_incremental_rotation_grid_point(size_t n, double *initial_rotation_grid, double *rotation);

void generate_incremental_rotation_grid_point_recur(size_t base_grid_index, size_t current_index, size_t resolution_level, size_t healpix_point, double psi_in_degrees, double *rotation_in_hopf);
