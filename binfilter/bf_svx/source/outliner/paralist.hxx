/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: paralist.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:31:26 $
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

#ifndef _PARALIST_HXX
#define _PARALIST_HXX

//STRIP008 class Paragraph;

#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif

#ifndef _LINK_HXX
#include <tools/link.hxx>
#endif
namespace binfilter {
class Paragraph;

class ParagraphList : private List
{
private:
    Link			aVisibleStateChangedHdl;

public:
    void			Clear( BOOL bDestroyParagraphs );

    ULONG			GetParagraphCount() const			{ return List::Count(); }
    Paragraph*		GetParagraph( ULONG nPos ) const 	{ return (Paragraph*)List::GetObject( nPos ); }

    ULONG			GetAbsPos( Paragraph* pParent ) const { return List::GetPos( pParent ); }

    void			Insert( Paragraph* pPara, ULONG nAbsPos = LIST_APPEND ) { List::Insert( pPara, nAbsPos ); }
    void			Remove( ULONG nPara ) { List::Remove( nPara ); }


/*NBFF*/ 	Paragraph*		GetParent( Paragraph* pParagraph, USHORT& rRelPos ) const;


    void			SetVisibleStateChangedHdl( const Link& rLink ) { aVisibleStateChangedHdl = rLink; }
    Link			GetVisibleStateChangedHdl() const { return aVisibleStateChangedHdl; }
};

}//end of namespace binfilter
#endif
