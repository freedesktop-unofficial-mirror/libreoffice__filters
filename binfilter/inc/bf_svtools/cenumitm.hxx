/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: cenumitm.hxx,v $
 * $Revision: 1.3 $
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

#ifndef _SVTOOLS_CENUMITM_HXX
#define _SVTOOLS_CENUMITM_HXX

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif

namespace binfilter {

//============================================================================
DBG_NAMEEX(SfxEnumItemInterface)

class  SfxEnumItemInterface: public SfxPoolItem
{
protected:
    SfxEnumItemInterface(USHORT which): SfxPoolItem(which) {}

    SfxEnumItemInterface(const SfxEnumItemInterface & rItem):
        SfxPoolItem(rItem) {}

public:
    TYPEINFO();

    virtual int operator ==(const SfxPoolItem & rItem) const;

    virtual SfxItemPresentation GetPresentation(SfxItemPresentation,
                                                SfxMapUnit, SfxMapUnit,
                                                XubString & rText,
                                                const ::IntlWrapper * = 0)
        const;

    virtual	BOOL QueryValue(::com::sun::star::uno::Any & rVal, BYTE = 0) const;

    virtual	BOOL PutValue(const ::com::sun::star::uno::Any & rVal, BYTE = 0);

    virtual USHORT GetValueCount() const = 0;

    virtual XubString GetValueTextByPos(USHORT nPos) const;

    virtual USHORT GetValueByPos(USHORT nPos) const;

    /// Return the position of some value within this enumeration.
    ///
    /// @descr  This method is implemented using GetValueCount() and
    /// GetValueByPos().  Derived classes may replace this with a more
    /// efficient implementation.
    ///
    /// @param nValue  Some value.
    ///
    /// @return  The position of nValue within this enumeration, or USHRT_MAX
    /// if not included.
    virtual USHORT GetPosByValue(USHORT nValue) const;

    virtual BOOL IsEnabled(USHORT nValue) const;

    virtual USHORT GetEnumValue() const = 0;

    virtual void SetEnumValue(USHORT nValue) = 0;

    virtual int HasBoolValue() const;

    virtual BOOL GetBoolValue() const;

    virtual void SetBoolValue(BOOL bValue);
};

//============================================================================
DBG_NAMEEX(CntEnumItem)

class  CntEnumItem: public SfxEnumItemInterface
{
    USHORT m_nValue;

protected:
    CntEnumItem(USHORT which = 0, USHORT nTheValue = 0):
        SfxEnumItemInterface(which), m_nValue(nTheValue) {}

    CntEnumItem(USHORT which, SvStream & rStream);

    CntEnumItem(const CntEnumItem & rItem):
        SfxEnumItemInterface(rItem), m_nValue(rItem.m_nValue) {}

public:
    TYPEINFO();

    virtual SvStream & Store(SvStream & rStream, USHORT) const;

    virtual USHORT GetEnumValue() const;

    virtual void SetEnumValue(USHORT nTheValue);

    USHORT GetValue() const { return m_nValue; }

    inline void SetValue(USHORT nTheValue);
};

inline void CntEnumItem::SetValue(USHORT nTheValue)
{
    DBG_ASSERT(GetRefCount() == 0, "CntEnumItem::SetValue(): Pooled item");
    m_nValue = nTheValue;
}

//============================================================================
DBG_NAMEEX(CntBoolItem)

class  CntBoolItem: public SfxPoolItem
{
    BOOL m_bValue;

public:
    TYPEINFO();

    CntBoolItem(USHORT which = 0, BOOL bTheValue = FALSE):
        SfxPoolItem(which), m_bValue(bTheValue) {}

    CntBoolItem(USHORT nWhich, SvStream & rStream);

    CntBoolItem(const CntBoolItem & rItem):
        SfxPoolItem(rItem), m_bValue(rItem.m_bValue) {}

    virtual int operator ==(const SfxPoolItem & rItem) const;

    using SfxPoolItem::Compare;
    virtual int Compare(const SfxPoolItem & rWith) const;

    virtual SfxItemPresentation GetPresentation(SfxItemPresentation,
                                                SfxMapUnit, SfxMapUnit,
                                                UniString & rText,
                                                const ::IntlWrapper * = 0)
        const;

    virtual	BOOL QueryValue(::com::sun::star::uno::Any& rVal, BYTE = 0) const;

    virtual	BOOL PutValue(const ::com::sun::star::uno::Any& rVal, BYTE = 0);

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SvStream & Store(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const;

    virtual USHORT GetValueCount() const;

    virtual UniString GetValueTextByVal(BOOL bTheValue) const;

    BOOL GetValue() const { return m_bValue; }

    void SetValue(BOOL bTheValue) { m_bValue = bTheValue; }
};

}

#endif // _SVTOOLS_CENUMITM_HXX

