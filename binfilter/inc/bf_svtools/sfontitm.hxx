/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfontitm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:26:50 $
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

#ifndef _SFONTITM_HXX
#define _SFONTITM_HXX

#ifndef _TOOLS_COLOR_HXX
#include <tools/color.hxx>
#endif
#ifndef _SV_GEN_HXX
#include <tools/gen.hxx>
#endif
#ifndef INCLUDED_I18NPOOL_LANG_H
#include <i18npool/lang.h>
#endif

#ifndef _SFXPOOLITEM_HXX
#include <bf_svtools/poolitem.hxx>
#endif

namespace binfilter
{

//============================================================================
class SfxFontItem: public SfxPoolItem
{
    XubString m_aName;
    XubString m_aStyleName;
    Size m_aSize;
    Color m_aColor;
    Color m_aFillColor;
    rtl_TextEncoding m_nCharSet;
    LanguageType m_nLanguage;
    sal_Int16 m_nFamily;
    sal_Int16 m_nPitch;
    sal_Int16 m_nWeight;
    sal_Int16 m_nWidthType;
    sal_Int16 m_nItalic;
    sal_Int16 m_nUnderline;
    sal_Int16 m_nStrikeout;
    sal_Int16 m_nOrientation;
    unsigned m_bWordLine: 1;
    unsigned m_bOutline: 1;
    unsigned m_bShadow: 1;
    unsigned m_bKerning: 1;
    unsigned m_bHasFont: 1;
    unsigned m_bHasColor: 1;
    unsigned m_bHasFillColor: 1;

public:
    TYPEINFO();

    inline SfxFontItem(USHORT nWhich);

    virtual	int operator ==(const SfxPoolItem & rItem) const;

    virtual SfxPoolItem * Create(SvStream & rStream, USHORT) const;

    virtual SvStream & Store(SvStream & rStream, USHORT) const;

    virtual SfxPoolItem * Clone(SfxItemPool * = 0) const
    { return new SfxFontItem(*this); }

    sal_Bool hasFont() const { return m_bHasFont; }

    sal_Bool hasColor() const { return m_bHasColor; }

    sal_Bool hasFillColor() const { return m_bHasFillColor; }

    const XubString & getName() const { return m_aName; }

    const XubString & getStyleName() const { return m_aStyleName; }

    const Size & getSize() const { return m_aSize; }

    const Color & getColor() const { return m_aColor; }

    const Color & getFillColor() const { return m_aFillColor; }

    rtl_TextEncoding getCharSet() const { return m_nCharSet; }

    LanguageType getLanguage() const { return m_nLanguage; }

    sal_Int16 getFamily() const { return m_nFamily; }

    sal_Int16 getPitch() const { return m_nPitch; }

    sal_Int16 getWeight() const { return m_nWeight; }

    sal_Int16 getWidthType() const { return m_nWidthType; }

    sal_Int16 getItalic() const { return m_nItalic; }

    sal_Int16 getUnderline() const { return m_nUnderline; }

    sal_Int16 getStrikeout() const { return m_nStrikeout; }

    sal_Int16 getOrientation() const { return m_nOrientation; }

    sal_Bool getWordLine() const { return m_bWordLine; }

    sal_Bool getOutline() const { return m_bOutline; }

    sal_Bool getShadow() const { return m_bShadow; }

    sal_Bool getKerning() const { return m_bKerning; }

    inline void setFont(sal_Int16 nTheFamily, const XubString & rTheName,
                        const XubString & rTheStyleName, sal_Int16 nThePitch,
                        rtl_TextEncoding nTheCharSet);

    inline void setWeight(sal_Int16 nTheWeight);

    inline void setItalic(sal_Int16 nTheItalic);

    inline void setHeight(sal_Int32 nHeight);

    inline void setColor(const Color & rTheColor);

    inline void setFillColor(const Color & rTheFillColor);

    inline void setUnderline(sal_Int16 nTheUnderline);

    inline void setStrikeout(sal_Int16 nTheStrikeout);

    inline void setOutline(sal_Bool bTheOutline);

    inline void setShadow(sal_Bool bTheShadow);

    inline void setLanguage(LanguageType nTheLanguage);
};

inline SfxFontItem::SfxFontItem(USHORT which):
    SfxPoolItem(which),
    m_nCharSet(RTL_TEXTENCODING_DONTKNOW),
    m_nLanguage(LANGUAGE_DONTKNOW),
    m_nFamily(0), // FAMILY_DONTKNOW
    m_nPitch(0), // PITCH_DONTKNOW
    m_nWeight(0), // WEIGHT_DONTKNOW
    m_nWidthType(0), // WIDTH_DONTKNOW
    m_nItalic(3), // ITALIC_DONTKNOW
    m_nUnderline(4), // UNDERLINE_DONTKNOW
    m_nStrikeout(3), // STRIKEOUT_DONTKNOW
    m_nOrientation(0),
    m_bWordLine(sal_False),
    m_bOutline(sal_False),
    m_bShadow(sal_False),
    m_bKerning(sal_False),
    m_bHasFont(sal_False),
    m_bHasColor(sal_False),
    m_bHasFillColor(sal_False)
{}

inline void SfxFontItem::setFont(sal_Int16 nTheFamily,
                                 const XubString & rTheName,
                                 const XubString & rTheStyleName,
                                 sal_Int16 nThePitch,
                                 rtl_TextEncoding nTheCharSet)
{
    m_nFamily = nTheFamily;
    m_aName = rTheName;
    m_aStyleName = rTheStyleName;
    m_nPitch = nThePitch;
    m_nCharSet = nTheCharSet;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setWeight(sal_Int16 nTheWeight)
{
    m_nWeight = nTheWeight;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setItalic(sal_Int16 nTheItalic)
{
    m_nItalic = nTheItalic;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setHeight(sal_Int32 nHeight)
{
    m_aSize.setHeight(nHeight);
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setColor(const Color & rTheColor)
{
    m_aColor = rTheColor;
    m_bHasColor = sal_True;
}

inline void SfxFontItem::setFillColor(const Color & rTheFillColor)
{
    m_aFillColor = rTheFillColor;
    m_bHasFillColor = sal_True;
}

inline void SfxFontItem::setUnderline(sal_Int16 nTheUnderline)
{
    m_nUnderline = nTheUnderline;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setStrikeout(sal_Int16 nTheStrikeout)
{
    m_nStrikeout = nTheStrikeout;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setOutline(sal_Bool bTheOutline)
{
    m_bOutline = bTheOutline;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setShadow(sal_Bool bTheShadow)
{
    m_bShadow = bTheShadow;
    m_bHasFont = sal_True;
}

inline void SfxFontItem::setLanguage(LanguageType nTheLanguage)
{
    m_nLanguage = nTheLanguage;
    m_bHasFont = sal_True;
}

}

#endif // _SFONTITM_HXX

