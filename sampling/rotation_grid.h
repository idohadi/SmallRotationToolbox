#include <stdint.h>

// Initial ordering of grid points
extern const size_t rotation_grid_initial_ordering[144];

extern const size_t initial_rotations_no;


void initialize_incremental_rotation_grid(double *initial_rotation_grid);

void generate_incremental_rotation_grid_point(size_t n, double *initial_rotation_grid, double *rotation);

void generate_incremental_rotation_grid_point_recur(size_t base_grid_index, size_t current_index, size_t resolution_level, size_t healpix_point, double psi_in_degrees, double *rotation_in_hopf);

// void approximate_incremental_rotation_grid_dispersion(size_t sampled_rotations_no, 
//                                                         size_t sequence_lower_bound, 
//                                                         size_t sequence_upper_bound, 
//                                                         double *initial_rotation_grid, 
//                                                         sfmt_t *sfmt, 
//                                                         double *dispersion);
