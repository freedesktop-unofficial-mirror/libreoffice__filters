/*************************************************************************
 *
 *  $RCSfile: numpara.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:49:57 $
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
#ifndef _NUMPARA_HXX
#define _NUMPARA_HXX

#include "numrule.hxx"
#ifndef _NDARR_HXX //autogen
#include "ndarr.hxx"
#endif
#include "ndindex.hxx"
namespace binfilter {

class SwTxtNode;
class SwDoc;
class SwNumSection;
class SwNodes;

class _NumPara
{
    const SwNumSection& rNumSection;

    void _Init();

public:
    SwNodeIndex aNdIdx;
    ULONG nCnt;
    SwNum aNum;
    char nDiff;				// +1, 0, -1 !! dafuer reicht ein char !!
    BYTE nOldLevel;
    BOOL bInitNum : 1;
    BOOL bWasUndo : 1;
    BOOL bOverTbl : 1;		// Flag fuer ForEach-Methoden, Tabelle ueberspr.

    _NumPara( char nOffset, const SwNodeIndex& rNdIdx,
                const SwNumSection& rSect, ULONG nCntNodes );
    _NumPara( const SwNodeIndex& rNdIdx, const SwNumSection& rSect );
    ~_NumPara();

    void UpdateNum( SwTxtNode& rTxtNd );
};

// Funktion fuer ForEach am Nodes-Array
BOOL _NumUpDown( const SwNodePtr& rpNode, void* pPara );


} //namespace binfilter
#endif	// _NUMPARA_HXX
