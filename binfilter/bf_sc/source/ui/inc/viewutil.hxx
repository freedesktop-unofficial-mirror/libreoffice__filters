/*************************************************************************
 *
 *  $RCSfile: viewutil.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:19 $
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

#ifndef SC_VIEWUTIL_HXX
#define SC_VIEWUTIL_HXX

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif
class String;
class SfxItemSet;
namespace binfilter {

class SvxFontItem;

class ScChangeAction;
class ScChangeViewSettings;
class ScDocument;
class ScAddress;


enum ScUpdateMode { SC_UPDATE_ALL, SC_UPDATE_CHANGED, SC_UPDATE_MARKS };


// ---------------------------------------------------------------------------

class ScViewUtil								// static Methoden
{
public:
//STRIP001 	static BOOL	ExecuteCharMap( const SvxFontItem&	rOldFont,
//STRIP001 								SvxFontItem&		rNewFont,
//STRIP001 								String&				rString );

//STRIP001 	static BOOL IsActionShown( const ScChangeAction& rAction,
//STRIP001 								const ScChangeViewSettings& rSettings,
//STRIP001 								ScDocument& rDocument );

    static void PutItemScript( SfxItemSet& rShellSet, const SfxItemSet& rCoreSet,
                                USHORT nWhichId, USHORT nScript );

//STRIP001 	static USHORT GetEffLanguage( ScDocument* pDoc, const ScAddress& rPos );

//STRIP001 	static sal_Int32 GetTransliterationType( USHORT nSlotID );
};

// ---------------------------------------------------------------------------

//STRIP001 class ScUpdateRect
//STRIP001 {
//STRIP001 private:
//STRIP001 	USHORT	nOldStartX;
//STRIP001 	USHORT	nOldStartY;
//STRIP001 	USHORT	nOldEndX;
//STRIP001 	USHORT	nOldEndY;
//STRIP001 	USHORT	nNewStartX;
//STRIP001 	USHORT	nNewStartY;
//STRIP001 	USHORT	nNewEndX;
//STRIP001 	USHORT	nNewEndY;
//STRIP001 	USHORT	nContX1;
//STRIP001 	USHORT	nContY1;
//STRIP001 	USHORT	nContX2;
//STRIP001 	USHORT	nContY2;
//STRIP001 public:
//STRIP001 			ScUpdateRect( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );
//STRIP001 	void	SetNew( USHORT nX1, USHORT nY1, USHORT nX2, USHORT nY2 );
//STRIP001 	BOOL	GetDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2 );
//STRIP001 	BOOL	GetXorDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2, BOOL& rCont );
//STRIP001 	void	GetContDiff( USHORT& rX1, USHORT& rY1, USHORT& rX2, USHORT& rY2 );
//STRIP001 };




} //namespace binfilter
#endif

