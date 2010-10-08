/*************************************************************************
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
 *  The Initial Developer of the Original Code is: IBM Corporation
 *
 *  Copyright: 2008 by IBM Corporation
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#include	"xftextboxstyle.hxx"
#include	"xfcolumns.hxx"
#include	"xfborders.hxx"
#include	"xfshadow.hxx"
#include	"xfbgimage.hxx"

XFTextBoxStyle::XFTextBoxStyle()
{
}

XFTextBoxStyle::~XFTextBoxStyle()
{
}

enumXFStyle	XFTextBoxStyle::GetStyleFamily()
{
    return enumXFStyleGraphics;
}

void	XFTextBoxStyle::ToXml(IXFStream *pStrm)
{
    IXFAttrList *pAttrList = pStrm->GetAttrList();

    pAttrList->Clear();
    pAttrList->AddAttribute( A2OUSTR("style:name"), GetStyleName() );
    if( GetParentStyleName().getLength() > 0 )
        pAttrList->AddAttribute(A2OUSTR("style:parent-style-name"),GetParentStyleName());
    pAttrList->AddAttribute( A2OUSTR("style:family"), A2OUSTR("graphics") );
    //parent style name ignore now.
    pStrm->StartElement( A2OUSTR("style:style") );

    pAttrList->Clear();
    pAttrList->AddAttribute( A2OUSTR("draw:stroke"), A2OUSTR("none") );
    pAttrList->AddAttribute( A2OUSTR("svg:stroke-color"), A2OUSTR("#000000") );
    pAttrList->AddAttribute( A2OUSTR("draw:fill"), A2OUSTR("none") );
    pAttrList->AddAttribute( A2OUSTR("draw:fill-color"), A2OUSTR("#ffffff") );
    pAttrList->AddAttribute( A2OUSTR("draw:auto-grow-height"), A2OUSTR("true") );
    pAttrList->AddAttribute( A2OUSTR("style:run-through"), A2OUSTR("foreground") );
    pAttrList->AddAttribute( A2OUSTR("style:wrap"), A2OUSTR("run-through") );
    pAttrList->AddAttribute( A2OUSTR("style:wrap"), A2OUSTR("run-through") );
    pAttrList->AddAttribute( A2OUSTR("style:number-wrapped-paragraphs"), A2OUSTR("no-limit") );
    pAttrList->AddAttribute( A2OUSTR("style:wrap-contour"), A2OUSTR("false") );

    pStrm->StartElement( A2OUSTR("style:properties") );
    pStrm->EndElement( A2OUSTR("style:properties") );

    pStrm->EndElement( A2OUSTR("style:style") );
}