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

#ifndef SC_XMLIMPRT_HXX
#define SC_XMLIMPRT_HXX

#include <rsc/rscsfx.hxx>
#include <bf_xmloff/xmlictxt.hxx>
#include <bf_xmloff/xmlimp.hxx>
#include <bf_xmloff/xmltkmap.hxx>
#include <bf_xmloff/xmlaustp.hxx>
#include <bf_xmloff/xmlstyle.hxx>
#include <vcl/svapp.hxx>
#include <com/sun/star/frame/XModel.hpp>
#include <tools/time.hxx>
#include <com/sun/star/util/DateTime.hpp>
#ifndef __SGI_STL_VECTOR
#include <vector>
#endif
#include "xmlsubti.hxx"
#include "global.hxx"
#include "xmlstyle.hxx"
#include "XMLDetectiveContext.hxx"
#include <com/sun/star/sheet/ValidationAlertStyle.hpp>
#include <com/sun/star/sheet/ValidationType.hpp>
#include <com/sun/star/sheet/ConditionOperator.hpp>
#include <com/sun/star/table/CellAddress.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/util/XNumberFormatTypes.hpp>
#include <com/sun/star/sheet/XSheetCellRangeContainer.hpp>
namespace binfilter {

class SfxItemSet;
class ScRangeList;
class ScMyStyleNumberFormats;
class XMLShapeImportHelper;
class XMLNumberFormatAttributesExportHelper;
class SvXMLTokenMap;
class SvXMLStyleContext;

using namespace ::rtl;

enum ScXMLDocTokens
{
    XML_TOK_DOC_FONTDECLS,
    XML_TOK_DOC_STYLES,
    XML_TOK_DOC_AUTOSTYLES,
    XML_TOK_DOC_MASTERSTYLES,
    XML_TOK_DOC_META,
    XML_TOK_DOC_SCRIPTS,
    XML_TOK_DOC_BODY,
    XML_TOK_DOC_SETTINGS,
    XML_TOK_OFFICE_END=XML_TOK_UNKNOWN
};

enum ScXMLStylesTokens
{
    XML_TOK_STYLES_STYLE
};

enum ScXMLStylesAttrTokens
{
    XML_TOK_STYLES_STYLE_NAME,
    XML_TOK_STYLES_STYLE_FAMILY,
    XML_TOK_STYLES_STYLE_PARENT_STYLE_NAME
};

enum ScXMLStyleTokens
{
    XML_TOK_STYLE_PROPERTIES
};

enum ScXMLBodyTokens
{
    XML_TOK_BODY_TRACKED_CHANGES,
    XML_TOK_BODY_CALCULATION_SETTINGS,
    XML_TOK_BODY_CONTENT_VALIDATIONS,
    XML_TOK_BODY_LABEL_RANGES,
    XML_TOK_BODY_TABLE,
    XML_TOK_BODY_NAMED_EXPRESSIONS,
    XML_TOK_BODY_DATABASE_RANGES,
    XML_TOK_BODY_DATABASE_RANGE,
    XML_TOK_BODY_DATA_PILOT_TABLES,
    XML_TOK_BODY_CONSOLIDATION,
    XML_TOK_BODY_DDE_LINKS
};

enum ScXMLContentValidationsElemTokens
{
    XML_TOK_CONTENT_VALIDATION
};

enum ScXMLContentValidationElemTokens
{
    XML_TOK_CONTENT_VALIDATION_ELEM_HELP_MESSAGE,
    XML_TOK_CONTENT_VALIDATION_ELEM_ERROR_MESSAGE,
    XML_TOK_CONTENT_VALIDATION_ELEM_ERROR_MACRO
};

enum ScXMLContentValidationAttrTokens
{
    XML_TOK_CONTENT_VALIDATION_NAME,
    XML_TOK_CONTENT_VALIDATION_CONDITION,
    XML_TOK_CONTENT_VALIDATION_BASE_CELL_ADDRESS,
    XML_TOK_CONTENT_VALIDATION_ALLOW_EMPTY_CELL
};

enum ScXMLContentValidationMessageElemTokens
{
    XML_TOK_P
};

enum ScXMLContentValidationHelpMessageAttrTokens
{
    XML_TOK_HELP_MESSAGE_ATTR_TITLE,
    XML_TOK_HELP_MESSAGE_ATTR_DISPLAY
};

enum ScXMLContentValidationErrorMessageAttrTokens
{
    XML_TOK_ERROR_MESSAGE_ATTR_TITLE,
    XML_TOK_ERROR_MESSAGE_ATTR_DISPLAY,
    XML_TOK_ERROR_MESSAGE_ATTR_MESSAGE_TYPE
};

enum ScXMLContentValidationErrorMacroAttrTokens
{
    XML_TOK_ERROR_MACRO_ATTR_NAME,
    XML_TOK_ERROR_MACRO_ATTR_EXECUTE
};

enum ScXMLLabelRangesElemTokens
{
    XML_TOK_LABEL_RANGE_ELEM
};

enum ScXMLLabelRangeAttrTokens
{
    XML_TOK_LABEL_RANGE_ATTR_LABEL_RANGE,
    XML_TOK_LABEL_RANGE_ATTR_DATA_RANGE,
    XML_TOK_LABEL_RANGE_ATTR_ORIENTATION
};

enum ScXMLTableTokens
{
    XML_TOK_TABLE_COL_GROUP,
    XML_TOK_TABLE_HEADER_COLS,
    XML_TOK_TABLE_COLS,
    XML_TOK_TABLE_COL,
    XML_TOK_TABLE_ROW_GROUP,
    XML_TOK_TABLE_HEADER_ROWS,
    XML_TOK_TABLE_ROWS,
    XML_TOK_TABLE_ROW,
    XML_TOK_TABLE_SOURCE,
    XML_TOK_TABLE_SCENARIO,
    XML_TOK_TABLE_SHAPES,
    XML_TOK_TABLE_FORMS
};

enum ScXMLTableRowsTokens
{
    XML_TOK_TABLE_ROWS_ROW_GROUP,
    XML_TOK_TABLE_ROWS_HEADER_ROWS,
    XML_TOK_TABLE_ROWS_ROWS,
    XML_TOK_TABLE_ROWS_ROW
};

enum ScXMLTableColsTokens
{
    XML_TOK_TABLE_COLS_COL_GROUP,
    XML_TOK_TABLE_COLS_HEADER_COLS,
    XML_TOK_TABLE_COLS_COLS,
    XML_TOK_TABLE_COLS_COL
};

enum ScXMLTableAttrTokens
{
    XML_TOK_TABLE_NAME,
    XML_TOK_TABLE_STYLE_NAME,
    XML_TOK_TABLE_PROTECTION,
    XML_TOK_TABLE_PRINT_RANGES,
    XML_TOK_TABLE_PASSWORD
};

enum ScXMLTableScenarioAttrTokens
{
    XML_TOK_TABLE_SCENARIO_ATTR_DISPLAY_BORDER,
    XML_TOK_TABLE_SCENARIO_ATTR_BORDER_COLOR,
    XML_TOK_TABLE_SCENARIO_ATTR_COPY_BACK,
    XML_TOK_TABLE_SCENARIO_ATTR_COPY_STYLES,
    XML_TOK_TABLE_SCENARIO_ATTR_COPY_FORMULAS,
    XML_TOK_TABLE_SCENARIO_ATTR_IS_ACTIVE,
    XML_TOK_TABLE_SCENARIO_ATTR_SCENARIO_RANGES,
    XML_TOK_TABLE_SCENARIO_ATTR_COMMENT
};

enum ScXMLTableColAttrTokens
{
    XML_TOK_TABLE_COL_ATTR_STYLE_NAME,
    XML_TOK_TABLE_COL_ATTR_REPEATED,
    XML_TOK_TABLE_COL_ATTR_VISIBILITY,
    XML_TOK_TABLE_COL_ATTR_DEFAULT_CELL_STYLE_NAME
};

enum ScXMLTableRowTokens
{
    XML_TOK_TABLE_ROW_CELL,
    XML_TOK_TABLE_ROW_COVERED_CELL
};

enum ScXMLTableRowAttrTokens
{
    XML_TOK_TABLE_ROW_ATTR_STYLE_NAME,
    XML_TOK_TABLE_ROW_ATTR_VISIBILITY,
    XML_TOK_TABLE_ROW_ATTR_REPEATED,
    XML_TOK_TABLE_ROW_ATTR_DEFAULT_CELL_STYLE_NAME
//	XML_TOK_TABLE_ROW_ATTR_USE_OPTIMAL_HEIGHT
};

enum ScXMLTableRowCellTokens
{
    XML_TOK_TABLE_ROW_CELL_P,
    XML_TOK_TABLE_ROW_CELL_SUBTABLE,
    XML_TOK_TABLE_ROW_CELL_ANNOTATION,
    XML_TOK_TABLE_ROW_CELL_DETECTIVE,
    XML_TOK_TABLE_ROW_CELL_CELL_RANGE_SOURCE
};

enum ScXMLTableRowCellAttrTokens
{
    XML_TOK_TABLE_ROW_CELL_ATTR_STYLE_NAME,
    XML_TOK_TABLE_ROW_CELL_ATTR_CONTENT_VALIDATION_NAME,
    XML_TOK_TABLE_ROW_CELL_ATTR_SPANNED_ROWS,
    XML_TOK_TABLE_ROW_CELL_ATTR_SPANNED_COLS,
    XML_TOK_TABLE_ROW_CELL_ATTR_SPANNED_MATRIX_COLS,
    XML_TOK_TABLE_ROW_CELL_ATTR_SPANNED_MATRIX_ROWS,
    XML_TOK_TABLE_ROW_CELL_ATTR_REPEATED,
    XML_TOK_TABLE_ROW_CELL_ATTR_VALUE_TYPE,
    XML_TOK_TABLE_ROW_CELL_ATTR_VALUE,
    XML_TOK_TABLE_ROW_CELL_ATTR_DATE_VALUE,
    XML_TOK_TABLE_ROW_CELL_ATTR_TIME_VALUE,
    XML_TOK_TABLE_ROW_CELL_ATTR_STRING_VALUE,
    XML_TOK_TABLE_ROW_CELL_ATTR_BOOLEAN_VALUE,
    XML_TOK_TABLE_ROW_CELL_ATTR_FORMULA,
    XML_TOK_TABLE_ROW_CELL_ATTR_CURRENCY
};

enum ScXMLAnnotationAttrTokens
{
    XML_TOK_TABLE_ANNOTATION_ATTR_AUTHOR,
    XML_TOK_TABLE_ANNOTATION_ATTR_CREATE_DATE,
    XML_TOK_TABLE_ANNOTATION_ATTR_CREATE_DATE_STRING,
    XML_TOK_TABLE_ANNOTATION_ATTR_DISPLAY
};

enum ScXMLDetectiveElemTokens
{
    XML_TOK_DETECTIVE_ELEM_HIGHLIGHTED,
    XML_TOK_DETECTIVE_ELEM_OPERATION
};

enum ScXMLDetectiveHighlightedAttrTokens
{
    XML_TOK_DETECTIVE_HIGHLIGHTED_ATTR_CELL_RANGE,
    XML_TOK_DETECTIVE_HIGHLIGHTED_ATTR_DIRECTION,
    XML_TOK_DETECTIVE_HIGHLIGHTED_ATTR_CONTAINS_ERROR,
    XML_TOK_DETECTIVE_HIGHLIGHTED_ATTR_MARKED_INVALID
};

enum ScXMLDetectiveOperationAttrTokens
{
    XML_TOK_DETECTIVE_OPERATION_ATTR_NAME,
    XML_TOK_DETECTIVE_OPERATION_ATTR_INDEX
};

enum ScXMLCellRangeSourceAttrTokens
{
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_NAME,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_HREF,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_FILTER_NAME,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_FILTER_OPTIONS,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_LAST_COLUMN,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_LAST_ROW,
    XML_TOK_TABLE_CELL_RANGE_SOURCE_ATTR_REFRESH_DELAY
};

enum ScXMLNamedExpressionsTokens
{
    XML_TOK_NAMED_EXPRESSIONS_NAMED_RANGE,
    XML_TOK_NAMED_EXPRESSIONS_NAMED_EXPRESSION
};

enum ScXMLNamedRangeAttrTokens
{
    XML_TOK_NAMED_RANGE_ATTR_NAME,
    XML_TOK_NAMED_RANGE_ATTR_CELL_RANGE_ADDRESS,
    XML_TOK_NAMED_RANGE_ATTR_BASE_CELL_ADDRESS,
    XML_TOK_NAMED_RANGE_ATTR_RANGE_USABLE_AS
};

enum ScXMLNamedExpressionAttrTokens
{
    XML_TOK_NAMED_EXPRESSION_ATTR_NAME,
    XML_TOK_NAMED_EXPRESSION_ATTR_BASE_CELL_ADDRESS,
    XML_TOK_NAMED_EXPRESSION_ATTR_EXPRESSION
};

enum ScXMLDatabaseRangesTokens
{
    XML_TOK_DATABASE_RANGE
};

enum ScXMLDatabaseRangeTokens
{
    XML_TOK_DATABASE_RANGE_SOURCE_SQL,
    XML_TOK_DATABASE_RANGE_SOURCE_TABLE,
    XML_TOK_DATABASE_RANGE_SOURCE_QUERY,
    XML_TOK_FILTER,
    XML_TOK_SORT,
    XML_TOK_DATABASE_RANGE_SUBTOTAL_RULES
};

enum ScXMLDatabaseRangeAttrTokens
{
    XML_TOK_DATABASE_RANGE_ATTR_NAME,
    XML_TOK_DATABASE_RANGE_ATTR_IS_SELECTION,
    XML_TOK_DATABASE_RANGE_ATTR_ON_UPDATE_KEEP_STYLES,
    XML_TOK_DATABASE_RANGE_ATTR_ON_UPDATE_KEEP_SIZE,
    XML_TOK_DATABASE_RANGE_ATTR_HAS_PERSISTENT_DATA,
    XML_TOK_DATABASE_RANGE_ATTR_ORIENTATION,
    XML_TOK_DATABASE_RANGE_ATTR_CONTAINS_HEADER,
    XML_TOK_DATABASE_RANGE_ATTR_DISPLAY_FILTER_BUTTONS,
    XML_TOK_DATABASE_RANGE_ATTR_TARGET_RANGE_ADDRESS,
    XML_TOK_DATABASE_RANGE_ATTR_REFRESH_DELAY
};

enum ScXMLDatabaseRangeSourceSQLAttrTokens
{
    XML_TOK_SOURCE_SQL_ATTR_DATABASE_NAME,
    XML_TOK_SOURCE_SQL_ATTR_SQL_STATEMENT,
    XML_TOK_SOURCE_SQL_ATTR_PARSE_SQL_STATEMENT
};

enum ScXMLDatabaseRangeSourceTableAttrTokens
{
    XML_TOK_SOURCE_TABLE_ATTR_DATABASE_NAME,
    XML_TOK_SOURCE_TABLE_ATTR_TABLE_NAME
};

enum ScXMLDatabaseRangeSourceQueryAttrTokens
{
    XML_TOK_SOURCE_QUERY_ATTR_DATABASE_NAME,
    XML_TOK_SOURCE_QUERY_ATTR_QUERY_NAME
};

enum ScXMLFilterTokens
{
    XML_TOK_FILTER_AND,
    XML_TOK_FILTER_OR,
    XML_TOK_FILTER_CONDITION
};

enum ScXMLFilterAttrTokens
{
    XML_TOK_FILTER_ATTR_TARGET_RANGE_ADDRESS,
    XML_TOK_FILTER_ATTR_CONDITION_SOURCE_RANGE_ADDRESS,
    XML_TOK_FILTER_ATTR_CONDITION_SOURCE,
    XML_TOK_FILTER_ATTR_DISPLAY_DUPLICATES
};

enum ScXMLFilterConditionAttrTokens
{
    XML_TOK_CONDITION_ATTR_FIELD_NUMBER,
    XML_TOK_CONDITION_ATTR_CASE_SENSITIVE,
    XML_TOK_CONDITION_ATTR_DATA_TYPE,
    XML_TOK_CONDITION_ATTR_VALUE,
    XML_TOK_CONDITION_ATTR_OPERATOR
};

enum ScXMLSortTokens
{
    XML_TOK_SORT_SORT_BY
};

enum ScXMLSortAttrTokens
{
    XML_TOK_SORT_ATTR_BIND_STYLES_TO_CONTENT,
    XML_TOK_SORT_ATTR_TARGET_RANGE_ADDRESS,
    XML_TOK_SORT_ATTR_CASE_SENSITIVE,
    XML_TOK_SORT_ATTR_LANGUAGE,
    XML_TOK_SORT_ATTR_COUNTRY,
    XML_TOK_SORT_ATTR_ALGORITHM
};

enum ScXMLSortSortByAttrTokens
{
    XML_TOK_SORT_BY_ATTR_FIELD_NUMBER,
    XML_TOK_SORT_BY_ATTR_DATA_TYPE,
    XML_TOK_SORT_BY_ATTR_ORDER
};

enum ScXMLDatabaseRangeSubTotalRulesTokens
{
    XML_TOK_SUBTOTAL_RULES_SORT_GROUPS,
    XML_TOK_SUBTOTAL_RULES_SUBTOTAL_RULE
};

enum ScXMLDatabaseRangeSubTotalRulesAttrTokens
{
    XML_TOK_SUBTOTAL_RULES_ATTR_BIND_STYLES_TO_CONTENT,
    XML_TOK_SUBTOTAL_RULES_ATTR_CASE_SENSITIVE,
    XML_TOK_SUBTOTAL_RULES_ATTR_PAGE_BREAKS_ON_GROUP_CHANGE
};

enum ScXMLSubTotalRulesSortGroupsAttrTokens
{
    XML_TOK_SORT_GROUPS_ATTR_DATA_TYPE,
    XML_TOK_SORT_GROUPS_ATTR_ORDER
};

enum ScXMLSubTotalRulesSubTotalRuleTokens
{
    XML_TOK_SUBTOTAL_RULE_SUBTOTAL_FIELD
};

enum ScXMLSubTotalRulesSubTotalRuleAttrTokens
{
    XML_TOK_SUBTOTAL_RULE_ATTR_GROUP_BY_FIELD_NUMBER
};

enum ScXMLSubTotalRuleSubTotalField
{
    XML_TOK_SUBTOTAL_FIELD_ATTR_FIELD_NUMBER,
    XML_TOK_SUBTOTAL_FIELD_ATTR_FUNCTION
};

enum ScXMLDataPilotTablesElemTokens
{
    XML_TOK_DATA_PILOT_TABLE
};

enum ScXMLDataPilotTableAttrTokens
{
    XML_TOK_DATA_PILOT_TABLE_ATTR_NAME,
    XML_TOK_DATA_PILOT_TABLE_ATTR_APPLICATION_DATA,
    XML_TOK_DATA_PILOT_TABLE_ATTR_GRAND_TOTAL,
    XML_TOK_DATA_PILOT_TABLE_ATTR_IGNORE_EMPTY_ROWS,
    XML_TOK_DATA_PILOT_TABLE_ATTR_IDENTIFY_CATEGORIES,
    XML_TOK_DATA_PILOT_TABLE_ATTR_TARGET_RANGE_ADDRESS,
    XML_TOK_DATA_PILOT_TABLE_ATTR_BUTTONS
};

enum ScXMLDataPilotTableElemTokens
{
    XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_SQL,
    XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_TABLE,
    XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_QUERY,
    XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_SERVICE,
    XML_TOK_DATA_PILOT_TABLE_ELEM_SOURCE_CELL_RANGE,
    XML_TOK_DATA_PILOT_TABLE_ELEM_DATA_PILOT_FIELD
};

enum ScXMLDataPilotTableSourceServiceAttrTokens
{
    XML_TOK_SOURCE_SERVICE_ATTR_NAME,
    XML_TOK_SOURCE_SERVICE_ATTR_SOURCE_NAME,
    XML_TOK_SOURCE_SERVICE_ATTR_OBJECT_NAME,
    XML_TOK_SOURCE_SERVICE_ATTR_USERNAME,
    XML_TOK_SOURCE_SERVICE_ATTR_PASSWORD
};

enum ScXMLDataPilotTableSourceCellRangeElemTokens
{
    XML_TOK_SOURCE_CELL_RANGE_ELEM_FILTER
};

enum ScXMLDataPilotTableSourceCellRangeAttrTokens
{
    XML_TOK_SOURCE_CELL_RANGE_ATTR_CELL_RANGE_ADDRESS
};

enum ScXMLDataPilotFieldAttrTokens
{
    XML_TOK_DATA_PILOT_FIELD_ATTR_SOURCE_FIELD_NAME,
    XML_TOK_DATA_PILOT_FIELD_ATTR_IS_DATA_LAYOUT_FIELD,
    XML_TOK_DATA_PILOT_FIELD_ATTR_FUNCTION,
    XML_TOK_DATA_PILOT_FIELD_ATTR_ORIENTATION,
    XML_TOK_DATA_PILOT_FIELD_ATTR_USED_HIERARCHY
};

enum ScXMLDataPilotFieldElemTokens
{
    XML_TOK_DATA_PILOT_FIELD_ELEM_DATA_PILOT_LEVEL
};

enum ScXMLDataPilotLevelAttrTokens
{
    XML_TOK_DATA_PILOT_LEVEL_ATTR_DISPLAY_EMPTY
};

enum ScXMLDataPilotLevelElemTokens
{
    XML_TOK_DATA_PILOT_LEVEL_ELEM_DATA_PILOT_SUBTOTALS,
    XML_TOK_DATA_PILOT_LEVEL_ELEM_DATA_PILOT_MEMBERS
};

enum ScXMLDataPilotSubTotalsElemTokens
{
    XML_TOK_DATA_PILOT_SUBTOTALS_ELEM_DATA_PILOT_SUBTOTAL
};

enum ScXMLDataPilotSubTotalAttrTokens
{
    XML_TOK_DATA_PILOT_SUBTOTAL_ATTR_FUNCTION
};

enum ScXMLDataPilotMembersElemTokens
{
    XML_TOK_DATA_PILOT_MEMBERS_ELEM_DATA_PILOT_MEMBER
};

enum ScXMLDataPilotMemberAttrTokens
{
    XML_TOK_DATA_PILOT_MEMBER_ATTR_NAME,
    XML_TOK_DATA_PILOT_MEMBER_ATTR_DISPLAY,
    XML_TOK_DATA_PILOT_MEMBER_ATTR_DISPLAY_DETAILS
};

enum ScXMLConsolidationAttrTokens
{
    XML_TOK_CONSOLIDATION_ATTR_FUNCTION,
    XML_TOK_CONSOLIDATION_ATTR_SOURCE_RANGES,
    XML_TOK_CONSOLIDATION_ATTR_TARGET_ADDRESS,
    XML_TOK_CONSOLIDATION_ATTR_USE_LABEL,
    XML_TOK_CONSOLIDATION_ATTR_LINK_TO_SOURCE
};


class SvI18NMap;
//class SvXMLImportItemMapper;
class SvXMLNumFmtHelper;
class ScXMLChangeTrackingImportHelper;

struct tScMyCellRange
{
    sal_Int16 Sheet;
    sal_Int32 StartColumn, EndColumn;
    sal_Int32 StartRow, EndRow;
};

struct ScMyNamedExpression
{
    ::rtl::OUString 	sName;
    ::rtl::OUString 	sContent;
    ::rtl::OUString 	sBaseCellAddress;
    ::rtl::OUString 	sRangeType;
    sal_Bool		bIsExpression : 1;
};

typedef std::list<const ScMyNamedExpression*> ScMyNamedExpressions;

struct ScMyImportValidation
{
    ::rtl::OUString									sName;
    ::rtl::OUString									sImputTitle;
    ::rtl::OUString									sImputMessage;
    ::rtl::OUString									sErrorTitle;
    ::rtl::OUString									sErrorMessage;
    ::rtl::OUString									sFormula1;
    ::rtl::OUString									sFormula2;
    ::rtl::OUString									sBaseCellAddress;
    ::com::sun::star::table::CellAddress				aBaseCellAddress;
    ::com::sun::star::sheet::ValidationAlertStyle		aAlertStyle;
    ::com::sun::star::sheet::ValidationType			aValidationType;
    ::com::sun::star::sheet::ConditionOperator		aOperator;
    sal_Bool										bShowErrorMessage : 1;
    sal_Bool										bShowImputMessage : 1;
    sal_Bool										bIgnoreBlanks : 1;
};

typedef std::vector<ScMyImportValidation>			ScMyImportValidations;
typedef std::list<SvXMLImportContext*>				ScMyViewContextList;
class ScMyStylesImportHelper;

class ScXMLImport: public SvXMLImport
{
    ScDocument*				pDoc;
    ScXMLChangeTrackingImportHelper*	pChangeTrackingImportHelper;
    ScMyViewContextList					aViewContextList;
    ScMyStylesImportHelper*				pStylesImportHelper;
    ::rtl::OUString						sNumberFormat;
    ::rtl::OUString						sLocale;
    ::rtl::OUString						sCellStyle;
    ::rtl::OUString						sStandardFormat;
    ::rtl::OUString						sType;

//	SvXMLAutoStylePoolP		*pScAutoStylePool;
    UniReference < XMLPropertyHandlerFactory >	xScPropHdlFactory;
    UniReference < XMLPropertySetMapper >		xCellStylesPropertySetMapper;
    UniReference < XMLPropertySetMapper >		xColumnStylesPropertySetMapper;
    UniReference < XMLPropertySetMapper >		xRowStylesPropertySetMapper;
    UniReference < XMLPropertySetMapper >		xTableStylesPropertySetMapper;
//	SvXMLImportContextRef		xStyles;
//	SvXMLImportContextRef		xAutoStyles;

//	SvXMLImportItemMapper	*pParaItemMapper;// paragraph item import
//	SvI18NMap				*pI18NMap;			// name mapping for I18N
    SvXMLTokenMap			*pDocElemTokenMap;
    SvXMLTokenMap			*pStylesElemTokenMap;
    SvXMLTokenMap			*pStylesAttrTokenMap;
    SvXMLTokenMap			*pStyleElemTokenMap;
    SvXMLTokenMap			*pBodyElemTokenMap;
    SvXMLTokenMap			*pContentValidationsElemTokenMap;
    SvXMLTokenMap			*pContentValidationElemTokenMap;
    SvXMLTokenMap			*pContentValidationAttrTokenMap;
    SvXMLTokenMap			*pContentValidationMessageElemTokenMap;
    SvXMLTokenMap			*pContentValidationHelpMessageAttrTokenMap;
    SvXMLTokenMap			*pContentValidationErrorMessageAttrTokenMap;
    SvXMLTokenMap			*pContentValidationErrorMacroAttrTokenMap;
    SvXMLTokenMap			*pLabelRangesElemTokenMap;
    SvXMLTokenMap			*pLabelRangeAttrTokenMap;
    SvXMLTokenMap			*pTableElemTokenMap;
    SvXMLTokenMap			*pTableRowsElemTokenMap;
    SvXMLTokenMap			*pTableColsElemTokenMap;
    SvXMLTokenMap			*pTableScenarioAttrTokenMap;
    SvXMLTokenMap			*pTableAttrTokenMap;
    SvXMLTokenMap			*pTableColAttrTokenMap;
    SvXMLTokenMap			*pTableRowElemTokenMap;
    SvXMLTokenMap			*pTableRowAttrTokenMap;
    SvXMLTokenMap			*pTableRowCellElemTokenMap;
    SvXMLTokenMap			*pTableRowCellAttrTokenMap;
    SvXMLTokenMap			*pTableAnnotationAttrTokenMap;
    SvXMLTokenMap			*pDetectiveElemTokenMap;
    SvXMLTokenMap			*pDetectiveHighlightedAttrTokenMap;
    SvXMLTokenMap			*pDetectiveOperationAttrTokenMap;
    SvXMLTokenMap			*pTableCellRangeSourceAttrTokenMap;
    SvXMLTokenMap			*pNamedExpressionsElemTokenMap;
    SvXMLTokenMap			*pNamedRangeAttrTokenMap;
    SvXMLTokenMap			*pNamedExpressionAttrTokenMap;
    SvXMLTokenMap			*pDatabaseRangesElemTokenMap;
    SvXMLTokenMap			*pDatabaseRangeElemTokenMap;
    SvXMLTokenMap			*pDatabaseRangeAttrTokenMap;
    SvXMLTokenMap			*pDatabaseRangeSourceSQLAttrTokenMap;
    SvXMLTokenMap			*pDatabaseRangeSourceTableAttrTokenMap;
    SvXMLTokenMap			*pDatabaseRangeSourceQueryAttrTokenMap;
    SvXMLTokenMap			*pFilterElemTokenMap;
    SvXMLTokenMap			*pFilterAttrTokenMap;
    SvXMLTokenMap			*pFilterConditionAttrTokenMap;
    SvXMLTokenMap			*pSortElemTokenMap;
    SvXMLTokenMap			*pSortAttrTokenMap;
    SvXMLTokenMap			*pSortSortByAttrTokenMap;
    SvXMLTokenMap			*pDatabaseRangeSubTotalRulesElemTokenMap;
    SvXMLTokenMap			*pDatabaseRangeSubTotalRulesAttrTokenMap;
    SvXMLTokenMap			*pSubTotalRulesSortGroupsAttrTokenMap;
    SvXMLTokenMap			*pSubTotalRulesSubTotalRuleElemTokenMap;
    SvXMLTokenMap			*pSubTotalRulesSubTotalRuleAttrTokenMap;
    SvXMLTokenMap			*pSubTotalRuleSubTotalFieldAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotTablesElemTokenMap;
    SvXMLTokenMap 			*pDataPilotTableAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotTableElemTokenMap;
    SvXMLTokenMap 			*pDataPilotTableSourceServiceAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotTableSourceCellRangeElemTokenMap;
    SvXMLTokenMap 			*pDataPilotTableSourceCellRangeAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotFieldAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotFieldElemTokenMap;
    SvXMLTokenMap 			*pDataPilotLevelAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotLevelElemTokenMap;
    SvXMLTokenMap 			*pDataPilotSubTotalsElemTokenMap;
    SvXMLTokenMap 			*pDataPilotSubTotalAttrTokenMap;
    SvXMLTokenMap 			*pDataPilotMembersElemTokenMap;
    SvXMLTokenMap 			*pDataPilotMemberAttrTokenMap;
    SvXMLTokenMap 			*pConsolidationAttrTokenMap;

    ScMyTables				aTables;

    ScMyNamedExpressions* 	pMyNamedExpressions;
    ScMyImportValidations*	pValidations;
    ScMyImpDetectiveOpArray*	pDetectiveOpArray;
    SolarMutexGuard*        pSolarMutexGuard;

    ::rtl::OUString			sFirstTableStyle;
    XMLNumberFormatAttributesExportHelper* pNumberFormatAttributesExportHelper;
    ScMyStyleNumberFormats* pStyleNumberFormats;
    ::com::sun::star::uno::Reference < ::com::sun::star::util::XNumberFormats> xNumberFormats;
    ::com::sun::star::uno::Reference < ::com::sun::star::util::XNumberFormatTypes> xNumberFormatTypes;

    ::com::sun::star::uno::Reference < ::com::sun::star::sheet::XSheetCellRangeContainer> xSheetCellRanges;

    ::rtl::OUString			sEmpty;
    ::rtl::OUString			sPrevStyleName;
    ::rtl::OUString			sPrevCurrency;
    sal_uInt32				nSolarMutexLocked;
    sal_uInt16				nStyleFamilyMask;// Mask of styles to load
    sal_Int16				nPrevCellType;
    sal_Bool				bLoadDoc;	// Load doc or styles only
    sal_Bool				bRemoveLastChar;
    sal_Bool				bNullDateSetted;
    sal_Bool                bSelfImportingXMLSet;
    sal_uInt32              nRangeOverflowType;


protected:

    // This method is called after the namespace map has been updated, but
    // before a context for the current element has been pushed.
    virtual SvXMLImportContext *CreateContext(USHORT nPrefix,
                                      const ::rtl::OUString& rLocalName,
                                      const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );
    virtual XMLShapeImportHelper* CreateShapeImport();

public:
    // #110680#
    ScXMLImport(
        const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
        const sal_uInt16 nImportFlag);

        ~ScXMLImport() throw();

    // namespace office
    SvXMLImportContext *CreateMetaContext(
                                    const ::rtl::OUString& rLocalName );
    SvXMLImportContext *CreateFontDeclsContext(const USHORT nPrefix, const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList);
    SvXMLImportContext *CreateScriptContext(
                                    const ::rtl::OUString& rLocalName );
    SvXMLImportContext *CreateStylesContext(const ::rtl::OUString& rLocalName,
                                     const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList, sal_Bool bAutoStyles );
//	SvXMLImportContext *CreateUseStylesContext(const ::rtl::OUString& rLocalName ,
//									const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList);
    SvXMLImportContext *CreateBodyContext(
                                    const ::rtl::OUString& rLocalName,
                                    const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    virtual void SetStatisticAttributes( const ::com::sun::star::uno::Reference<
                                          ::com::sun::star::xml::sax::XAttributeList>& xAttrList );

    inline ScDocument*			GetDocument()			{ return pDoc; }
    inline const ScDocument*	GetDocument() const		{ return pDoc; }

    ScMyTables& GetTables() { return aTables; }

    sal_uInt16 GetStyleFamilyMask() const { return nStyleFamilyMask; }
    sal_Bool IsStylesOnlyMode() const { return !bLoadDoc; }

//	SvI18NMap& GetI18NMap() { return *pI18NMap; }

//	inline const SvXMLImportItemMapper& GetParaItemMapper() const;
//	SvXMLImportContext *CreateParaItemImportContext( USHORT nPrefix,
//								  const ::rtl::OUString& rLocalName,
//								  const ::com::sun::star::uno::Reference<
//									::com::sun::star::xml::sax::XAttributeList& xAttrList,
//								  SfxItemSet& rItemSet );

    UniReference < XMLPropertySetMapper > GetCellStylesPropertySetMapper() const { return xCellStylesPropertySetMapper; }
    UniReference < XMLPropertySetMapper > GetColumnStylesPropertySetMapper() const { return xColumnStylesPropertySetMapper; }
    UniReference < XMLPropertySetMapper > GetRowStylesPropertySetMapper() const { return xRowStylesPropertySetMapper; }
    UniReference < XMLPropertySetMapper > GetTableStylesPropertySetMapper() const { return xTableStylesPropertySetMapper; }
//	SvXMLImportContextRef			GetAutoStyles() const { return xAutoStyles; }
//	SvXMLImportContextRef			GetStyles() const { return xStyles; }

    const SvXMLTokenMap& GetDocElemTokenMap();
    const SvXMLTokenMap& GetBodyElemTokenMap();
    const SvXMLTokenMap& GetContentValidationsElemTokenMap();
    const SvXMLTokenMap& GetContentValidationElemTokenMap();
    const SvXMLTokenMap& GetContentValidationAttrTokenMap();
    const SvXMLTokenMap& GetContentValidationMessageElemTokenMap();
    const SvXMLTokenMap& GetContentValidationHelpMessageAttrTokenMap();
    const SvXMLTokenMap& GetContentValidationErrorMessageAttrTokenMap();
    const SvXMLTokenMap& GetContentValidationErrorMacroAttrTokenMap();
    const SvXMLTokenMap& GetLabelRangesElemTokenMap();
    const SvXMLTokenMap& GetLabelRangeAttrTokenMap();
    const SvXMLTokenMap& GetTableElemTokenMap();
    const SvXMLTokenMap& GetTableRowsElemTokenMap();
    const SvXMLTokenMap& GetTableColsElemTokenMap();
    const SvXMLTokenMap& GetTableAttrTokenMap();
    const SvXMLTokenMap& GetTableScenarioAttrTokenMap();
    const SvXMLTokenMap& GetTableColAttrTokenMap();
    const SvXMLTokenMap& GetTableRowElemTokenMap();
    const SvXMLTokenMap& GetTableRowAttrTokenMap();
    const SvXMLTokenMap& GetTableRowCellElemTokenMap();
    const SvXMLTokenMap& GetTableAnnotationAttrTokenMap();
    const SvXMLTokenMap& GetDetectiveElemTokenMap();
    const SvXMLTokenMap& GetDetectiveHighlightedAttrTokenMap();
    const SvXMLTokenMap& GetDetectiveOperationAttrTokenMap();
    const SvXMLTokenMap& GetTableCellRangeSourceAttrTokenMap();
    const SvXMLTokenMap& GetNamedExpressionsElemTokenMap();
    const SvXMLTokenMap& GetNamedRangeAttrTokenMap();
    const SvXMLTokenMap& GetNamedExpressionAttrTokenMap();
    const SvXMLTokenMap& GetDatabaseRangesElemTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeElemTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeAttrTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeSourceSQLAttrTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeSourceTableAttrTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeSourceQueryAttrTokenMap();
    const SvXMLTokenMap& GetFilterElemTokenMap();
    const SvXMLTokenMap& GetFilterAttrTokenMap();
    const SvXMLTokenMap& GetFilterConditionAttrTokenMap();
    const SvXMLTokenMap& GetSortElemTokenMap();
    const SvXMLTokenMap& GetSortAttrTokenMap();
    const SvXMLTokenMap& GetSortSortByAttrTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeSubTotalRulesElemTokenMap();
    const SvXMLTokenMap& GetDatabaseRangeSubTotalRulesAttrTokenMap();
    const SvXMLTokenMap& GetSubTotalRulesSortGroupsAttrTokenMap();
    const SvXMLTokenMap& GetSubTotalRulesSubTotalRuleElemTokenMap();
    const SvXMLTokenMap& GetSubTotalRulesSubTotalRuleAttrTokenMap();
    const SvXMLTokenMap& GetSubTotalRuleSubTotalFieldAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotTablesElemTokenMap();
    const SvXMLTokenMap& GetDataPilotTableAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotTableElemTokenMap();
    const SvXMLTokenMap& GetDataPilotTableSourceServiceAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotTableSourceCellRangeElemTokenMap();
    const SvXMLTokenMap& GetDataPilotTableSourceCellRangeAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotFieldAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotFieldElemTokenMap();
    const SvXMLTokenMap& GetDataPilotLevelAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotLevelElemTokenMap();
    const SvXMLTokenMap& GetDataPilotSubTotalsElemTokenMap();
    const SvXMLTokenMap& GetDataPilotSubTotalAttrTokenMap();
    const SvXMLTokenMap& GetDataPilotMembersElemTokenMap();
    const SvXMLTokenMap& GetDataPilotMemberAttrTokenMap();
    const SvXMLTokenMap& GetConsolidationAttrTokenMap();
//	const SvXMLTokenMap& GetTextPElemTokenMap();
//	const SvXMLTokenMap& GetTextPAttrTokenMap();
//	const SvXMLTokenMap& GetStyleStylesElemTokenMap();
//	const SvXMLTokenMap& GetTextListBlockAttrTokenMap();
//	const SvXMLTokenMap& GetTextListBlockElemTokenMap();

    void	AddNamedExpression(const ScMyNamedExpression* pMyNamedExpression) {
        if (!pMyNamedExpressions)
            pMyNamedExpressions = new ScMyNamedExpressions();
        pMyNamedExpressions->push_back(pMyNamedExpression); }
    ScMyNamedExpressions* GetNamedExpressions() { return pMyNamedExpressions; }

    void AddValidation(const ScMyImportValidation& rValidation) {
        if (!pValidations)
            pValidations = new ScMyImportValidations();
        pValidations->push_back(rValidation); }
    sal_Bool GetValidation(const ::rtl::OUString& sName, ScMyImportValidation& aValidation);

    inline ScMyImpDetectiveOpArray* GetDetectiveOpArray()	{
        if (!pDetectiveOpArray)
            pDetectiveOpArray = new ScMyImpDetectiveOpArray();
        return pDetectiveOpArray; }

    void SetRemoveLastChar(sal_Bool bValue) { bRemoveLastChar = bValue; }
    sal_Bool GetRemoveLastChar() { return bRemoveLastChar; }

    ScXMLChangeTrackingImportHelper* GetChangeTrackingImportHelper();
    void AddViewContext(SvXMLImportContext* pContext) { aViewContextList.push_back(pContext); }
    void InsertStyles();

    void SetChangeTrackingViewSettings(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& rChangeProps);
    virtual void SetViewSettings(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aViewProps);
    virtual void SetConfigurationSettings(const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& aConfigProps);

    void SetFirstTableStyle(const ::rtl::OUString& rValue) { sFirstTableStyle = rValue; }
    ::rtl::OUString GetFirstTableStyle() { return sFirstTableStyle; }
    ScMyStylesImportHelper* GetStylesImportHelper() { return pStylesImportHelper; }
    sal_Int32 SetCurrencySymbol(const sal_Int32 nKey, const ::rtl::OUString& rCurrency);
    sal_Bool IsCurrencySymbol(const sal_Int32 nNumberFormat, const ::rtl::OUString& sCurrencySymbol);
    void SetType(::com::sun::star::uno::Reference < ::com::sun::star::beans::XPropertySet>& rProperties,
        sal_Int32& rNumberFormat,
        const sal_Int16 nCellType,
        const ::rtl::OUString& rCurrency);
private:
    void AddStyleRange(const ::com::sun::star::table::CellRangeAddress& rCellRange);
    void SetStyleToRanges();
public:
    void SetStyleToRange(const ScRange& rRange, const ::rtl::OUString* pStyleName,
        const sal_Int16 nCellType, const ::rtl::OUString* pCurrency);
    sal_Bool SetNullDateOnUnitConverter();
    XMLNumberFormatAttributesExportHelper* GetNumberFormatAttributesExportHelper();
    ScMyStyleNumberFormats* GetStyleNumberFormats();

    void SetStylesToRangesFinished();

    // XImporter
    virtual void SAL_CALL setTargetDocument( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XComponent >& xDoc ) throw(::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::uno::RuntimeException);

    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);

    // ::com::sun::star::xml::sax::XDocumentHandler
    virtual void SAL_CALL startDocument(void)
        throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException ); 
    virtual void SAL_CALL endDocument(void)
        throw( ::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException );

    virtual void DisposingModel();

    void LockSolarMutex();
    void UnlockSolarMutex();

    void SetRangeOverflowType(sal_uInt32 nType) { nRangeOverflowType = nType; }
    sal_Bool HasRangeOverflow() const { return nRangeOverflowType != 0; }
    sal_uInt32 GetRangeOverflowType() const { return nRangeOverflowType; }
};

} //namespace binfilter
#endif

