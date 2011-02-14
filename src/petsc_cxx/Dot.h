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

#ifndef _petsc_cxx_Dot_h
#define _petsc_cxx_Dot_h

#include "BO.h"
#include "Vector.h"

namespace petsc_cxx
{
    template < typename Atom >
    class Dot : public BO< Vector< Atom >, Vector< Atom >, Atom >
    {
    public:
	void operator()( const Vector< Atom >& a, const Vector< Atom >& b, Atom& dot )
	{
	    // TODO
	}
    };
}

#endif // !_petsc_cxx_Dot_h
