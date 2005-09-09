/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_docshdrw.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 03:51:21 $
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


#pragma hdrstop

// auto strip #ifndef _HINTIDS_HXX
// auto strip #include <hintids.hxx>
// auto strip #endif

#ifndef _SVX_SVXIDS_HRC //autogen
#include <bf_svx/svxids.hrc>
#endif

#define ITEMID_COLOR_TABLE		SID_COLOR_TABLE
#define ITEMID_GRADIENT_LIST	SID_GRADIENT_LIST
#define ITEMID_HATCH_LIST		SID_HATCH_LIST
#define ITEMID_BITMAP_LIST		SID_BITMAP_LIST
#define ITEMID_DASH_LIST		SID_DASH_LIST
#define ITEMID_LINEEND_LIST 	SID_LINEEND_LIST


// auto strip #ifndef _SFXSTRITEM_HXX //autogen
// auto strip #include <svtools/stritem.hxx>
// auto strip #endif
#ifndef _OFF_APP_HXX //autogen
#include <bf_offmgr/app.hxx>
#endif
#ifndef _SVX_DRAWITEM_HXX //autogen
#include <bf_svx/drawitem.hxx>
#endif
#ifndef _SVDMODEL_HXX //autogen
#include <bf_svx/svdmodel.hxx>
#endif
#ifndef _SVDOUTL_HXX
#include <bf_svx/svdoutl.hxx>
#endif

#ifndef _DOCSH_HXX
#include <docsh.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX
#include <doc.hxx>
#endif
namespace binfilter {

/*--------------------------------------------------------------------
    Beschreibung: Document laden
 --------------------------------------------------------------------*/


/*N*/ void  SwDocShell::InitDraw()
/*N*/ {
/*N*/ 	SdrModel *pDrDoc = pDoc->GetDrawModel();
/*N*/ 	if( pDrDoc )
/*N*/ 	{
/*N*/ 		// Listen, bzw. Tables im ItemSet der DocShell anlegen
/*N*/ 		PutItem( SvxGradientListItem( pDrDoc->GetGradientList() ) );
/*N*/ 		PutItem( SvxHatchListItem( pDrDoc->GetHatchList() ) );
/*N*/ 		PutItem( SvxBitmapListItem( pDrDoc->GetBitmapList() ) );
/*N*/ 		PutItem( SvxDashListItem( pDrDoc->GetDashList() ) );
/*N*/ 		PutItem( SvxLineEndListItem( pDrDoc->GetLineEndList() ) );
/*N*/ 
/*N*/ 		Outliner& rOutliner = pDrDoc->GetDrawOutliner();
    /*N*/         ::com::sun::star::uno::Reference< ::com::sun::star::linguistic2::XHyphenator> xHyphenator( ::binfilter::GetHyphenator() );
/*N*/ 		rOutliner.SetHyphenator( xHyphenator );
/*N*/ 	}
/*N*/ 	else
/*N*/ 		PutItem( SvxColorTableItem( OFF_APP()->GetStdColorTable() ));
/*N*/ }

}
