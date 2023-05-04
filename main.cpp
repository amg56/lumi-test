
#include <AMReX.H>
#include <AMReX_Geometry.H>
#include <AMReX_MultiFabUtil.H>
#include <AMReX_Print.H>

using namespace amrex;

int main(int argc, char* argv[])
{
    Initialize(argc,argv);
    {
        //create Geometry, BoxArray with 16 boxes, and DistributionMapping
        int n_cell = 64;

        Box domain(IntVect{AMREX_D_DECL(       0,        0,        0)},
                IntVect{AMREX_D_DECL(2*n_cell-1, n_cell-1, n_cell-1)});
        RealBox real_box({AMREX_D_DECL(-2.0,-1.0,-1.0)},
                        {AMREX_D_DECL( 2.0, 1.0, 1.0)});
        int coord = 0;
        Array<int,AMREX_SPACEDIM> is_periodic {AMREX_D_DECL(1,1,1)};
        Geometry geom(domain, real_box, coord, is_periodic);

        BoxArray ba(domain);
        ba.maxSize(n_cell/2);
        Print() << "\nSetting up " << ba.size() << " boxes with " << ba.numPts() << " total cells\n\n";

        //create dm
        DistributionMapping dm {ba};

        //create & initialise multifabs - 1 with ghost cells
        MultiFab mfa(ba, dm, 1, 1);
        mfa.setVal(1.0);
        MultiFab mfb(ba, dm, 1, 0);
        mfb.setVal(2.0);

        //Start MPI communication to fill the ghost cells
        Print() << "Starting MPI communication...\n\n";
        mfa.FillBoundary_nowait(geom.periodicity());

        //intermediate work
        mfb.setVal(3.0);
        Print() << "MultiFab 'mfb' set to " << mfb.max(0) << "\n\n";

        Print() << "Finishing MPI communication...\n";
        mfa.FillBoundary_finish();
        Print() << "MPI Communication finished!\n\n";
    }
    Finalize();
}

