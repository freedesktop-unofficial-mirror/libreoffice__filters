/*************************************************************************
 *
 *  $RCSfile: sw_swxmlat.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 18:22:19 $
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


#pragma hdrstop

#include <hintids.hxx>

#ifndef _RSCSFX_HXX
#include <rsc/rscsfx.hxx>
#endif

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _HORIORNT_HXX
#include <horiornt.hxx>
#endif

#ifndef _DOC_HXX //autogen wg. SwDoc
#include <doc.hxx>
#endif
#ifndef _FCHRFMT_HXX
#include <fchrfmt.hxx>
#endif
#ifndef _CHARFMT_HXX
#include <charfmt.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _PARATR_HXX
#include <paratr.hxx>
#endif
#ifndef _FMTPDSC_HXX
#include <fmtpdsc.hxx>
#endif
#ifndef _FMTTSPLT_HXX 
#include "fmtlsplt.hxx"
#endif
#ifndef _FMTORNT_HXX 
#include "fmtornt.hxx"
#endif
#ifndef _FMTFSIZE_HXX 
#include "fmtfsize.hxx"
#endif
#ifndef _UNOMID_H
#include <unomid.h>
#endif
#ifndef _UNOSTYLE_HXX
#include "unostyle.hxx"
#endif

#ifndef _XMLOFF_XMLUCONV_HXX
#include <bf_xmloff/xmluconv.hxx>
#endif
#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif
#ifndef _XMLOFF_XMLTKMAP_HXX
#include <bf_xmloff/xmltkmap.hxx>
#endif
#ifndef _XMLOFF_I18NMAP_HXX
#include <bf_xmloff/i18nmap.hxx>
#endif

#ifndef _XMLIMP_HXX
#include "xmlimp.hxx"
#endif
namespace binfilter {

using namespace ::rtl;
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::binfilter::xmloff::token;

// ---------------------------------------------------------------------

sal_Bool SwFmtDrop::equalsXML( const SfxPoolItem& rItem ) const
{
    ASSERT( !this, "obsolete implementation!" );
    return sal_True;
}

// ---------------------------------------------------------------------

sal_Bool SwRegisterItem::importXML( const OUString& rValue, sal_uInt16,
                                    const SvXMLUnitConverter& rUnitConverter )
{
    ASSERT( !this, "obsolete implementation!" );
    return sal_False;
}

sal_Bool SwRegisterItem::exportXML(
        OUString& rValue, sal_uInt16,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    ASSERT( !this, "obsolete implementation!" );
    return sal_True;
}

// ---------------------------------------------------------------------

sal_Bool SwNumRuleItem::equalsXML( const SfxPoolItem& rItem ) const
{
    ASSERT( !this, "obsolete implementation!" );
    return sal_True;
}

// ---------------------------------------------------------------------

sal_Bool SwFmtPageDesc::importXML( const OUString& rValue, sal_uInt16 nMemberId,
                                    const SvXMLUnitConverter& rUnitConverter )
{
    sal_Bool bRet = sal_False;

    if( MID_PAGEDESC_PAGENUMOFFSET==nMemberId )
    {
        sal_Int32 nVal;
        bRet = rUnitConverter.convertNumber( nVal, rValue, 0, USHRT_MAX );
        if( bRet )
            SetNumOffset( (USHORT)nVal );
    }

    return bRet;
}

sal_Bool SwFmtPageDesc::exportXML(
        OUString& rValue, sal_uInt16 nMemberId,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;

    if( MID_PAGEDESC_PAGENUMOFFSET==nMemberId )
    {
        OUStringBuffer aOut;

        rUnitConverter.convertNumber( aOut, (sal_Int32)GetNumOffset() );
        rValue = aOut.makeStringAndClear();

        bRet = sal_True;
    }

    return bRet;
}
sal_Bool SwFmtPageDesc::equalsXML( const SfxPoolItem& rItem ) const
{
    // Everything except pDefinedIn must be the same.
    return ( nNumOffset == ((SwFmtPageDesc&)rItem).nNumOffset ) &&
           ( GetPageDesc() == ((SwFmtPageDesc&)rItem).GetPageDesc() );
}

// ---------------------------------------------------------------------

sal_Bool SwFmtCharFmt::exportXML( OUString& rValue, sal_uInt16,
                              const SvXMLUnitConverter& ) const
{
    ASSERT( !this, "obsolete implementation!" );
    return sal_True;
}

// ---------------------------------------------------------------------

sal_Bool SwFmtLayoutSplit::importXML( const OUString& rValue, sal_uInt16,
                                        const SvXMLUnitConverter& rUnitConverter )
{
    sal_Bool bValue;
    sal_Bool bRet = rUnitConverter.convertBool( bValue, rValue );
    if( bRet )
        SetValue( bValue );

    return bRet;
}

sal_Bool SwFmtLayoutSplit::exportXML(
        OUString& rValue, sal_uInt16,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;

    rUnitConverter.convertBool( aOut, GetValue() );
    rValue = aOut.makeStringAndClear();

    return sal_True;
}

// ---------------------------------------------------------------------

static __FAR_DATA struct SvXMLEnumMapEntry aXMLTableAlignMap[] =
{
    { XML_LEFT,				HORI_LEFT			},
    { XML_LEFT,				HORI_LEFT_AND_WIDTH	},
    { XML_CENTER, 			HORI_CENTER			},
    { XML_RIGHT, 			HORI_RIGHT			},
    { XML_MARGINS, 			HORI_FULL			},
    { XML_MARGINS,			HORI_NONE			},
    { XML_TOKEN_INVALID, 0 }
};

sal_Bool SwFmtHoriOrient::importXML( const OUString& rValue, sal_uInt16,
                                       const SvXMLUnitConverter& rUnitConverter )
{
    sal_uInt16 nValue;
    sal_Bool bRet = rUnitConverter.convertEnum( nValue, rValue,
                                                aXMLTableAlignMap );
    if( bRet )
        SetHoriOrient( (SwHoriOrient)nValue );

    return bRet;
}

sal_Bool SwFmtHoriOrient::exportXML(
        OUString& rValue, sal_uInt16,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;

    rUnitConverter.convertEnum( aOut, GetHoriOrient(), aXMLTableAlignMap );
    rValue = aOut.makeStringAndClear();

    return sal_True;
}

// ---------------------------------------------------------------------

static __FAR_DATA SvXMLEnumMapEntry aXMLTableVAlignMap[] =
{
    { XML_TOP,					VERT_TOP		},
    { XML_MIDDLE,				VERT_CENTER		},
    { XML_BOTTOM, 				VERT_BOTTOM		},
    { XML_TOKEN_INVALID, 0 }
};

sal_Bool SwFmtVertOrient::importXML( const OUString& rValue, sal_uInt16,
                                       const SvXMLUnitConverter& rUnitConverter )
{
    sal_uInt16 nValue;
    sal_Bool bRet =
        rUnitConverter.convertEnum( nValue, rValue,aXMLTableVAlignMap );
    if( bRet )
        SetVertOrient( (SwVertOrient)nValue );

    return bRet;
}

sal_Bool SwFmtVertOrient::exportXML(
        OUString& rValue, sal_uInt16,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    OUStringBuffer aOut;

    rUnitConverter.convertEnum( aOut, GetVertOrient(), aXMLTableVAlignMap );
    rValue = aOut.makeStringAndClear();

    return sal_True;
}

// ---------------------------------------------------------------------

sal_Bool SwFmtFrmSize::importXML( const OUString& rValue, sal_uInt16 nMemberId,
                                  const SvXMLUnitConverter& rUnitConverter )
{
    sal_Bool bRet = sal_False;
    sal_Bool bSetHeight = sal_False;
    sal_Bool bSetWidth = sal_False;
    sal_Bool bSetSizeType = sal_False;
    SwFrmSize eSizeType = ATT_VAR_SIZE;
    sal_Int32 nMin = MINLAY;

    switch( nMemberId )
    {
    case MID_FRMSIZE_REL_WIDTH:
        {
            sal_Int32 nValue;
            bRet = rUnitConverter.convertPercent( nValue, rValue );
            if( bRet )
            {
                if( nValue < 1 )
                    nValue = 1;
                else if( nValue > 100 )
                    nValue = 100;

                SetWidthPercent( (sal_Int8)nValue );
            }
        }
        break;
    case MID_FRMSIZE_WIDTH:
        bSetWidth = sal_True;
        break;
    case MID_FRMSIZE_MIN_HEIGHT:
        eSizeType = ATT_MIN_SIZE;
        bSetHeight = sal_True;
        nMin = 1;
        bSetSizeType = sal_True;
        break;
    case MID_FRMSIZE_FIX_HEIGHT:
        eSizeType = ATT_FIX_SIZE;
        bSetHeight = sal_True;
        nMin = 1;
        bSetSizeType = sal_True;
        break;
    case MID_FRMSIZE_COL_WIDTH:
        eSizeType = ATT_FIX_SIZE;
        bSetWidth = sal_True;
        bSetSizeType = sal_True;
        break;
    case MID_FRMSIZE_REL_COL_WIDTH:
        {
            sal_Int32 nPos = rValue.indexOf( (sal_Unicode)'*' );
            if( -1L != nPos )
            {
                OUString sNum( rValue.copy( 0L, nPos ) );
                sal_Int32 nValue = rValue.toInt32();
                if( nValue < MINLAY )
                    nValue = MINLAY;
                else if( nValue > USHRT_MAX )
                    nValue = USHRT_MAX;

                SetWidth( (sal_uInt16)nValue );
                SetSizeType( ATT_VAR_SIZE );
                bRet = sal_True;
            }
        }
        break;
    }

    sal_Int32 nValue;
    if( bSetHeight || bSetWidth )
    {
        bRet = rUnitConverter.convertMeasure( nValue, rValue, nMin,
                                              USHRT_MAX );
        if( bRet )
        {
            if( bSetWidth )
                SetWidth( (sal_uInt16)nValue );
            if( bSetHeight )
                SetHeight( (sal_uInt16)nValue );
            if( bSetSizeType )
                SetSizeType( eSizeType );
        }
    }
    return bRet;
}

sal_Bool SwFmtFrmSize::exportXML(
        OUString& rValue, sal_uInt16 nMemberId,
        const SvXMLUnitConverter& rUnitConverter ) const
{
    sal_Bool bRet = sal_False;
    sal_Bool bOutHeight = sal_False;
    switch( nMemberId )
    {
    case MID_FRMSIZE_REL_WIDTH:
        if( GetWidthPercent() )
        {
            OUStringBuffer aOut;
            rUnitConverter.convertPercent( aOut, GetWidthPercent() );
            rValue = aOut.makeStringAndClear();
            bRet = sal_True;
        }
        break;
    case MID_FRMSIZE_MIN_HEIGHT:
        if( ATT_MIN_SIZE == GetSizeType() )
            bOutHeight = sal_True;
        break;
    case MID_FRMSIZE_FIX_HEIGHT:
        if( ATT_FIX_SIZE == GetSizeType() )
            bOutHeight = sal_True;
        break;
    }

    if( bOutHeight )
    {
        OUStringBuffer aOut;
        rUnitConverter.convertMeasure( aOut, GetHeight() );
        rValue = aOut.makeStringAndClear();
        bRet = sal_True;
    }

    return bRet;
}
}
