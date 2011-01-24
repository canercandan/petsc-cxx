#ifdef _MSC_VER
// to avoid long name warnings
#pragma warning(disable:4786)
#endif 

//-----------------------------------------------------------------------------
// Printable.cpp
//-----------------------------------------------------------------------------

#include <Printable.h>

namespace Petsc
{

    //-----------------------------------------------------------------------------
    //Implementation of these objects
    //-----------------------------------------------------------------------------

    std::ostream & operator << ( std::ostream& _os, const Printable& _o ) {
	_o.printOn(_os);
	return _os;
    }

    //-----------------------------------------------------------------------------

}
