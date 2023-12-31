#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "parallel.h"

#define TRUE 1
#define FALSE 0


const unsigned char VERBOSE_COMM = TRUE;


void communicate_left(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank % proc_rows == 0)
        return;

    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank-1);

    MPI_Isend(edges->left, grid_width, MPI_CHAR, rank - 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(grid->left, grid_width, MPI_CHAR, rank - 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_right(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank % proc_rows == proc_rows - 1)
        return;

    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank+1);

    MPI_Isend(edges->right, grid_width, MPI_CHAR, rank + 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(grid->right, grid_width, MPI_CHAR, rank + 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_above(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == 0)
        return;

    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank-proc_rows);

    MPI_Isend(edges->top, grid_width, MPI_CHAR, rank - proc_rows, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(grid->top, grid_width, MPI_CHAR, rank - proc_rows, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_below(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == proc_rows - 1)
        return;
    
    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank+proc_rows);

    MPI_Isend(edges->bottom, grid_width, MPI_CHAR, rank + proc_rows, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(grid->bottom, grid_width, MPI_CHAR, rank + proc_rows, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_upper_left(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == 0 || rank % proc_rows == 0)
        return;
    
    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank-proc_rows-1);
    MPI_Isend(&edges->topL, 1, MPI_CHAR, rank - proc_rows - 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(&grid->topL, 1, MPI_CHAR, rank - proc_rows - 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_upper_right(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == 0 || rank % proc_rows == proc_rows - 1)
        return;
    
    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank-proc_rows+1);
    MPI_Isend(&edges->topR, 1, MPI_CHAR, rank - proc_rows + 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(&grid->topR, 1, MPI_CHAR, rank - proc_rows + 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_lower_right(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == proc_rows - 1 || rank % proc_rows == proc_rows - 1)
        return;
    
    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank+proc_rows+1);
    MPI_Isend(&edges->botR, 1, MPI_CHAR, rank + proc_rows + 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(&grid->botR, 1, MPI_CHAR, rank + proc_rows + 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_lower_left(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    int proc_rows = (int) sqrt(num_procs);

    if (rank / proc_rows == proc_rows - 1 || rank % proc_rows == 0)
        return;
    
    MPI_Request send_rqst, recv_rqst;
    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, rank+proc_rows-1);
    MPI_Isend(&edges->botL, 1, MPI_CHAR, rank + proc_rows - 1, tag, MPI_COMM_WORLD, &send_rqst);
    MPI_Irecv(&grid->botL, 1, MPI_CHAR, rank + proc_rows - 1, tag, MPI_COMM_WORLD, &recv_rqst);

    MPI_Wait(&send_rqst, MPI_STATUS_IGNORE);
    MPI_Wait(&recv_rqst, MPI_STATUS_IGNORE);
}


void communicate_edges(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    communicate_left(grid, grid_width, edges, rank, num_procs);
    communicate_right(grid, grid_width, edges, rank, num_procs);
    communicate_above(grid, grid_width, edges, rank, num_procs);
    communicate_below(grid, grid_width, edges, rank, num_procs);

    communicate_upper_left(grid, grid_width, edges, rank, num_procs);
    communicate_upper_right(grid, grid_width, edges, rank, num_procs);
    communicate_lower_right(grid, grid_width, edges, rank, num_procs);
    communicate_lower_left(grid, grid_width, edges, rank, num_procs);
}


int get_left_proc_circular(int rank, int proc_rows) {
    if (rank % proc_rows == 0)
        return rank + proc_rows - 1;
    else
        return rank - 1;
}


int get_right_proc_circular(int rank, int proc_rows) {
    if (rank % proc_rows == proc_rows - 1)
        return rank - proc_rows + 1;
    else
        return rank + 1;
}


int get_above_proc_circular(int rank, int proc_rows) {
    if (rank / proc_rows == 0)
        return rank + proc_rows * (proc_rows - 1);
    else
        return rank - proc_rows;
}


int get_below_proc_circular(int rank, int proc_rows) {
    if (rank / proc_rows == proc_rows - 1)
        return rank - proc_rows * (proc_rows - 1);
    else
        return rank + proc_rows;
}


int get_upper_left_proc_circular(int rank, int proc_rows) {
    int upper_left = rank;

    if (rank % proc_rows == 0)
        upper_left += proc_rows - 1;
    else
        upper_left -= 1;

    if (rank / proc_rows == 0)
        upper_left += proc_rows * (proc_rows - 1);
    else
        upper_left -= proc_rows;

    return upper_left;
}


int get_upper_right_proc_circular(int rank, int proc_rows) {
    int upper_right = rank;

    if (rank % proc_rows == proc_rows - 1)
        upper_right -= (proc_rows - 1);
    else
        upper_right += 1;

    if (rank / proc_rows == 0)
        upper_right += proc_rows * (proc_rows - 1);
    else
        upper_right -= proc_rows;

    return upper_right;
}


int get_lower_right_proc_circular(int rank, int proc_rows) {
    int lower_right = rank;

    if (rank % proc_rows == proc_rows - 1)
        lower_right -= (proc_rows - 1);
    else
        lower_right += 1;

    if (rank / proc_rows == proc_rows - 1)
        lower_right -= proc_rows * (proc_rows - 1);
    else
        lower_right += proc_rows;

    return lower_right;
}


int get_lower_left_proc_circular(int rank, int proc_rows) {
    int lower_left = rank;

    if (rank % proc_rows == 0)
        lower_left += (proc_rows - 1);
    else
        lower_left -= 1;

    if (rank / proc_rows == proc_rows - 1)
        lower_left -= proc_rows * (proc_rows - 1);
    else
        lower_left += proc_rows;

    return lower_left;
}


void communicate_left_circular(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    unsigned left_proc = get_left_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, left_proc);

    MPI_Isend(edges->left, grid_width, MPI_CHAR, left_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(grid->left, grid_width, MPI_CHAR, left_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_right_circular(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    unsigned right_proc = get_right_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, right_proc);

    MPI_Isend(edges->right, grid_width, MPI_CHAR, right_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(grid->right, grid_width, MPI_CHAR, right_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_above_circular(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    unsigned above_proc = get_above_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, above_proc);

    MPI_Isend(edges->top, grid_width, MPI_CHAR, above_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(grid->top, grid_width, MPI_CHAR, above_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_below_circular(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    unsigned below_proc = get_below_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, below_proc);
    
    MPI_Isend(edges->bottom, grid_width, MPI_CHAR, below_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(grid->bottom, grid_width, MPI_CHAR, below_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_upper_left_toroidal(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    int upper_left_proc = get_upper_left_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, upper_left_proc);

    MPI_Isend(&edges->topL, 1, MPI_CHAR, upper_left_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(&grid->topL, 1, MPI_CHAR, upper_left_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_upper_right_toroidal(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    int upper_right_proc = get_upper_right_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, upper_right_proc);

    MPI_Isend(&edges->topR, 1, MPI_CHAR, upper_right_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(&grid->topR, 1, MPI_CHAR, upper_right_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_lower_right_toroidal(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    int lower_right_proc = get_lower_right_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, lower_right_proc);

    MPI_Isend(&edges->botR, 1, MPI_CHAR, lower_right_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(&grid->botR, 1, MPI_CHAR, lower_right_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_lower_left_toroidal(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs, MPI_Request* send_rqst, MPI_Request* recv_rqst) {
    int proc_rows = (int) sqrt(num_procs);
    int lower_left_proc = get_lower_left_proc_circular(rank, proc_rows);

    int tag = 1234;

    if (VERBOSE_COMM)
        printf("Sending and receiving from proc %d to proc %d...\n", rank, lower_left_proc);

    MPI_Isend(&edges->botL, 1, MPI_CHAR, lower_left_proc, tag, MPI_COMM_WORLD, send_rqst);
    MPI_Irecv(&grid->botL, 1, MPI_CHAR, lower_left_proc, tag, MPI_COMM_WORLD, recv_rqst);
}


void communicate_edges_toroidal(struct AugmentedDomain* grid, unsigned long grid_width, struct DomainEdges* edges, int rank, unsigned num_procs) {
    MPI_Request* requests = malloc(16*sizeof(MPI_Request));
    MPI_Status* statuses = malloc(16*sizeof(MPI_Status));

    communicate_left_circular(grid, grid_width, edges, rank, num_procs, &requests[0], &requests[1]);
    communicate_right_circular(grid, grid_width, edges, rank, num_procs, &requests[2], &requests[3]);
    communicate_above_circular(grid, grid_width, edges, rank, num_procs, &requests[4], &requests[5]);
    communicate_below_circular(grid, grid_width, edges, rank, num_procs, &requests[6], &requests[7]);

    communicate_upper_left_toroidal(grid, grid_width, edges, rank, num_procs, &requests[8], &requests[9]);
    communicate_upper_right_toroidal(grid, grid_width, edges, rank, num_procs, &requests[10], &requests[11]);
    communicate_lower_right_toroidal(grid, grid_width, edges, rank, num_procs, &requests[12], &requests[13]);
    communicate_lower_left_toroidal(grid, grid_width, edges, rank, num_procs, &requests[14], &requests[15]);

    MPI_Waitall(16, requests, statuses);

    free(requests);
    free(statuses);
}
