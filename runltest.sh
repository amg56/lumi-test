#!/bin/bash -l
#SBATCH --job-name=amr_lt   # Job name
#SBATCH --output=ltest.out # Name of stdout output file
#SBATCH --error=stderr.err  # Name of stderr error file
#SBATCH --partition=standard-g  # Partition (queue) name
#SBATCH --nodes=2              # Total number of nodes 
#SBATCH --ntasks-per-node=8     # 8 MPI ranks per node, 16 total (2x8)
#SBATCH --gpus-per-node=8       # Allocate one gpu per MPI rank
#SBATCH --time=0-00:01:00       # Run time (d-hh:mm:ss)
#SBATCH --account=  # Project for billing

cat << EOF > select_gpu
#!/bin/bash

export ROCR_VISIBLE_DEVICES=\$SLURM_LOCALID
exec \$*
EOF

chmod +x ./select_gpu

CPU_BIND="map_cpu:48,56,16,24,1,8,32,40"

export MPICH_GPU_SUPPORT_ENABLED=1
#export FI_MR_CACHE_MAX_COUNT=0

module load PrgEnv-amd
module load craype-accel-amd-gfx90a

srun --cpu-bind=${CPU_BIND} ./select_gpu ./gpu_test3d.hip.x86-trento.TPROF.MPI.HIP.ex amrex.use_gpu_aware_mpi=1 #amrex.the_arena_init_size=17179869184
rm -rf ./select_gpu

