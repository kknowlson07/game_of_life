#ifndef MPI_LIFE_HPP
#define MPI_LIFE_HPP


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>
#include <math.h>
#include <omp.h>

// Return process in process-row 'row' and
// process-column 'col'
int get_proc(int row, int col, int sq_procs);

// Performs local (serial) update
void update(unsigned long  dim, char* A, char* B);

// Performs local (serial) update
void updateInner(unsigned long dim, char* A, char* B);

// Performs local (serial) update
void updateOuter(unsigned long dim, char* A, char* B);

// Allocate a char array wth padded bording, dim is an unpadded dimension
// therefore total size of array is (dim+2) * (dim + 2)
char* init_grid(unsigned long dim);

// mallocs a char array with border padding
// total size = (dim + 2) * (dim + 2)
char* agar(unsigned long dim);

// generates a random filled grid
char* rand_grid(unsigned long dim);

// print the given char* grid, provided the unpadded dimension
void print_grid(unsigned long dim, char *grid);

// swaps the pointers of 2 char arrays
void swap(char **A, char **B);

// naive test provided initial grid A, grid B of same size, dimension of partition
void mpi_naive(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

// openmp test provided initial grid A, grid B of same size, dimension of partition
void openmp_naive(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

// concurrency test provided initial grid A, grid B of same size, dimension of partition
void concurrency_naive(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

// concurrency test provided initial grid A, grid B of same size, dimension of partition with TESTALL included
void concurrency_naive_testall(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

// concurrency with openmp
void concurrency_openmp_naive(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

// updates grid with openmp threaded assistance
void updateThreads(unsigned long dim, char* A, char* B);

void updateInnerThread(unsigned long dim, char* A, char* B);

void updateOuterThread(unsigned long dim, char* A, char* B);

void mpi_naive_calc(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

void mpi_naive_comm(char* A, char* B, unsigned long dim, int sq_num_procs, int rank_row, int rank_col, int ticks, int rank);

#endif
