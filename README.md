# Small Rotation Toolbox

This repo is a MATLAB implementation of several functions relating to 3d rotations. These include:

- Uniformly and quasi-uniformly sampling rotations (***sampling***)
- Converting between several representations of rotations (***conversion***)
- Applying a rotation in quaternion representation to 3d vectors (***utility/applyRotation.m***)
- Measuring distance between rotations (***utility/rotationDistance.m***)

Parts of the code is written in C.

## How to Install

1. Run the make file (using GNU Make). This compiles the MEX and C files. 

   If you have GNU make installed, simply navigate to the root folder of the repo and run the in a shell

   ```
   make
   ```

2. Within MATLAB, run ***setup.m***. It adds the necessary folders to path.

## Documentation

Documentation is available for every function, and includes specification of the conventions used for angles and notations.

A more detailed, expansive documentation is in the works (***docs***).

## Quasi-Uniform Sampling of Rotations

[1] defines a sequence of rotations with the following properties:

- ***Deterministic.*** The *n*th rotation is completely determined by the first 72 initial rotations and their ordering.
- ***Quasi-Uniform<sup>1</sup>.*** It behaves roughly like a uniform grid on [-1,1]<sup>3</sup> in that the first *n* points "fill" the rotation group better the larger *n* is.

[1] implemented their method in C++. [Their code][https://mitchell-web.ornl.gov/SOI/index.php] is available online. I rewrote it in C and wrote a MATLAB MEX interface for it.

## Notes

<sup>1</sup> I prefer the term quasi-uniform to describe this behavior. In [1] it is described as having significantly smaller dispersion 

## Bibliography

[1] Yershova, A., Jain, S., LaValle, S. M., & Mitchell, J. C. (2009). [Generating Uniform Incremental Grids on SO(3) Using the Hopf Fibration](https://doi.org/10.1177/0278364909352700). *The International Journal of Robotics Research*, 29(7), 801–812.