// -*- mode: c++; c-indent-level: 4; c++-member-init-indent: 8; comment-column: 35; -*-

//-----------------------------------------------------------------------------
// Functor.h
// (c) Maarten Keijzer 2000
/* 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Contact: todos@geneura.ugr.es, http://geneura.ugr.es
             mak@dhi.dk
    CVS Info: $Date: 2004-12-01 09:22:48 $ $Header: /home/nojhan/dev/eodev/eodev_cvs/eo/src/Functor.h,v 1.7 2004-12-01 09:22:48 evomarc Exp $ $Author: evomarc $ 
 */
//-----------------------------------------------------------------------------

#ifndef _Functor_h
#define _Functor_h

#include <functional>

namespace petsc_cxx
{

    /** @addtogroup Core
     * @{
     */

    /** Base class for functors to get a nice hierarchy diagram

	That's actually quite an understatement as it does quite a bit more than
	just that. By having all functors derive from the same base class, we can
	do some memory management that would otherwise be very hard.

	The memory management base class is called FunctorStore, and it supports
	a member add() to add a pointer to a functor. When the functorStore is
	destroyed, it will delete all those pointers. So beware: do not delete
	the functorStore before you are done with anything that might have been allocated.

	@see FunctorStore

    */
    class FunctorBase
    {
    public :
	/// virtual dtor here so there is no need to define it in derived classes
	virtual ~FunctorBase() {}

	/// tag to identify a procedure in compile time function selection @see functor_category
	struct procedure_tag {};
	/// tag to identify a unary function in compile time function selection @see functor_category
	struct unary_function_tag {};
	/// tag to identify a binary function in compile time function selection @see functor_category
	struct binary_function_tag {};
    };
    /** @example t-Functor.cpp
     */

    /**
       Basic Function. Derive from this class when defining
       any procedure. It defines a result_type that can be used
       to determine the return type
       Argument and result types can be any type including void for
       result_type
    **/
    template <class R>
    class F : public FunctorBase
    {
    public :

	/// virtual dtor here so there is no need to define it in derived classes
	virtual ~F() {}

	/// the return type - probably useless ....
	typedef R result_type;

	/// The pure virtual function that needs to be implemented by the subclass
	virtual R operator()() = 0;

	/// tag to identify a procedure in compile time function selection @see functor_category
	static FunctorBase::procedure_tag functor_category()
	{
	    return FunctorBase::procedure_tag();
	}
    };

    /**
       Overloaded function that can help in the compile time detection 
       of the type of functor we are dealing with

       @see Counter, make_counter
    */
    template<class R>
    FunctorBase::procedure_tag functor_category(const F<R>&)
    {
	return FunctorBase::procedure_tag();
    }

    /** 
	Basic Unary Functor. Derive from this class when defining 
	any unary function. First template argument is the first_argument_type,
	second result_type.
	Argument and result types can be any type including void for
	result_type
    **/
    template <class A1, class R>
    class UF : public FunctorBase, public std::unary_function<A1, R>
    {
    public :

	/// virtual dtor here so there is no need to define it in derived classes
	virtual ~UF() {}

	/// The pure virtual function that needs to be implemented by the subclass
	virtual R operator()(A1) = 0;

	/// tag to identify a procedure in compile time function selection @see functor_category
	static FunctorBase::unary_function_tag functor_category()
	{
	    return FunctorBase::unary_function_tag();
	}
    };

    /**
       Overloaded function that can help in the compile time detection 
       of the type of functor we are dealing with
       @see Counter, make_counter
    */
    template<class R, class A1>
    FunctorBase::unary_function_tag functor_category(const UF<A1, R>&)
    {
	return FunctorBase::unary_function_tag();
    }


    /** 
	Basic Binary Functor. Derive from this class when defining 
	any binary function. First template argument is result_type, second
	is first_argument_type, third is second_argument_type.
	Argument and result types can be any type including void for
	result_type
    **/
    template <class A1, class A2, class R>
    class BF : public FunctorBase, public std::binary_function<A1, A2, R>
    {
    public :
        /// virtual dtor here so there is no need to define it in derived classes
	virtual ~BF() {}
    
	//typedef R result_type;
	//typedef A1 first_argument_type;
	//typedef A2 second_argument_type;

	/// The pure virtual function that needs to be implemented by the subclass
	virtual R operator()(A1, A2) = 0;

	/// tag to identify a procedure in compile time function selection @see functor_category
	static FunctorBase::binary_function_tag functor_category()
	{
	    return FunctorBase::binary_function_tag();
	}
    };

    /**
       Overloaded function that can help in the compile time detection 
       of the type of functor we are dealing with
       @see Counter, make_counter
    */
    template<class R, class A1, class A2>
    FunctorBase::binary_function_tag functor_category(const BF<A1, A2, R>&)
    {
	return FunctorBase::binary_function_tag();
    }

}

/** @} */

#endif
