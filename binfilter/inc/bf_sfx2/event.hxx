/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: event.hxx,v $
 * $Revision: 1.5 $
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
#ifndef _SFXEVENT_HXX
#define _SFXEVENT_HXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SFXHINT_HXX //autogen
#include <bf_svtools/hint.hxx>
#endif

#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/beans/PropertyValue.hpp>
class PrintDialog;
class Printer;
namespace binfilter {

class SfxObjectShell;

//-------------------------------------------------------------------

class SfxEventHint : public SfxHint
{
    USHORT				nEventId;
    SfxObjectShell* 	pObjShell;
    String				_aArgs;
    BOOL				_bDummy;
    BOOL                _bAddToHistory;

public:
    TYPEINFO();
                        SfxEventHint( USHORT nId,
                                      const String& rArgs,
                                      SfxObjectShell *pObj = 0  )
                        :	nEventId(nId),
                            pObjShell(pObj),
                            _bAddToHistory(FALSE),
                            _aArgs( rArgs )
                        {}
                        SfxEventHint( USHORT nId, SfxObjectShell *pObj = 0 )
                        :	nEventId(nId),
                            pObjShell(pObj),
                            _bAddToHistory(FALSE)
                        {}

    const String& GetArgs() const {	return _aArgs;}

    USHORT				GetEventId() const
                        { return nEventId; }

    SfxObjectShell* 	GetObjShell() const
                        { return pObjShell; }
};

//-------------------------------------------------------------------

class SfxNamedHint : public SfxHint
{
    String				_aEventName;
    SfxObjectShell* 	_pObjShell;
    String				_aArgs;
    BOOL				_bDummy;
    BOOL                _bAddToHistory;

public:
                        TYPEINFO();

                        SfxNamedHint( const String& rName,
                                      const String& rArgs,
                                      SfxObjectShell *pObj = 0  )
                        :	_aEventName( rName ),
                            _pObjShell( pObj),
                            _bAddToHistory( FALSE ),
                            _aArgs( rArgs )
                        {}

                        SfxNamedHint( const String& rName,
                                      SfxObjectShell *pObj = 0 )
                        :	_aEventName( rName ),
                            _pObjShell( pObj ),
                            _bAddToHistory( FALSE )
                        {}

    const String&		GetArgs() const { return _aArgs;}
    const String&		GetName() const { return _aEventName; }
    SfxObjectShell*     GetObjShell() const { return _pObjShell; }
};

class SfxPrintingHint : public SfxHint
{
    PrintDialog*		pDialog;
    Printer*			pPrinter;
    sal_Int32			nWhich;
    ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue > aOpts;
public:
                        TYPEINFO();
                        SfxPrintingHint( sal_Int32 nEvent, PrintDialog* pDlg, Printer* pPrt, const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& rOpts )
                            : pDialog( pDlg )
                            , pPrinter( pPrt )
                            , nWhich( nEvent )
                            , aOpts( rOpts )
                        {}

                        SfxPrintingHint( sal_Int32 nEvent, PrintDialog* pDlg, Printer* pPrt )
                            : pDialog( pDlg )
                            , pPrinter( pPrt )
                            , nWhich( nEvent )
                        {}

    Printer*  			GetPrinter() const { return pPrinter; }
    PrintDialog*		GetPrintDialog() const { return pDialog; }
    sal_Int32			GetWhich() const { return nWhich; }
    const ::com::sun::star::uno::Sequence < ::com::sun::star::beans::PropertyValue >& GetAdditionalOptions() { return aOpts; }
};

}//end of namespace binfilter
#endif
