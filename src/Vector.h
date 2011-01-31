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

#ifndef _Vector_h
#define _Vector_h

#include <petscsys.h>
#include <petscvec.h>

#include "Object.h"
#include "Printable.h"
#include "Petsc.h"

namespace Petsc
{
    template < typename Atom >
    class Vector : public Object, public Printable
    {
    public:
	static Vec Create(Int size, MPI_Comm comm = PETSC_COMM_WORLD)
	{
	    Vec vec;
	    VecCreate( comm, &vec );
	    VecSetSizes( vec, PETSC_DECIDE, size );
	    VecSetFromOptions(vec);
	    return vec;
	}

	static void Destroy(const Vec& vec) { VecDestroy( vec ); }

	Vector(Int size = 0) : _vector( Create(size) ) {}

	Vector(Int size, Int value) : _vector( Create(size) )
	{
	    if ( size == 0 ) { return; }

	    for ( Int i = 0; i < size; ++i )
	    	{
		    insert( i, value );
	    	}
	}

	Vector( const Vec& vector ) : _vector( vector ) {}

	Vector( const Vector< Atom >& v ) { *this = v; }

	~Vector() { Destroy( _vector ); }

	Vector& operator=( const Vector< Atom >& v )
	{
	    Int size = this->size();

	    if ( size <= 0 ) { return *this; }

	    VecCopy(v._vector, _vector);
	    return *this;
	}

	Atom operator[]( Int row ) const
	{
	    Scalar ret;
	    Int i = row;
	    VecGetValues( _vector, 0, &i, &ret );
	    return (Atom)ret;
	}

	void add( const Atom& value ) { VecSetValue( _vector, 1, (Scalar)value, ADD_VALUES ); }
	void insert( Int row, const Atom& value ) { VecSetValue( _vector, row, (Scalar)value, INSERT_VALUES ); }

	Int size() const
	{
	    Int size = 0;
	    VecGetSize( _vector, &size );
	    return size;
	}

	void resize( Int size )
	{
	    VecSetSizes( _vector, PETSC_DECIDE, size );
	}

	void printOn( std::ostream& os ) const
	{
	    const Int s = size();

	    os << "size: " << s << std::endl;

	    if ( s <= 0 ) { return; }

	    VecAssemblyBegin(_vector);
	    VecAssemblyEnd(_vector);

	    VecView( _vector, PETSC_VIEWER_STDOUT_WORLD );
	}

	std::string className() const { return "Vector"; }

	operator Vec() const { return _vector; }

    private:
	Vec _vector;
    };

    template < typename Atom >
    Vector< Atom > operator*( const Vector< Atom >& a, const Vector< Atom >& b )
    {
	Vector< Atom > c( a.size() );
	VecPointwiseMult( c, a, b );
	return c;
    }
}

#endif // !_Vector_h
