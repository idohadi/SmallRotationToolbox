#include "SFMT.h"

void generate_uniformly_random_rotation(double *rotation, sfmt_t *sfmt);

void hopf_to_quaternions(double *hopf, double *quaternion);

void apply_rotation(double *x, double *quaternion, double *result);

void cross_product(double *a, double *b, double *result);

void dot_product(double *a, double *b, size_t n, double *result);

void quaternion_to_angleaxis(double *quaternion, double *angleaxis);

void calculate_rotation_distance(double *quaternion1, double *quaternion2, double *distance);
