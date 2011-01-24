#include <petscsys.h>

static char help[] = "Synchronized printing.\n\n";

int main(int ac, char** av)
{
    PetscMPIInt rank, size;

    PetscInitialize(&ac, &av, (char *)0, help);

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    PetscPrintf(PETSC_COMM_WORLD,"Number of processors = %d, rank = %d\n",size,rank);

    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] Synchronized Hello World.\n",rank);
    PetscSynchronizedPrintf(PETSC_COMM_WORLD,"[%d] Synchronized Hello World - Part II.\n",rank);
    PetscSynchronizedFlush(PETSC_COMM_WORLD);

    MPI_Barrier(PETSC_COMM_WORLD);

    PetscPrintf(PETSC_COMM_SELF,"[%d] Jumbled Hello World\n",rank);

    PetscFinalize();

    return 0;
}
