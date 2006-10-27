/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: impex.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 16:14:11 $
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

#ifndef SC_IMPEX_HXX
#define SC_IMPEX_HXX

#ifndef _SOT_EXCHANGE_HXX //autogen
#include <sot/exchange.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef _OSL_ENDIAN_H_
#include <osl/endian.h>
#endif
class SvStream;
namespace binfilter {

class ScDocShell;
class ScDocument;
class SfxMedium;
class ScAsciiOptions;

class ScImportExport
{
    ScDocShell* pDocSh;
    ScDocument* pDoc;
    ScDocument* pUndoDoc;
    ScRange     aRange;
    String		aStreamPath;
    String      aNonConvertibleChars;
    ULONG		nSizeLimit;
    sal_Unicode	cSep;					// Separator
    sal_Unicode	cStr;					// String Delimiter
    BOOL		bFormulas;				// Formeln im Text?
    BOOL		bIncludeFiltered;		// include filtered rows? (default true)
    BOOL		bAll;					// keine Selektion
    BOOL		bSingle;				// Einfachselektion
    BOOL		bUndo;					// Mit Undo?
    BOOL		bOverflow;				// zuviele Zeilen/Spalten

    ScAsciiOptions*	pExtOptions;		// erweiterte Optionen

    BOOL ExtText2Doc( SvStream& );		// mit pExtOptions

    //! only if stream is only used in own (!) memory

public:
    ScImportExport( ScDocument* );					// Gesamtdokument
   ~ScImportExport();

    void SetExtOptions( const ScAsciiOptions& rOpt );

    BOOL IsDoubleRef() const { return BOOL( !( bAll || bSingle ) ); }
    BOOL IsSingleRef() const { return bSingle; }
    BOOL IsNoRef() const	 { return bAll;    }
    BOOL IsRef() const	 	 { return BOOL( !bAll ); }

    const ScRange& GetRange() const { return aRange; }

    BOOL IsUndo() const		 { return bUndo; }
    void SetUndo( BOOL b )	 { bUndo = b;	 }

    static const sal_Unicode* ScanNextFieldFromString( const sal_Unicode* p,
            String& rField, sal_Unicode cStr, const sal_Unicode* pSeps, BOOL bMergeSeps );
    static	inline	BOOL	IsEndianSwap( const SvStream& rStrm );

    sal_Unicode GetSeparator() const { return cSep; }
    void SetSeparator( sal_Unicode c ) { cSep = c; }
    sal_Unicode GetDelimiter() const { return cStr; }
    void SetDelimiter( sal_Unicode c ) { cStr = c; }
    BOOL IsFormulas() const { return bFormulas; }
    void SetFormulas( BOOL b ) { bFormulas = b; }
    BOOL IsIncludeFiltered() const { return bIncludeFiltered; }
    void SetIncludeFiltered( BOOL b ) { bIncludeFiltered = b; }

    void SetSizeLimit( ULONG nNew ) { nSizeLimit = nNew; }	// momentan nur fuer Ascii

    void			SetStreamPath( const String& rPath ) { aStreamPath = rPath; }
    const String&	GetStreamPath() const { return aStreamPath; }


    BOOL ImportStream( SvStream&, ULONG=FORMAT_STRING );


    BOOL IsOverflow() const	{ return bOverflow; }		// nach dem Importieren

    const String& GetNonConvertibleChars() const { return aNonConvertibleChars; }
};


// static
inline BOOL ScImportExport::IsEndianSwap( const SvStream& rStrm )
{
#ifdef OSL_BIGENDIAN
    return rStrm.GetNumberFormatInt() != NUMBERFORMAT_INT_BIGENDIAN;
#else
    return rStrm.GetNumberFormatInt() != NUMBERFORMAT_INT_LITTLEENDIAN;
#endif
}


} //namespace binfilter
#endif

