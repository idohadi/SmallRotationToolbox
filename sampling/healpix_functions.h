/**
 * This is part of an implementation of the main algorithm of [1]. It generates an deterministic, 
 * incremental, well-dispersed sequence of rotations, represented in Hopf coordinates.
 * 
 * 
 * This header file declares two relevant functions from a previous HEALPix version (circa ~2008).
 * 
 * NOTES: 
 *  (1) The original code herein was taken from Jain (2009). I merely placed them in the same 
 *      source file and removed code that was commented out.
 *  (2) [1] cites Jain (2009) as a reference to the source code. It is no longer available online. 
 *      My C code is derived from the Authors' C++ code. Their original C++ code is available at
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


void mk_pix2xy(int *pix2x, int *pix2y);

void pix2ang_nest( long nside, long ipix, double *theta, double *phi);
