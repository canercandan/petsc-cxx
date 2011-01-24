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

#include "Object.h"
#include "Printable.h"
#include "Vector.h"

static char help[] = "How to create a vector.\n\n";

using namespace Petsc;

int main(int ac, char** av)
{
    PetscInitialize(&ac, &av, (char*)0, help);

    PetscMPIInt rank,size;

    MPI_Comm_size( PETSC_COMM_WORLD, &size );
    MPI_Comm_rank( PETSC_COMM_WORLD, &rank );

    PetscPrintf(PETSC_COMM_SELF, "Number of processors = %d, rank = %d\n", size, rank);

    {
	const Int n = 20;

	Vector< Scalar > w(n), x(n, 2), y(n, 2);

	std::cout << x << y << std::endl;

	w = x * y;

	std::cout << w << std::endl;
    }

    PetscFinalize();

    return 0;
}
