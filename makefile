include make.inc

MEXFILES = applyRotation_mex

compile : 	clean \
			$(MEXFILES)
			

applyRotation_mex : 
	$(MEX) $(MATLABFAGS) $(OUTPATH) utility/applyRotation_mex.c -outdir utility/

.PHONY : clean
clean :
	rm -f *.mexw64
