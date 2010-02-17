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

#ifndef _EDITATTR_HXX
#define	_EDITATTR_HXX

#include <eeitemid.hxx>
namespace binfilter {

class SvxFont;
class SvxFontItem;
class SvxWeightItem;
class SvxPostureItem;
class SvxShadowedItem;
class SvxEscapementItem;
class SvxContourItem;
class SvxCrossedOutItem;
class SvxUnderlineItem;
class SvxFontHeightItem;
class SvxCharScaleWidthItem;
class SvxColorItem;
class SvxAutoKernItem;
class SvxKerningItem;
class SvxCharSetColorItem;
class SvxWordLineModeItem;
class SvxFieldItem;
class SvxLanguageItem;
class SvxEmphasisMarkItem;
class SvxCharReliefItem;
}//end of namespace binfilter
#ifndef _SFXPOOLITEM_HXX //autogen
#include <bf_svtools/poolitem.hxx>
#endif
class SfxVoidItem;
namespace binfilter {


#define CH_FEATURE_OLD	(BYTE)			0xFF
#define CH_FEATURE		(sal_Unicode) 	0x01

// DEF_METRIC: Bei meinem Pool sollte immer die DefMetric bei
// GetMetric( nWhich ) ankommen!
// => Zum ermitteln der DefMetrik einfach ein GetMetric( 0 )
#define DEF_METRIC	0

// -------------------------------------------------------------------------
// class EditAttrib
// -------------------------------------------------------------------------
class EditAttrib
{
private:
            EditAttrib() {;}
            EditAttrib( const EditAttrib & ) {;}

protected:
    const SfxPoolItem*	pItem;

                        EditAttrib( const SfxPoolItem& rAttr );
    virtual				~EditAttrib();

public:
    // RemoveFromPool muss immer vorm DTOR Aufruf erfolgen!!
    void				RemoveFromPool( SfxItemPool& rPool );

    USHORT				Which() const	{ return pItem->Which(); }
    const SfxPoolItem*	GetItem() const	{ return pItem; }
};

// -------------------------------------------------------------------------
// class EditCharAttrib
// -------------------------------------------------------------------------
// bFeature: Attribut darf nicht expandieren/schrumfen, Laenge immer 1
// bEdge: Attribut expandiert nicht, wenn genau an der Kante expandiert werden soll
class EditCharAttrib : public EditAttrib
{
protected:

    USHORT 				nStart;
    USHORT 				nEnd;
    BOOL				bFeature	:1;
    BOOL				bEdge		:1;

public:
            EditCharAttrib( const SfxPoolItem& rAttr, USHORT nStart, USHORT nEnd );

    USHORT&			GetStart()					{ return nStart; }
    USHORT&			GetEnd()					{ return nEnd; }

    USHORT			GetStart() const			{ return nStart; }
    USHORT			GetEnd() const				{ return nEnd; }

    inline USHORT	GetLen() const;

    inline void		MoveForward( USHORT nDiff );
    inline void		MoveBackward( USHORT nDiff );

    inline void		Expand( USHORT nDiff );
    inline void		Collaps( USHORT nDiff );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );

    BOOL	IsIn( USHORT nIndex )
                { return ( ( nStart <= nIndex ) && ( nEnd >= nIndex ) ); }
    BOOL	IsInside( USHORT nIndex )
                { return ( ( nStart < nIndex ) && ( nEnd > nIndex ) ); }
    BOOL	IsEmpty()
                { return nStart == nEnd; }

    BOOL	IsFeature() const	{ return bFeature; }
    void	SetFeature( BOOL b) { bFeature = b; }

    BOOL	IsEdge() const		{ return bEdge; }
    void	SetEdge( BOOL b )	{ bEdge = b; }
};

inline USHORT EditCharAttrib::GetLen() const
{
    DBG_ASSERT( nEnd >= nStart, "EditCharAttrib: nEnd < nStart!" );
    return nEnd-nStart;
}

inline void EditCharAttrib::MoveForward( USHORT nDiff )
{
    DBG_ASSERT( ((long)nEnd + nDiff) <= 0xFFFF, "EditCharAttrib: MoveForward?!" );
    nStart += nDiff;
    nEnd += nDiff;
}

inline void EditCharAttrib::MoveBackward( USHORT nDiff )
{
    DBG_ASSERT( ((long)nStart - nDiff) >= 0, "EditCharAttrib: MoveBackward?!" );
    nStart -= nDiff;
    nEnd -= nDiff;
}

inline void	EditCharAttrib::Expand( USHORT nDiff )
{
    DBG_ASSERT( ( ((long)nEnd + nDiff) <= (long)0xFFFF ), "EditCharAttrib: Expand?!" );
    DBG_ASSERT( !bFeature, "Bitte keine Features expandieren!" );
    nEnd += nDiff;
}

inline void	EditCharAttrib::Collaps( USHORT nDiff )
{
    DBG_ASSERT( (long)nEnd - nDiff >= (long)nStart, "EditCharAttrib: Collaps?!" );
    DBG_ASSERT( !bFeature, "Bitte keine Features schrumpfen!" );
    nEnd -= nDiff;
}

// -------------------------------------------------------------------------
// class EditCharAttribFont
// -------------------------------------------------------------------------
class EditCharAttribFont: public EditCharAttrib
{
public:
    EditCharAttribFont( const SvxFontItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribWeight
// -------------------------------------------------------------------------
class EditCharAttribWeight : public EditCharAttrib
{
public:
    EditCharAttribWeight( const SvxWeightItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};
// -------------------------------------------------------------------------
// class EditCharAttribItalic
// -------------------------------------------------------------------------
class EditCharAttribItalic : public EditCharAttrib
{
public:
    EditCharAttribItalic( const SvxPostureItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribShadow
// -------------------------------------------------------------------------
class EditCharAttribShadow : public EditCharAttrib
{
public:
    EditCharAttribShadow( const SvxShadowedItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribEscapement
// -------------------------------------------------------------------------
class EditCharAttribEscapement : public EditCharAttrib
{
public:
    EditCharAttribEscapement( const SvxEscapementItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribOutline
// -------------------------------------------------------------------------
class EditCharAttribOutline : public EditCharAttrib
{
public:
    EditCharAttribOutline( const SvxContourItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribStrikeout
// -------------------------------------------------------------------------
class EditCharAttribStrikeout : public EditCharAttrib
{
public:
    EditCharAttribStrikeout( const SvxCrossedOutItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribUnderline
// -------------------------------------------------------------------------
class EditCharAttribUnderline : public EditCharAttrib
{
public:
    EditCharAttribUnderline( const SvxUnderlineItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribEmphasisMark
// -------------------------------------------------------------------------
class EditCharAttribEmphasisMark : public EditCharAttrib
{
public:
    EditCharAttribEmphasisMark( const SvxEmphasisMarkItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribRelief
// -------------------------------------------------------------------------
class EditCharAttribRelief : public EditCharAttrib
{
public:
    EditCharAttribRelief( const SvxCharReliefItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribFontHeight
// -------------------------------------------------------------------------
class EditCharAttribFontHeight : public EditCharAttrib
{
public:
    EditCharAttribFontHeight( const SvxFontHeightItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribFontWidth
// -------------------------------------------------------------------------
class EditCharAttribFontWidth : public EditCharAttrib
{
public:
    EditCharAttribFontWidth( const SvxCharScaleWidthItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribColor
// -------------------------------------------------------------------------
class EditCharAttribColor : public EditCharAttrib
{
public:
    EditCharAttribColor( const SvxColorItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribLanguage
// -------------------------------------------------------------------------
class EditCharAttribLanguage : public EditCharAttrib
{
public:
    EditCharAttribLanguage( const SvxLanguageItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribTab
// -------------------------------------------------------------------------
class EditCharAttribTab : public EditCharAttrib
{
public:
    EditCharAttribTab( const SfxVoidItem& rAttr, USHORT nPos );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribLineBreak
// -------------------------------------------------------------------------
class EditCharAttribLineBreak : public EditCharAttrib
{
public:
    EditCharAttribLineBreak( const SfxVoidItem& rAttr, USHORT nPos );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribField
// -------------------------------------------------------------------------
class EditCharAttribField: public EditCharAttrib
{
    XubString		aFieldValue;
    Color*			pTxtColor;
    Color*			pFldColor;

    EditCharAttribField& operator = ( const EditCharAttribField& rAttr ) const;

public:
    EditCharAttribField( const SvxFieldItem& rAttr, USHORT nPos );
    EditCharAttribField( const EditCharAttribField& rAttr );
    ~EditCharAttribField();

    BOOL operator == ( const EditCharAttribField& rAttr ) const;
    BOOL operator != ( const EditCharAttribField& rAttr ) const
                                    { return !(operator == ( rAttr ) ); }

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
    Color*&			GetTxtColor() 			{ return pTxtColor; }
    Color*&			GetFldColor() 			{ return pFldColor; }

    const XubString&	GetFieldValue() const 	{ return aFieldValue; }
    XubString&		GetFieldValue() 		{ return aFieldValue; }

    void			Reset()
                    {
                        aFieldValue.Erase();
                        delete pTxtColor; pTxtColor = 0;
                        delete pFldColor; pFldColor = 0;
                    }
};

// -------------------------------------------------------------------------
// class EditCharAttribPairKerning
// -------------------------------------------------------------------------
class EditCharAttribPairKerning : public EditCharAttrib
{
public:
    EditCharAttribPairKerning( const SvxAutoKernItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribKerning
// -------------------------------------------------------------------------
class EditCharAttribKerning : public EditCharAttrib
{
public:
    EditCharAttribKerning( const SvxKerningItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};

// -------------------------------------------------------------------------
// class EditCharAttribWordLineMode
// -------------------------------------------------------------------------
class EditCharAttribWordLineMode: public EditCharAttrib
{
public:
    EditCharAttribWordLineMode( const SvxWordLineModeItem& rAttr, USHORT nStart, USHORT nEnd );

    virtual void 	SetFont( SvxFont& rFont, OutputDevice* pOutDev );
};


}//end of namespace binfilter
#endif // _EDITATTR_HXX
