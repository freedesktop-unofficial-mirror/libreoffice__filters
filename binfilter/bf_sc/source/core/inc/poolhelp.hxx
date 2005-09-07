/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: poolhelp.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:58:46 $
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

#ifndef SC_POOLHELP_HXX
#define SC_POOLHELP_HXX

#ifndef _VOS_REFERNCE_HXX_
#include <vos/refernce.hxx>
#endif

// auto strip #ifndef _LINK_HXX
// auto strip #include <tools/link.hxx>
// auto strip #endif
class SvNumberFormatter;
class SfxItemPool;

namespace binfilter {

class ScDocument;
class ScDocumentPool;
class ScStyleSheetPool;


class ScPoolHelper : public vos::OReference
{
private:
    ScDocumentPool*		pDocPool;
    ScStyleSheetPool*	pStylePool;
    SvNumberFormatter*	pFormTable;
    SfxItemPool*		pEditPool;						// EditTextObjectPool
    SfxItemPool*		pEnginePool;					// EditEnginePool

public:
                ScPoolHelper( ScDocument* pSourceDoc );
    virtual		~ScPoolHelper();

                // called in dtor of main document
    void		SourceDocumentGone();

                // access to pointers (are never 0):
    ScDocumentPool*		GetDocPool() const		{ return pDocPool; }
    ScStyleSheetPool*	GetStylePool() const	{ return pStylePool; }
    SvNumberFormatter*	GetFormTable() const	{ return pFormTable; }
    SfxItemPool*		GetEditPool() const		{ return pEditPool; }
    SfxItemPool*		GetEnginePool() const	{ return pEnginePool; }
};

} //namespace binfilter
#endif

