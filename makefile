include make.inc

MEXFILES = applyRotation_mex \
			quasiRandRotation_mex

compile : 	clean \
			$(MEXFILES)
			

applyRotation_mex : 
	$(MEX) $(MATLABFAGS) $(MEXCFALGS) utility/applyRotation_mex.c -outdir utility/

quasiRandRotation_mex : 
	$(MEX) $(MATLABFAGS) $(MEXCFALGS) sampling/quasiRandRotation_mex.c sampling/healpix_functions.c sampling/rotation_grid.c -outdir sampling/


.PHONY : clean
clean :
	find . -name "*.mex*" -type f -delete
	find . -name "*.o" -type f -delete
