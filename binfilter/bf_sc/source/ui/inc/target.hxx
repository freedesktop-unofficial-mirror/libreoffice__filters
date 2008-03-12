/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: target.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 07:10:35 $
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

#ifndef SC_TARGET_HXX
#define SC_TARGET_HXX

#ifndef _UNDO_HXX //autogen
#include <bf_svtools/undo.hxx>
#endif
namespace binfilter {

class ScTabViewShell;

class ScTabViewTarget : public SfxRepeatTarget
{
private:
    ScTabViewShell*	pViewShell;

public:
                    TYPEINFO();

                    ScTabViewTarget( ScTabViewShell* pShell ) : pViewShell( pShell ) {}
    virtual 		~ScTabViewTarget();

    ScTabViewShell*	GetViewShell() const { return pViewShell; }
};



} //namespace binfilter
#endif

