/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: progress.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:39:37 $
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

#ifndef SC_PROGRESS_HXX
#define SC_PROGRESS_HXX

#ifndef _SFX_PROGRESS_HXX //autogen
#include <bf_sfx2/progress.hxx>
#endif
namespace binfilter {

class ScDocument;

class ScProgress
{
private:
    static	SfxProgress*	pGlobalProgress;
    static	ULONG			nGlobalRange;
    static	ULONG			nGlobalPercent;
    static	BOOL			bGlobalNoUserBreak;
    static	ScProgress*		pInterpretProgress;
    static	ScProgress*		pOldInterpretProgress;
    static	ULONG			nInterpretProgress;
    static	BOOL			bAllowInterpretProgress;
    static	ScDocument*		pInterpretDoc;
    static	BOOL			bIdleWasDisabled;

            SfxProgress*	pProgress;

                            // not implemented
                            ScProgress( const ScProgress& );
            ScProgress&		operator=( const ScProgress& );

    static	void			CalcGlobalPercent( ULONG nVal )
                                {
                                    nGlobalPercent = nGlobalRange ?
                                        nVal * 100 / nGlobalRange : 0;
                                }

public:
    static	SfxProgress*	GetGlobalSfxProgress() { return pGlobalProgress; }
    static	BOOL			IsUserBreak() { return !bGlobalNoUserBreak; }
    static	ScProgress*		GetInterpretProgress() { return pInterpretProgress; }
    static	BOOL			GetAllowInterpret() { return bAllowInterpretProgress; }
    static	ULONG			GetInterpretCount() { return nInterpretProgress; }
    static	ULONG			GetGlobalRange()	{ return nGlobalRange; }
    static	ULONG			GetGlobalPercent()	{ return nGlobalPercent; }

                            ScProgress( SfxObjectShell* pObjSh,
                                         const String& rText,
                                         ULONG nRange, BOOL bAllDocs = FALSE,
                                         BOOL bWait = TRUE );
                            ~ScProgress();

#ifdef SC_PROGRESS_CXX
                            // nur fuer DummyInterpret, sonst nie benutzen!!!
                            ScProgress();
#endif
                            // kann NULL sein!
            SfxProgress*	GetSfxProgress() const { return pProgress; }

            BOOL			SetState( ULONG nVal, ULONG nNewRange = 0 )
                                {
                                    if ( pProgress )
                                    {
                                        if ( nNewRange )
                                            nGlobalRange = nNewRange;
                                        CalcGlobalPercent( nVal );
                                        if ( !pProgress->SetState( nVal, nNewRange ) )
                                            bGlobalNoUserBreak = FALSE;
                                        return bGlobalNoUserBreak;
                                    }
                                    return TRUE;
                                }
            BOOL			SetStateCountDown( ULONG nVal )
                                {
                                    if ( pProgress )
                                    {
                                        CalcGlobalPercent( nGlobalRange - nVal );
                                        if ( !pProgress->SetState( nGlobalRange - nVal ) )
                                            bGlobalNoUserBreak = FALSE;
                                        return bGlobalNoUserBreak;
                                    }
                                    return TRUE;
                                }
            BOOL			SetStateOnPercent( ULONG nVal )
                                {	// nur wenn Prozent mehr als vorher
                                    if ( nGlobalRange && (nVal * 100 /
                                            nGlobalRange) > nGlobalPercent )
                                        return SetState( nVal );
                                    return TRUE;
                                }
            BOOL			SetStateCountDownOnPercent( ULONG nVal )
                                {	// nur wenn Prozent mehr als vorher
                                    if ( nGlobalRange &&
                                            ((nGlobalRange - nVal) * 100 /
                                            nGlobalRange) > nGlobalPercent )
                                        return SetStateCountDown( nVal );
                                    return TRUE;
                                }
            ULONG			GetState()
                                {
                                    if ( pProgress )
                                        return pProgress->GetState();
                                    return 0;
                                }
};


} //namespace binfilter
#endif

