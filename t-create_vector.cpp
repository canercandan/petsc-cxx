// file:///usr/share/doc/petsc3.1-doc/src/vec/vec/examples/tutorials/ex1.c.html

#include <petscsys.h>
#include <petscvec.h>

static char help[] = "How to create a vector.\n\n";

int main(int ac, char** av)
{
    PetscInitialize(&ac, &av, (char*)0, help);

    PetscMPIInt rank,size;

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    PetscPrintf(PETSC_COMM_SELF, "Number of processors = %d, rank = %d\n", size, rank);

    Vec w, x, y;

    PetscInt n = 20;

    VecCreate( PETSC_COMM_WORLD, &x );
    VecSetSizes( x, PETSC_DECIDE, n );
    VecSetFromOptions(x);

    VecDuplicate( x, &y );
    VecDuplicate( x, &w );

    PetscScalar one = 1.0, two = 2.0;

    for ( PetscInt i = 0; i < n; i++)
	{
	    VecSetValues( x, 1, &i, &one, ADD_VALUES );
	    VecSetValues( y, 1, &i, &two, ADD_VALUES );
	}

    VecPointwiseMult( w, y, x );

    VecView(w, PETSC_VIEWER_STDOUT_WORLD);

    VecDestroy(w);
    VecDestroy(x);
    VecDestroy(y);

    PetscFinalize();

    return 0;
}
