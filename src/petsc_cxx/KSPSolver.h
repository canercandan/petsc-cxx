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

#ifndef _petsc_cxx_KSPSolver_h
#define _petsc_cxx_KSPSolver_h

#include <petscksp.h>

#include <core_library/Printable.h>
#include <core_library/BO.h>

#include "Matrix.h"
#include "Vector.h"

namespace petsc_cxx
{

    template < typename Atom >
    class KSPSolver : public core_library::BO< Matrix< Atom >, Vector< Atom >, Vector< Atom > >, public core_library::Printable
    {
    public:
	KSPSolver( MPI_Comm comm = PETSC_COMM_WORLD, MatStructure flag = DIFFERENT_NONZERO_PATTERN )
	    : _flag( flag )
	    {
		KSPCreate( comm, &_solver );
		//KSPSetTolerences( _solver, 1.e-7, PETSC_DEFAULT, PETSC_DEFAULT, PETSC_DEFAULT );
		KSPSetFromOptions( _solver );
	    }

	~KSPSolver() { KSPDestroy( _solver ); }

	virtual void operator()( const Matrix< Atom >& A, const Vector< Atom >& x, Vector< Atom >& b )
	{
	    if ( b.size() != x.size() ) { b.resize( x.size() ); }
	    KSPSetOperators( _solver, A, A, _flag );
	    KSPSolve( _solver, x, b );
	}

	operator KSP() const { return _solver; }

	void printOn(std::ostream&) const
	{
	    KSPView( _solver, PETSC_VIEWER_STDOUT_WORLD );
	}

    private:
	KSP _solver;
	MatStructure _flag;
    };

}

#endif // !_petsc_cxx_KSPSolver_h
