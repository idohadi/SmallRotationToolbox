%% Compiling all th mex functions
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast -msse2 -DHAVE_SSE2' -DSFMT_MEXP=2281 applyRotation.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c ..\extern\SFMT-1.5.1\SFMT.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast' calculateRotationDistance.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast -msse2 -DHAVE_SSE2' -DSFMT_MEXP=2281 estimateDispersionOfRotationsSet.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c ..\extern\SFMT-1.5.1\SFMT.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast -msse2 -DHAVE_SSE2' -DSFMT_MEXP=2281 estimateDispersionOfUniformRotationsGrid.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c ..\extern\SFMT-1.5.1\SFMT.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast -msse2 -DHAVE_SSE2' -DSFMT_MEXP=2281 generateUniformlyRandomRotations.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c ..\extern\SFMT-1.5.1\SFMT.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast -msse2 -DHAVE_SSE2' -DSFMT_MEXP=2281 generateUniformRotationSequencePoint.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c ..\extern\SFMT-1.5.1\SFMT.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast' generateUniformRotationsGridInHopf.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c
mex -R2018a COMPFLAGS='$COMPFLAGS -Ofast' generateUniformRotationsGridInQuaternions.c ..\c\utility_functions.c ..\c\healpix_functions.c ..\c\rotation_grid.c
