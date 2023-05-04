Simple test case for AMReX MPI

This is a simple example of an AMReX MPI call that stalls on LUMI when trying to use GPU-aware MPI.

The code requires AMReX, which can be downloaded from https://github.com/AMReX-Codes/amrex.

To build AMReX and the example on LUMI, the Make.local file should be placed in the amrex_dir/Tools/GNUMake folder.  AMReX assumes you will use hipcc to compile for hip but doesn't specify this directly, so this Make.local files sets that.  It also sets the environment variable AMREX_AMD_ARCH to gfx90a so AMReX knows that it should compile for the MI250X GPUs on LUMI.

To use hipcc to compile on LUMI, the following modules/flags should be set:

module load craype-x86-trento
module load PrgEnv-amd
module load craype-accel-amd-gfx90a
export HIPCC_COMPILE_FLAGS_APPEND=$(CC --cray-print-opts=cflags)
export HIPCC_LINK_FLAGS_APPEND=$(CC --cray-print-opts=libs)


The makefile will also need to be edited to point to the location of the folder where AMReX was downloaded.  Once this is done, the example should build with 'make'.

Once compiled, the example can be run with the provided submission script 'runltest.sh'.

At time of writing, the test is expected to hang after printing 'Starting MPI communication...', due to a bug in libfabric.