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

	static void Destroy(Vec& vec) { VecDestroy( vec ); }

	Vector(Int size = 0) : _vector( Create(size) ) {}

	Vector(Int size, Int value) : _vector( Create(size) )
	{
	    if ( size == 0 ) { return; }

	    for ( Int i = 0; i < size; ++i )
	    	{
		    insert( i, value );
	    	}
	}

	Vector( Vec& vector ) : _vector( vector ) {}

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
	    VecGetValues( _vector, row, &i, &ret );
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

	    std::cout << "size: " << s << std::endl;

	    if ( s <= 0 ) { return; }

	    // std::cout << "[ ";
	    // std::cout << (Atom)(*this)[0];
	    // for ( Int i = 1; i < s; ++i )
	    // 	{
	    // 	    std::cout << ", " << (*this)[i];
	    // 	}
	    // std::cout << " ]" << std::endl;

	    VecView( _vector, PETSC_VIEWER_STDOUT_WORLD );
	}

	std::string className() const { return "Vector"; }

	operator Vec() { return _vector; }

    private:
	Vec _vector;
    };

    template < typename Atom >
    Vector< Atom > operator*( Vector< Atom >& a, Vector< Atom >& b )
    {
	Vector< Atom > c( a.size() );
	VecPointwiseMult( c, a, b );
	return c;
    }
}

#endif // !_Vector_h
