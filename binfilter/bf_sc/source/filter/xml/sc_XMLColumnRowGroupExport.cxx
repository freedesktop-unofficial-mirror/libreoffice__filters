/*************************************************************************
 *
 *  $RCSfile: sc_XMLColumnRowGroupExport.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: aw $ $Date: 2003-12-05 15:10:16 $
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

#ifdef PCH
#include "filt_pch.hxx"
#endif

#pragma hdrstop

// INCLUDE ---------------------------------------------------------------

#ifndef _SC_XMLCOLUMNROWGROUPEXPORT_HXX
#include "XMLColumnRowGroupExport.hxx"
#endif
#ifndef SC_XMLEXPRT_HXX
#include "xmlexprt.hxx"
#endif

#ifndef _XMLOFF_NMSPMAP_HXX
#include <bf_xmloff/nmspmap.hxx>
#endif
#ifndef _XMLOFF_XMLTOKEN_HXX
#include <bf_xmloff/xmltoken.hxx>
#endif
#ifndef _XMLOFF_XMLNMSPE_HXX
#include <bf_xmloff/xmlnmspe.hxx>
#endif

#include <algorithm>
namespace binfilter {

using namespace xmloff::token;

ScMyColumnRowGroup::ScMyColumnRowGroup()
{
}

sal_Bool ScMyColumnRowGroup::operator<(const ScMyColumnRowGroup& rGroup) const
{
    if (rGroup.nField > nField)
        return sal_True;
    else
        if (rGroup.nField == nField && rGroup.nLevel > nLevel)
            return sal_True;
        else
            return sal_False;
}

ScMyOpenCloseColumnRowGroup::ScMyOpenCloseColumnRowGroup(ScXMLExport& rTempExport, sal_uInt32 nToken)
    : rExport(rTempExport),
    aTableStart(),
    aTableEnd(),
    rName(rExport.GetNamespaceMap().GetQNameByKey(XML_NAMESPACE_TABLE, GetXMLToken(XMLTokenEnum(nToken))))
{
}

ScMyOpenCloseColumnRowGroup::~ScMyOpenCloseColumnRowGroup()
{
}

void ScMyOpenCloseColumnRowGroup::NewTable()
{
    aTableStart.clear();
    aTableEnd.clear();
}

void ScMyOpenCloseColumnRowGroup::AddGroup(const ScMyColumnRowGroup& aGroup, const sal_Int32 nEndField)
{
    aTableStart.push_back(aGroup);
    aTableEnd.push_back(nEndField);
}

sal_Bool ScMyOpenCloseColumnRowGroup::IsGroupStart(const sal_Int32 nField)
{
    sal_Bool bGroupStart(sal_False);
    if (!aTableStart.empty())
    {
        ScMyColumnRowGroupVec::iterator aItr = aTableStart.begin();
        sal_Int32 nItrField = aItr->nField;
        if ( nItrField < nField )
        {
            //	#103327# when used to find repeated rows at the beginning of a group,
            //	aTableStart may contain entries before nField. They must be skipped here
            //	(they will be used for OpenGroups later in the right order).

            ScMyColumnRowGroupVec::iterator aEnd = aTableStart.end();
            while ( aItr != aEnd && nItrField < nField )
            {
                aItr++;
                if ( aItr != aEnd )
                    nItrField = aItr->nField;
            }
        }

        if (nItrField == nField)
            bGroupStart = sal_True;
    }
    return bGroupStart;
}

void ScMyOpenCloseColumnRowGroup::OpenGroup(const ScMyColumnRowGroup& rGroup)
{
    if (!rGroup.bDisplay)
        rExport.AddAttribute(XML_NAMESPACE_TABLE, XML_DISPLAY, XML_FALSE);
    rExport.StartElement( rName, sal_True);
}

void ScMyOpenCloseColumnRowGroup::OpenGroups(const sal_Int32 nField)
{
    ScMyColumnRowGroupVec::iterator aItr = aTableStart.begin();
    sal_Bool bReady(sal_False);
    while(!bReady && aItr != aTableStart.end())
    {
        if (aItr->nField == nField)
        {
            OpenGroup(*aItr);
            aItr = aTableStart.erase(aItr);
        }
        else
            bReady = sal_True;
    }
}

sal_Bool ScMyOpenCloseColumnRowGroup::IsGroupEnd(const sal_Int32 nField)
{
    sal_Bool bGroupEnd(sal_False);
    if (!aTableEnd.empty())
    {
        if (*(aTableEnd.begin()) == nField)
            bGroupEnd = sal_True;
    }
    return bGroupEnd;
}

void ScMyOpenCloseColumnRowGroup::CloseGroup()
{
    rExport.EndElement( rName, sal_True );
}

void ScMyOpenCloseColumnRowGroup::CloseGroups(const sal_Int32 nField)
{
    ScMyFieldGroupVec::iterator aItr = aTableEnd.begin();
    sal_Bool bReady(sal_False);
    while(!bReady && aItr != aTableEnd.end())
    {
        if (*aItr == nField)
        {
            CloseGroup();
            aItr = aTableEnd.erase(aItr);
        }
        else
            bReady = sal_True;
    }
}

sal_Int32 ScMyOpenCloseColumnRowGroup::GetLast()
{
    sal_Int32 maximum(-1);
    for (ScMyFieldGroupVec::iterator i = aTableEnd.begin(); i != aTableEnd.end(); i++)
        if (*i > maximum)
            maximum = *i;
    return maximum;
}

void ScMyOpenCloseColumnRowGroup::Sort()
{
    aTableStart.sort();
    aTableEnd.sort();
}

}
