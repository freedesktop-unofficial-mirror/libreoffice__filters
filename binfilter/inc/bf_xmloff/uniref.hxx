/*************************************************************************
 *
 *  $RCSfile: uniref.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: jmeng $ $Date: 2003-12-04 01:45:45 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#ifndef _UNIVERSALL_REFERENCE_HXX
#define _UNIVERSALL_REFERENCE_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
#ifndef _OSL_INTERLOCK_H_
#include <osl/interlck.h>
#endif
namespace binfilter {

/**
 * An instance of this class holds a pointer to an object. The lifetime of 
 * the object is controled by the instance. The constructor calls
 * acquire() and the destructor calls release().
 * You could delive your class from the baseclass UniRefBase wich implements
 * the methods acquire and release, yet.
 */
template< class T > class UniReference
{
private:
    T*	mpElement;

public:
    /** Create an empty reference.*/
    UniReference()
    : mpElement( NULL )
    {}

    /** Destroy the reference and releases the element.*/
    inline ~UniReference();

    /** Create a new reference with the same element as in rRef and acquire this one.*/
    inline UniReference( const UniReference< T > & rRef );

    /** 
     * Create a new reference with the given element pElement and acquire this one.
     */
    inline UniReference( T * pElement );

    /**
     * Release the reference and set the new one pObj.
     */
    inline UniReference< T > & operator = ( T * pElement );

    /**
     * Release the reference and set the new one from rObj.
     */
    inline UniReference< T > & operator = ( const UniReference< T > & rRef );

    /**
     * Return the pointer to the element, may be null.
     */
    inline T* operator -> () const;

    /**
     * Returns true if the pointer to the element is valid.
     */
    inline sal_Bool is() const;

    /**
     * Return true if both elements refer to the same object.
     */
    inline sal_Bool operator == ( const UniReference & rRef ) const;

    /**
     * Return true if both elements does not refer to the same object.
     */
    inline sal_Bool operator != ( const UniReference & rRef ) const;

    /** Gets implementation pointer.
        This call does <b>not</b> acquire the implementation.
        <br>
        @return <b>un</b>acquired implementation pointer
    */
    inline T* get() const;
};

class UniRefBase
{
private:
    /**
     * The reference counter.
     */
    oslInterlockedCount			m_refCount;

public:
    UniRefBase() : m_refCount( 0 )
    {}
    virtual ~UniRefBase();

    void acquire() { osl_incrementInterlockedCount( &m_refCount ); }
    void release();
};

///////////////////////////////////////////////////////////////////////////////
//
// Inline-implementations of UniReference
//

/** Create a new reference with the same element as in rRef and acquire this one.*/
template< class T >
inline UniReference< T >::UniReference( const UniReference< T > & rRef )
    : mpElement( rRef.mpElement )
{
    if( mpElement )
        mpElement->acquire();
}

template< class T >
inline UniReference< T >::~UniReference()
{
    if( mpElement )
        mpElement->release();
}

/** 
 * Create a new reference with the given element pElement and acquire this one.
 * @param pInterface the interface, pointer may be null.
 */
template< class T >
inline UniReference< T >::UniReference( T * pElement )
    : mpElement( pElement )
{
    if( mpElement )
        mpElement->acquire();
}

/**
 * Release the reference and set the new one pObj.<BR>
 * <B>The operation is not thread save. You must protect all assigns to a reference class.</B>
 */
template< class T >
inline UniReference< T > & UniReference< T >::operator = ( T * pElement )
{
    if( pElement )
        pElement->acquire();
    if( mpElement )
        mpElement->release();

    mpElement = pElement;

    return *this;
}

/**
 * Release the reference and set the new one from rObj.<BR>
 * <B>The operation is not thread save. You must protect all assigns to a reference class.</B>
 */
template< class T >
inline UniReference< T > & UniReference< T >::operator = ( const UniReference< T > & rRef )
{
    return operator = ( rRef.mpElement );
}

/**
 * Return the pointer to the interface, may be null.
 */
template< class T >
inline T* UniReference< T >::operator -> () const 
{ 
    return get(); 
}

/**
 * Return the pointer to the interface, may be null.
 */
template< class T >
inline T* UniReference< T >::get () const 
{ 
    return static_cast< T * >( mpElement ); 
}

/**
 * Returns true if the pointer to the interface is valid.
 */
template< class T >
inline sal_Bool UniReference< T >::is() const
{ 
    return (mpElement != 0); 
}
/**
 * Return true if both interfaces refer to the same object. The operation can be
 * much more expensive than a pointer comparision.<BR>
 *
 * @param rRef		another interface reference
 */
template< class T >
inline sal_Bool UniReference< T >::operator == ( const UniReference & rRef ) const
{
    return ( mpElement == rRef.mpElement );
}
/**
 * Return true if both interfaces does not refer to the same object. The operation can be
 * much more expensive than a pointer comparision.<BR>
 *
 * @param rRef		another interface reference
 */
template< class T >
inline sal_Bool UniReference< T >::operator != ( const UniReference & rRef ) const
{ 
    return ( ! operator == ( rRef ) ); 
}

}//end of namespace binfilter
#endif	// _UNIVERSALL_REFERENCE_HXX
