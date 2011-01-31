// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Authors: Caner Candan <caner@candan.fr>, http://caner.candan.fr
 */

// file:///usr/share/doc/petsc3.1-doc/src/vec/vec/examples/tutorials/ex1.c.html

#include <iostream>

#include <petscsys.h>
#include <petscvec.h>

static char help[] = "How to create a vector.\n\n";

Vec create_vector(int n)
{
    Vec x;
    VecCreate( PETSC_COMM_WORLD, &x );
    VecSetSizes( x, PETSC_DECIDE, n );
    VecSetFromOptions(x);
    return x;
}

void routine()
{
    PetscInt size = 0;

    Vec w, x, y;

    PetscInt n = 20;

    x = create_vector(n);

    // VecCreate( PETSC_COMM_WORLD, &x );
    // VecSetSizes( x, PETSC_DECIDE, n );
    // VecSetFromOptions(x);

    VecDuplicate( x, &y );
    VecDuplicate( x, &w );

    VecGetSize(x, &size);
    std::cout << size << std::endl;

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
}

int main(int ac, char** av)
{
    PetscInitialize(&ac, &av, (char*)0, help);

    PetscMPIInt rank,size;

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    PetscPrintf(PETSC_COMM_SELF, "Number of processors = %d, rank = %d\n", size, rank);

    routine();

    PetscFinalize();

    return 0;
}
