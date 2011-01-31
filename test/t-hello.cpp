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

#include <petscsys.h>

static char help[] = "Introductory example that illustrates printing.\n\n";

int main(int ac, char** av)
{
    PetscMPIInt    rank,size;

    PetscInitialize(&ac, &av, (char *)0, help);

    MPI_Comm_size(PETSC_COMM_WORLD,&size);
    MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

    PetscPrintf(PETSC_COMM_WORLD,"Number of processors = %d, rank = %d\n",size,rank);

    MPI_Barrier(PETSC_COMM_WORLD);

    PetscPrintf(PETSC_COMM_SELF,"[%d] Jumbled Hello World\n",rank);

    PetscFinalize();

    return 0;
}
