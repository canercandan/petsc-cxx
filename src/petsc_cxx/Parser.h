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

#ifndef _petsc_cxx_Parser_h
#define _petsc_cxx_Parser_h

#include <string>

#include "AbstractParser.h"

namespace petsc_cxx
{
    class Parser : public AbstractParser
    {
    public:
	Parser(int& ac, char**& av, std::string help = "", char* file = 0);

	void create() const;
	void destroy() const;

	std::string className() const { return "Parser"; }

    private:
	int& _ac;
	char**& _av;
	std::string _help;
	char* _file;
    };

    class NoParser : public AbstractParser
    {
    public:
	void create() const;
	void destroy() const;

	std::string className() const { return "NoParser"; }
    };
}

#endif // !_petsc_cxx_Parser_h
