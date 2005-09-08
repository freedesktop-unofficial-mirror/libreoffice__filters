/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sd_unowcntr.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 01:29:49 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif

#include <unowcntr.hxx>
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;

DECLARE_LIST( WeakRefList, uno::WeakReference< uno::XInterface >* )//STRIP008 ;

SvUnoWeakContainer::SvUnoWeakContainer() throw()
{
    mpList = new WeakRefList;
}

SvUnoWeakContainer::~SvUnoWeakContainer() throw()
{
    uno::WeakReference< uno::XInterface >* pRef = mpList->First();
    while( pRef )
    {
        delete mpList->Remove();
        pRef = mpList->GetCurObject();
    }
    delete mpList;
}

/** inserts the given ref into this container */
void SvUnoWeakContainer::insert( uno::WeakReference< uno::XInterface > xRef ) throw()
{
    uno::WeakReference< uno::XInterface >* pRef = mpList->First();
    while( pRef )
    {
        ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  xTestRef( *pRef );
        if(! xTestRef.is() )
        {
            delete mpList->Remove();
            pRef = mpList->GetCurObject();
        }
        else
        {
            if( *pRef == xRef )
                return;

            pRef = mpList->Next();
        }
    }

    mpList->Insert( new uno::WeakReference< uno::XInterface >( xRef ) );
}

/** removes the given ref from this container */
void SvUnoWeakContainer::remove( uno::WeakReference< uno::XInterface > xRef ) throw()
{
    uno::WeakReference< uno::XInterface >* pRef = mpList->First();
    while( pRef )
    {
        uno::Reference< uno::XInterface > xTestRef( *pRef );
        if(!xTestRef.is())
        {
            delete mpList->Remove();
            pRef = mpList->GetCurObject();
        }
        else
        {
            if( *pRef == xRef )
            {
                delete mpList->Remove();
                break;
            }

            pRef = mpList->Next();
        }
    }
}

/** searches the container for a ref that returns true on the given 
    search function
*/
sal_Bool SvUnoWeakContainer::findRef( uno::WeakReference< uno::XInterface >& rRef, void* pSearchData, weakref_searchfunc pSearchFunc )
{
    uno::WeakReference< uno::XInterface >* pRef = mpList->First();
    while( pRef )
    {
        uno::Reference< ::com::sun::star::uno::XInterface > xTestRef( *pRef );
        if(!xTestRef.is())
        {
            delete mpList->Remove();
            pRef = mpList->GetCurObject();
        }
        else
        {
            if( (*pSearchFunc)( *pRef, pSearchData ) )
            {
                rRef = *pRef;
                return sal_True;
            }

            pRef = mpList->Next();
        }
    }

    return sal_False;
}

}
