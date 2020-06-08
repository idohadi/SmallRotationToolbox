/**
 * This header file declares two relevant functions from a previous HEALPix version (circa ~2008).
 * 
 * NOTE: 
 *  (1) The original code herein was taken from Jain (2009). I merely placed them in the same 
 *      source file and removed code that was commented out.
 *  (2) Jain (2009) is no longer available online. Instead, the source code is 
 *      available here:
 *          https://mitchell-web.ornl.gov/SOI/index.php

 * 
 * REFERENCE:
 *  Yershova, A., Jain, S., LaValle, S. M., & Mitchell, J. C. (2009). Generating Uniform 
 *  Incremental Grids on SO(3) Using the Hopf Fibration. The International Journal of Robotics 
 *  Research, 29(7), 801–812. https://doi.org/10.1177/0278364909352700
 * 
 */

void mk_pix2xy(int *pix2x, int *pix2y);

void pix2ang_nest( long nside, long ipix, double *theta, double *phi);
