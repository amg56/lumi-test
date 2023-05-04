AMREX_HOME ?= ../amrex

DEBUG	= FALSE
#DEBUG	= TRUE

DIM	= 3

COMP    = llvm

USE_MPI   = TRUE
USE_OMP   = FALSE
USE_CUDA  = FALSE
USE_HIP   = TRUE

BL_NO_FORT = TRUE

NO_MPI_CHECKING = TRUE

TINY_PROFILE = TRUE

EBASE = gpu_test

include $(AMREX_HOME)/Tools/GNUMake/Make.defs

CEXE_sources += main.cpp

include $(AMREX_HOME)/Src/Base/Make.package

include $(AMREX_HOME)/Tools/GNUMake/Make.rules
