/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: extcolorcfg.hxx,v $
 * $Revision: 1.4 $
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
#ifndef INCLUDED_SVTOOLS_EXTCOLORCFG_HXX
#define INCLUDED_SVTOOLS_EXTCOLORCFG_HXX

#ifndef INCLUDED_SVTDLLAPI_H
#include "bf_svtools/svtdllapi.h"
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _COM_SUN_STAR_UNO_SEQUENCE_H_
#include <com/sun/star/uno/Sequence.h>
#endif
#ifndef _SFXBRDCST_HXX
#include <bf_svtools/brdcst.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <bf_svtools/lstner.hxx>
#endif

//-----------------------------------------------------------------------------
namespace binfilter
{
/* -----------------------------22.03.2002 15:36------------------------------

 ---------------------------------------------------------------------------*/
class ExtendedColorConfig_Impl;
class ExtendedColorConfigValue
{
    ::rtl::OUString m_sName;
    ::rtl::OUString m_sDisplayName;
    sal_Int32		m_nColor;
    sal_Int32		m_nDefaultColor;
public:
    ExtendedColorConfigValue() : m_nColor(0),m_nDefaultColor(0){}
    ExtendedColorConfigValue(const ::rtl::OUString& _sName
                            ,const ::rtl::OUString& _sDisplayName
                            ,sal_Int32		_nColor
                            ,sal_Int32		_nDefaultColor) 
    : m_sName(_sName)
    ,m_sDisplayName(_sDisplayName)
    ,m_nColor(_nColor)
    ,m_nDefaultColor(_nDefaultColor) 
    {}

    inline ::rtl::OUString getName()         const { return m_sName; }
    inline ::rtl::OUString getDisplayName()  const { return m_sDisplayName; }
    inline sal_Int32	   getColor()        const { return m_nColor; }
    inline sal_Int32	   getDefaultColor() const { return m_nDefaultColor; }

    inline void	setColor(sal_Int32 _nColor) { m_nColor = _nColor; }

    sal_Bool operator !=(const ExtendedColorConfigValue& rCmp) const
        { return m_nColor != rCmp.m_nColor;}
};
/* -----------------------------22.03.2002 15:36------------------------------

 ---------------------------------------------------------------------------*/
class  ExtendedColorConfig : public SfxBroadcaster, public SfxListener
{
    friend class ExtendedColorConfig_Impl;
private:
    static ExtendedColorConfig_Impl* m_pImpl;
public:
    ExtendedColorConfig();
    ~ExtendedColorConfig();

    virtual void        Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
};
/* -----------------------------22.03.2002 15:31------------------------------

 ---------------------------------------------------------------------------*/
class  EditableExtendedColorConfig
{
    ExtendedColorConfig_Impl*   m_pImpl;
    sal_Bool            m_bModified;
public:
    EditableExtendedColorConfig();
    ~EditableExtendedColorConfig();

    sal_Bool                                            LoadScheme(const ::rtl::OUString& rScheme );
    void                        ClearModified(){m_bModified = sal_False;}
    sal_Bool                    IsModified()const{return m_bModified;}
};
}
#endif

