
#
#  C preprocessor definitions:  set CDEFS to one of the following:
#
#     -DNoChange (fortran subprogram names are lower case without any suffix)
#     -DUpCase   (fortran subprogram names are upper case without any suffix)
#     -DAdd_     (fortran subprogram names are lower case with "_" appended)

CDEFS         = -DAdd_

#
#  The fortran and C compilers, loaders, and their flags
#

FC            = gfortran
CC            = gcc
NOOPT         = -O0
FCFLAGS       = -O2 -lmsmpi 
CCFLAGS       = -O2 -lmsmpi
SRCFLAG       =
FCLOADER      = $(FC)
CCLOADER      = $(CC)
FCLOADFLAGS   = 
CCLOADFLAGS   =

#
#  The archiver and the flag(s) to use when building archive (library)
#  Also the ranlib routine.  If your system has no ranlib, set RANLIB = echo
#

ARCH          = ar
ARCHFLAGS     = cr
RANLIB        = echo

#
#  The name of the ScaLAPACK library to be created
#

SCALAPACKLIB  = libscalapack.a

#
#  BLAS, LAPACK (and possibly other) libraries needed for linking test programs
#

BLASLIB       = /mingw64/lib/libopenblas.a
LAPACKLIB     = /mingw64/lib/libopenblas.a
LIBS          = $(LAPACKLIB) $(BLASLIB)
        