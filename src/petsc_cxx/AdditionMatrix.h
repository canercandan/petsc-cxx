// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

/* This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 * Caner Candan <caner@candan.fr>, http://caner.candan.fr
 */

#ifndef _petsc_cxx_AdditionMatrix_h
#define _petsc_cxx_AdditionMatrix_h

#include "core_library/BO.h"

#include "Matrix.h"

namespace petsc_cxx
{
    template < typename Atom >
    class AdditionMatrix : public core_library::BO< Matrix< Atom >, Matrix< Atom >, Matrix< Atom > >
    {
    public:
	void operator()( const Matrix< Atom >& A, const Matrix< Atom >& B, Matrix< Atom >& C )
	{
	    // TODO
	}
    };
}

#endif // !_petsc_cxx_AdditionMatrix_h
