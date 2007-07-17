/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: srchitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2007-07-17 12:44:03 $
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
#ifndef _SFX_SRCHITEM_HXX
#define _SFX_SRCHITEM_HXX

// include ---------------------------------------------------------------
#ifndef _COM_SUN_STAR_UTIL_XSEARCHDESCRIPTOR_HPP_
#include <com/sun/star/util/XSearchDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SEARCHOPTIONS_HPP_
#include <com/sun/star/util/SearchOptions.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_SEARCHFLAGS_HPP_
#include <com/sun/star/util/SearchFlags.hpp>
#endif
#ifndef _COM_SUN_STAR_I18N_TRANSLITERATIONMODULES_HPP_
#include <com/sun/star/i18n/TransliterationModules.hpp>
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
#ifndef _RSCSFX_HXX //autogen
#include <rsc/rscsfx.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif

#ifndef _SFX_SRCHDEFS_HXX_
#include <bf_sfx2/srchdefs.hxx>
#endif
namespace binfilter {

// defines ---------------------------------------------------------------

// Kommandos
#define		SVX_SEARCHCMD_FIND			((sal_uInt16)0)
#define		SVX_SEARCHCMD_FIND_ALL		((sal_uInt16)1)
#define		SVX_SEARCHCMD_REPLACE		((sal_uInt16)2)
#define		SVX_SEARCHCMD_REPLACE_ALL	((sal_uInt16)3)

// Suche in (fuer Calc)
#define		SVX_SEARCHIN_FORMULA		((sal_uInt16)0)
#define		SVX_SEARCHIN_VALUE			((sal_uInt16)1)
#define		SVX_SEARCHIN_NOTE			((sal_uInt16)2)

// Applicationsflag
#define		SVX_SEARCHAPP_WRITER		((sal_uInt16)0)
#define		SVX_SEARCHAPP_CALC			((sal_uInt16)1)
#define		SVX_SEARCHAPP_DRAW			((sal_uInt16)2)
#define		SVX_SEARCHAPP_BASE			((sal_uInt16)3)

// class SvxSearchItem ---------------------------------------------------

#ifdef ITEMID_SEARCH

/*	[Beschreibung]

    In diesem Item werden alle Such-Attribute gespeichert.
*/
class SvxSearchItem :
        public SfxPoolItem,
        public ::utl::ConfigItem
{
    ::com::sun::star::util::SearchOptions	aSearchOpt;

    SfxStyleFamily	eFamily;			// Vorlagen-Familie

    sal_uInt16		nCommand;			// Kommando (Suchen, Alle Suchen, Ersetzen, Alle Ersetzen)

    // Calc-Spezifische Daten
    sal_uInt16		nCellType;			// Suche in Formeln/Werten/Notizen
    sal_uInt16		nAppFlag;   		// Fuer welche Applikation ist der Dialog ueberhaupt
    sal_Bool		bRowDirection;		// Suchrichtung Zeilenweise/Spaltenweise
    sal_Bool		bAllTables;			// in alle Tabellen suchen

    sal_Bool		bBackward;          // Suche Rueckwaerts
    sal_Bool		bPattern;           // Suche nach Vorlagen
    sal_Bool		bContent;			// Suche im Inhalt
    sal_Bool		bAsianOptions;		// use asian options?

public:
    TYPEINFO();

    SvxSearchItem( const sal_uInt16 nId = ITEMID_SEARCH );
    SvxSearchItem( const SvxSearchItem& rItem );
    virtual ~SvxSearchItem();

    virtual	sal_Bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	sal_Bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );
    virtual int 			 operator == ( const SfxPoolItem& ) const;
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const;
    virtual SfxItemPresentation GetPresentation( SfxItemPresentation ePres,
                                    SfxMapUnit eCoreMetric,
                                    SfxMapUnit ePresMetric,
                                    String &rText, const IntlWrapper * = 0 ) const;

    // ConfigItem
    virtual void 			Notify( const ::com::sun::star::uno::Sequence< ::rtl::OUString > &rPropertyNames );

            sal_uInt16		GetCommand() const { return nCommand; }
            void			SetCommand(sal_uInt16 nNewCommand) { nCommand = nNewCommand; }

    inline 	const String	GetSearchString() const;
    inline 	void			SetSearchString(const String& rNewString);

    inline 	const String	GetReplaceString() const;
    inline 	void	   		SetReplaceString(const String& rNewString);

    inline 	sal_Bool		GetWordOnly() const;
            void			SetWordOnly(sal_Bool bNewWordOnly);

    inline 	sal_Bool		GetExact() const;
            void			SetExact(sal_Bool bNewExact);

            sal_Bool		GetBackward() const { return bBackward; }
            void			SetBackward(sal_Bool bNewBackward) { bBackward = bNewBackward; }

    inline sal_Bool			GetSelection() const;
            void			SetSelection(sal_Bool bNewSelection);

    inline	sal_Bool		GetRegExp() const;
            void			SetRegExp( sal_Bool bVal );

            sal_Bool		GetPattern() const { return bPattern; }
            void			SetPattern(sal_Bool bNewPattern) { bPattern = bNewPattern; }

            sal_Bool		IsContent() const { return bContent; }
            void			SetContent( sal_Bool bNew ) { bContent = bNew; }

            SfxStyleFamily	GetFamily() const { return eFamily; }
            void			SetFamily( SfxStyleFamily eNewFamily )
                                { eFamily = eNewFamily; }

            sal_Bool		GetRowDirection() const { return bRowDirection; }
            void			SetRowDirection(sal_Bool bNewRowDirection) { bRowDirection = bNewRowDirection; }

            sal_Bool		IsAllTables() const { return bAllTables; }
            void			SetAllTables(sal_Bool bNew) { bAllTables = bNew; }

            sal_uInt16		GetCellType() const { return nCellType; }
            void			SetCellType(sal_uInt16 nNewCellType) { nCellType = nNewCellType; }

            sal_uInt16		GetAppFlag() const { return nAppFlag; }
            void			SetAppFlag(sal_uInt16 nNewAppFlag) { nAppFlag = nNewAppFlag; }

    inline	sal_Bool 		IsLevenshtein() const;
            void			SetLevenshtein( sal_Bool bVal );

    inline	sal_Bool 		IsLEVRelaxed() const;
            void	        SetLEVRelaxed(sal_Bool bSet);

    inline	sal_uInt16		GetLEVOther() const;
    inline	void			SetLEVOther(sal_uInt16 nSet);

    inline	sal_uInt16		GetLEVShorter() const;
    inline	void			SetLEVShorter(sal_uInt16 nSet);

    inline	sal_uInt16		GetLEVLonger() const;
    inline	void			SetLEVLonger(sal_uInt16 nSet);

            void			GetFromDescriptor( const ::com::sun::star::uno::Reference< ::com::sun::star::util::XSearchDescriptor > & rDescr );
            void			SetToDescriptor( ::com::sun::star::uno::Reference< ::com::sun::star::util::XSearchDescriptor > & rDescr );

    inline const ::com::sun::star::util::SearchOptions &
                GetSearchOptions() const;
    inline void	SetSearchOptions( const ::com::sun::star::util::SearchOptions &rOpt );

    inline 	sal_Int32		GetTransliterationFlags() const;
            void			SetTransliterationFlags( sal_Int32 nFlags );

    inline 	sal_Bool		IsMatchFullHalfWidthForms() const;
    void					SetMatchFullHalfWidthForms( sal_Bool bVal );

    inline 	sal_Bool		IsUseAsianOptions() const			{ return bAsianOptions; }
    inline 	void			SetUseAsianOptions( sal_Bool bVal )	{ bAsianOptions = bVal; }
};

const String SvxSearchItem::GetSearchString() const
{
    return aSearchOpt.searchString;
}

void SvxSearchItem::SetSearchString(const String& rNewString)
{
    aSearchOpt.searchString = rNewString;
}

const String SvxSearchItem::GetReplaceString() const
{
    return aSearchOpt.replaceString;
}

void SvxSearchItem::SetReplaceString(const String& rNewString)
{
    aSearchOpt.replaceString = rNewString;
}

sal_Bool SvxSearchItem::GetWordOnly() const
{
    return 0 != (aSearchOpt.searchFlag &
                        ::com::sun::star::util::SearchFlags::NORM_WORD_ONLY);
}

sal_Bool SvxSearchItem::GetExact() const
{
    return 0 == (aSearchOpt.transliterateFlags &
                        ::com::sun::star::i18n::TransliterationModules_IGNORE_CASE);
}

sal_Bool SvxSearchItem::GetSelection() const
{
    return 0 != (aSearchOpt.searchFlag &
                        ::com::sun::star::util::SearchFlags::REG_NOT_BEGINOFLINE);
}

sal_Bool SvxSearchItem::GetRegExp() const
{
    return aSearchOpt.algorithmType == ::com::sun::star::util::SearchAlgorithms_REGEXP ;
}

sal_Bool SvxSearchItem::IsLEVRelaxed() const
{
    return 0 != (aSearchOpt.searchFlag &
                        ::com::sun::star::util::SearchFlags::LEV_RELAXED);
}

sal_uInt16 SvxSearchItem::GetLEVOther() const
{
    return (INT16) aSearchOpt.changedChars;
}

void SvxSearchItem::SetLEVOther( sal_uInt16 nVal )
{
    aSearchOpt.changedChars = nVal;
}

sal_uInt16 SvxSearchItem::GetLEVShorter() const
{
    return (INT16) aSearchOpt.insertedChars;
}

void SvxSearchItem::SetLEVShorter( sal_uInt16 nVal )
{
    aSearchOpt.insertedChars = nVal;
}

sal_uInt16 SvxSearchItem::GetLEVLonger() const
{
    return (INT16) aSearchOpt.deletedChars;
}

void SvxSearchItem::SetLEVLonger( sal_uInt16 nVal )
{
    aSearchOpt.deletedChars = nVal;
}

sal_Bool SvxSearchItem::IsLevenshtein() const
{
    return aSearchOpt.algorithmType == ::com::sun::star::util::SearchAlgorithms_APPROXIMATE;
}

const ::com::sun::star::util::SearchOptions & SvxSearchItem::GetSearchOptions() const
{
    return aSearchOpt;
}

void SvxSearchItem::SetSearchOptions( const ::com::sun::star::util::SearchOptions &rOpt )
{
    aSearchOpt = rOpt;
}

sal_Int32 SvxSearchItem::GetTransliterationFlags() const
{
    return aSearchOpt.transliterateFlags;
}

sal_Bool SvxSearchItem::IsMatchFullHalfWidthForms() const
{
    return 0 != (aSearchOpt.transliterateFlags &
                        ::com::sun::star::i18n::TransliterationModules_IGNORE_WIDTH);
}

#endif

}//end of namespace binfilter
#endif

