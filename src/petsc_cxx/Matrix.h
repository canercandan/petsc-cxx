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

#ifndef _petsc_cxx_Matrix_h
#define _petsc_cxx_Matrix_h

#include <petscmat.h>

#include "Object.h"
#include "Printable.h"
#include "Petsc.h"
#include "Vector.h"

namespace petsc_cxx
{
    template < typename Atom >
    class Matrix : public Object, public Printable
    {
    public:
	static Mat Create(Int nrows, Int ncols, MPI_Comm comm = PETSC_COMM_WORLD)
	{
	    Mat mat;
	    MatCreate( comm, &mat );
	    MatSetSizes( mat, PETSC_DECIDE, PETSC_DECIDE, nrows, ncols );
	    MatSetFromOptions(mat);
	    return mat;
	}

	static void Destroy(const Mat& mat) { MatDestroy( mat ); }

	Matrix(Int size = 0) : _matrix( Create(size, size) ) {}

	Matrix(Int nrows, Int ncols) : _matrix( Create(nrows, ncols) ) {}

	Matrix(Int nrows, Int ncols, Int value) : _matrix( Create(nrows, ncols) )
	{
	    if ( nrows == 0 && ncols == 0 ) { return; }

	    for ( Int i = 0; i < nrows; ++i )
	    	{
		    for ( Int j = 0; j < ncols; ++j )
			{
			    insert( i, j, value );
			}
		}
	}

	Matrix( const Mat& matrix ) : _matrix( matrix ) {}

	Matrix( const Matrix< Atom >& v ) { *this = v; }

	~Matrix() { Destroy( _matrix ); }

	Matrix& operator=( const Matrix< Atom >& v )
	{
	    if ( nrows() <= 0 && ncols() <= 0 ) { return *this; }

	    MatCopy(v._matrix, _matrix, SAME_NONZERO_PATTERN);
	    return *this;
	}

	Scalar* operator[]( Int row ) const
	{
	    Int ncols;
	    const Int* cols;
	    const Scalar* ret;
	    MatGetRow( _matrix, row, &ncols, &cols, &ret );
	    return (Atom)ret;
	}

	// TODO:
	// Scalar operator()( Int row, Int col ) const
	// {
	//     Int ncols;
	//     const Int* cols;
	//     const Scalar* ret;
	//     MatGetValue( _matrix, row, &ncols, &cols, &ret );
	//     return (Atom)ret;
	// }

	void add( Int row, const Atom& value ) { MatSetValue( _matrix, row, 1, (Scalar)value, ADD_VALUES ); }
	void insert( Int row, Int col, const Atom& value ) { MatSetValue( _matrix, row, col, (Scalar)value, INSERT_VALUES ); }

	Int nrows() const
	{
	    Int nrows = 0;
	    Int ncols = 0;
	    MatGetSize( _matrix, &nrows, &ncols );
	    return nrows;
	}

	Int ncols() const
	{
	    Int nrows = 0;
	    Int ncols = 0;
	    MatGetSize( _matrix, &nrows, &ncols );
	    return ncols;
	}

	void resize( Int nrows, Int ncols )
	{
	    MatSetSizes( _matrix, PETSC_DECIDE, PETSC_DECIDE, nrows, ncols );
	}

	void printOn( std::ostream& os ) const
	{
	    const Int nr = nrows();
	    const Int nc = ncols();

	    os << "size: " << nr << "x" << nc << std::endl;

	    if ( nr <= 0 && nc <= 0 ) { return; }

	    MatAssemblyBegin(_matrix, MAT_FINAL_ASSEMBLY);
	    MatAssemblyEnd(_matrix, MAT_FINAL_ASSEMBLY);

	    MatView( _matrix, PETSC_VIEWER_STDOUT_WORLD );
	}

	std::string className() const { return "Matrix"; }

	operator Mat() const { return _matrix; }

	template < typename T > friend Matrix< T > operator*( const Matrix< T >& A, const Matrix< T >& B );

	Matrix< Atom >& operator*=( const Matrix< Atom >& A )
	{
	    MatMatMult( _matrix, A, MAT_INITIAL_MATRIX, 1., &_matrix );
	    return *this;
	}

    private:
	Mat _matrix;
    };

    template < typename Atom >
    Matrix< Atom > operator*( const Matrix< Atom >& A, const Matrix< Atom >& B )
    {
	Matrix< Atom > C( A.nrows(), A.ncols() );
	MatMatMult( A, B, MAT_INITIAL_MATRIX, 1., &(C._matrix) );
	return C;
    }

    template < typename Atom >
    Vector< Atom > operator*( const Matrix< Atom >& A, const Vector< Atom >& x )
    {
	Vector< Atom > y( x.size() );
	MatMult( A, x, y );
	return y;
    }
}

#endif // !_petsc_cxx_Matrix_h
