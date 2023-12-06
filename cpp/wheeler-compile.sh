module load gcc
module load openmpi

mpicxx -o output time_life.cpp mpi_life.cpp naive.cpp
#srun --partition=normal --nodes=8 --ntasks-per-node=8 --ntasks=64 ./output 4096 100