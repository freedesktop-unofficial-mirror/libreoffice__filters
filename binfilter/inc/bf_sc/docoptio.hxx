/*************************************************************************
 *
 *  $RCSfile: docoptio.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:59:43 $
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

#ifndef SC_DOCOPTIO_HXX
#define SC_DOCOPTIO_HXX


#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef SC_OPTUTIL_HXX
#include "optutil.hxx"
#endif
namespace binfilter {



class ScDocOptions
{
    double fIterEps;				// Epsilon-Wert dazu
    USHORT nIterCount;				// Anzahl
    USHORT nPrecStandardFormat;		// Nachkommastellen Standard
    USHORT nDay;					// Nulldatum:
    USHORT nMonth;
    USHORT nYear;
    USHORT nYear2000;				// bis zu welcher zweistelligen Jahreszahl 20xx angenommen wird
    USHORT nTabDistance;			// Abstand Standardtabulatoren
    BOOL   bIsIgnoreCase;			// Gross-/Kleinschr. bei Vergleichen
    BOOL   bIsIter;					// Iteration bei cirk. Ref
    BOOL   bCalcAsShown;			// berechnen wie angezeigt (Precision)
    BOOL   bMatchWholeCell;			// Suchkriterien muessen ganze Zelle matchen
    BOOL   bDoAutoSpell;			// Auto-Spelling
    BOOL   bLookUpColRowNames;		// Spalten-/Zeilenbeschriftungen automagisch suchen
    BOOL   bFormulaRegexEnabled;    // regular expressions in formulas enabled

public:
                ScDocOptions();
                ScDocOptions( const ScDocOptions& rCpy );
                ~ScDocOptions();

    BOOL   IsLookUpColRowNames() const	{ return bLookUpColRowNames; }
    void   SetLookUpColRowNames( BOOL bVal ) { bLookUpColRowNames = bVal; }
    BOOL   IsAutoSpell() const			{ return bDoAutoSpell; }
    void   SetAutoSpell( BOOL bVal )	{ bDoAutoSpell = bVal; }
    BOOL   IsMatchWholeCell() const		{ return bMatchWholeCell; }
    void   SetMatchWholeCell( BOOL bVal ){ bMatchWholeCell = bVal; }
    BOOL   IsIgnoreCase() const			{ return bIsIgnoreCase; }
    void   SetIgnoreCase( BOOL bVal )	{ bIsIgnoreCase = bVal; }
    BOOL   IsIter() const				{ return bIsIter; }
    void   SetIter( BOOL bVal )			{ bIsIter = bVal; }
    USHORT GetIterCount() const			{ return nIterCount; }
    void   SetIterCount( USHORT nCount) { nIterCount = nCount; }
    double GetIterEps() const			{ return fIterEps; }
    void   SetIterEps( double fEps )	{ fIterEps = fEps; }

    void   GetDate( USHORT& rD, USHORT& rM, USHORT& rY ) const
                                        { rD = nDay; rM = nMonth; rY = nYear;}
    void   SetDate (USHORT nD, USHORT nM, USHORT nY)
                                        { nDay = nD; nMonth = nM; nYear = nY; }
    USHORT GetTabDistance() const { return nTabDistance;}
    void   SetTabDistance( USHORT nTabDist ) {nTabDistance = nTabDist;}

    void		ResetDocOptions();
    inline void		CopyTo(ScDocOptions& rOpt);
    void		Load(SvStream& rStream);
    void		Save(SvStream& rStream, BOOL bConfig = FALSE) const;

    inline const ScDocOptions&	operator=( const ScDocOptions& rOpt );
    inline int					operator==( const ScDocOptions& rOpt ) const;
    inline int					operator!=( const ScDocOptions& rOpt ) const;

    USHORT	GetStdPrecision() const 	{ return nPrecStandardFormat; }
    void	SetStdPrecision( USHORT n ) { nPrecStandardFormat = n; }

    BOOL	IsCalcAsShown() const		{ return bCalcAsShown; }
    void	SetCalcAsShown( BOOL bVal )	{ bCalcAsShown = bVal; }

    void	SetYear2000( USHORT nVal )	{ nYear2000 = nVal; }
    USHORT	GetYear2000() const			{ return nYear2000; }

    void    SetFormulaRegexEnabled( BOOL bVal ) { bFormulaRegexEnabled = bVal; }
    BOOL    IsFormulaRegexEnabled() const       { return bFormulaRegexEnabled; }
};


inline void ScDocOptions::CopyTo(ScDocOptions& rOpt)
{
    rOpt.bIsIgnoreCase			= bIsIgnoreCase;
    rOpt.bIsIter 				= bIsIter;
    rOpt.nIterCount 			= nIterCount;
    rOpt.fIterEps 				= fIterEps;
    rOpt.nPrecStandardFormat 	= nPrecStandardFormat;
    rOpt.nDay 					= nDay;
    rOpt.nMonth 				= nMonth;
    rOpt.nYear2000				= nYear2000;
    rOpt.nYear 					= nYear;
    rOpt.nTabDistance			= nTabDistance;
    rOpt.bCalcAsShown			= bCalcAsShown;
    rOpt.bMatchWholeCell		= bMatchWholeCell;
    rOpt.bDoAutoSpell			= bDoAutoSpell;
    rOpt.bLookUpColRowNames		= bLookUpColRowNames;
    rOpt.bFormulaRegexEnabled   = bFormulaRegexEnabled;
}

inline const ScDocOptions& ScDocOptions::operator=( const ScDocOptions& rCpy )
{
    bIsIgnoreCase		= rCpy.bIsIgnoreCase;
    bIsIter				= rCpy.bIsIter;
    nIterCount			= rCpy.nIterCount;
    fIterEps			= rCpy.fIterEps;
    nPrecStandardFormat = rCpy.nPrecStandardFormat;
    nDay				= rCpy.nDay;
    nMonth				= rCpy.nMonth;
    nYear				= rCpy.nYear;
    nYear2000			= rCpy.nYear2000;
    nTabDistance 		= rCpy.nTabDistance;
    bCalcAsShown		= rCpy.bCalcAsShown;
    bMatchWholeCell		= rCpy.bMatchWholeCell;
    bDoAutoSpell		= rCpy.bDoAutoSpell;
    bLookUpColRowNames	= rCpy.bLookUpColRowNames;
    bFormulaRegexEnabled= rCpy.bFormulaRegexEnabled;

    return *this;
}

inline int ScDocOptions::operator==( const ScDocOptions& rOpt ) const
{
    return (
                rOpt.bIsIgnoreCase			== bIsIgnoreCase
            &&	rOpt.bIsIter 				== bIsIter
            &&	rOpt.nIterCount 			== nIterCount
            &&	rOpt.fIterEps 				== fIterEps
            &&	rOpt.nPrecStandardFormat 	== nPrecStandardFormat
            &&	rOpt.nDay 					== nDay
            &&	rOpt.nMonth 				== nMonth
            &&	rOpt.nYear 					== nYear
            &&	rOpt.nYear2000				== nYear2000
            &&  rOpt.nTabDistance 			== nTabDistance
            &&	rOpt.bCalcAsShown			== bCalcAsShown
            &&	rOpt.bMatchWholeCell		== bMatchWholeCell
            &&	rOpt.bDoAutoSpell			== bDoAutoSpell
            &&	rOpt.bLookUpColRowNames		== bLookUpColRowNames
            &&  rOpt.bFormulaRegexEnabled   == bFormulaRegexEnabled
            );
}

inline int ScDocOptions::operator!=( const ScDocOptions& rOpt ) const
{
    return !(operator==(rOpt));
}

//==================================================================
// Item fuer Einstellungsdialog - Berechnen
//==================================================================

//STRIP001 class ScTpCalcItem : public SfxPoolItem
//STRIP001 {
//STRIP001 public:
//STRIP001 				TYPEINFO();
//STRIP001 				ScTpCalcItem( USHORT nWhich );
//STRIP001 				ScTpCalcItem( USHORT nWhich,
//STRIP001 							  const ScDocOptions& rOpt );
//STRIP001 				ScTpCalcItem( const ScTpCalcItem& rItem );
//STRIP001 				~ScTpCalcItem();
//STRIP001 
//STRIP001 	virtual String          GetValueText() const;
//STRIP001 	virtual int             operator==( const SfxPoolItem& ) const;
//STRIP001 	virtual SfxPoolItem*    Clone( SfxItemPool *pPool = 0 ) const;
//STRIP001 
//STRIP001 	const ScDocOptions&	GetDocOptions() const { return theOptions; }
//STRIP001 
//STRIP001 private:
//STRIP001 	ScDocOptions theOptions;
//STRIP001 };

//==================================================================
//	Config Item containing document options
//==================================================================

class ScDocCfg : public ScDocOptions
{
    ScLinkConfigItem	aCalcItem;
    ScLinkConfigItem	aLayoutItem;

    DECL_LINK( CalcCommitHdl, void* );
    DECL_LINK( LayoutCommitHdl, void* );

    ::com::sun::star::uno::Sequence<rtl::OUString> GetCalcPropertyNames();
    ::com::sun::star::uno::Sequence<rtl::OUString> GetLayoutPropertyNames();

public:
            ScDocCfg();

//STRIP001 	void	SetOptions( const ScDocOptions& rNew );
};


} //namespace binfilter
#endif

