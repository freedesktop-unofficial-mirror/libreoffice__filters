/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: XMLConverter.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 16:59:46 $
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

#ifndef _SC_XMLCONVERTER_HXX
#define _SC_XMLCONVERTER_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef SC_DETFUNC_HXX
#include "detfunc.hxx"
#endif
#ifndef SC_DETDATA_HXX
#include "detdata.hxx"
#endif

#ifndef _RTL_USTRBUF_HXX_
#include <rtl/ustrbuf.hxx>
#endif

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif

#ifndef _COM_SUN_STAR_SHEET_DATAPILOTFIELDORIENTATION_HPP_
#include <com/sun/star/sheet/DataPilotFieldOrientation.hpp>
#endif
#ifndef _COM_SUN_STAR_SHEET_GENERALFUNCTION_HPP_
#include <com/sun/star/sheet/GeneralFunction.hpp>
#endif

#ifndef _COM_SUN_STAR_TABLE_CELLADDRESS_HPP_
#include <com/sun/star/table/CellAddress.hpp>
#endif
#ifndef _COM_SUN_STAR_TABLE_CELLRANGEADDRESS_HPP_
#include <com/sun/star/table/CellRangeAddress.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_DATETIME_HPP_
#include <com/sun/star/util/DateTime.hpp>
#endif
class DateTime;
namespace binfilter {

class ScArea;
class ScDocument;
class ScRangeList;
class SvXMLUnitConverter;

//___________________________________________________________________

class ScXMLConverter
{
protected:
    static void			AssignString(
                            ::rtl::OUString& rString,
                            const ::rtl::OUString& rNewStr,
                            sal_Bool bAppendStr );

    static sal_Int32	IndexOf(
                            const ::rtl::OUString& rString,
                            sal_Unicode cSearchChar,
                            sal_Int32 nOffset,
                            sal_Unicode cQuote = '\'' );

    static sal_Int32	IndexOfDifferent(
                            const ::rtl::OUString& rString,
                            sal_Unicode cSearchChar,
                            sal_Int32 nOffset );

public:
    inline				ScXMLConverter()	{}
    inline				~ScXMLConverter()	{}

// helper methods
    static sal_Int32	GetTokenCount(
                            const ::rtl::OUString& rString );
    static void			GetTokenByOffset(
                            ::rtl::OUString& rToken,
                            const ::rtl::OUString& rString,
                            sal_Int32& nOffset,
                            sal_Unicode cQuote = '\'' );

    static ScDocument*	GetScDocument(
                            ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel > xModel );

// IMPORT: CellAddress / CellRange
    static sal_Bool		GetAddressFromString(
                            ScAddress& rAddress,
                            const ::rtl::OUString& rAddressStr,
                            const ScDocument* pDocument,
                            sal_Int32& nOffset );
    static sal_Bool		GetRangeFromString(
                            ScRange& rRange,
                            const ::rtl::OUString& rRangeStr,
                            const ScDocument* pDocument,
                            sal_Int32& nOffset );
    static void			GetRangeListFromString(
                            ScRangeList& rRangeList,
                            const ::rtl::OUString& rRangeListStr,
                            const ScDocument* pDocument );

    static sal_Bool		GetAreaFromString(
                            ScArea& rArea,
                            const ::rtl::OUString& rRangeStr,
                            const ScDocument* pDocument,
                            sal_Int32& nOffset );

    static sal_Bool		GetAddressFromString(
                            ::com::sun::star::table::CellAddress& rAddress,
                            const ::rtl::OUString& rAddressStr,
                            const ScDocument* pDocument,
                            sal_Int32& nOffset );
    static sal_Bool		GetRangeFromString(
                            ::com::sun::star::table::CellRangeAddress& rRange,
                            const ::rtl::OUString& rRangeStr,
                            const ScDocument* pDocument,
                            sal_Int32& nOffset );
    static void			GetRangeListFromString(
                            ::com::sun::star::uno::Sequence< ::com::sun::star::table::CellRangeAddress >& rRangeSeq,
                            const ::rtl::OUString& rRangeListStr,
                            const ScDocument* pDocument );

// EXPORT: CellAddress / CellRange
    static void			GetStringFromAddress(
                            ::rtl::OUString& rString,
                            const ScAddress& rAddress,
                            const ScDocument* pDocument,
                            sal_Bool bAppendStr = sal_False,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void			GetStringFromRange(
                            ::rtl::OUString& rString,
                            const ScRange& rRange,
                            const ScDocument* pDocument,
                            sal_Bool bAppendStr = sal_False,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void			GetStringFromRangeList(
                            ::rtl::OUString& rString,
                            const ScRangeList* pRangeList,
                            const ScDocument* pDocument,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );

    static void			GetStringFromArea(
                            ::rtl::OUString& rString,
                            const ScArea& rArea,
                            const ScDocument* pDocument,
                            sal_Bool bAppendStr = sal_False,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );

    static void			GetStringFromAddress(
                            ::rtl::OUString& rString,
                            const ::com::sun::star::table::CellAddress& rAddress,
                            const ScDocument* pDocument,
                            sal_Bool bAppendStr = sal_False,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void			GetStringFromRange(
                            ::rtl::OUString& rString,
                            const ::com::sun::star::table::CellRangeAddress& rRange,
                            const ScDocument* pDocument,
                            sal_Bool bAppendStr = sal_False,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );
    static void			GetStringFromRangeList(
                            ::rtl::OUString& rString,
                            const ::com::sun::star::uno::Sequence< ::com::sun::star::table::CellRangeAddress >& rRangeSeq,
                            const ScDocument* pDocument,
                            sal_uInt16 nFormatFlags = (SCA_VALID | SCA_TAB_3D) );

// IMPORT: GeneralFunction / ScSubTotalFunc
    static ::com::sun::star::sheet::GeneralFunction
                        GetFunctionFromString(
                            const ::rtl::OUString& rString );
    static ScSubTotalFunc GetSubTotalFuncFromString(
                            const ::rtl::OUString& rString );

// EXPORT: GeneralFunction / ScSubTotalFunc
    static void			GetStringFromFunction(
                            ::rtl::OUString& rString,
                            const ::com::sun::star::sheet::GeneralFunction eFunction,
                            sal_Bool bAppendStr = sal_False );
    static void			GetStringFromFunction(
                            ::rtl::OUString& rString,
                            const ScSubTotalFunc eFunction,
                            sal_Bool bAppendStr = sal_False );

// IMPORT: DataPilotFieldOrientation
    static ::com::sun::star::sheet::DataPilotFieldOrientation
                        GetOrientationFromString(
                            const ::rtl::OUString& rString );

// EXPORT: DataPilotFieldOrientation
    static void			GetStringFromOrientation(
                            ::rtl::OUString& rString,
                            const ::com::sun::star::sheet::DataPilotFieldOrientation eOrientation,
                            sal_Bool bAppendStr = sal_False );

// IMPORT: Detective
    static ScDetectiveObjType
                        GetDetObjTypeFromString(
                            const ::rtl::OUString& rString );
    static sal_Bool		GetDetOpTypeFromString(
                            ScDetOpType& rDetOpType,
                            const ::rtl::OUString& rString );

// EXPORT: Detective
    static void			GetStringFromDetObjType(
                            ::rtl::OUString& rString,
                            const ScDetectiveObjType eObjType,
                            sal_Bool bAppendStr = sal_False );
    static void			GetStringFromDetOpType(
                            ::rtl::OUString& rString,
                            const ScDetOpType eOpType,
                            sal_Bool bAppendStr = sal_False );

// IMPORT: Formulas
    static void			ParseFormula(
                            ::rtl::OUString& sFormula,
                            const sal_Bool bIsFormula = sal_True);
// EXPORT: Core Date Time
    static void			ConvertDateTimeToString(const DateTime& aDateTime, ::rtl::OUStringBuffer& sDate);

    static void			ConvertCoreToAPIDateTime(const DateTime& aDateTime, ::com::sun::star::util::DateTime& rDateTime);

    static void         ConvertAPIToCoreDateTime(const ::com::sun::star::util::DateTime& aDateTime, DateTime& rDateTime);
};


} //namespace binfilter
#endif

