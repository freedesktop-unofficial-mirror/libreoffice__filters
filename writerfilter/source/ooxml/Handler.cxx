/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: Handler.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: obo $ $Date: 2008-01-10 11:55:43 $
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

#include <ooxml/resourceids.hxx>
#include <resourcemodel/QNameToString.hxx>
#include "Handler.hxx"

namespace writerfilter {
namespace ooxml 
{

/*
  class OOXMLFootnoteHandler
 */
OOXMLFootnoteHandler::OOXMLFootnoteHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext)
{
}

OOXMLFootnoteHandler::~OOXMLFootnoteHandler()
{
}

void OOXMLFootnoteHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_FtnEdnRef_id:
        mpFastContext->resolveFootnote(val.getString());
        break;
    default:
        break;
    }
}

void OOXMLFootnoteHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLEndnoteHandler
 */
OOXMLEndnoteHandler::OOXMLEndnoteHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext)
{
}

OOXMLEndnoteHandler::~OOXMLEndnoteHandler()
{
}

void OOXMLEndnoteHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_FtnEdnRef_id:
        mpFastContext->resolveEndnote(val.getString());
        break;
    default:
        break;
    }
}

void OOXMLEndnoteHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLCommentHandler
*/
OOXMLCommentHandler::OOXMLCommentHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext)
{    
}

OOXMLCommentHandler::~OOXMLCommentHandler()
{
}

void OOXMLCommentHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_Markup_id:
        mpFastContext->resolveComment(val.getString());
        break;
    default:
        ;
    }
}

void OOXMLCommentHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLFooterHandler
 */
OOXMLFooterHandler::OOXMLFooterHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext), msStreamId(), mnType(0)
{
}

OOXMLFooterHandler::~OOXMLFooterHandler()
{
    mpFastContext->resolveFooter(mnType, msStreamId);
}

void OOXMLFooterHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_HdrFtrRef_id:
        msStreamId = val.getString();
        break;
    case NS_ooxml::LN_CT_HdrFtrRef_type:
        mnType = val.getInt();
        break;
    default:
        break;
    }
}

void OOXMLFooterHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLHeaderHandler
 */
OOXMLHeaderHandler::OOXMLHeaderHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext), msStreamId(), mnType(0)
{
}

OOXMLHeaderHandler::~OOXMLHeaderHandler()
{
    mpFastContext->resolveHeader(mnType, msStreamId);
}

void OOXMLHeaderHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_HdrFtrRef_id:
        msStreamId = val.getString();
        break;
    case NS_ooxml::LN_CT_HdrFtrRef_type:
        mnType = val.getInt();
        break;
    default:
        break;
    }
}

void OOXMLHeaderHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLBreakHandler
 */
OOXMLBreakHandler::OOXMLBreakHandler(Stream &rStream, 
                                     OOXMLFastContextHandler * pContext)
: mpFastContext(pContext), mnType(0), mnClear(0), 
  mrStream(rStream)
{
}

OOXMLBreakHandler::~OOXMLBreakHandler()
{
    sal_uInt8 tmpBreak[1];
    switch (mnType)
    {
    case NS_ooxml::LN_Value_ST_BrType_column:
        tmpBreak[0] = 0x0E;
        break;
    case NS_ooxml::LN_Value_ST_BrType_page:
        tmpBreak[0] = 0x0C;
        break;
    case NS_ooxml::LN_Value_ST_BrType_textWrapping:
    default: // when no attribute type is present, the spec assume textWrapping
        tmpBreak[0] = 0x0A;
        break;
    }
    mrStream.text(&tmpBreak[0], 1);
}

void OOXMLBreakHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_Br_type:
        mnType = val.getInt();
        break;
    case NS_ooxml::LN_CT_Br_clear:
        mnClear = val.getInt();
        break;
    default:
        break;
    }
}

void OOXMLBreakHandler::sprm(Sprm & /*sprm*/)
{
}

/*
  class OOXMLPictureHandler
 */
OOXMLPictureHandler::OOXMLPictureHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext)
{    
}

OOXMLPictureHandler::~OOXMLPictureHandler()
{
}

void OOXMLPictureHandler::attribute(Id name, Value & val)
{
#ifdef DEBUG_PICTURE
    logger("DEBUG", "handle picture:" + (*QNameToString::Instance())(name)); 
#endif

    if (name == NS_ooxml::LN_AG_Blob_r_embed)
        mpFastContext->resolvePicture(val.getString());            
    else
    {
        writerfilter::Reference<Properties>::Pointer_t pProps
            (val.getProperties());
        if (pProps.get() != NULL)
            pProps->resolve(*this);
    }
}

void OOXMLPictureHandler::sprm(Sprm & rSprm)
{
    writerfilter::Reference<Properties>::Pointer_t pProps
        (rSprm.getProps());

    if (pProps.get() != NULL)
        pProps->resolve(*this);
}

/**
   class OOXMLHyperlinkHandler
 */

OOXMLHyperlinkHandler::OOXMLHyperlinkHandler(OOXMLFastContextHandler * pContext)
: mpFastContext(pContext)
{    
}

OOXMLHyperlinkHandler::~OOXMLHyperlinkHandler()
{
    ::rtl::OUString sReturn(RTL_CONSTASCII_USTRINGPARAM(" HYPERLINK \""));
    
    sReturn += mURL;
    sReturn += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\""));
    sReturn += mFieldCode;

    mpFastContext->characters(sReturn);
}

void OOXMLHyperlinkHandler::attribute(Id name, Value & val)
{
    switch (name)
    {
    case NS_ooxml::LN_CT_Hyperlink_tgtFrame:
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" \\t \""));
        mFieldCode += val.getString();
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\""));
        break;
    case NS_ooxml::LN_CT_Hyperlink_tooltip:
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" \\o \""));
        mFieldCode += val.getString();
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\""));
        break;
    case NS_ooxml::LN_CT_Hyperlink_docLocation:
        break;
    case NS_ooxml::LN_CT_Hyperlink_history:
        break;
    case NS_ooxml::LN_CT_Hyperlink_anchor:
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM(" \\l \""));
        mFieldCode += val.getString();
        mFieldCode += ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("\""));
        break;
    case NS_ooxml::LN_CT_Hyperlink_r_id:
        mURL = mpFastContext->getTargetForId(val.getString());
        break;
    default:
        break;
    }
}

void OOXMLHyperlinkHandler::sprm(Sprm & /*rSprm*/)
{
}
}}
