/*************************************************************************
 *
 *  $RCSfile: sd_cusshow.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:34:21 $
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

#pragma hdrstop

#ifndef _COM_SUN_STAR_LANG_XCOMPONENT_HPP_
#include <com/sun/star/lang/XComponent.hpp>
#endif

#include "sdiocmpt.hxx"
#include "cusshow.hxx"
#include "sdpage.hxx"
#include "drawdoc.hxx"

// #90477#
#ifndef _TOOLS_TENCCVT_HXX
#include <tools/tenccvt.hxx>
#endif
namespace binfilter {

using namespace ::com::sun::star;

/*************************************************************************
|*
|* Ctor
|*
\************************************************************************/
/*N*/ SdCustomShow::SdCustomShow(SdDrawDocument* pDrawDoc)
/*N*/   : List(),
/*N*/   pDoc(pDrawDoc)
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Copy-Ctor
|*
\************************************************************************/
/*N*/ SdCustomShow::SdCustomShow( const SdCustomShow& rShow )
/*N*/ 	: List( rShow )
/*N*/ {
/*N*/ 	aName = rShow.GetName();
/*N*/ 	pDoc = rShow.GetDoc();
/*N*/ }

/*N*/ SdCustomShow::SdCustomShow(SdDrawDocument* pDrawDoc, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xShow )
/*N*/   : List(),
/*N*/   pDoc(pDrawDoc),
/*N*/   mxUnoCustomShow( xShow )
/*N*/ {
/*N*/ }

/*************************************************************************
|*
|* Dtor
|*
\************************************************************************/
/*N*/ SdCustomShow::~SdCustomShow()
/*N*/ {
/*N*/ 	uno::Reference< uno::XInterface > xShow( mxUnoCustomShow );
/*N*/ 	uno::Reference< lang::XComponent > xComponent( xShow, uno::UNO_QUERY );
/*N*/ 	if( xComponent.is() )
/*N*/ 		xComponent->dispose();
/*N*/ }


/*************************************************************************
|*
|* Inserter fuer SvStream zum Speichern
|*
\************************************************************************/
/*N*/ SvStream& operator << (SvStream& rOut, const SdCustomShow& rCustomShow)
/*N*/ {
/*N*/ 	// Letzter Parameter ist die aktuelle Versionsnummer des Codes
/*N*/ 	SdIOCompat aIO(rOut, STREAM_WRITE, 0);
/*N*/ 
/*N*/ 	// Name
/*N*/ 	// #90477# rOut.WriteByteString( rCustomShow.aName, ::GetStoreCharSet( gsl_getSystemTextEncoding() ) );
/*N*/ 	rOut.WriteByteString(rCustomShow.aName, 
/*N*/ 		GetSOStoreTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rOut.GetVersion()));
/*N*/ 
/*N*/ 	// Anzahl Seiten
/*N*/ 	UINT32 nCount = rCustomShow.Count();
/*N*/ 	rOut << nCount;
/*N*/ 
/*N*/ 	for (UINT32 i = 0; i < nCount; i++)
/*N*/ 	{
/*N*/ 		// Seite aus Liste holen
/*N*/ 		SdPage* pPage = (SdPage*) rCustomShow.GetObject(i);
/*N*/ 
/*N*/ 		if (pPage)
/*N*/ 		{
/*N*/ 			// SdPage-Seitennummer
/*N*/ 			UINT16 nPageNum = (pPage->GetPageNum() - 1) / 2;
/*N*/ 			rOut << nPageNum;
/*N*/ 		}
/*N*/ 	}
/*N*/ 
/*N*/ 	return rOut;
/*N*/ }

/*************************************************************************
|*
|* Extractor fuer SvStream zum Laden
|*
\************************************************************************/
/*N*/ SvStream& operator >> (SvStream& rIn, SdCustomShow& rCustomShow)
/*N*/ {
/*N*/ 	SdIOCompat aIO(rIn, STREAM_READ);
/*N*/ 
/*N*/ 	// Name
/*N*/ 	// #90477# rIn.ReadByteString( rCustomShow.aName, ::GetStoreCharSet( gsl_getSystemTextEncoding() ) );
/*N*/ 	rIn.ReadByteString(rCustomShow.aName, 
/*N*/ 		GetSOLoadTextEncoding(gsl_getSystemTextEncoding(), (sal_uInt16)rIn.GetVersion()));
/*N*/ 
/*N*/ 	// Anzahl Seiten
/*N*/ 	UINT32 nCount = 0;
/*N*/ 	rIn >> nCount;
/*N*/ 
/*N*/ 	rCustomShow.Clear();
/*N*/ 
/*N*/ 	for (UINT32 i = 0; i < nCount; i++)
/*N*/ 	{
/*N*/ 		// Seitennummer
/*N*/ 		UINT16 nPageNum;
/*N*/ 		rIn >> nPageNum;
/*N*/ 
/*N*/ 		// Seite in Liste einfuegen
/*N*/ 		SdPage* pPage = (SdPage*) rCustomShow.pDoc->GetSdPage(nPageNum, PK_STANDARD);
/*N*/ 		rCustomShow.Insert(pPage, LIST_APPEND);
/*N*/ 	}
/*N*/ 
/*N*/ 	return rIn;
/*N*/ }

/*N*/ extern uno::Reference< uno::XInterface > createUnoCustomShow( SdCustomShow* pShow );

/*N*/ uno::Reference< uno::XInterface > SdCustomShow::getUnoCustomShow()
/*N*/ {
/*N*/ 	// try weak reference first
/*N*/ 	uno::Reference< uno::XInterface > xShow( mxUnoCustomShow );
/*N*/ 
/*N*/ 	if( !xShow.is() )
/*N*/ 	{
/*N*/ 		xShow = createUnoCustomShow( this );
/*N*/ 	}
/*N*/ 
/*N*/ 	return xShow;
/*N*/ }
}
