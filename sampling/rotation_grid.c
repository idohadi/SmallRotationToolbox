// TODO: write all the functions

#include <math.h>
#include "rotation_grid.h"
#include "healpix_functions.h"

#define PI 3.14159265358979323846

/* Defining variables frmo rotation_grid.h */
const size_t rotation_grid_initial_ordering[144]
	= { 6,0,
        6,3,
        6,1,
        6,4,
        6,2,
        6,5,
        4,0,
        4,3,
        4,1,
        4,4,
        4,2,
        4,5,
        1,0,
        1,3,
        1,1,
        1,4,
        1,2,
        1,5,
        11,0,
        11,3,
        11,1,
        11,4,
        11,2,
        11,5,
        9,0,
        9,3,
        9,1,
        9,4,
        9,2,
        9,5,
        3,0,
        3,3,
        3,1,
        3,4,
        3,2,
        3,5,
        5,0,
        5,3,
        5,1,
        5,4,
        5,2,
        5,5,
        7,0,
        7,3,
        7,1,
        7,4,
        7,2,
        7,5,
        10,0,
        10,3,
        10,1,
        10,4,
        10,2,
        10,5,
        0,0,
        0,3,
        0,1,
        0,4,
        0,2,
        0,5,
        2,0,
        2,3,
        2,1,
        2,4,
        2,2,
        2,5,
        8,0,
        8,3,
        8,1,
        8,4,
        8,2,
        8,5};

const size_t initial_rotations_no = 72;

/* Defining functions */
void initialize_incremental_rotation_grid(double *initial_rotation_grid)
{
    /* Generates the initial grid points in quaternion representation.
        initial_rotation_grid is a 4 x initial_rotations_no C array such that
            initial_rotation_grid [4*i+j] (j=0,1,2,4) is a quaternion representation 
            of a rotation */

	// Initialize things
    double *hopf; // Hopfs coordinates, hopf[0] = theta, hopf[1] = phi, hopf[2] = psi

    for (size_t i = 0; i < initial_rotations_no; ++i)
    {
		hopf = &initial_rotation_grid[3*i];

        // Calculate theta and phi (the S^2 coordinates) using HEALPix's function
        pix2ang_nest(1, rotation_grid_initial_ordering[2*i], &hopf[0], &hopf[1]);

        // Calculate psi (the S^1 coordinate)
        switch(rotation_grid_initial_ordering[2*i+1]) //mapping index on S1 to its angle value
		{
			case 0:
                hopf[2] = 30.0*PI/180.0;
				break;
			case 1:
                hopf[2] = 90.0*PI/180.0;
				break;
			case 2: 
				hopf[2] = 150.0*PI/180.0;
				break;
			case 3:
				hopf[2] = 210.0*PI/180.0;
				break;
			case 4: 
				hopf[2] = 270.0*PI/180.0;
				break;
			case 5: 
				hopf[2] = 330.0*PI/180.0;
				break;
		}
    }
}

void generate_incremental_rotation_grid_point(size_t n, double *initial_rotation_grid, double *rotation)
{
    /* Generates the sequence point with index n. All in all Hopf coordiantes.
    NOTE: First index of sequence is 0. The initial grid corresponds to sequence points 0 to 71 (included). */
    if (n < initial_rotations_no) // If the required point is in the initial rotation grid
    {
        for (size_t i = 0; i < 3; ++i)
        {
            rotation[i] = initial_rotation_grid[3*n+i];
        }
    }
    else
    {
        size_t base_grid_index = (n - initial_rotations_no) % initial_rotations_no;

        // Calculate the Hopf coordinate on S^1 in degrees
        double psi_in_degrees; // The Hopf coordinate on S^1
        switch(rotation_grid_initial_ordering[2*base_grid_index+1]) //mapping index on S1 to its angle value
		{
			case 0:
				psi_in_degrees = 30;
				break;
			case 1:
				psi_in_degrees = 90;
				break;
			case 2: 
				psi_in_degrees = 150;
				break;
			case 3:
				psi_in_degrees = 210;
				break;
			case 4: 
				psi_in_degrees = 270;
				break;
			case 5: 
				psi_in_degrees = 330;
				break;
		}

        // Calculate the new rotation by recursion
        // double hopf[3]; // Rotation in Hopf coordinates
        generate_incremental_rotation_grid_point_recur(rotation_grid_initial_ordering[2*base_grid_index], 
                                                        (size_t) ((n - initial_rotations_no) / initial_rotations_no), 
                                                        1, 
														4*rotation_grid_initial_ordering[2*base_grid_index], 
                                                        psi_in_degrees, 
														rotation);
    }
}

void generate_incremental_rotation_grid_point_recur(size_t base_grid_index, size_t current_index, size_t resolution_level, size_t healpix_point, double psi_in_degrees, double *rotation_in_hopf)
// My variable names:           (base_grid,         point,          level,              healpix_point,  s1_point) 
// Jain's variable names:       (base_grid_index,   current_index,  resolution_level,   healpix_point,  psi_in_degrees,     rotation_in_hopf)
{
    /* Recursion which produces a rotation grid point (beyond the initla grid) */
    size_t position = current_index % 8;
    double interval = 30/resolution_level;

    if(base_grid_index == 6 || base_grid_index == 7)
	{
		switch(position) //this position tells which of the eight points of the cube to consider 
		{ 
			case 0:
				healpix_point += 3;
				psi_in_degrees -= interval/2;
				break;
			case 1:
				psi_in_degrees += interval/2;
				break;
			case 2: 
				healpix_point += 3;
				psi_in_degrees += interval/2;
				break;
			case 3:
				psi_in_degrees -= interval/2;
				break;
			case 4:
				healpix_point += 2;
				psi_in_degrees -= interval/2;
				break;
			case 5:
				healpix_point += 1;
				psi_in_degrees += interval/2;
				break;
			case 6:
				healpix_point += 2;
				psi_in_degrees += interval/2;
				break;
			case 7:
				healpix_point += 1;
				psi_in_degrees -= interval/2;
				break;
		}
	}
	else if(base_grid_index == 3 || base_grid_index == 1 || base_grid_index == 9 || base_grid_index == 11)
	{
		switch(position) 
		{
			case 0:
				healpix_point += 3;
				psi_in_degrees -= interval/2;
				break;
			case 1:
				psi_in_degrees += interval/2;
				break;
			case 2: 
				healpix_point += 3;
				psi_in_degrees += interval/2;
				break;
			case 3:
				psi_in_degrees -= interval/2;
				break;
			case 4:
				healpix_point += 1;
				psi_in_degrees -= interval/2;
				break;
			case 5:
				healpix_point+=2;
				psi_in_degrees += interval/2;
				break;
			case 6:
				healpix_point += 1;
				psi_in_degrees += interval/2;
				break;
			case 7:
				healpix_point += 2;
				psi_in_degrees -= interval/2;
				break;
		}
	}
	else if(base_grid_index == 2 || base_grid_index == 0 || base_grid_index == 10 || base_grid_index == 8)
	{
		switch(position) 
		{ 
			case 0:
				psi_in_degrees -= interval/2;
				break;
			case 1:
				healpix_point += 3;
				psi_in_degrees += interval/2;
				break;
			case 2: 
				psi_in_degrees += interval/2;
				break;
			case 3:
				healpix_point += 3;
				psi_in_degrees -= interval/2;
				break;
			case 4:
				healpix_point += 1;
				psi_in_degrees -= interval/2;
				break;
			case 5:
				healpix_point += 2;
				psi_in_degrees += interval/2;
				break;
			case 6:
				healpix_point += 1;
				psi_in_degrees += interval/2;
				break;
			case 7:
				healpix_point += 2;
				psi_in_degrees -= interval/2;
				break;
		}
	}
	else if(base_grid_index == 4 || base_grid_index == 5)
	{
		switch(position) 
		{ 
			case 0:
				psi_in_degrees -= interval/2;
				break;
			case 1:
				healpix_point+=3;
				psi_in_degrees += interval/2;
				break;
			case 2: 
				psi_in_degrees += interval/2;
				break;
			case 3:
				healpix_point += 3;
				psi_in_degrees -= interval/2;
				break;
			case 4:
				healpix_point += 2;
				psi_in_degrees -= interval/2;
				break;
			case 5:
				healpix_point += 1;
				psi_in_degrees += interval/2;
				break;
			case 6:
				healpix_point += 2;
				psi_in_degrees += interval/2;
				break;
			case 7:
				healpix_point += 1;
				psi_in_degrees -= interval/2;
				break;
		}
	}

    // Handle the recursion
    size_t test_value = current_index/8;
    if (test_value == 0)
    {
        pix2ang_nest(pow(2, resolution_level), healpix_point, &rotation_in_hopf[0], &rotation_in_hopf[1]);
        rotation_in_hopf[2] = psi_in_degrees*PI/180;
    }
    else
    {
        generate_incremental_rotation_grid_point_recur(base_grid_index, test_value-1, resolution_level+1, 4*healpix_point, psi_in_degrees, rotation_in_hopf); 
    }
}


// void approximate_incremental_rotation_grid_dispersion(size_t sampled_rotations_no, 
// 														size_t sequence_lower_bound, 
// 														size_t sequence_upper_bound, 
// 														double *initial_rotation_grid, 
// 														sfmt_t *sfmt, 
// 														double *dispersion)
// {
//     /* Given a range of points frmo the incremental sequence, estimate their dispersion. */
//     /* Explanation: given a set of rotations, calculate sampeld_rotations_no unifmrly random rotations and 
//         measure their distance (in the appropriate metric) from rotations from the rotations seqeunce with
//         indices between sequence_lower_bound and sequence_upper_bound. */
//     double sequence_rotation[4]; 
// 	double hopf[3];
//     double random_rotation[4];  
//     double current_distance, distance_min, distance_max;
//     distance_max = 0;

//     for (size_t i = 0; i < sampled_rotations_no; ++i)
//     {
//         distance_min = PI;
//         generate_uniformly_random_rotation(random_rotation, sfmt);

//         for (size_t n = sequence_lower_bound; n <= sequence_upper_bound; ++n)
//         {
//             generate_incremental_rotation_grid_point(n, initial_rotation_grid, hopf);
//             hopf_to_quaternions(hopf, sequence_rotation);
//             calculate_rotation_distance(sequence_rotation, random_rotation, &current_distance);
            
//             if (current_distance < distance_min)
//             {
//                 distance_min = current_distance;
//             }
//         }

//         if (distance_min > distance_max)
//         {
//             distance_max = distance_min;
//         }
//     }

//     *dispersion = distance_max;
// }
