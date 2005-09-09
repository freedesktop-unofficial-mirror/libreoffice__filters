/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLPropertyBackpatcher.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:08:44 $
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


#ifndef _XMLOFF_XMLPROPERTYBACKPATCHER_HXX
#define _XMLOFF_XMLPROPERTYBACKPATCHER_HXX

#ifndef __SGI_STL_MAP
#include <map>
#endif

#ifndef __SGI_STL_VECTOR
#include <vector>
#endif

#if SUPD > 632 || DVO_TEST
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#else
// auto strip #ifndef _XMLOFF_FUNCTIONAL_HXX
// auto strip #include "functional.hxx"
// auto strip #endif
#endif

namespace rtl { class OUString; }
namespace com { namespace sun { namespace star { 
    namespace beans { class XPropertySet; }
    namespace uno { template<class A> class Reference; }
} } }
namespace binfilter {


/** This class maintains an OUString->sal_Int16 mapping for cases in
 * which an XPropertySet needs to be filled with values that are not
 * yet known.
 *
 * A good example for appropriate use are footnotes and references to
 * footnoes. Internally, the StarOffice API numbers footnotes, and
 * references to footnotes refer to that internal numbering. In the
 * XML file format, these numbers are replaced with name strings. Now
 * if during import of a document a reference to a footnote is
 * encountered, two things can happen: 1) The footnote already
 * appeared in the document. In this case the name is already known
 * and the proper ID can be requested from the footnote. 2) The
 * footnote will appear later in the document. In this case the ID is
 * not yet known, and the reference-ID property of the reference
 * cannot be determined. Hence, the reference has to be stored and the
 * ID needs to bet set later, when the footnote is eventually found in
 * the document.
 *
 * This class simplifies this process: If the footnote is found,
 * ResolveId with the XML name and the ID is called. When a reference
 * is encountered, SetProperty gets called with the reference's
 * XPropertySet and the XML name. All remaining tasks are handled by
 * the class.
 */
template <class A>
class XMLPropertyBackpatcher
{

    /// name of property that gets set or backpatched
     ::rtl::OUString sPropertyName;	

    /// should a default value be set for unresolved properties
    sal_Bool bDefaultHandling;

    /// should the sPreservePropertyName be preserved
    sal_Bool bPreserveProperty;

    /// name of the property to preserve
    ::rtl::OUString sPreservePropertyName;

    /// default value for unresolved properties (if bDefaultHandling)
    A aDefault;

    /// backpatch list type
    typedef ::std::vector< 
                ::com::sun::star::uno::Reference<
                    ::com::sun::star::beans::XPropertySet> > BackpatchListType;

    /* use void* instead of BackpatchListType to avoid linker problems
       with long typenames. The real typename (commented out) contains
       >1200 chars. */

    /// backpatch list for unresolved IDs
    //::std::map<const ::rtl::OUString, BackpatchListType*> aBackpatchListMap;
#if SUPD > 632 || DVO_TEST
    ::std::map<const ::rtl::OUString, void*, ::comphelper::UStringLess> aBackpatchListMap;
#else
    ::std::map<const ::rtl::OUString, void*, less_functor> aBackpatchListMap;
#endif

    /// mapping of names -> IDs
#if SUPD > 632 || DVO_TEST
    ::std::map<const ::rtl::OUString, A, ::comphelper::UStringLess> aIDMap;
#else
    ::std::map<const ::rtl::OUString, A, less_functor> aIDMap;
#endif

public:
    
    XMLPropertyBackpatcher(
        const ::rtl::OUString& sPropertyName);

    XMLPropertyBackpatcher(
        const ::rtl::OUString& sPropertyName, 
        const ::rtl::OUString& sPreservePropertyName,
        sal_Bool bDefault,
        A aDef);

    XMLPropertyBackpatcher(
        const sal_Char* pPropertyName);

    XMLPropertyBackpatcher(
        const sal_Char* pPropertyName,
        const sal_Char* pPreservePropertyName,
        sal_Bool bDefault,
        A aDef);

    ~XMLPropertyBackpatcher();

    /// resolve a known ID.
    /// Call this as soon as the value for a particular name is known.
    void ResolveId(
        const ::rtl::OUString& sName,
        A aValue);

    /// Set property with the proper value for this name. If the value
    /// is not yet known, store the XPropertySet in the backpatch list.
    /// Use this whenever the value should be set, even if it is not yet known.
    /// const version
    void SetProperty(
        const ::com::sun::star::uno::Reference<
                ::com::sun::star::beans::XPropertySet> & xPropSet,
        const ::rtl::OUString& sName);

    /// non-const version of SetProperty
    void SetProperty(
        ::com::sun::star::uno::Reference<
                ::com::sun::star::beans::XPropertySet> & xPropSet,
        const ::rtl::OUString& sName);

    /// set default (if bDefaultHandling) for unresolved names
    /// called by destructor
    void SetDefault();

};

}//end of namespace binfilter
#endif
