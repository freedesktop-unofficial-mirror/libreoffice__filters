/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmloff_XMLPropertyBackpatcher.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:26:56 $
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

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_H_ 
#include <com/sun/star/uno/Reference.h>
#endif

#ifndef _RTL_USTRING
#include <rtl/ustring>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _XMLOFF_XMLPROPERTYBACKPATCHER_HXX
#include "XMLPropertyBackpatcher.hxx"
#endif

#ifndef _XMLOFF_TEXTIMP_HXX_
#include "txtimp.hxx"	// XMLTextImportHelper partially implemented here
#endif
namespace binfilter {


using ::rtl::OUString;
using ::std::vector;
using ::std::map;
using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Any;
using ::com::sun::star::beans::XPropertySet;


template<class A>
XMLPropertyBackpatcher<A>::XMLPropertyBackpatcher(
    const ::rtl::OUString& sPropName) :
        sPropertyName(sPropName),
        bDefaultHandling(sal_False),
        bPreserveProperty(sal_False),
        sPreservePropertyName()
{
}

template<class A>
XMLPropertyBackpatcher<A>::XMLPropertyBackpatcher(
    const OUString& sPropName, 
    const OUString& sPreserveName,
    sal_Bool bDefault,
    A aDef) :
        sPropertyName(sPropName),
        bDefaultHandling(bDefault),
        aDefault(aDef),
        sPreservePropertyName(sPreserveName),
        bPreserveProperty(sPreserveName.getLength()>0)
{
}

template<class A>
XMLPropertyBackpatcher<A>::XMLPropertyBackpatcher(
    const sal_Char* pPropName) :
        sPropertyName(),
        bDefaultHandling(sal_False),
        bPreserveProperty(sal_False),
        sPreservePropertyName()
{
    DBG_ASSERT(pPropName != NULL, "need property name");
    sPropertyName = OUString::createFromAscii(pPropName);
}

template<class A>
XMLPropertyBackpatcher<A>::XMLPropertyBackpatcher(
    const sal_Char* pPropName,
    const sal_Char* pPreservePropName,
    sal_Bool bDefault,
    A aDef) :
        sPropertyName(),
        sPreservePropertyName(),
        bDefaultHandling(bDefault),
        bPreserveProperty(pPreservePropName != NULL),
        aDefault(aDef)
{
    DBG_ASSERT(pPropName != NULL, "need property name");
    sPropertyName = OUString::createFromAscii(pPropName);
    if (pPreservePropName != NULL)
    {
        sPreservePropertyName = OUString::createFromAscii(pPreservePropName);
    }
}

template<class A>
XMLPropertyBackpatcher<A>::~XMLPropertyBackpatcher()
{
    SetDefault();
}


template<class A>
void XMLPropertyBackpatcher<A>::ResolveId(
    const OUString& sName,
    A aValue)
{
    // insert ID into ID map
    aIDMap[sName] = aValue;
    
    // backpatch old references, if backpatch list exists
    if (aBackpatchListMap.count(sName))
    {
        // aah, we have a backpatch list!
        BackpatchListType* pList = 
            (BackpatchListType*)aBackpatchListMap[sName];

        // a) remove list from list map
        aBackpatchListMap.erase(sName);

        // b) for every item, set SequenceNumber
        //    (and preserve Property, if appropriate)
        Any aAny;
        aAny <<= aValue;
        if (bPreserveProperty)
        {
            // preserve version
            for(BackpatchListType::iterator aIter = pList->begin();
                aIter != pList->end();
                aIter++)
            {
                Reference<XPropertySet> xProp = (*aIter);
                Any aPres = xProp->getPropertyValue(sPreservePropertyName);
                xProp->setPropertyValue(sPropertyName, aAny);
                xProp->setPropertyValue(sPreservePropertyName, aPres);
            }
        }
        else
        {
            // without preserve
            for(BackpatchListType::iterator aIter = pList->begin();
                aIter != pList->end();
                aIter++)
            {
                (*aIter)->setPropertyValue(sPropertyName, aAny);
            }
        }

        // c) delete list
        delete pList;
    }
    // else: no backpatch list -> then we're finished
}

template<class A>
void XMLPropertyBackpatcher<A>::SetProperty(
    const Reference<XPropertySet> & xPropSet,
    const OUString& sName)
{
    Reference<XPropertySet> xNonConstPropSet(xPropSet);
    SetProperty(xNonConstPropSet, sName);
}

template<class A>
void XMLPropertyBackpatcher<A>::SetProperty(
    Reference<XPropertySet> & xPropSet,
    const OUString& sName)
{
    if (aIDMap.count(sName))
    {
        // we know this ID -> set property
        Any aAny;
        aAny <<= aIDMap[sName];
        xPropSet->setPropertyValue(sPropertyName, aAny);
    }
    else
    {
        // ID unknown -> into backpatch list for later fixup
        if (! aBackpatchListMap.count(sName))
        {
            // create backpatch list for this name
            BackpatchListType* pTmp = new BackpatchListType() ;
            aBackpatchListMap[sName] = (void*)pTmp;
        }

        // insert footnote
        ((BackpatchListType*)aBackpatchListMap[sName])->push_back(xPropSet);
    }
}

template<class A>
void XMLPropertyBackpatcher<A>::SetDefault()
{
    if (bDefaultHandling)
    {
        // not implemented yet
    }
}

// force instantiation of templates
template class XMLPropertyBackpatcher<sal_Int16>;
template class XMLPropertyBackpatcher<OUString>;



//
// XMLTextImportHelper
//
// Code from XMLTextImportHelper using the XMLPropertyBackpatcher is
// implemented here. The reason is that in the unxsols2 environment,
// all templates are instatiated as file local (switch
// -instances=static), and thus are not accessible from the outside.
//
// The previous solution was to force additional instantiation of
// XMLPropertyBackpatcher in txtimp.cxx. This solution combines all
// usage of the XMLPropertyBackpatcher in XMLPropertyBackpatcher.cxx
// instead.
//

XMLPropertyBackpatcher<sal_Int16>& XMLTextImportHelper::GetFootnoteBP()
{
    if (NULL == pFootnoteBackpatcher)
    {
        pFootnoteBackpatcher = 
            new XMLPropertyBackpatcher<sal_Int16>(sSequenceNumber);
    }
    return *pFootnoteBackpatcher;
}

XMLPropertyBackpatcher<sal_Int16>& XMLTextImportHelper::GetSequenceIdBP()
{
    if (NULL == pSequenceIdBackpatcher)
    {
        pSequenceIdBackpatcher = 
            new XMLPropertyBackpatcher<sal_Int16>(sSequenceNumber);
    }
    return *pSequenceIdBackpatcher;
}

XMLPropertyBackpatcher<OUString>& XMLTextImportHelper::GetSequenceNameBP()
{
    if (NULL == pSequenceNameBackpatcher)
    {
        pSequenceNameBackpatcher = 
            new XMLPropertyBackpatcher<OUString>(sSourceName);
    }
    return *pSequenceNameBackpatcher;
}

void XMLTextImportHelper::InsertFootnoteID(
    const OUString& sXMLId, 
    sal_Int16 nAPIId)
{
    GetFootnoteBP().ResolveId(sXMLId, nAPIId);
}

void XMLTextImportHelper::ProcessFootnoteReference(
    const OUString& sXMLId, 
    const Reference<XPropertySet> & xPropSet)
{
    GetFootnoteBP().SetProperty(xPropSet, sXMLId);
}

void XMLTextImportHelper::InsertSequenceID(
    const OUString& sXMLId, 
    const OUString& sName,
    sal_Int16 nAPIId)
{
    GetSequenceIdBP().ResolveId(sXMLId, nAPIId);
    GetSequenceNameBP().ResolveId(sXMLId, sName);
}

void XMLTextImportHelper::ProcessSequenceReference(
    const OUString& sXMLId, 
    const Reference<XPropertySet> & xPropSet)
{
    GetSequenceIdBP().SetProperty(xPropSet, sXMLId);
    GetSequenceNameBP().SetProperty(xPropSet, sXMLId);
}

void XMLTextImportHelper::_FinitBackpatcher()
{
    delete pFootnoteBackpatcher;
    delete pSequenceIdBackpatcher;
    delete pSequenceNameBackpatcher;
}
}//end of namespace binfilter
