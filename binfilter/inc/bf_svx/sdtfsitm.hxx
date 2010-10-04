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
#ifndef _SDTFSITM_HXX
#define _SDTFSITM_HXX

#ifndef _SFXENUMITEM_HXX //autogen
#include <bf_svtools/eitem.hxx>
#endif

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

enum SdrFitToSizeType {SDRTEXTFIT_NONE,         // - kein FitToSize
                       SDRTEXTFIT_PROPORTIONAL, // - Alle Buchstaben proportional umgroessern
                       SDRTEXTFIT_ALLLINES,     // - Zus. jede Zeile separat in der Breite stretchen
                       SDRTEXTFIT_RESIZEATTR};  // - Bei Rahmenumgroesserung (ausser Autogrow) wird
                                                //   die Schriftgroesse umattributiert (hart)

// Bei SDRTEXTFIT_PROPORTIONAL und SDRTEXTFIT_ALLLINES gibt es kein AutoGrow und
// keine automatischen Umbrueche.
// Ist SDRTEXTFIT_RESIZEATTR gesetzt, so wird beim umgroessern des Textrahmens
// (ausser bei AutoGrow) die Schrift durch harte Attributierung ebenfalls
// umgegroessert.
// Bei AutoGrowingWidth gibt es ebenfalls keine automatischen Umbrueche (erst bei
// TextMaxFrameWidth).

//--------------------------------
// class SdrTextFitToSizeTypeItem
//--------------------------------
class SdrTextFitToSizeTypeItem: public SfxEnumItem {
public:
    TYPEINFO();
    SdrTextFitToSizeTypeItem(SdrFitToSizeType eFit=SDRTEXTFIT_NONE): SfxEnumItem(SDRATTR_TEXT_FITTOSIZE,eFit) {}
    SdrTextFitToSizeTypeItem(SvStream& rIn)                        : SfxEnumItem(SDRATTR_TEXT_FITTOSIZE,rIn)  {}
    virtual SfxPoolItem*     Clone(SfxItemPool* pPool=NULL) const;
    virtual SfxPoolItem*     Create(SvStream& rIn, USHORT nVer) const;
    virtual USHORT           GetValueCount() const; // { return 4; }
            SdrFitToSizeType GetValue() const      { return (SdrFitToSizeType)SfxEnumItem::GetValue(); }

    virtual	bool        	 QueryValue( ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 ) const;
    virtual	bool			 PutValue( const ::com::sun::star::uno::Any& rVal, BYTE nMemberId = 0 );

};

}//end of namespace binfilter
#endif
