/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sc_rechead.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: kz $ $Date: 2006-07-06 09:15:26 $
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

#ifdef PCH
// auto strip #include "core_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#include <tools/debug.hxx>

#include "rechead.hxx"
#include "scerrors.hxx"
namespace binfilter {

// STATIC DATA -----------------------------------------------------------

// =======================================================================

/*N*/ ScReadHeader::ScReadHeader(SvStream& rNewStream) :
/*N*/ 	rStream( rNewStream )
/*N*/ {
/*N*/ 	sal_uInt32 nDataSize;
/*N*/ 	rStream >> nDataSize;
/*N*/ 	nDataEnd = rStream.Tell() + nDataSize;
/*N*/ }

/*N*/ ScReadHeader::~ScReadHeader()
/*N*/ {
/*N*/ 	ULONG nReadEnd = rStream.Tell();
/*N*/ 	DBG_ASSERT( nReadEnd <= nDataEnd, "zuviele Bytes gelesen" );
/*N*/ 	if ( nReadEnd != nDataEnd )
/*N*/ 	{
/*?*/ 		if ( rStream.GetError() == SVSTREAM_OK )
/*?*/ 			rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*?*/ 		rStream.Seek(nDataEnd); 					// Rest ueberspringen
/*N*/ 	}
/*N*/ }

/*N*/ ULONG ScReadHeader::BytesLeft() const
/*N*/ {
/*N*/ 	ULONG nReadEnd = rStream.Tell();
/*N*/ 	if (nReadEnd <= nDataEnd)
/*N*/ 		return nDataEnd-nReadEnd;
/*N*/ 
/*N*/ 	DBG_ERROR("Fehler bei ScReadHeader::BytesLeft");
/*N*/ 	return 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScWriteHeader::ScWriteHeader(SvStream& rNewStream, sal_uInt32 nDefault) :
/*N*/ 	rStream( rNewStream )
/*N*/ {
/*N*/ 	nDataSize = nDefault;
/*N*/ 	rStream << nDataSize;
/*N*/ 
/*N*/ 	nDataPos = rStream.Tell();
/*N*/ }

/*N*/ ScWriteHeader::~ScWriteHeader()
/*N*/ {
/*N*/ 	ULONG nPos = rStream.Tell();
/*N*/ 
/*N*/ 	if ( nPos - nDataPos != nDataSize )				// Default getroffen?
/*N*/ 	{
/*N*/ 		nDataSize = nPos - nDataPos;
/*N*/ 		rStream.Seek(nDataPos - sizeof(ULONG));
/*N*/ 		rStream << nDataSize;						// Groesse am Anfang eintragen
/*N*/ 		rStream.Seek(nPos);
/*N*/ 	}
/*N*/ }

// =======================================================================

/*N*/ ScMultipleReadHeader::ScMultipleReadHeader(SvStream& rNewStream) :
/*N*/ 	rStream( rNewStream )
/*N*/ {
/*N*/ 	sal_uInt32 nDataSize;
/*N*/ 	rStream >> nDataSize;
/*N*/ 	ULONG nDataPos = rStream.Tell();
/*N*/ 	nTotalEnd = nDataPos + nDataSize;
/*N*/ 	nEntryEnd = nTotalEnd;
/*N*/ 
/*N*/ 	rStream.SeekRel(nDataSize);
/*N*/ 	USHORT nID;
/*N*/ 	rStream >> nID;
/*N*/ 	if (nID != SCID_SIZES)
/*N*/ 	{
/*N*/ 		DBG_ERROR("SCID_SIZES nicht gefunden");
/*N*/ 		if ( rStream.GetError() == SVSTREAM_OK )
/*N*/ 			rStream.SetError( SVSTREAM_FILEFORMAT_ERROR );
/*N*/ 
/*N*/ 		//	alles auf 0, damit BytesLeft() wenigstens abbricht
/*N*/ 		pBuf = NULL; pMemStream = NULL;
/*N*/ 		nEntryEnd = nDataPos;
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		sal_uInt32 nSizeTableLen;
/*N*/ 		rStream >> nSizeTableLen;
/*N*/ 		pBuf = new BYTE[nSizeTableLen];
/*N*/ 		rStream.Read( pBuf, nSizeTableLen );
/*N*/ 		pMemStream = new SvMemoryStream( (char*)pBuf, nSizeTableLen, STREAM_READ );
/*N*/ 	}
/*N*/ 
/*N*/ 	nEndPos = rStream.Tell();
/*N*/ 	rStream.Seek( nDataPos );
/*N*/ }

/*N*/ ScMultipleReadHeader::~ScMultipleReadHeader()
/*N*/ {
/*N*/ 	if ( pMemStream && pMemStream->Tell() != pMemStream->GetSize() )
/*N*/ 	{
/*N*/ 		DBG_ERRORFILE( "Sizes nicht vollstaendig gelesen" );
/*N*/ 		if ( rStream.GetError() == SVSTREAM_OK )
/*N*/ 			rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*N*/ 	}
/*N*/ 	delete pMemStream;
/*N*/ 	delete[] pBuf;
/*N*/ 
/*N*/ 	rStream.Seek(nEndPos);
/*N*/ }

/*N*/ void ScMultipleReadHeader::EndEntry()
/*N*/ {
/*N*/ 	ULONG nPos = rStream.Tell();
/*N*/ 	DBG_ASSERT( nPos <= nEntryEnd, "zuviel gelesen" );
/*N*/ 	if ( nPos != nEntryEnd )
/*N*/ 	{
/*?*/ 		if ( rStream.GetError() == SVSTREAM_OK )
/*?*/ 			rStream.SetError( SCWARN_IMPORT_INFOLOST );
/*?*/ 		rStream.Seek( nEntryEnd );			// Rest ueberspringen
/*N*/ 	}
/*N*/ 
/*N*/ 	nEntryEnd = nTotalEnd;			// den ganzen Rest, wenn kein StartEntry kommt
/*N*/ }

/*N*/ void ScMultipleReadHeader::StartEntry()
/*N*/ {
/*N*/ 	ULONG nPos = rStream.Tell();
/*N*/ 	sal_uInt32 nEntrySize;
/*N*/ 	(*pMemStream) >> nEntrySize;
/*N*/ 
/*N*/ 	nEntryEnd = nPos + nEntrySize;
/*N*/ 	DBG_ASSERT( nEntryEnd <= nTotalEnd, "zuviele Eintraege gelesen" );
/*N*/ }

/*N*/ ULONG ScMultipleReadHeader::BytesLeft() const
/*N*/ {
/*N*/ 	ULONG nReadEnd = rStream.Tell();
/*N*/ 	if (nReadEnd <= nEntryEnd)
/*N*/ 		return nEntryEnd-nReadEnd;
/*N*/ 
/*N*/ 	DBG_ERROR("Fehler bei ScMultipleReadHeader::BytesLeft");
/*N*/ 	return 0;
/*N*/ }

// -----------------------------------------------------------------------

/*N*/ ScMultipleWriteHeader::ScMultipleWriteHeader(SvStream& rNewStream, sal_uInt32 nDefault) :
/*N*/ 	rStream( rNewStream ),
/*N*/ 	aMemStream( 4096, 4096 )
/*N*/ {
/*N*/ 	nDataSize = nDefault;
/*N*/ 	rStream << nDataSize;
/*N*/ 
/*N*/ 	nDataPos = rStream.Tell();
/*N*/ 	nEntryStart = nDataPos;
/*N*/ }

/*N*/ ScMultipleWriteHeader::~ScMultipleWriteHeader()
/*N*/ {
/*N*/ 	ULONG nDataEnd = rStream.Tell();
/*N*/ 
/*N*/ 	rStream << (USHORT) SCID_SIZES;
/*N*/ 	rStream << static_cast<sal_uInt32>(aMemStream.Tell());
/*N*/ 	rStream.Write( aMemStream.GetData(), aMemStream.Tell() );
/*N*/ 
/*N*/ 	if ( nDataEnd - nDataPos != nDataSize )					// Default getroffen?
/*N*/ 	{
/*N*/ 		nDataSize = nDataEnd - nDataPos;
/*N*/ 		ULONG nPos = rStream.Tell();
/*N*/ 		rStream.Seek(nDataPos-sizeof(ULONG));
/*N*/ 		rStream << nDataSize;								// Groesse am Anfang eintragen
/*N*/ 		rStream.Seek(nPos);
/*N*/ 	}
/*N*/ }

/*N*/ void ScMultipleWriteHeader::EndEntry()
/*N*/ {
/*N*/ 	ULONG nPos = rStream.Tell();
/*N*/ 	aMemStream << static_cast<sal_uInt32>(nPos - nEntryStart);
/*N*/ }

/*N*/ void ScMultipleWriteHeader::StartEntry()
/*N*/ {
/*N*/ 	ULONG nPos = rStream.Tell();
/*N*/ 	nEntryStart = nPos;
/*N*/ }





}
