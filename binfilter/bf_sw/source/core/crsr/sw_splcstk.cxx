/*************************************************************************
 *
 *  $RCSfile: sw_splcstk.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:48:34 $
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

#include "crsrsh.hxx"

#include "splcstk.hxx"
#include "viscrs.hxx"
namespace binfilter {



SwSpellCrsrStk::SwSpellCrsrStk( SwCrsrShell& rShell )
    : rCrsrShell( rShell ), pErrorPos( 0 )
{
    pCurCrsr =
    pCrsrStk = new SwIntrnlCrsr( rCrsrShell,
                                 *rCrsrShell.GetCrsr()->GetPoint() );
    if( rCrsrShell.GetCrsr()->HasMark() )
    {
        pCurCrsr->SetMark();
        *pCurCrsr->GetMark() = *rCrsrShell.GetCrsr()->GetMark();
    }
        // gibt es mehr als einen Cursor ??
    if( rCrsrShell.GetCrsr()->GetNext() != rCrsrShell.GetCrsr() )
    {
        rCrsrShell.HideCrsr(); // alle Cursor erstmal verstecken

        // dann verschiebe den gesamten Ring hierher, in dem aus der Shell
        // alle ausgekettet und hier eingekettet werden. Bis auf den akt. !
        Ring* pCrsr = rCrsrShell.GetCrsr();
        pCrsr->MoveRingTo( pCurCrsr );
        pCrsr->MoveTo( pCrsr );
    }
}


SwSpellCrsrStk::~SwSpellCrsrStk()
{
    register Ring* p = pCrsrStk;
    while( p->GetNext() != pCrsrStk )
        delete p->GetNext();

    delete pCrsrStk;
    delete pErrorPos;
}


    // akt. Cursor in der CrsrShell mit akt. setzen
void SwSpellCrsrStk::SetCurCrsr()
{
    *rCrsrShell.GetCrsr()->GetPoint() = *pCurCrsr->Start();
    if( pCurCrsr->HasMark() )
    {
        rCrsrShell.GetCrsr()->SetMark();
        *rCrsrShell.GetCrsr()->GetMark() = *pCurCrsr->End();
    }
    else
        rCrsrShell.GetCrsr()->DeleteMark();
}

    // gehe zum naechsten Cursor im Ring (falls am Ende returne FALSE;


BOOL SwSpellCrsrStk::SetNextCrsr()
{
    if( pCurCrsr->GetNext() == pCrsrStk )
        return FALSE;

    pCurCrsr = (SwIntrnlCrsr*)pCurCrsr->GetNext();
    SetCurCrsr();
    return TRUE;
}


    // alle Cursor aus dem CursorStack wieder in der Shell setzen
void SwSpellCrsrStk::RestoreCrsrs()
{
    // verschiebe den gesamten Ring in die Shell, in dem hier
    // alle ausgekettet und dort eingekettet werden. Bis auf den Stack !
    if( pCrsrStk->GetNext() != pCrsrStk )
    {
        // sich selbst "ausketten"
        pCrsrStk->MoveRingTo( rCrsrShell.GetCrsr() );
        pCrsrStk->MoveTo( pCrsrStk );
    }

    pCurCrsr = pCrsrStk;

    SetCurCrsr();

    rCrsrShell.ShowCrsr(); 				// Cursor wieder anzeigen
}


    // speicher die akt. Start-Position als Error. An dieser wird spaeter
    // wieder aufgesetzt
void SwSpellCrsrStk::StoreErrPos()
{
    if( !pErrorPos )
        pErrorPos = new SwPosition( *rCrsrShell.GetCrsr()->Start() );
    else
        *pErrorPos = *rCrsrShell.GetCrsr()->Start();
}


    // akt. Cursor auf die Error-Position setzen
void SwSpellCrsrStk::SetErrPos()
{
    if( !pErrorPos )
        return;

    *rCrsrShell.GetCrsr()->GetPoint() = *pErrorPos;
    if( pCurCrsr->HasMark() )
    {
        rCrsrShell.GetCrsr()->SetMark();
        *rCrsrShell.GetCrsr()->GetMark() = *pCurCrsr->End();
    }
    else
        rCrsrShell.GetCrsr()->DeleteMark();
}


#if 0

SwPaM* SwSpellCrsrStk::GetCurCrsr() const { return pCurCrsr; }
#endif



}
