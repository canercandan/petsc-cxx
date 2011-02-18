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

#ifndef _petsc_cxx_Multiply_h
#define _petsc_cxx_Multiply_h

#include "core_library/ConstBF.h"

#include "Matrix.h"
#include "Vector.h"

namespace petsc_cxx
{

    /* here's the matrix-matrix multiplication resulting to a new matrix */
    template < typename Atom >
    class MultiplyMatrix : public core_library::ConstBF< Matrix< Atom >, Matrix< Atom >, Matrix< Atom > >
    {
    public:
	Matrix< Atom > operator()( const Matrix< Atom >& a, const Matrix< Atom >& b) const { return a * b; }
    };

    /* here's the matrix-vector multiplication resulting to a new vector */
    template < typename Atom >
    class MultiplyMatrixVector : public core_library::ConstBF< Matrix< Atom >, Vector< Atom >, Vector< Atom > >
    {
    public:
	Vector< Atom > operator()( const Matrix< Atom >& a, const Vector< Atom >& b) const { return a * b; }
    };

}

#endif // !_petsc_cxx_Multiply_h
