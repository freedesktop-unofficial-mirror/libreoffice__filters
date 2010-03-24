/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifdef PCH
#endif

#ifdef _MSC_VER
#pragma hdrstop
#endif

//------------------------------------------------------------------------

#include <bf_svtools/zformat.hxx>
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#include <tools/debug.hxx>

#include "zforauto.hxx"
#include "global.hxx"
namespace binfilter {

static const sal_Char __FAR_DATA pStandardName[] = "Standard";

//------------------------------------------------------------------------

/*N*/ ScNumFormatAbbrev::ScNumFormatAbbrev() :
/*N*/ 	eLnge			(LANGUAGE_SYSTEM),
/*N*/ 	eSysLnge		(LANGUAGE_GERMAN),		// sonst passt "Standard" nicht
/*N*/ 	sFormatstring	( RTL_CONSTASCII_USTRINGPARAM( pStandardName ) )
/*N*/ {
/*N*/ }

/*N*/ ScNumFormatAbbrev::ScNumFormatAbbrev(const ScNumFormatAbbrev& aFormat) :
/*N*/ 	eLnge			(aFormat.eLnge),
/*N*/ 	eSysLnge		(aFormat.eSysLnge),
/*N*/ 	sFormatstring	(aFormat.sFormatstring)
/*N*/ {
/*N*/ }

/*N*/ void ScNumFormatAbbrev::Load( SvStream& rStream )
/*N*/ {
/*N*/ 	USHORT nSysLang, nLang;
/*N*/ 	rStream.ReadByteString( sFormatstring, rStream.GetStreamCharSet() );
/*N*/ 	rStream >> nSysLang >> nLang;
/*N*/ 	eLnge = (LanguageType) nLang;
/*N*/ 	eSysLnge = (LanguageType) nSysLang;
/*N*/     if ( eSysLnge == LANGUAGE_SYSTEM )          // old versions did write it
/*N*/         eSysLnge = Application::GetSettings().GetLanguage();
/*N*/ }

/*N*/ void ScNumFormatAbbrev::Save( SvStream& rStream ) const
/*N*/ {
/*N*/ 	rStream.WriteByteString( sFormatstring, rStream.GetStreamCharSet() );
/*N*/ 	rStream << (USHORT) eSysLnge << (USHORT) eLnge;
/*N*/ }







}
