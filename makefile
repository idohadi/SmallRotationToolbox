include var.inc


#Useful variable definitions
CDir=c
MEXDir=mex
COMONCOMPFLAGS=-Ofast
SIMDCOMPFLAGS=-msse2 -DHAVE_SSE2
DSFMTVAR=-DSFMT_MEXP=2281


SFMTCOMPSTR=COMPFLAGS='$COMPFLAGS $(COMONCOMPFLAGS) $(SIMDCOMPFLAGS)' $(DSFMTVAR)
NONSFMTCOMPTSTR=COMPFLAGS='$COMPFLAGS $(COMONCOMPFLAGS)'


SFMTFILE=$(SMFTDir)/SFMT.c
ROTATIONFILE=$(CDir)/utility_functions.c $(CDir)/healpix_functions.c $(CDir)/rotation_grid.c
INCLUDEPATH=-I$(CDir) -I$(SMFTDir)
OUTPATH=-outdir $(MEXOUTDIR)


#Rules
compile : 	applyRotation \
			generateUniformlyRandomRotations \
			generateUniformRotationSequencePoint


applyRotation : 
	$(MEX) $(MATLABFAGS) $(SFMTCOMPSTR) $(OUTPATH) $(INCLUDEPATH) $(MEXDir)/applyRotation.c $(ROTATIONFILE) $(SFMTFILE) 

generateUniformlyRandomRotations : 
	$(MEX) $(MATLABFAGS) $(SFMTCOMPSTR) $(OUTPATH) $(INCLUDEPATH) $(MEXDir)/generateUniformlyRandomRotations.c $(ROTATIONFILE) $(SFMTFILE)
	
generateUniformRotationSequencePoint : 
	$(MEX) $(MATLABFAGS) $(SFMTCOMPSTR) $(OUTPATH) $(INCLUDEPATH) $(MEXDir)/generateUniformRotationSequencePoint.c $(ROTATIONFILE) $(SFMTFILE)
