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

#ifndef _SCH_SCHOPT_HXX
#define _SCH_SCHOPT_HXX

#include <bf_svtools/bf_solar.h>

// header for TYPEINFO
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif
// header for ConfigItem
#ifndef _UTL_CONFIGITEM_HXX_ 
#include <unotools/configitem.hxx>
#endif
// header for SfxPoolItem
#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif
// header for Color
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
// header for Table
#ifndef _TOOLS_TABLE_HXX
#include <tools/table.hxx>
#endif
// header for XColorEntry
#ifndef _XTABLE_HXX
#include <bf_svx/xtable.hxx>   //STRIP002 
#endif
namespace binfilter {

// --------------------
// default colors
// --------------------
class SchColorTable : private Table
{
public:
    SchColorTable();
    virtual ~SchColorTable() {}


    // make public
    Table::Count;

    // specialized methods from Table
    void			ClearAndDestroy();

    BOOL			Insert( ULONG nKey, XColorEntry* );
    XColorEntry*	Get( ULONG nKey ) const;

    Color			GetColor( ULONG nKey ) const;
    ColorData		GetColorData( ULONG nKey ) const;

    BOOL			operator ==( const SchColorTable& rCol ) const
                    { return Table::operator ==( rCol ); }
    BOOL			operator !=( const SchColorTable& rCol ) const
                    { return Table::operator !=( rCol ); }
};

// ====================
// all options
// ====================
class SchOptions : public ::utl::ConfigItem
{
private:
    SchColorTable		maDefColors;
    BOOL				mbIsInitialized;
    ::com::sun::star::uno::Sequence< ::rtl::OUString > maPropertyNames;

    ::com::sun::star::uno::Sequence< ::rtl::OUString > GetPropertyNames() const
        { return maPropertyNames; }
    BOOL RetrieveOptions();

public:
    SchOptions();
    virtual ~SchOptions();
void Notify( const ::com::sun::star::uno::Sequence< rtl::OUString >& aPropertyNames );
void Commit();

    const SchColorTable& GetDefaultColors();

};

// ====================
// items
// ====================

} //namespace binfilter
#endif	// _SCH_SCHOPT_HXX

