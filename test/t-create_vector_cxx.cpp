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

#include <petsc_cxx/petsc_cxx>

using namespace petsc_cxx;

int main(int ac, char** av)
{
    Parser parser(ac, av, "How to create a vector.");
    Context context(parser);

    PetscMPIInt rank,size;

    MPI_Comm_size( PETSC_COMM_WORLD, &size );
    MPI_Comm_rank( PETSC_COMM_WORLD, &rank );

    PetscPrintf(PETSC_COMM_SELF, "Number of processors = %d, rank = %d\n", size, rank);

    const Int n = 20;

    Vector< Scalar > x(n, 2);
    Vector< Scalar > y(n, 2);

    std::cout << x << y;

    Vector< Scalar > w = x * y;

    std::cout << w;

    return 0;
}
