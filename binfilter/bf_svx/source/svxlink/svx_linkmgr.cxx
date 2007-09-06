/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_linkmgr.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:46:39 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#include <sot/formats.hxx>
#ifndef _SV_GRAPH_HXX
#include <vcl/graph.hxx>
#endif
#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
#ifndef _SFXITEMSET_HXX
#include <svtools/itemset.hxx>
#endif

#include "linkmgr.hxx"
#include "fileobj.hxx"
#include "dialmgr.hxx"
#include "dialogs.hrc"
#include "so3/staticbaseurl.hxx"
namespace binfilter {



/*N*/ SvxLinkManager::SvxLinkManager( SvPersist * pPersist )
/*N*/ {
/*N*/ 	SvLinkManager::SetPersist( pPersist );
/*N*/ }

/*N*/ ::so3::SvLinkSourceRef SvxLinkManager::CreateObj( ::so3::SvBaseLink * pLink )
/*N*/ {
/*N*/ 	switch( pLink->GetObjType() )
/*N*/ 	{
/*N*/ 	case OBJECT_CLIENT_FILE:
/*N*/ 	case OBJECT_CLIENT_GRF:
/*N*/ 		return new SvFileObject;
/*N*/ 
/*N*/ 	case OBJECT_INTERN:
/*?*/ 		{DBG_BF_ASSERT(0, "STRIP");} //STRIP001 return new SvxInternalLink();
/*N*/ 	}
/*?*/ 	return SvLinkManager::CreateObj( pLink );
/*N*/ }


/*N*/ BOOL SvxLinkManager::InsertFileLink( ::so3::SvBaseLink& rLink,
/*N*/ 									USHORT nFileType,
/*N*/ 									const String& rFileNm,
/*N*/ 									const String* pFilterNm,
/*N*/ 									const String* pRange )
/*N*/ {
/*N*/ 	if( !( OBJECT_CLIENT_SO & rLink.GetObjType() ))
/*N*/ 		return FALSE;
/*N*/ 
/*N*/ 	String sCmd( rFileNm );
/*N*/ 	sCmd += ::so3::cTokenSeperator;
/*N*/ 	if( pRange )
/*N*/ 		sCmd += *pRange;
/*N*/ 	if( pFilterNm )
/*N*/ 		( sCmd += ::so3::cTokenSeperator ) += *pFilterNm;
/*N*/ 
/*N*/ 	return SvLinkManager::InsertLink( &rLink, nFileType,
/*N*/ 									::so3::LINKUPDATE_ONCALL, &sCmd );
/*N*/ }


        // erfrage die Strings fuer den Dialog
/*N*/ BOOL SvxLinkManager::GetDisplayNames( const ::so3::SvBaseLink* pBaseLink,
/*N*/ 										String* pType,
/*N*/ 										String* pFile,
/*N*/ 										String* pLink,
/*N*/ 										String* pFilter ) const
/*N*/ {
/*N*/ 	BOOL bRet = FALSE;
/*N*/ 	const String sLNm( pBaseLink->GetLinkSourceName() );
/*N*/ 	if( sLNm.Len() )
/*N*/ 		switch( pBaseLink->GetObjType() )
/*N*/ 		{
/*N*/ 		case OBJECT_CLIENT_FILE:
/*N*/ 		case OBJECT_CLIENT_GRF:
/*N*/ 			{
/*N*/ 				USHORT nPos = 0;
/*N*/ 				String sFile( sLNm.GetToken( 0, ::so3::cTokenSeperator, nPos ) );
/*N*/ 				String sRange( sLNm.GetToken( 0, ::so3::cTokenSeperator, nPos ) );
/*N*/ 
/*N*/ 				if( pFile )
/*N*/ 					*pFile = sFile;
/*N*/ 				if( pLink )
/*N*/ 					*pLink = sRange;
/*N*/ 				if( pFilter )
/*N*/ 					*pFilter = sLNm.Copy( nPos );
/*N*/ 
/*N*/ 				if( pType )
/*?*/ 					*pType = String( ResId(
/*?*/ 								OBJECT_CLIENT_FILE == pBaseLink->GetObjType()
/*?*/ 										? RID_SVXSTR_FILELINK
/*?*/ 										: RID_SVXSTR_GRAFIKLINK
/*?*/ 										, DIALOG_MGR() ));
/*N*/ 
/*N*/ 				bRet = TRUE;
/*N*/ 			}
/*N*/ 			break;
/*N*/ 		default:
/*N*/ 			bRet = SvLinkManager::GetDisplayNames( pBaseLink, pType, pFile,
/*N*/ 													pLink, pFilter );
/*N*/ 			break;
/*N*/ 		}
/*N*/ 	return bRet;
/*N*/ }

// eine Uebertragung wird abgebrochen, also alle DownloadMedien canceln
// (ist zur Zeit nur fuer die FileLinks interressant!)
/*N*/ void SvxLinkManager::CancelTransfers()
/*N*/ {
/*N*/ 	SvFileObject* pFileObj;
/*N*/ 	::so3::SvBaseLink* pLnk;
/*N*/ 
/*N*/ 	const ::so3::SvBaseLinks& rLnks = GetLinks();
/*N*/ 	for( USHORT n = rLnks.Count(); n; )
/*N*/ 		if( 0 != ( pLnk = &(*rLnks[ --n ])) &&
/*N*/ 			OBJECT_CLIENT_FILE == (OBJECT_CLIENT_FILE & pLnk->GetObjType()) &&
/*N*/ 			0 != ( pFileObj = (SvFileObject*)pLnk->GetObj() ) )
/*N*/ //			0 != ( pFileObj = (SvFileObject*)SvFileObject::ClassFactory()->
/*N*/ //									CastAndAddRef( pLnk->GetObj() )) )
/*N*/ 			pFileObj->CancelTransfers();
/*N*/ }



    // um Status Informationen aus dem FileObject an den BaseLink zu
    // senden, gibt es eine eigene ClipBoardId. Das SvData-Object hat
    // dann die entsprechenden Informationen als String.
    // Wird zur Zeit fuer FileObject in Verbindung mit JavaScript benoetigt
    // - das braucht Informationen ueber Load/Abort/Error
/*N*/ ULONG SvxLinkManager::RegisterStatusInfoId()
/*N*/ {
/*N*/ 	static ULONG nFormat = 0;
/*N*/ 
/*N*/ 	if( !nFormat )
/*N*/ 	{
/*N*/ // wie sieht die neue Schnittstelle aus?
/*N*/ //		nFormat = Exchange::RegisterFormatName( "StatusInfo vom SvxInternalLink" );
/*N*/ 		nFormat = SotExchange::RegisterFormatName(
/*N*/ 					String::CreateFromAscii( RTL_CONSTASCII_STRINGPARAM(
/*N*/ 								"StatusInfo vom SvxInternalLink" )));
/*N*/ 	}
/*N*/ 	return nFormat;
/*N*/ }

// ----------------------------------------------------------------------

/*N*/ BOOL SvxLinkManager::GetGraphicFromAny( const String& rMimeType,
/*N*/ 								const ::com::sun::star::uno::Any & rValue,
/*N*/ 								Graphic& rGrf )
/*N*/ {
/*?*/ 	BOOL bRet = FALSE;
/*?*/ 	::com::sun::star::uno::Sequence< sal_Int8 > aSeq;
/*?*/ 	if( rValue.hasValue() && ( rValue >>= aSeq ) )
/*?*/ 	{
/*?*/ 		SvMemoryStream aMemStm( (void*)aSeq.getConstArray(), aSeq.getLength(),
/*?*/ 								STREAM_READ );
/*?*/ 		aMemStm.Seek( 0 );
/*?*/ 
/*?*/ 		switch( SotExchange::GetFormatIdFromMimeType( rMimeType ) )
/*?*/ 		{
/*?*/ 		case SOT_FORMATSTR_ID_SVXB:
/*?*/ 			{
/*?*/ 				aMemStm >> rGrf;
/*?*/ 				bRet = TRUE;
/*?*/ 			}
/*?*/ 			break;
/*?*/ 		case FORMAT_GDIMETAFILE:
/*?*/ 			{
/*?*/ 				GDIMetaFile aMtf;
/*?*/ 				aMtf.Read( aMemStm );
/*?*/ 				rGrf = aMtf;
/*?*/ 				bRet = TRUE;
/*?*/ 			}
/*?*/ 			break;
/*?*/ 		case FORMAT_BITMAP:
/*?*/ 			{
/*?*/ 				Bitmap aBmp;
/*?*/ 				aMemStm >> aBmp;
/*?*/ 				rGrf = aBmp;
/*?*/ 				bRet = TRUE;
/*?*/ 			}
/*?*/ 			break;
/*?*/ 		}
/*?*/ 	}
/*?*/ 	return bRet;
/*N*/ }


// ----------------------------------------------------------------------



}
