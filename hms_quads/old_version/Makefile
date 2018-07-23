#--------------------------------------------------------------------------
# Makefile for `field', and effective length programs
#
# 22FEb1999 DWM -- Use `f77' rather than `g77' on the cdaq machines.
# 20Jan1999 DWM -- works on linux, but there is nothing special here.
#--------------------------------------------------------------------------

OBJ = field99.o params.o

FC = f77

FFLAGS = 

all : field99

field99 : ${OBJ}
	${FC} ${FFLAGS} ${OBJ} -o $@ 

clean : 
	rm -f *.o
	rm -f field
	rm -f *~

