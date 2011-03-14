/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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


#ifdef _MSC_VER
#pragma hdrstop
#endif

#include <swtypes.hxx>
#include <cmdid.h>

#include <horiornt.hxx>

#include <doc.hxx>
#include <hints.hxx>
#include <fmtfld.hxx>
#include <txtfld.hxx>
#include <ndtxt.hxx>
#include <unomap.hxx>
#include <unoprnms.hxx>

#include <osl/diagnose.h>

#include <unoobj.hxx>
#include <unocoll.hxx>
#include <bf_svtools/itemprop.hxx>
#include <bf_svx/linkmgr.hxx>
#include <docstat.hxx>
#include <comphelper/types.hxx>
#include <com/sun/star/util/Time.hpp>
#include <com/sun/star/util/DateTimeRange.hpp>
#include <com/sun/star/util/DateTime.hpp>
#include <com/sun/star/util/Date.hpp>
#include <com/sun/star/beans/PropertyValues.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/PropertyState.hpp>
#include <com/sun/star/beans/XPropertySetInfo.hpp>
#include <com/sun/star/beans/XMultiPropertySet.hpp>
#include <com/sun/star/beans/XFastPropertySet.hpp>
#include <com/sun/star/beans/XVetoableChangeListener.hpp>
#include <com/sun/star/beans/XPropertyState.hpp>
#include <com/sun/star/beans/XPropertyStateChangeListener.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/beans/XPropertiesChangeListener.hpp>
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#include <com/sun/star/beans/XPropertyAccess.hpp>
#include <com/sun/star/beans/XPropertyContainer.hpp>
#include <com/sun/star/beans/PropertyStateChangeEvent.hpp>
#include <com/sun/star/beans/PropertyChangeEvent.hpp>
//undef to prevent error (from bf_sfx2/docfile.cxx)
#undef SEQUENCE
#include <com/sun/star/text/SetVariableType.hpp>
#include <com/sun/star/text/WrapTextMode.hpp>
#include <com/sun/star/text/TextContentAnchorType.hpp>
#include <com/sun/star/text/PageNumberType.hpp>
#include <unofield.hxx>
#include <unocrsr.hxx>
#include <fldbas.hxx>
#include <authfld.hxx>
#include <flddat.hxx>
#include <dbfld.hxx>
#include <usrfld.hxx>
#include <docufld.hxx>
#include <expfld.hxx>
#include <chpfld.hxx>
#include <flddropdown.hxx>
#include <poolfmt.hxx>
#include <poolfmt.hrc>
#include <pagedesc.hxx>
#include <docary.hxx>
#include <reffld.hxx>
#include <ddefld.hxx>
#include <tools/datetime.hxx>
#define _SVSTDARR_STRINGS
#include <bf_svtools/svstdarr.hxx>
#include <osl/mutex.hxx>
#include <vcl/svapp.hxx>
#include <SwStyleNameMapper.hxx>
#include <swunohelper.hxx>
#include <unofldmid.h>
namespace binfilter {
String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr );
using namespace ::com::sun::star;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::text;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;

using rtl::OUString;

#define COM_TEXT_FLDMASTER		"com.sun.star.text.FieldMaster."

static const sal_uInt16 aDocInfoSubTypeFromService[] =
{
    DI_CHANGE|DI_SUB_AUTHOR,	//PROPERTY_MAP_FLDTYP_DOCINFO_CHANGE_AUTHOR
    DI_CHANGE|DI_SUB_DATE,		//PROPERTY_MAP_FLDTYP_DOCINFO_CHANGE_DATE_TIME
    DI_EDIT|DI_SUB_TIME,		//PROPERTY_MAP_FLDTYP_DOCINFO_EDIT_TIME
    DI_COMMENT,					//PROPERTY_MAP_FLDTYP_DOCINFO_DESCRIPTION
    DI_CREATE|DI_SUB_AUTHOR,	//PROPERTY_MAP_FLDTYP_DOCINFO_CREATE_AUTHOR
    DI_CREATE|DI_SUB_DATE,		//PROPERTY_MAP_FLDTYP_DOCINFO_CREATE_DATE_TIME
    DI_INFO1, 					//PROPERTY_MAP_FLDTYP_DOCINFO_INFO_0
    DI_INFO2, 					//PROPERTY_MAP_FLDTYP_DOCINFO_INFO_1
    DI_INFO3, 					//PROPERTY_MAP_FLDTYP_DOCINFO_INFO_2
    DI_INFO4, 					//PROPERTY_MAP_FLDTYP_DOCINFO_INFO_3
    DI_PRINT|DI_SUB_AUTHOR,		//PROPERTY_MAP_FLDTYP_DOCINFO_PRINT_AUTHOR
    DI_PRINT|DI_SUB_DATE,		//PROPERTY_MAP_FLDTYP_DOCINFO_PRINT_DATE_TIME
    DI_KEYS,					//PROPERTY_MAP_FLDTYP_DOCINFO_KEY_WORDS
    DI_THEMA,					//PROPERTY_MAP_FLDTYP_DOCINFO_SUBJECT
    DI_TITEL,					//PROPERTY_MAP_FLDTYP_DOCINFO_TITLE
    DI_DOCNO					//PROPERTY_MAP_FLDTYP_DOCINFO_REVISION
};
struct ServiceIdResId
{
    USHORT nResId;
    USHORT nServiceId;
};
static const ServiceIdResId aServiceToRes[] =
{
    {RES_DATETIMEFLD, 	SW_SERVICE_FIELDTYPE_DATETIME				},
    {RES_USERFLD, 		SW_SERVICE_FIELDTYPE_USER                   },
    {RES_SETEXPFLD, 		SW_SERVICE_FIELDTYPE_SET_EXP            }    ,
    {RES_GETEXPFLD, 		SW_SERVICE_FIELDTYPE_GET_EXP            }    ,
    {RES_FILENAMEFLD, 	SW_SERVICE_FIELDTYPE_FILE_NAME              },
    {RES_PAGENUMBERFLD, 	SW_SERVICE_FIELDTYPE_PAGE_NUM           }    ,
    {RES_AUTHORFLD, 		SW_SERVICE_FIELDTYPE_AUTHOR             }    ,
    {RES_CHAPTERFLD, 	SW_SERVICE_FIELDTYPE_CHAPTER                },
    {RES_GETREFFLD, 		SW_SERVICE_FIELDTYPE_GET_REFERENCE      }    ,
    {RES_HIDDENTXTFLD, 	SW_SERVICE_FIELDTYPE_CONDITIONED_TEXT       },
    {RES_POSTITFLD, 		SW_SERVICE_FIELDTYPE_ANNOTATION         }    ,
    {RES_INPUTFLD, 		SW_SERVICE_FIELDTYPE_INPUT                  },
    {RES_MACROFLD, 		SW_SERVICE_FIELDTYPE_MACRO                  },
    {RES_DDEFLD, 		SW_SERVICE_FIELDTYPE_DDE                    },
    {RES_HIDDENPARAFLD, 	SW_SERVICE_FIELDTYPE_HIDDEN_PARA        }    ,
    {RES_DOCINFOFLD, 	SW_SERVICE_FIELDTYPE_DOC_INFO               },
    {RES_TEMPLNAMEFLD, 	SW_SERVICE_FIELDTYPE_TEMPLATE_NAME          },
    {RES_EXTUSERFLD, 	SW_SERVICE_FIELDTYPE_USER_EXT               },
    {RES_REFPAGESETFLD, 	SW_SERVICE_FIELDTYPE_REF_PAGE_SET       }    ,
    {RES_REFPAGEGETFLD, 	SW_SERVICE_FIELDTYPE_REF_PAGE_GET       }    ,
    {RES_JUMPEDITFLD, 	SW_SERVICE_FIELDTYPE_JUMP_EDIT              },
    {RES_SCRIPTFLD, 		SW_SERVICE_FIELDTYPE_SCRIPT             }    ,
    {RES_DBNEXTSETFLD, 	SW_SERVICE_FIELDTYPE_DATABASE_NEXT_SET      },
    {RES_DBNUMSETFLD, 	SW_SERVICE_FIELDTYPE_DATABASE_NUM_SET       },
    {RES_DBSETNUMBERFLD, SW_SERVICE_FIELDTYPE_DATABASE_SET_NUM      } ,
    {RES_DBFLD, 			SW_SERVICE_FIELDTYPE_DATABASE           }    ,
    {RES_DBNAMEFLD,		SW_SERVICE_FIELDTYPE_DATABASE_NAME          },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_PAGE_COUNT             },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_PARAGRAPH_COUNT        },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_WORD_COUNT             },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_CHARACTER_COUNT        },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_TABLE_COUNT            },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_GRAPHIC_OBJECT_COUNT   },
    {RES_DOCSTATFLD, 	SW_SERVICE_FIELDTYPE_EMBEDDED_OBJECT_COUNT  },
    {RES_DOCINFOFLD, 	SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_AUTHOR  },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_DATE_TIME},
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_EDIT_TIME       },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_DESCRIPTION     },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_AUTHOR   },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_DATE_TIME},
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_INFO_0          },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_INFO_1          },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_INFO_2          },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_INFO_3          },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_AUTHOR    },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_DATE_TIME },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_KEY_WORDS       },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_SUBJECT         },
    {RES_DOCINFOFLD,		SW_SERVICE_FIELDTYPE_DOCINFO_TITLE           },
    {RES_INPUTFLD, 		SW_SERVICE_FIELDTYPE_INPUT_USER                  },
    {RES_HIDDENTXTFLD, 	SW_SERVICE_FIELDTYPE_HIDDEN_TEXT                 },
    {RES_AUTHORITY, 	SW_SERVICE_FIELDTYPE_BIBLIOGRAPHY                },
    {RES_COMBINED_CHARS,	SW_SERVICE_FIELDTYPE_COMBINED_CHARACTERS	 },
    {RES_DROPDOWN,	SW_SERVICE_FIELDTYPE_DROPDOWN	                     },
    {RES_TABLEFLD,      SW_SERVICE_FIELDTYPE_TABLE_FORMULA              },
    {USHRT_MAX,			USHRT_MAX                                        }
};
//-----------------------------------------------------------------
sal_uInt16 lcl_ServiceIdToResId(sal_uInt16 nServiceId)
{
    const ServiceIdResId* pMap;
    for( pMap = aServiceToRes;
            USHRT_MAX != pMap->nServiceId && nServiceId != pMap->nServiceId;
            ++pMap )
        ;
#ifdef DBG_UTIL
    if( USHRT_MAX == pMap->nServiceId )
        OSL_FAIL("service id not found");
#endif
    return pMap->nResId;
}
//-----------------------------------------------------------------
sal_uInt16 lcl_GetServiceForField( const SwField& rFld )
{
    sal_uInt16 nWhich = rFld.Which(), nSrvId = USHRT_MAX;
    //special handling for some fields
    switch( nWhich )
    {
    case RES_INPUTFLD:
        if( INP_USR == (rFld.GetSubType() & 0x00ff) )
            nSrvId = SW_SERVICE_FIELDTYPE_INPUT_USER;
        break;

    case RES_DOCINFOFLD:
        {
            USHORT nSubType = rFld.GetSubType();
            switch( (nSubType & 0xff))
            {
            case DI_CHANGE:
                nSrvId = ((nSubType&0x300) == DI_SUB_AUTHOR)
                        ? SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_AUTHOR
                        : SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_DATE_TIME;
                break;
            case DI_CREATE:
                nSrvId = ((nSubType&0x300) == DI_SUB_AUTHOR)
                        ? SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_AUTHOR
                        : SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_DATE_TIME;
                break;
            case DI_PRINT:
                nSrvId = ((nSubType&0x300) == DI_SUB_AUTHOR)
                        ? SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_AUTHOR
                        : SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_DATE_TIME;
                break;
            case DI_EDIT:	nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_EDIT_TIME;break;
            case DI_COMMENT:nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_DESCRIPTION;break;
            case DI_INFO1:	nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_INFO_0;	break;
            case DI_INFO2:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_INFO_1;	break;
            case DI_INFO3:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_INFO_2;	break;
            case DI_INFO4:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_INFO_3;	break;
            case DI_KEYS:   nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_KEY_WORDS;break;
            case DI_THEMA:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_SUBJECT;	break;
            case DI_TITEL:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_TITLE;	break;
            case DI_DOCNO:  nSrvId = SW_SERVICE_FIELDTYPE_DOCINFO_REVISION;	break;
            }
        }
        break;

    case RES_HIDDENTXTFLD:
        nSrvId = TYP_CONDTXTFLD == rFld.GetSubType()
                        ? SW_SERVICE_FIELDTYPE_CONDITIONED_TEXT
                        : SW_SERVICE_FIELDTYPE_HIDDEN_TEXT;
        break;

    case RES_DOCSTATFLD:
        {
            switch( rFld.GetSubType() )
            {
            case DS_PAGE: nSrvId = SW_SERVICE_FIELDTYPE_PAGE_COUNT; break;
            case DS_PARA: nSrvId = SW_SERVICE_FIELDTYPE_PARAGRAPH_COUNT; break;
            case DS_WORD: nSrvId = SW_SERVICE_FIELDTYPE_WORD_COUNT     ; break;
            case DS_CHAR: nSrvId = SW_SERVICE_FIELDTYPE_CHARACTER_COUNT; break;
            case DS_TBL:  nSrvId = SW_SERVICE_FIELDTYPE_TABLE_COUNT    ; break;
            case DS_GRF:  nSrvId = SW_SERVICE_FIELDTYPE_GRAPHIC_OBJECT_COUNT; break;
            case DS_OLE:  nSrvId = SW_SERVICE_FIELDTYPE_EMBEDDED_OBJECT_COUNT; break;
            }
        }
        break;
    }
    if( USHRT_MAX == nSrvId )
    {
        for( const ServiceIdResId* pMap = aServiceToRes;
                USHRT_MAX != pMap->nResId; ++pMap )
            if( nWhich == pMap->nResId )
            {
                nSrvId = pMap->nServiceId;
                break;
            }
    }
#ifdef DBG_UTIL
    if( USHRT_MAX == nSrvId )
        OSL_FAIL("resid not found");
#endif
    return nSrvId;
}

sal_uInt16 lcl_GetPropMapIdForFieldType( USHORT nWhich )
{
    sal_uInt16 nId;
    switch( nWhich )
    {
    case RES_USERFLD:	nId = PROPERTY_MAP_FLDMSTR_USER;			break;
    case RES_DBFLD:		nId = PROPERTY_MAP_FLDMSTR_DATABASE;		break;
    case RES_SETEXPFLD:	nId = PROPERTY_MAP_FLDMSTR_SET_EXP;			break;
    case RES_DDEFLD:	nId = PROPERTY_MAP_FLDMSTR_DDE;				break;
    case RES_AUTHORITY:	nId = PROPERTY_MAP_FLDMSTR_BIBLIOGRAPHY;	break;
    default:			nId = PROPERTY_MAP_FLDMSTR_DUMMY0;
    }
    return nId;
}


BYTE GetFieldTypeMId( const OUString& rProperty, const SwFieldType& rTyp )
{
    USHORT nId = lcl_GetPropMapIdForFieldType( rTyp.Which() );
    const SfxItemPropertyMap* pMap = aSwMapProvider.GetPropertyMap( nId );
    if( !pMap )
        nId = USHRT_MAX;
    else
    {
        nId = USHRT_MAX;    // in case of property not found
        for( ; pMap->pName; ++pMap )
            if( rProperty.equalsAsciiL( pMap->pName, pMap->nNameLen ) )
            {
                nId = pMap->nWID;
                break;
            }
    }
    return (BYTE)nId;
}

USHORT lcl_GetPropertyMapOfService( USHORT nServiceId )
{
    USHORT nRet;
    switch ( nServiceId)
    {
    case SW_SERVICE_FIELDTYPE_DATETIME: nRet = PROPERTY_MAP_FLDTYP_DATETIME; break;
    case SW_SERVICE_FIELDTYPE_USER: nRet = PROPERTY_MAP_FLDTYP_USER; break;
    case SW_SERVICE_FIELDTYPE_SET_EXP: nRet = PROPERTY_MAP_FLDTYP_SET_EXP; break;
    case SW_SERVICE_FIELDTYPE_GET_EXP: nRet = PROPERTY_MAP_FLDTYP_GET_EXP; break;
    case SW_SERVICE_FIELDTYPE_FILE_NAME: nRet = PROPERTY_MAP_FLDTYP_FILE_NAME; break;
    case SW_SERVICE_FIELDTYPE_PAGE_NUM: nRet = PROPERTY_MAP_FLDTYP_PAGE_NUM; break;
    case SW_SERVICE_FIELDTYPE_AUTHOR: nRet = PROPERTY_MAP_FLDTYP_AUTHOR; break;
    case SW_SERVICE_FIELDTYPE_CHAPTER: nRet = PROPERTY_MAP_FLDTYP_CHAPTER; break;
    case SW_SERVICE_FIELDTYPE_GET_REFERENCE: nRet = PROPERTY_MAP_FLDTYP_GET_REFERENCE; break;
    case SW_SERVICE_FIELDTYPE_CONDITIONED_TEXT: nRet = PROPERTY_MAP_FLDTYP_CONDITIONED_TEXT; break;
    case SW_SERVICE_FIELDTYPE_ANNOTATION: nRet = PROPERTY_MAP_FLDTYP_ANNOTATION; break;
    case SW_SERVICE_FIELDTYPE_INPUT_USER:
    case SW_SERVICE_FIELDTYPE_INPUT: nRet = PROPERTY_MAP_FLDTYP_INPUT; break;
    case SW_SERVICE_FIELDTYPE_MACRO: nRet = PROPERTY_MAP_FLDTYP_MACRO; break;
    case SW_SERVICE_FIELDTYPE_DDE: nRet = PROPERTY_MAP_FLDTYP_DDE; break;
    case SW_SERVICE_FIELDTYPE_HIDDEN_PARA: nRet = PROPERTY_MAP_FLDTYP_HIDDEN_PARA; break;
    case SW_SERVICE_FIELDTYPE_DOC_INFO: nRet = PROPERTY_MAP_FLDTYP_DOC_INFO; break;
    case SW_SERVICE_FIELDTYPE_TEMPLATE_NAME: nRet = PROPERTY_MAP_FLDTYP_TEMPLATE_NAME; break;
    case SW_SERVICE_FIELDTYPE_USER_EXT: nRet = PROPERTY_MAP_FLDTYP_USER_EXT; break;
    case SW_SERVICE_FIELDTYPE_REF_PAGE_SET: nRet = PROPERTY_MAP_FLDTYP_REF_PAGE_SET; break;
    case SW_SERVICE_FIELDTYPE_REF_PAGE_GET: nRet = PROPERTY_MAP_FLDTYP_REF_PAGE_GET; break;
    case SW_SERVICE_FIELDTYPE_JUMP_EDIT: nRet = PROPERTY_MAP_FLDTYP_JUMP_EDIT; break;
    case SW_SERVICE_FIELDTYPE_SCRIPT: nRet = PROPERTY_MAP_FLDTYP_SCRIPT; break;
    case SW_SERVICE_FIELDTYPE_DATABASE_NEXT_SET: nRet = PROPERTY_MAP_FLDTYP_DATABASE_NEXT_SET; break;
    case SW_SERVICE_FIELDTYPE_DATABASE_NUM_SET: nRet = PROPERTY_MAP_FLDTYP_DATABASE_NUM_SET; break;
    case SW_SERVICE_FIELDTYPE_DATABASE_SET_NUM: nRet = PROPERTY_MAP_FLDTYP_DATABASE_SET_NUM; break;
    case SW_SERVICE_FIELDTYPE_DATABASE: nRet = PROPERTY_MAP_FLDTYP_DATABASE; break;
    case SW_SERVICE_FIELDTYPE_DATABASE_NAME: nRet = PROPERTY_MAP_FLDTYP_DATABASE_NAME; break;
    case SW_SERVICE_FIELDTYPE_TABLE_FORMULA: nRet = PROPERTY_MAP_FLDTYP_TABLE_FORMULA; break;
    case SW_SERVICE_FIELDTYPE_PAGE_COUNT:
    case SW_SERVICE_FIELDTYPE_PARAGRAPH_COUNT:
    case SW_SERVICE_FIELDTYPE_WORD_COUNT:
    case SW_SERVICE_FIELDTYPE_CHARACTER_COUNT:
    case SW_SERVICE_FIELDTYPE_TABLE_COUNT:
    case SW_SERVICE_FIELDTYPE_GRAPHIC_OBJECT_COUNT:
    case SW_SERVICE_FIELDTYPE_EMBEDDED_OBJECT_COUNT: nRet = PROPERTY_MAP_FLDTYP_DOCSTAT; break;
    case SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_AUTHOR:
    case SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_AUTHOR:
    case SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_AUTHOR: nRet = PROPERTY_MAP_FLDTYP_DOCINFO_AUTHOR; break;
    case SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_DATE_TIME:
    case SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_DATE_TIME:
    case SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_DATE_TIME: nRet = PROPERTY_MAP_FLDTYP_DOCINFO_DATE_TIME; break;
    case SW_SERVICE_FIELDTYPE_DOCINFO_EDIT_TIME: nRet = PROPERTY_MAP_FLDTYP_DOCINFO_EDIT_TIME; break;
    case SW_SERVICE_FIELDTYPE_DOCINFO_DESCRIPTION:
    case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_0:
    case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_1:
    case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_2:
    case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_3:
    case SW_SERVICE_FIELDTYPE_DOCINFO_KEY_WORDS:
    case SW_SERVICE_FIELDTYPE_DOCINFO_SUBJECT:
    case SW_SERVICE_FIELDTYPE_DOCINFO_TITLE: nRet = PROPERTY_MAP_FLDTYP_DOCINFO_MISC; break;
    case SW_SERVICE_FIELDTYPE_DOCINFO_REVISION: nRet = PROPERTY_MAP_FLDTYP_DOCINFO_REVISION; break;
    case SW_SERVICE_FIELDTYPE_BIBLIOGRAPHY: nRet = PROPERTY_MAP_FLDTYP_BIBLIOGRAPHY; break;
    case SW_SERVICE_FIELDTYPE_DUMMY_0:
    case SW_SERVICE_FIELDTYPE_COMBINED_CHARACTERS: nRet = PROPERTY_MAP_FLDTYP_COMBINED_CHARACTERS; break;
    case SW_SERVICE_FIELDTYPE_DROPDOWN: nRet = PROPERTY_MAP_FLDTYP_DROPDOWN; break;
    case SW_SERVICE_FIELDTYPE_DUMMY_4:
    case SW_SERVICE_FIELDTYPE_DUMMY_5:
    case SW_SERVICE_FIELDTYPE_DUMMY_6:
    case SW_SERVICE_FIELDTYPE_DUMMY_7:
    case SW_SERVICE_FIELDTYPE_DUMMY_8: nRet = PROPERTY_MAP_FLDTYP_DUMMY_0; break;
    case SW_SERVICE_FIELDMASTER_USER: nRet = PROPERTY_MAP_FLDMSTR_USER; break;
    case SW_SERVICE_FIELDMASTER_DDE: nRet = PROPERTY_MAP_FLDMSTR_DDE; break;
    case SW_SERVICE_FIELDMASTER_SET_EXP: nRet = PROPERTY_MAP_FLDMSTR_SET_EXP; break;
    case SW_SERVICE_FIELDMASTER_DATABASE: nRet = PROPERTY_MAP_FLDMSTR_DATABASE; break;
    case SW_SERVICE_FIELDMASTER_BIBLIOGRAPHY: nRet = PROPERTY_MAP_FLDMSTR_BIBLIOGRAPHY; break;
    case SW_SERVICE_FIELDMASTER_DUMMY2:
    case SW_SERVICE_FIELDMASTER_DUMMY3:
    case SW_SERVICE_FIELDMASTER_DUMMY4:
    case SW_SERVICE_FIELDMASTER_DUMMY5: nRet = PROPERTY_MAP_FLDMSTR_DUMMY0; break;
    case SW_SERVICE_FIELDTYPE_HIDDEN_TEXT: nRet = PROPERTY_MAP_FLDTYP_HIDDEN_TEXT; break;
    default:
        OSL_FAIL( "wrong service id" );
        nRet = USHRT_MAX;
    }
    return nRet;
}

/******************************************************************
 * SwXFieldMaster
 ******************************************************************/
TYPEINIT1(SwXFieldMaster, SwClient);
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
const ::com::sun::star::uno::Sequence< sal_Int8 > & SwXFieldMaster::getUnoTunnelId()
{
    static uno::Sequence< sal_Int8 > aSeq = ::binfilter::CreateUnoTunnelId();
    return aSeq;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
sal_Int64 SAL_CALL SwXFieldMaster::getSomething( const uno::Sequence< sal_Int8 >& rId )
    throw(uno::RuntimeException)
{
    if( rId.getLength() == 16
        && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                        rId.getConstArray(), 16 ) )
    {
            return (sal_Int64)this;
    }
    return 0;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXFieldMaster::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXFieldMaster");
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwXFieldMaster::supportsService(const OUString& rServiceName) throw( RuntimeException )
{
    sal_Bool bRet = sal_False;
    if(rServiceName.equalsAsciiL(
            RTL_CONSTASCII_STRINGPARAM("com.sun.star.text.TextFieldMaster")))
        bRet = sal_True;
    else
    {
        const sal_Char* pEntry;
        switch( nResTypeId )
        {
        case RES_USERFLD:	pEntry = "User"; 			break;
        case RES_DBFLD:		pEntry = "Database"; 		break;
        case RES_SETEXPFLD:	pEntry = "SetExpression";	break;
        case RES_DDEFLD:	pEntry = "DDE";				break;
        case RES_AUTHORITY:	pEntry = "Bibliography"; 	break;
        default: pEntry = 0;
        }
        if( pEntry )
        {
            ByteString aTmp( RTL_CONSTASCII_STRINGPARAM(
                            "com.sun.star.text.fieldmaster."));
            aTmp.Append( pEntry );
            bRet = rServiceName.equalsAsciiL(aTmp.GetBuffer(), aTmp.Len());
        }
    }
    return bRet;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
Sequence< OUString > SwXFieldMaster::getSupportedServiceNames(void) throw( RuntimeException )
{
    Sequence< OUString > aRet(2);
    OUString* pArray = aRet.getArray();
    pArray[0] = C2U("com.sun.star.text.TextFieldMaster");

    const sal_Char* pEntry1;
    switch( nResTypeId )
    {
    case RES_USERFLD: 	pEntry1 = "User"; 			break;
    case RES_DBFLD:	  	pEntry1 = "Database";		break;
    case RES_SETEXPFLD:	pEntry1 = "SetExpression";	break;
    case RES_DDEFLD:	pEntry1 = "DDE"; 			break;
    case RES_AUTHORITY:	pEntry1 = "Bibliography";	break;
    default: pEntry1 = 0;
    }
    if( pEntry1 )
    {
        String s;
        s.AppendAscii( "com.sun.star.text.fieldmaster." ).AppendAscii( pEntry1 );
        pArray[1] = s;
    }
    return aRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXFieldMaster::SwXFieldMaster(SwDoc* pDoc, sal_uInt16 nResId) :
    aLstnrCntnr( (XPropertySet*)this),
    nResTypeId(nResId),
    m_pDoc(pDoc),
    m_bIsDescriptor(sal_True),
    fParam1(0.),
    nParam1(-1),
    bParam1(FALSE),
    nParam2(0)
{
    pDoc->GetPageDescFromPool(RES_POOLPAGE_STANDARD)->Add(this);
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXFieldMaster::SwXFieldMaster(SwFieldType& rType, SwDoc* pDoc) :
    SwClient(&rType),
    aLstnrCntnr( (XPropertySet*)this),
    nResTypeId(rType.Which()),
    m_pDoc(pDoc),
    m_bIsDescriptor(sal_False),
    fParam1(0.),
    nParam1(-1),
    bParam1(FALSE)
{

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXFieldMaster::~SwXFieldMaster()
{

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XPropertySetInfo >  SwXFieldMaster::getPropertySetInfo(void)
                                            throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    uno::Reference< XPropertySetInfo >  aRef = new SfxItemPropertySetInfo(
                        aSwMapProvider.GetPropertyMap(
                                lcl_GetPropMapIdForFieldType( nResTypeId ) ));
    return aRef;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::setPropertyValue( const OUString& rPropertyName,
                                    const uno::Any& rValue)
    throw( UnknownPropertyException, PropertyVetoException,
            IllegalArgumentException, WrappedTargetException, uno::RuntimeException)
{
    SolarMutexGuard aGuard;
    SwFieldType* pType = GetFldType(sal_True);
    if(pType)
    {
        sal_Bool bSetValue = sal_True;
        if( rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_SUB_TYPE)))
        {
            const SvStringsDtor& rExtraArr = SwStyleNameMapper::GetExtraUINameArray();
            String sTypeName = pType->GetName();
            static sal_uInt16 nIds[] =
            {
                RES_POOLCOLL_LABEL_DRAWING - RES_POOLCOLL_EXTRA_BEGIN,
                RES_POOLCOLL_LABEL_ABB - RES_POOLCOLL_EXTRA_BEGIN,
                RES_POOLCOLL_LABEL_TABLE - RES_POOLCOLL_EXTRA_BEGIN,
                RES_POOLCOLL_LABEL_FRAME- RES_POOLCOLL_EXTRA_BEGIN,
                0
            };
            for(const sal_uInt16 * pIds = nIds; *pIds; ++pIds)
            {
                if(sTypeName ==	*rExtraArr[ *pIds ] )
                {
                    bSetValue = sal_False;
                    break;
                }
            }
        }
        if( bSetValue )
        {
            BYTE nMId = GetFieldTypeMId( rPropertyName, *pType  );
            if( UCHAR_MAX != nMId )
                pType->PutValue( rValue, nMId );
            else
                throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );
        }
    }
    else if(!pType && m_pDoc &&
        ( rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_NAME))) )
    {
        OUString uTmp;
        rValue >>= uTmp;
        String sTypeName(uTmp);
        SwFieldType* pLclType = m_pDoc->GetFldType(nResTypeId, sTypeName);

        String sTable(SW_RES(STR_POOLCOLL_LABEL_TABLE));
        String sDrawing(SW_RES(STR_POOLCOLL_LABEL_DRAWING));
        String sFrame(SW_RES(STR_POOLCOLL_LABEL_FRAME));
        String sIllustration(SW_RES(STR_POOLCOLL_LABEL_ABB));

        if(pLclType ||
            (RES_SETEXPFLD == nResTypeId &&
            ( sTypeName == sTable || sTypeName == sDrawing ||
              sTypeName == sFrame || sTypeName == sIllustration )))
        {
            throw IllegalArgumentException();
        }
        else
        {
            switch(nResTypeId)
            {
                case RES_USERFLD :
                {
                    SwUserFieldType aType(m_pDoc, sTypeName);
                    pLclType = m_pDoc->InsertFldType(aType);
                    ((SwUserFieldType*)pLclType)->SetContent(sParam1);
                    ((SwUserFieldType*)pLclType)->SetValue(fParam1);
                    ((SwUserFieldType*)pLclType)->SetType(bParam1 ? GSE_EXPR : GSE_STRING);
                }
                break;
                case RES_DDEFLD :
                {
                    SwDDEFieldType aType(sTypeName, sParam1,
                        bParam1 ? ::binfilter::LINKUPDATE_ALWAYS : ::binfilter::LINKUPDATE_ONCALL);
                    pLclType = m_pDoc->InsertFldType(aType);
                }
                break;
                case RES_SETEXPFLD :
                {
                    SwSetExpFieldType aType(m_pDoc, sTypeName);
                    if(sParam1.Len())
                        aType.SetDelimiter( sParam1.GetChar(0));
                    if(nParam1 > -1 && nParam1 < MAXLEVEL)
                        aType.SetOutlineLvl(nParam1);
                    pLclType = m_pDoc->InsertFldType(aType);
                }
                break;
            }
            if(pLclType)
            {
                pLclType->Add(this);
                m_bIsDescriptor = sal_False;
            }
            else
                throw uno::RuntimeException();
        }

        DBG_ASSERT(pLclType, "kein FieldType gefunden!" );
    }
    else
    {
        switch( nResTypeId )
        {
        case RES_USERFLD:
            if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_CONTENT)))
                ::binfilter::GetString( rValue, sParam1 );
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_VALUE )))
            {
                if(rValue.getValueType() != ::getCppuType((const double*)0))
                    throw IllegalArgumentException();
                fParam1 = *(double*)rValue.getValue();
            }
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_IS_EXPRESSION )))
            {
                if(rValue.getValueType() != ::getBooleanCppuType())
                    throw IllegalArgumentException();
                bParam1 = *(sal_Bool*)rValue.getValue();
            }
            break;
        case RES_DBFLD:
            if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_BASE_NAME)))
                ::binfilter::GetString( rValue, sParam1 );
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_TABLE_NAME)))
                ::binfilter::GetString( rValue, sParam2 );
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COLUMN_NAME)))
                ::binfilter::GetString( rValue, sParam3 );
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COMMAND_TYPE)))
                rValue >>= nParam2;

            if(sParam1.Len() && sParam2.Len() && sParam3.Len())
                GetFldType();
            break;
        case  RES_SETEXPFLD:
            if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_NUMBERING_SEPARATOR)))
                ::binfilter::GetString( rValue, sParam1 );
            else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_CHAPTER_NUMBERING_LEVEL)))
                rValue >>= nParam1;
            break;
        case RES_DDEFLD:
            {
                USHORT nPart = rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_TYPE))  ? 0 :
                        rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_FILE))  ? 1 :
                        rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_ELEMENT))  ? 2 :
                        rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_IS_AUTOMATIC_UPDATE)) ? 3 : USHRT_MAX;
                if(nPart  < 3 )
                {
                    String sTmp;
                    if(!sParam1.Len())
                        (sParam1 = ::binfilter::cTokenSeperator)
                                += ::binfilter::cTokenSeperator;

                    sParam1.SetToken( nPart, ::binfilter::cTokenSeperator,
                                ::binfilter::GetString( rValue, sTmp ));
                }
                else if(3 == nPart)
                    bParam1 = *(sal_Bool*)rValue.getValue();
            }
            break;
        default:
            throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );
        }
    }
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
SwFieldType* SwXFieldMaster::GetFldType(sal_Bool bDontCreate) const
{
    if(!bDontCreate && RES_DBFLD == nResTypeId && m_bIsDescriptor && m_pDoc)
    {
        SwDBData aData;
        aData.sDataSource = sParam1;
        aData.sCommand = sParam2;
        aData.nCommandType = nParam2;
        SwDBFieldType aType(m_pDoc, sParam3,  aData);
        SwFieldType* pType = m_pDoc->InsertFldType(aType);
        SwXFieldMaster* pThis = ((SwXFieldMaster*)this);
        pType->Add(pThis);
        pThis->m_bIsDescriptor = sal_False;
    }
    if(m_bIsDescriptor)
        return 0;
    else
        return (SwFieldType*)GetRegisteredIn();
}

/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
typedef SwFmtFld* SwFmtFldPtr;
SV_DECL_PTRARR(SwDependentFields, SwFmtFldPtr, 5, 5)
SV_IMPL_PTRARR(SwDependentFields, SwFmtFldPtr)

uno::Any SwXFieldMaster::getPropertyValue(const OUString& rPropertyName)
        throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    uno::Any aRet;
    SwFieldType* pType = GetFldType(sal_True);
    if( rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_INSTANCE_NAME)) )
    {
        String sName;
        if(pType)
            SwXTextFieldMasters::getInstanceName(*pType, sName);
        aRet <<= OUString(sName);
    }
    else if(pType)
    {
        if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_NAME) ))
        {
            aRet <<= SwXFieldMaster::GetProgrammaticName(*pType, *GetDoc());
        }
        else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DEPENDENT_TEXT_FIELDS)) )
        {
            //fill all text fields into a sequence
            SwClientIter aIter( *pType );
            SwDependentFields aFldArr;
            SwFmtFldPtr pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
            while(pFld)
            {
                if(pFld->IsFldInDoc())
                    aFldArr.Insert(pFld, aFldArr.Count());
                pFld = (SwFmtFld*)aIter.Next();
            }
            Sequence<Reference <XDependentTextField> > aRetSeq(aFldArr.Count());
            Reference<XDependentTextField>* pRetSeq = aRetSeq.getArray();
            SwXTextField* pInsert = 0;
            for(int i = 0; i < aFldArr.Count(); i++)
            {
                pFld = aFldArr.GetObject(i);
                SwXTextField* pTemp = (SwXTextField*)aIter.First(TYPE(SwXTextField));
                while(pTemp)
                {
                    if(pTemp->GetFldFmt() == pFld)
                    {
                        pInsert = pTemp;
                        break;
                    }
                    pTemp = (SwXTextField*)aIter.Next();
                }
                if(!pInsert)
                    pInsert = new SwXTextField( *pFld, GetDoc());
                pRetSeq[i] = Reference<XDependentTextField>(pInsert);
                pInsert = 0;
            }
            aRet <<= aRetSeq;
        }
        else if(pType)
        {
            //TODO: Properties fuer die uebrigen Feldtypen einbauen
            BYTE nMId = GetFieldTypeMId( rPropertyName, *pType );
            if( UCHAR_MAX != nMId )
                pType->QueryValue( aRet, nMId );
            else
                throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );
        }
        else
        {
            if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COMMAND_TYPE)) )
                aRet <<= nParam2;
        }
    }
    else
    {
        if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COMMAND_TYPE)) )
            aRet <<= nParam2;
        else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DEPENDENT_TEXT_FIELDS)) )
        {
            Sequence<Reference <XDependentTextField> > aRetSeq(0);
            aRet <<= aRetSeq;
        }
        else
        {
            const String* pStr = 0;
            String sStr;
            switch ( nResTypeId )
            {
            case RES_USERFLD:
                if( rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_CONTENT)) )
                    pStr = &sParam1;
                else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_VALUE )))
                    aRet <<= fParam1;
                else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_IS_EXPRESSION )))
                    aRet.setValue(&bParam1, ::getBooleanCppuType());
                break;
            case RES_DBFLD:
                if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_BASE_NAME)))
                    pStr = &sParam1;
                else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_TABLE_NAME)))
                    pStr = &sParam2;
                else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COLUMN_NAME)))
                    pStr = &sParam3;
                break;
            case RES_SETEXPFLD:
                if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_NUMBERING_SEPARATOR)))
                    pStr = &sParam1;
                else if(rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_CHAPTER_NUMBERING_LEVEL)))
                    aRet <<= nParam1;
                break;
            case RES_DDEFLD:
                {
                    USHORT nPart = rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_TYPE))  ? 0 :
                        rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_FILE)) ? 1 :
                            rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DDE_COMMAND_ELEMENT))  ? 2 :
                            rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_IS_AUTOMATIC_UPDATE)) ? 3 : USHRT_MAX;
                    if(nPart  < 3 )
                        pStr = &(sStr = sParam1.GetToken(nPart, ::binfilter::cTokenSeperator));
                    else if(3 == nPart)
                        aRet.setValue(&bParam1, ::getBooleanCppuType());
                }
                break;
            default:
                throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );
            }

            if( pStr )
                aRet <<= OUString( *pStr );
        }
    }
    return aRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::addPropertyChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XPropertyChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::removePropertyChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XPropertyChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::addVetoableChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XVetoableChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::removeVetoableChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XVetoableChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}

/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::dispose(void) 			throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    SwFieldType* pFldType = GetFldType(sal_True);
    if(pFldType)
    {
        sal_uInt16 nTypeIdx = USHRT_MAX;
        const SwFldTypes* pTypes = GetDoc()->GetFldTypes();
        for( sal_uInt16 i = 0; i < pTypes->Count(); i++ )
        {
            if((*pTypes)[i] == pFldType)
                nTypeIdx = i;
        }

        // zuerst alle Felder loeschen
        SwClientIter aIter( *pFldType );
        SwFmtFld* pFld = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
        while(pFld)
        {
            // Feld im Undo?
            SwTxtFld *pTxtFld = pFld->GetTxtFld();
            if(pTxtFld && pTxtFld->GetTxtNode().GetNodes().IsDocNodes() )
            {
                SwTxtNode& rTxtNode = (SwTxtNode&)*pTxtFld->GetpTxtNode();
                SwPaM aPam(rTxtNode, *pTxtFld->GetStart());
                aPam.SetMark();
                aPam.Move();
                GetDoc()->DeleteAndJoin(aPam);
            }
            pFld = (SwFmtFld*)aIter.Next();
        }
        // dann den FieldType loeschen
        GetDoc()->RemoveFldType(nTypeIdx);
    }
    else
        throw uno::RuntimeException();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::addEventListener(const uno::Reference< XEventListener > & aListener)
                                            throw( uno::RuntimeException )
{
    if(!GetRegisteredIn())
        throw uno::RuntimeException();
    aLstnrCntnr.AddListener(aListener);
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::removeEventListener(const uno::Reference< XEventListener > & aListener)
                                                    throw( uno::RuntimeException )
{
    if(!GetRegisteredIn() || !aLstnrCntnr.RemoveListener(aListener))
        throw uno::RuntimeException();
}

/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXFieldMaster::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew)
{
    ClientModify(this, pOld, pNew);
    if(!GetRegisteredIn())
    {
        aLstnrCntnr.Disposing();
        m_pDoc = 0;
    }
}
/* ---------------------------------------------------------------------------

const Programmatic2UIName_Impl* lcl_GetFieldNameTable()
{
    static BOOL bInitialized = FALSE;
    static Programmatic2UIName_Impl aFieldNames[5];
    if(!bInitialized)
    {
        bInitialized = TRUE;
        int nName = 0;
        aFieldNames[nName].sUIName = String				(SW_RES(STR_POOLCOLL_LABEL_ABB ));
        aFieldNames[nName++].sProgrammaticName = String	(SW_RES(STR_POCO_PRGM_LABEL_ABB));
        aFieldNames[nName].sUIName = String				(SW_RES(STR_POOLCOLL_LABEL_TABLE ));
        aFieldNames[nName++].sProgrammaticName = String	(SW_RES(STR_POCO_PRGM_LABEL_TABLE));
        aFieldNames[nName].sUIName = String				(SW_RES(STR_POOLCOLL_LABEL_FRAME));
        aFieldNames[nName++].sProgrammaticName = String	(SW_RES(STR_POCO_PRGM_LABEL_FRAME));
        aFieldNames[nName].sUIName = String				(SW_RES(STR_POOLCOLL_LABEL_DRAWING ));
        aFieldNames[nName++].sProgrammaticName = String	(SW_RES(STR_POCO_PRGM_LABEL_DRAWING));
    }
    return &aFieldNames[0];
}
 ---------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXFieldMaster::GetProgrammaticName(const SwFieldType& rType, SwDoc& rDoc)
{
    OUString sRet(rType.GetName());
    if(RES_SETEXPFLD == rType.Which())
    {
        const SwFldTypes* pTypes = rDoc.GetFldTypes();
        for( sal_uInt16 i = 0; i <= INIT_FLDTYPES; i++ )
        {
            if((*pTypes)[i] == &rType)
            {
                sRet = SwStyleNameMapper::GetProgName ( sRet, GET_POOLID_TXTCOLL );
                break;
            }
        }
    }
    return sRet;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXFieldMaster::LocalizeFormula(
    const SwSetExpField& rFld,
    const OUString& rFormula,
    sal_Bool bQuery)
{
    const OUString sTypeName(rFld.GetTyp()->GetName());
    OUString sProgName = SwStyleNameMapper::GetProgName(sTypeName, GET_POOLID_TXTCOLL );
    if(sProgName != sTypeName)
    {
        OUString sSource = bQuery ? sTypeName : sProgName;
        OUString sDest = bQuery ? sProgName : sTypeName;
        if(!rFormula.compareTo(sSource, sSource.getLength()))
        {
            OUString sTmpFormula = sDest;
            sTmpFormula += rFormula.copy(sSource.getLength());
            return sTmpFormula;
        }
    }
    return rFormula;
}
/******************************************************************
 *
 ******************************************************************/
struct SwFieldProperties_Impl
{
    String 		sPar1;
    String 		sPar2;
    String 		sPar3;
    String 		sPar4;
    Date 			aDate;
    double 			fDouble;
    Sequence<PropertyValue>	aPropSeq;
    Sequence<OUString> aStrings;
    util::DateTime*	pDateTime;

    sal_Int32 		nSubType;
    sal_Int32 		nFormat;
    sal_uInt16 		nUSHORT1;
    sal_uInt16 		nUSHORT2;
    sal_Int16 		nSHORT1;
    sal_Int8 		nByte1;
    sal_Bool        bFormatIsDefault;
    sal_Bool 		bBool1;
    sal_Bool 		bBool2;
    sal_Bool 		bBool3;
    sal_Bool        bBool4;

    SwFieldProperties_Impl():
        fDouble(0.),
        pDateTime(0),
        nSubType(0),
        nFormat(0),
        nUSHORT1(0),
        nUSHORT2(0),
        nSHORT1(0),
        nByte1(0),
        bFormatIsDefault(sal_True),
        bBool1(sal_False),
        bBool2(sal_False),
        bBool3(sal_False),
        bBool4(sal_True) //Automatic language
        {}
    ~SwFieldProperties_Impl()
        {delete pDateTime;}

};

TYPEINIT1(SwXTextField, SwClient);
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
const ::com::sun::star::uno::Sequence< sal_Int8 > & SwXTextField::getUnoTunnelId()
{
    static uno::Sequence< sal_Int8 > aSeq = ::binfilter::CreateUnoTunnelId();
    return aSeq;
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
sal_Int64 SAL_CALL SwXTextField::getSomething( const uno::Sequence< sal_Int8 >& rId )
    throw(uno::RuntimeException)
{
    if( rId.getLength() == 16
        && 0 == rtl_compareMemory( getUnoTunnelId().getConstArray(),
                                        rId.getConstArray(), 16 ) )
    {
            return (sal_Int64)this;
    }
    return 0;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/

SwXTextField::SwXTextField(sal_uInt16 nServiceId) :
    aLstnrCntnr( (XTextContent*)this),
    pFmtFld(0),
    m_pDoc(0),
    m_bIsDescriptor(nServiceId != USHRT_MAX),
    m_bCallUpdate(sal_False),
    m_nServiceId(nServiceId),
    m_pProps(new SwFieldProperties_Impl)
{
    //Set visible as default!
    if(SW_SERVICE_FIELDTYPE_SET_EXP == nServiceId ||
            SW_SERVICE_FIELDTYPE_DATABASE_SET_NUM == nServiceId ||
            SW_SERVICE_FIELDTYPE_DATABASE == nServiceId ||
            SW_SERVICE_FIELDTYPE_DATABASE_NAME == nServiceId  )
        m_pProps->bBool2 = sal_True;
    else if(SW_SERVICE_FIELDTYPE_TABLE_FORMULA == nServiceId)
        m_pProps->bBool1 = sal_True;

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextField::SwXTextField(const SwFmtFld& rFmt, SwDoc* pDc) :
    aLstnrCntnr( (XTextContent*)this),
    pFmtFld(&rFmt),
    m_pDoc(pDc),
    m_bIsDescriptor(sal_False),
    m_bCallUpdate(sal_False),
    m_nServiceId( lcl_GetServiceForField( *pFmtFld->GetFld() ) ),
    m_pProps(0)
{
    pDc->GetUnoCallBack()->Add(this);
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextField::~SwXTextField()
{
    delete m_pProps;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::attachTextFieldMaster(const uno::Reference< XPropertySet > & xFieldMaster)
                    throw( IllegalArgumentException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!m_bIsDescriptor)
        throw uno::RuntimeException();
    uno::Reference< XUnoTunnel > xMasterTunnel(xFieldMaster, uno::UNO_QUERY);
    if (!xMasterTunnel.is())
        throw IllegalArgumentException();
    SwXFieldMaster* pMaster = (SwXFieldMaster*)xMasterTunnel->getSomething(
                SwXFieldMaster::getUnoTunnelId());

    SwFieldType* pFieldType = pMaster ? pMaster->GetFldType() : 0;
    if(pFieldType && pFieldType->Which() == lcl_ServiceIdToResId(m_nServiceId))
    {
        m_sTypeName = pFieldType->GetName();
    }
    else
        throw IllegalArgumentException();

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XPropertySet >  SwXTextField::getTextFieldMaster(void) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!GetRegisteredIn())
        throw uno::RuntimeException();
    SwFieldType* pType = pFmtFld->GetFld()->GetTyp();
    SwXFieldMaster* pMaster = (SwXFieldMaster*)
                SwClientIter(*pType).First(TYPE(SwXFieldMaster));
    if(!pMaster)
        pMaster = new SwXFieldMaster(*pType, GetDoc());

    return pMaster;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
OUString SwXTextField::getPresentation(sal_Bool bShowCommand) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    OUString sRet;
    const SwField* pField = GetField();
    if(pField)
        sRet = pField->GetCntnt(bShowCommand);
    else
        throw uno::RuntimeException();
    return sRet;
}

void SwXTextField::attachToRange(
        const uno::Reference< XTextRange > & xTextRange)
    throw( IllegalArgumentException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!m_bIsDescriptor)
        throw uno::RuntimeException();
    uno::Reference<XUnoTunnel> xRangeTunnel( xTextRange, uno::UNO_QUERY);
    SwXTextRange* pRange = 0;
    OTextCursorHelper* pCursor = 0;
    if(xRangeTunnel.is())
    {
        pRange = (SwXTextRange*)xRangeTunnel->getSomething(
                                SwXTextRange::getUnoTunnelId());
        pCursor = (OTextCursorHelper*)xRangeTunnel->getSomething(
                                OTextCursorHelper::getUnoTunnelId());
    }

    SwDoc* pDoc = pRange ? (SwDoc*)pRange->GetDoc() : pCursor ? (SwDoc*)pCursor->GetDoc() : 0;
    //wurde ein FieldMaster attached, dann ist das Dokument schon festgelegt!
    if(pDoc && (!m_pDoc || m_pDoc == pDoc))
    {
        SwUnoInternalPaM aPam(*pDoc);
        //das muss jetzt sal_True liefern
        SwXTextRange::XTextRangeToSwPaM(aPam, xTextRange);
        SwField* pFld = 0;
        switch(m_nServiceId)
        {
            case SW_SERVICE_FIELDTYPE_ANNOTATION:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_POSTITFLD);
                pFld = new SwPostItField((SwPostItFieldType*)pFldType,
                        m_pProps->sPar1, m_pProps->sPar2,
                        m_pProps->aDate);
            }
            break;
            case SW_SERVICE_FIELDTYPE_SCRIPT:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_SCRIPTFLD);
                pFld = new SwScriptField((SwScriptFieldType*)pFldType,
                        m_pProps->sPar1, m_pProps->sPar2,
                        m_pProps->bBool1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATETIME:
            {
                sal_uInt16 nSub = 0;
                if(m_pProps->bBool1)
                    nSub |= FIXEDFLD;
                if(m_pProps->bBool2)
                    nSub |= DATEFLD;
                else
                    nSub |= TIMEFLD;
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_DATETIMEFLD);
                pFld = new SwDateTimeField((SwDateTimeFieldType*)pFldType,
                nSub, m_pProps->nFormat);
                if(m_pProps->fDouble > 0.)
                    ((SwDateTimeField*)pFld)->SetValue( m_pProps->fDouble );
                if(m_pProps->pDateTime)
                {
                    Any aVal; aVal <<= *m_pProps->pDateTime;
                    pFld->PutValue( aVal, FIELD_PROP_DATE_TIME );
                }
                ((SwDateTimeField*)pFld)->SetOffset(m_pProps->nSubType);
            }
            break;
            case SW_SERVICE_FIELDTYPE_FILE_NAME:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_FILENAMEFLD);
                sal_Int32 nFormat = m_pProps->nFormat;
                if(m_pProps->bBool2)
                    nFormat |= FF_FIXED;
                pFld = new SwFileNameField((SwFileNameFieldType*)pFldType, nFormat);
                if(m_pProps->sPar3.Len())
                    ((SwFileNameField*)pFld)->SetExpansion(m_pProps->sPar3);
                Any aFormat(&m_pProps->nFormat, ::getCppuType(&m_pProps->nFormat));
                pFld->PutValue( aFormat, FIELD_PROP_FORMAT );
            }
            break;
            case SW_SERVICE_FIELDTYPE_TEMPLATE_NAME:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_TEMPLNAMEFLD);
                pFld = new SwTemplNameField((SwTemplNameFieldType*)pFldType,
                                                    m_pProps->nFormat);
                Any aFormat(&m_pProps->nFormat, ::getCppuType(&m_pProps->nFormat));
                pFld->PutValue(aFormat, FIELD_PROP_FORMAT);
            }
            break;
            case SW_SERVICE_FIELDTYPE_CHAPTER:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_CHAPTERFLD);
                pFld = new SwChapterField((SwChapterFieldType*)pFldType, m_pProps->nUSHORT1);
                ((SwChapterField*)pFld)->SetLevel(m_pProps->nByte1);
                Any aVal; aVal <<= (sal_Int16)m_pProps->nUSHORT1;
                pFld->PutValue(aVal, FIELD_PROP_USHORT1 );
            }
            break;
            case SW_SERVICE_FIELDTYPE_AUTHOR:
            {
                long nFormat = m_pProps->bBool1 ? AF_NAME : AF_SHORTCUT;
                if(m_pProps->bBool2)
                    nFormat |= AF_FIXED;

                SwFieldType* pFldType = pDoc->GetSysFldType(RES_AUTHORFLD);
                pFld = new SwAuthorField((SwAuthorFieldType*)pFldType, nFormat);
                ((SwAuthorField*)pFld)->SetExpansion(m_pProps->sPar1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_CONDITIONED_TEXT:
            case SW_SERVICE_FIELDTYPE_HIDDEN_TEXT:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_HIDDENTXTFLD);
                pFld = new SwHiddenTxtField(((SwHiddenTxtFieldType*)pFldType),
                        m_pProps->sPar1,
                        m_pProps->sPar2, m_pProps->sPar3,
                        SW_SERVICE_FIELDTYPE_HIDDEN_TEXT == m_nServiceId ?
                             TYP_HIDDENTXTFLD :
                                TYP_CONDTXTFLD);
                ((SwHiddenTxtField*)pFld)->SetValue(m_pProps->bBool1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_HIDDEN_PARA:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_HIDDENPARAFLD);
                pFld = new SwHiddenParaField((SwHiddenParaFieldType*)pFldType,
                                                m_pProps->sPar1);
                ((SwHiddenParaField*)pFld)->SetHidden(m_pProps->bBool1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_GET_REFERENCE:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_GETREFFLD);
                pFld = new SwGetRefField((SwGetRefFieldType*)pFldType,
                            m_pProps->sPar1,
                            0,
                            0,
                            0);
                if(m_pProps->sPar3.Len())
                    ((SwGetRefField*)pFld)->SetExpand(m_pProps->sPar3);
                Any aVal; aVal <<=(sal_Int16)m_pProps->nUSHORT1;
                pFld->PutValue(aVal, FIELD_PROP_USHORT1 );
                aVal <<=(sal_Int16)m_pProps->nUSHORT2;
                pFld->PutValue(aVal, FIELD_PROP_USHORT2 );
                aVal <<=(sal_Int16)m_pProps->nSHORT1;
                pFld->PutValue(aVal, FIELD_PROP_SHORT1 );
            }
            break;
            case SW_SERVICE_FIELDTYPE_JUMP_EDIT:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_JUMPEDITFLD);
                pFld = new SwJumpEditField((SwJumpEditFieldType*)pFldType,
                        m_pProps->nUSHORT1, m_pProps->sPar2, m_pProps->sPar1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_AUTHOR		:
            case SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_DATE_TIME  :
            case SW_SERVICE_FIELDTYPE_DOCINFO_EDIT_TIME         :
            case SW_SERVICE_FIELDTYPE_DOCINFO_DESCRIPTION       :
            case SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_AUTHOR     :
            case SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_DATE_TIME  :
            case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_0            :
            case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_1            :
            case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_2            :
            case SW_SERVICE_FIELDTYPE_DOCINFO_INFO_3            :
            case SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_AUTHOR      :
            case SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_DATE_TIME   :
            case SW_SERVICE_FIELDTYPE_DOCINFO_KEY_WORDS         :
            case SW_SERVICE_FIELDTYPE_DOCINFO_SUBJECT           :
            case SW_SERVICE_FIELDTYPE_DOCINFO_TITLE             :
            case SW_SERVICE_FIELDTYPE_DOCINFO_REVISION          :
            case SW_SERVICE_FIELDTYPE_DOC_INFO:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_DOCINFOFLD);
                sal_uInt16 nSubType = aDocInfoSubTypeFromService[
                        m_nServiceId - SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_AUTHOR];
                if( SW_SERVICE_FIELDTYPE_DOCINFO_CHANGE_DATE_TIME == m_nServiceId ||
                    SW_SERVICE_FIELDTYPE_DOCINFO_CREATE_DATE_TIME == m_nServiceId ||
                    SW_SERVICE_FIELDTYPE_DOCINFO_PRINT_DATE_TIME == m_nServiceId ||
                    SW_SERVICE_FIELDTYPE_DOCINFO_EDIT_TIME == m_nServiceId )
                {
                    if(m_pProps->bBool2) //IsDate
                    {
                        nSubType &= 0xf0ff;
                        nSubType |= DI_SUB_DATE;
                    }
                    else
                    {
                        nSubType &= 0xf0ff;
                        nSubType |= DI_SUB_TIME;
                    }
                }
                if(m_pProps->bBool1)
                    nSubType |= DI_SUB_FIXED;
                pFld = new SwDocInfoField((SwDocInfoFieldType*)pFldType, nSubType, m_pProps->nFormat);
                if(m_pProps->sPar3.Len())
                    ((SwDocInfoField*)pFld)->SetExpansion(m_pProps->sPar3);
            }
            break;
            case SW_SERVICE_FIELDTYPE_USER_EXT:
            {
                sal_Int32 nFormat = 0;
                if(m_pProps->bBool1)
                    nFormat = AF_FIXED;

                SwFieldType* pFldType = pDoc->GetSysFldType(RES_EXTUSERFLD);
                pFld = new SwExtUserField((SwExtUserFieldType*)pFldType, m_pProps->nUSHORT1, nFormat);
                ((SwExtUserField*)pFld)->SetExpansion(m_pProps->sPar1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_USER:
            {
                SwFieldType* pFldType = pDoc->GetFldType(RES_USERFLD, m_sTypeName);
                if(!pFldType)
                    throw uno::RuntimeException();
                USHORT nUserSubType = m_pProps->bBool1 ? SUB_INVISIBLE : 0;
                if(m_pProps->bBool2)
                    nUserSubType |= SUB_CMD;
                if(m_pProps->bFormatIsDefault &&
                    GSE_STRING == ((SwUserFieldType*)pFldType)->GetType())
                        m_pProps->nFormat = -1;
                pFld = new SwUserField((SwUserFieldType*)pFldType,
                                    nUserSubType,
                                    m_pProps->nFormat);
            }
            break;
            case SW_SERVICE_FIELDTYPE_REF_PAGE_SET:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_REFPAGESETFLD);
                pFld = new SwRefPageSetField( (SwRefPageSetFieldType*)pFldType,
                                    m_pProps->nUSHORT1,
                                    m_pProps->bBool1 );
            }
            break;
            case SW_SERVICE_FIELDTYPE_REF_PAGE_GET:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_REFPAGEGETFLD);
                pFld = new SwRefPageGetField( (SwRefPageGetFieldType*)pFldType,
                                                m_pProps->nUSHORT1 );
                ((SwRefPageGetField*)pFld)->SetText(m_pProps->sPar1);
            }
            break;
            case SW_SERVICE_FIELDTYPE_PAGE_NUM:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_PAGENUMBERFLD);
                pFld = new SwPageNumberField((SwPageNumberFieldType*)pFldType,
                                                PG_RANDOM,
                                                m_pProps->nFormat,
                                                m_pProps->nUSHORT1);
                ((SwPageNumberField*)pFld)->SetUserString(m_pProps->sPar1);
                Any aVal; aVal <<= m_pProps->nSubType;
                pFld->PutValue( aVal, FIELD_PROP_SUBTYPE );
            }
            break;
            case SW_SERVICE_FIELDTYPE_DDE:
            {
                SwFieldType* pFldType = pDoc->GetFldType(RES_DDEFLD, m_sTypeName);
                if(!pFldType)
                    throw uno::RuntimeException();
                pFld = new SwDDEField( (SwDDEFieldType*)pFldType );
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATABASE_NAME:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_DBNAMEFLD);
                SwDBData aData;
                aData.sDataSource = m_pProps->sPar1;
                aData.sCommand = m_pProps->sPar2;
                aData.nCommandType = m_pProps->nSHORT1;
                pFld = new SwDBNameField((SwDBNameFieldType*)pFldType, aData);
                sal_uInt16  nSubType = pFld->GetSubType();
                if(m_pProps->bBool2)
                    nSubType &= ~SUB_INVISIBLE;
                else
                    nSubType |= SUB_INVISIBLE;
                pFld->SetSubType(nSubType);
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATABASE_NEXT_SET:
            {
                SwDBData aData;
                aData.sDataSource = m_pProps->sPar1;
                aData.sCommand = m_pProps->sPar2;
                aData.nCommandType = m_pProps->nSHORT1;
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_DBNEXTSETFLD);
                pFld = new SwDBNextSetField((SwDBNextSetFieldType*)pFldType,
                        m_pProps->sPar3, aEmptyStr,
                        aData);
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATABASE_NUM_SET:
            {
                SwDBData aData;
                aData.sDataSource = m_pProps->sPar1;
                aData.sCommand = m_pProps->sPar2;
                aData.nCommandType = m_pProps->nSHORT1;
                pFld = new SwDBNumSetField( (SwDBNumSetFieldType*)
                    pDoc->GetSysFldType(RES_DBNUMSETFLD),
                    m_pProps->sPar3,
                    String::CreateFromInt32(m_pProps->nFormat),
                    aData );
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATABASE_SET_NUM:
            {
                SwDBData aData;
                aData.sDataSource = m_pProps->sPar1;
                aData.sCommand = m_pProps->sPar2;
                aData.nCommandType = m_pProps->nSHORT1;
                pFld = new SwDBSetNumberField((SwDBSetNumberFieldType*)
                        pDoc->GetSysFldType(RES_DBSETNUMBERFLD),
                        aData,
                        m_pProps->nUSHORT1);
                ((SwDBSetNumberField*)pFld)->SetSetNumber(m_pProps->nFormat);
                sal_uInt16  nSubType = pFld->GetSubType();
                if(m_pProps->bBool2)
                    nSubType &= ~SUB_INVISIBLE;
                else
                    nSubType |= SUB_INVISIBLE;
                pFld->SetSubType(nSubType);
            }
            break;
            case SW_SERVICE_FIELDTYPE_DATABASE:
            {
                SwFieldType* pFldType = pDoc->GetFldType(RES_DBFLD, m_sTypeName);
                if(!pFldType)
                    throw uno::RuntimeException();
                pFld = new SwDBField((SwDBFieldType*)pFldType, m_pProps->nFormat);
                ((SwDBField*)pFld)->InitContent(m_pProps->sPar1);
                sal_uInt16  nSubType = pFld->GetSubType();
                if(m_pProps->bBool2)
                    nSubType &= ~SUB_INVISIBLE;
                else
                    nSubType |= SUB_INVISIBLE;
                pFld->SetSubType(nSubType);
            }
            break;
            case SW_SERVICE_FIELDTYPE_SET_EXP:
            {
                SwFieldType* pFldType = pDoc->GetFldType(RES_SETEXPFLD, m_sTypeName);
                if(!pFldType)
                    throw uno::RuntimeException();
                //#93192# detect the field type's sub type and set an appropriate number format
                if(m_pProps->bFormatIsDefault &&
                    GSE_STRING == ((SwSetExpFieldType*)pFldType)->GetType())
                        m_pProps->nFormat = -1;
                pFld = new SwSetExpField((SwSetExpFieldType*)pFldType,
                    m_pProps->sPar2,
                    m_pProps->nFormat);

                sal_uInt16	nSubType = pFld->GetSubType();
                if(m_pProps->bBool2)
                    nSubType &= ~SUB_INVISIBLE;
                else
                    nSubType |= SUB_INVISIBLE;
                if(m_pProps->bBool3)
                    nSubType |= SUB_CMD;
                else
                    nSubType &= ~SUB_CMD;
                pFld->SetSubType(nSubType);
                ((SwSetExpField*)pFld)->SetSeqNumber( m_pProps->nUSHORT1 );
                ((SwSetExpField*)pFld)->SetInputFlag(m_pProps->bBool1);
                ((SwSetExpField*)pFld)->SetPromptText(m_pProps->sPar3);
                if(m_pProps->sPar4.Len())
                    ((SwSetExpField*)pFld)->ChgExpStr(m_pProps->sPar4);

            }
            break;
            case SW_SERVICE_FIELDTYPE_GET_EXP:
            {
                sal_uInt16 nSubType;
                switch(m_pProps->nSubType)
                {
                    case SetVariableType::STRING:	nSubType = GSE_STRING;	break;
                    case SetVariableType::VAR:		nSubType = GSE_EXPR;  break;
                    case SetVariableType::SEQUENCE: nSubType = GSE_SEQ;  break;
                    case SetVariableType::FORMULA: 	nSubType = GSE_FORMULA; break;
                    default:
                        OSL_FAIL("wrong value");
                        nSubType = GSE_EXPR;
                }
                if(m_pProps->bBool2)
                    nSubType |= SUB_CMD;
                else
                    nSubType &= ~SUB_CMD;
                pFld = new SwGetExpField((SwGetExpFieldType*)
                        pDoc->GetSysFldType(RES_GETEXPFLD),
                        m_pProps->sPar1, nSubType, m_pProps->nFormat);
                //TODO: SubType auswerten!
                if(m_pProps->sPar4.Len())
                    ((SwGetExpField*)pFld)->ChgExpStr(m_pProps->sPar4);
            }
            break;
            case SW_SERVICE_FIELDTYPE_INPUT_USER:
            case SW_SERVICE_FIELDTYPE_INPUT:
            {
                SwFieldType* pFldType = pDoc->GetFldType(RES_INPUTFLD, m_sTypeName);
                if(!pFldType)
                    throw uno::RuntimeException();
                USHORT nInpSubType = SW_SERVICE_FIELDTYPE_INPUT_USER == m_nServiceId ? INP_USR : INP_TXT;
                pFld = new SwInputField((SwInputFieldType*)pFldType,
                        m_pProps->sPar1, m_pProps->sPar2, nInpSubType);
            }
            break;
            case SW_SERVICE_FIELDTYPE_MACRO:
            {
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_MACROFLD);
                String aName;
                SwMacroField::CreateMacroString(
                    aName, m_pProps->sPar1, m_pProps->sPar3 );
                pFld = new SwMacroField((SwMacroFieldType*)pFldType, aName,
                                        m_pProps->sPar2);
            }
            break;
            case SW_SERVICE_FIELDTYPE_PAGE_COUNT            :
            case SW_SERVICE_FIELDTYPE_PARAGRAPH_COUNT       :
            case SW_SERVICE_FIELDTYPE_WORD_COUNT            :
            case SW_SERVICE_FIELDTYPE_CHARACTER_COUNT       :
            case SW_SERVICE_FIELDTYPE_TABLE_COUNT           :
            case SW_SERVICE_FIELDTYPE_GRAPHIC_OBJECT_COUNT  :
            case SW_SERVICE_FIELDTYPE_EMBEDDED_OBJECT_COUNT :
            {
                sal_uInt16 nSubType = DS_PAGE;
                switch(m_nServiceId)
                {
//					case SW_SERVICE_FIELDTYPE_PAGE_COUNT            : break;
                    case SW_SERVICE_FIELDTYPE_PARAGRAPH_COUNT       : nSubType = DS_PARA;break;
                    case SW_SERVICE_FIELDTYPE_WORD_COUNT            : nSubType = DS_WORD;break;
                    case SW_SERVICE_FIELDTYPE_CHARACTER_COUNT       : nSubType = DS_CHAR;break;
                    case SW_SERVICE_FIELDTYPE_TABLE_COUNT           : nSubType = DS_TBL;break;
                    case SW_SERVICE_FIELDTYPE_GRAPHIC_OBJECT_COUNT  : nSubType = DS_GRF;break;
                    case SW_SERVICE_FIELDTYPE_EMBEDDED_OBJECT_COUNT : nSubType = DS_OLE;break;
                }
                SwFieldType* pFldType = pDoc->GetSysFldType(RES_DOCSTATFLD);
                pFld = new SwDocStatField((SwDocStatFieldType*)pFldType, nSubType, m_pProps->nUSHORT2);
            }
            break;
            case SW_SERVICE_FIELDTYPE_BIBLIOGRAPHY:
                pFld = new SwAuthorityField( (SwAuthorityFieldType*)
                        pDoc->InsertFldType(SwAuthorityFieldType(pDoc)),
                        aEmptyStr );
                if(m_pProps->aPropSeq.getLength())
                {
                    Any aVal; aVal <<= m_pProps->aPropSeq;
                    pFld->PutValue( aVal, FIELD_PROP_PROP_SEQ );
                }
                break;
            case SW_SERVICE_FIELDTYPE_COMBINED_CHARACTERS:
                // create field
                pFld = new SwCombinedCharField( (SwCombinedCharFieldType*)
                            pDoc->GetSysFldType(RES_COMBINED_CHARS),
                            m_pProps->sPar1);
                break;
            case SW_SERVICE_FIELDTYPE_DROPDOWN:
                pFld = new SwDropDownField
                    ((SwDropDownFieldType *)
                     pDoc->GetSysFldType(RES_DROPDOWN));

                ((SwDropDownField *) pFld)->SetItems(m_pProps->aStrings);
                ((SwDropDownField *) pFld)->SetSelectedItem(m_pProps->sPar1);
                ((SwDropDownField *) pFld)->SetName(m_pProps->sPar2);
                break;

            case SW_SERVICE_FIELDTYPE_TABLE_FORMULA :
            {

                // create field
                USHORT nType = GSE_FORMULA;
                if(m_pProps->bBool1)
                {
                    nType |= SUB_CMD;
                    if(m_pProps->bFormatIsDefault)
                        m_pProps->nFormat = -1;
                }
                pFld = new SwTblField( (SwTblFieldType*)
                    pDoc->GetSysFldType(RES_TABLEFLD),
                    m_pProps->sPar2,
                    nType,
                    m_pProps->nFormat);
               ((SwTblField*)pFld)->ChgExpStr(m_pProps->sPar1);
            }
            break;
            default: OSL_FAIL("was ist das fuer ein Typ?");
        }
        if(pFld)
        {
            pFld->SetAutomaticLanguage(!m_pProps->bBool4);
            SwFmtFld aFmt( *pFld );

            UnoActionContext aCont(pDoc);
            SwTxtAttr* pTxtAttr = 0;
            if(aPam.HasMark())
                pDoc->DeleteAndJoin(aPam);
            pDoc->Insert(aPam, aFmt);
            pTxtAttr = aPam.GetNode()->GetTxtNode()->GetTxtAttr(
                    aPam.GetPoint()->nContent.GetIndex()-1, RES_TXTATR_FIELD);

            // was passiert mit dem Update der Felder ? (siehe fldmgr.cxx)
            if(pTxtAttr)
            {
                const SwFmtFld& rFld = pTxtAttr->GetFld();
                pFmtFld = &rFld;
            }
        }
        delete pFld;

        m_pDoc = pDoc;
        m_pDoc->GetUnoCallBack()->Add(this);
        m_bIsDescriptor = sal_False;
        DELETEZ(m_pProps);
        if(m_bCallUpdate)
            update();
    }
    else
        throw IllegalArgumentException();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::attach(const uno::Reference< XTextRange > & xTextRange)
    throw( IllegalArgumentException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    attachToRange( xTextRange );
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XTextRange >  SwXTextField::getAnchor(void) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    uno::Reference< XTextRange >   aRef;
    SwField* pField = (SwField*)GetField();
    if(pField)
    {
        const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
        if(!pTxtFld)
            throw uno::RuntimeException();
        const SwTxtNode& rTxtNode = pTxtFld->GetTxtNode();

        SwPaM aPam(rTxtNode, *pTxtFld->GetStart() + 1, rTxtNode, *pTxtFld->GetStart());

        aRef = SwXTextRange::CreateTextRangeFromPosition(m_pDoc,
                                *aPam.GetPoint(), aPam.GetMark());
    }
    return aRef;

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::dispose(void) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    SwField* pField = (SwField*)GetField();
    if(pField)
    {
        UnoActionContext aContext(GetDoc());
        const SwTxtFld* pTxtFld = pFmtFld->GetTxtFld();
        SwTxtNode& rTxtNode = (SwTxtNode&)*pTxtFld->GetpTxtNode();
        SwPaM aPam(rTxtNode, *pTxtFld->GetStart());
        aPam.SetMark();
        aPam.Move();
        GetDoc()->DeleteAndJoin(aPam);
    }
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::addEventListener(const uno::Reference< XEventListener > & aListener) throw( uno::RuntimeException )
{
    if(!GetRegisteredIn())
        throw uno::RuntimeException();
    aLstnrCntnr.AddListener(aListener);
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::removeEventListener(const uno::Reference< XEventListener > & aListener) throw( uno::RuntimeException )
{
    if(!GetRegisteredIn() || !aLstnrCntnr.RemoveListener(aListener))
        throw uno::RuntimeException();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XPropertySetInfo >  SwXTextField::getPropertySetInfo(void)
        throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    //kein static
    uno::Reference< XPropertySetInfo >  aRef;
    if(m_nServiceId != USHRT_MAX)
    {
        const SfxItemPropertyMap* pMap = aSwMapProvider.GetPropertyMap(
                        lcl_GetPropertyMapOfService( m_nServiceId ));
        uno::Reference< beans::XPropertySetInfo >  xInfo = new SfxItemPropertySetInfo(pMap);
        // extend PropertySetInfo!
        const uno::Sequence<beans::Property> aPropSeq = xInfo->getProperties();
        aRef = new SfxExtItemPropertySetInfo(
            aSwMapProvider.GetPropertyMap(PROPERTY_MAP_PARAGRAPH_EXTENSIONS),
            aPropSeq );
    }
    else
        throw uno::RuntimeException();
    return aRef;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::setPropertyValue(const OUString& rPropertyName, const uno::Any& rValue)
    throw( UnknownPropertyException, PropertyVetoException, IllegalArgumentException,
        WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    SwField* pField = (SwField*)GetField();
    const SfxItemPropertyMap* _pMap = aSwMapProvider.GetPropertyMap(
                                lcl_GetPropertyMapOfService( m_nServiceId));
    const SfxItemPropertyMap*	pMap = SfxItemPropertyMap::GetByName(_pMap, rPropertyName);

    if (!pMap)
        throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );
    if ( pMap->nFlags & PropertyAttribute::READONLY)
        throw PropertyVetoException ( OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Property is read-only: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );

    if(pField)
    {
        // Sonderbehandlung Serienbrieffeld
        sal_uInt16 nWhich = pField->Which();
        if( RES_DBFLD == nWhich &&
            (rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_BASE_NAME)) ||
            rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_TABLE_NAME))||
            rPropertyName.equalsAsciiL( SW_PROP_NAME(UNO_NAME_DATA_COLUMN_NAME))))
        {
            // hier muss ein neuer Feldtyp angelegt werden und
            // das Feld an den neuen Typ umgehaengt werden
            DBG_WARNING("not implemented");
        }
        else
            pField->PutValue( rValue, pMap->nWID );
    }
    else if(m_pProps)
    {
        String* pStr = 0;
        BOOL* pBool = 0;
        switch(pMap->nWID)
        {
        case FIELD_PROP_PAR1:
            pStr = &m_pProps->sPar1;
            break;
        case FIELD_PROP_PAR2:
            pStr = &m_pProps->sPar2;
            break;
        case FIELD_PROP_PAR3:
            pStr = &m_pProps->sPar3;
            break;
        case FIELD_PROP_PAR4:
            pStr = &m_pProps->sPar4;
            break;
        case FIELD_PROP_FORMAT:
            rValue >>= m_pProps->nFormat;
            m_pProps->bFormatIsDefault = sal_False;
            break;
        case FIELD_PROP_SUBTYPE:
            m_pProps->nSubType = SWUnoHelper::GetEnumAsInt32( rValue );
            break;
        case FIELD_PROP_BYTE1 :
            rValue >>= m_pProps->nByte1;
            break;
        case FIELD_PROP_BOOL1 :
            pBool = &m_pProps->bBool1;
            break;
        case FIELD_PROP_BOOL2 :
            pBool = &m_pProps->bBool2;
            break;
        case FIELD_PROP_BOOL3 :
            pBool = &m_pProps->bBool3;
            break;
        case FIELD_PROP_BOOL4:
            pBool = &m_pProps->bBool4;
        break;
        case FIELD_PROP_DATE :
        {
            if(rValue.getValueType() != ::getCppuType((const util::Date*)0))
                throw IllegalArgumentException();

            util::Date aTemp = *(const util::Date*)rValue.getValue();
            m_pProps->aDate = Date(aTemp.Day, aTemp.Month, aTemp.Year);
        }
        break;
        case FIELD_PROP_USHORT1:
        case FIELD_PROP_USHORT2:
            {
                sal_Int16 nVal(0);
                rValue >>= nVal;
                if( FIELD_PROP_USHORT1 == pMap->nWID)
                    m_pProps->nUSHORT1 = nVal;
                else
                    m_pProps->nUSHORT2 = nVal;
            }
            break;
        case FIELD_PROP_SHORT1:
            rValue >>= m_pProps->nSHORT1;
            break;
        case FIELD_PROP_DOUBLE:
            if(rValue.getValueType() != ::getCppuType((const double*)0))
                throw IllegalArgumentException();
            m_pProps->fDouble = *(double*)rValue.getValue();
            break;

        case FIELD_PROP_DATE_TIME :
            if(!m_pProps->pDateTime)
                m_pProps->pDateTime = new util::DateTime;
            rValue >>= (*m_pProps->pDateTime);
            break;
        case FIELD_PROP_PROP_SEQ:
            rValue >>= m_pProps->aPropSeq;
            break;
        case FIELD_PROP_STRINGS:
            rValue >>= m_pProps->aStrings;
            break;
        }
        if( pStr )
            ::binfilter::GetString( rValue, *pStr );
        else if( pBool )
        {
            if( rValue.getValueType() == getCppuBooleanType() )
                *pBool = *(sal_Bool*)rValue.getValue();
            else
                throw IllegalArgumentException();
        }
    }
    else
        throw uno::RuntimeException();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Any SwXTextField::getPropertyValue(const OUString& rPropertyName)
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    uno::Any aRet;
    const SwField* pField = GetField();
    const SfxItemPropertyMap* _pMap = aSwMapProvider.GetPropertyMap(
                                lcl_GetPropertyMapOfService( m_nServiceId));
    const SfxItemPropertyMap*	pMap = SfxItemPropertyMap::GetByName(_pMap, rPropertyName);
    if(!pMap )
    {
        _pMap = aSwMapProvider.GetPropertyMap(PROPERTY_MAP_PARAGRAPH_EXTENSIONS);
        pMap = SfxItemPropertyMap::GetByName(_pMap, rPropertyName);
    }
    if (!pMap)
        throw UnknownPropertyException(OUString ( RTL_CONSTASCII_USTRINGPARAM ( "Unknown property: " ) ) + rPropertyName, static_cast < cppu::OWeakObject * > ( this ) );

    switch( pMap->nWID )
    {
    case FN_UNO_TEXT_WRAP:
        aRet <<= WrapTextMode_NONE;
        break;
    case FN_UNO_ANCHOR_TYPE:
        aRet <<= TextContentAnchorType_AS_CHARACTER;
        break;
    case FN_UNO_ANCHOR_TYPES:
        {
            uno::Sequence<TextContentAnchorType> aTypes(1);
            TextContentAnchorType* pArray = aTypes.getArray();
            pArray[0] = TextContentAnchorType_AS_CHARACTER;
            aRet.setValue(&aTypes, ::getCppuType((uno::Sequence<TextContentAnchorType>*)0));
        }
        break;

    default:
        if( pField )
            pField->QueryValue( aRet, pMap->nWID );
        else if( m_pProps )
        {
            switch(pMap->nWID)
            {
            case FIELD_PROP_PAR1:
                aRet <<= OUString(m_pProps->sPar1);
                break;
            case FIELD_PROP_PAR2:
                aRet <<= OUString(m_pProps->sPar2);
                break;
            case FIELD_PROP_PAR3:
                aRet <<= OUString(m_pProps->sPar3);
                break;
            case FIELD_PROP_PAR4:
                aRet <<= OUString(m_pProps->sPar4);
                break;
            case FIELD_PROP_FORMAT:
                aRet <<= m_pProps->nFormat;
                break;
            case FIELD_PROP_SUBTYPE:
                aRet <<= m_pProps->nSubType;
                break;
            case FIELD_PROP_BYTE1 :
                aRet <<= m_pProps->nByte1;
                break;
            case FIELD_PROP_BOOL1 :
                aRet.setValue(&m_pProps->bBool1, ::getCppuBooleanType());
                break;
            case FIELD_PROP_BOOL2 :
                aRet.setValue(&m_pProps->bBool2, ::getCppuBooleanType());
                break;
            case FIELD_PROP_BOOL3 :
                aRet.setValue(&m_pProps->bBool3, ::getCppuBooleanType());
                break;
            case FIELD_PROP_BOOL4 :
                aRet.setValue(&m_pProps->bBool4, ::getCppuBooleanType());
                break;
            case FIELD_PROP_DATE :
                aRet.setValue(&m_pProps->aDate, ::getCppuType((const util::Date*)0));
                break;
            case FIELD_PROP_USHORT1:
                aRet <<= (sal_Int16)m_pProps->nUSHORT1;
                break;
            case FIELD_PROP_USHORT2:
                aRet <<= (sal_Int16)m_pProps->nUSHORT2;
                break;
            case FIELD_PROP_SHORT1:
                aRet <<= m_pProps->nSHORT1;
                break;
            case FIELD_PROP_DOUBLE:
                aRet <<= m_pProps->fDouble;
                break;
            case FIELD_PROP_DATE_TIME :
                if(m_pProps->pDateTime)
                    aRet <<= (*m_pProps->pDateTime);
                break;
            case FIELD_PROP_PROP_SEQ:
                aRet <<= m_pProps->aPropSeq;
                break;
            case FIELD_PROP_STRINGS:
                aRet <<= m_pProps->aStrings;
                break;
            }
        }
        else
            throw uno::RuntimeException();
    }
    return aRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::addPropertyChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XPropertyChangeListener > & /*aListener*/)
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::removePropertyChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XPropertyChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::addVetoableChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XVetoableChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextField::removeVetoableChangeListener(const OUString& /*PropertyName*/, const uno::Reference< XVetoableChangeListener > & /*aListener*/) 
    throw( UnknownPropertyException, WrappedTargetException, uno::RuntimeException )
{
    DBG_WARNING("not implemented");
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
void SwXTextField::update(  ) throw (RuntimeException)
{
    SolarMutexGuard aGuard;
    const SwField* pFld = GetField();
    if(pFld)
    {
        switch(pFld->Which())
        {
            case RES_DATETIMEFLD:
            ((SwDateTimeField*)pFld)->SetDateTime( ::DateTime() );
            break;

            case RES_EXTUSERFLD:
            {
                SwExtUserField* pExtUserFld = (SwExtUserField*)pFld;
                pExtUserFld->SetExpansion( ((SwExtUserFieldType*)pFld->GetTyp())->Expand(
                                            pExtUserFld->GetSubType(),
                                            pExtUserFld->GetFormat() ) );
            }
            break;

            case RES_AUTHORFLD:
            {
                SwAuthorField* pAuthorFld = (SwAuthorField*)pFld;
                pAuthorFld->SetExpansion( ((SwAuthorFieldType*)pFld->GetTyp())->Expand(
                                            pAuthorFld->GetFormat() ) );
            }
            break;

            case RES_FILENAMEFLD:
            {
                SwFileNameField* pFileNameFld = (SwFileNameField*)pFld;
                pFileNameFld->SetExpansion( ((SwFileNameFieldType*)pFld->GetTyp())->Expand(
                                            pFileNameFld->GetFormat() ) );
            }
            break;

            case RES_DOCINFOFLD:
            {
                    SwDocInfoField* pDocInfFld = (SwDocInfoField*)pFld;
                    pDocInfFld->SetExpansion( ((SwDocInfoFieldType*)pFld->GetTyp())->Expand(
                                                pDocInfFld->GetSubType(),
                                                pDocInfFld->GetFormat(),
                                                pDocInfFld->GetLanguage() ) );
            }
            break;
        }
    }
    else
        m_bCallUpdate = sal_True;
}

OUString SwXTextField::getImplementationName(void) throw( uno::RuntimeException )
{
    return C2U("SwXTextField");
}

sal_Bool SwXTextField::supportsService(const OUString& rServiceName) throw( uno::RuntimeException )
{
    OUString sServiceName = SwXServiceProvider::GetProviderName(m_nServiceId);
    return sServiceName == rServiceName ||
        rServiceName.equalsAsciiL(
                RTL_CONSTASCII_STRINGPARAM("com.sun.star.text.TextContent"));
}

uno::Sequence< OUString > SwXTextField::getSupportedServiceNames(void) throw( uno::RuntimeException )
{
    uno::Sequence< OUString > aRet(2);
    OUString* pArray = aRet.getArray();
    OUString sServiceName = SwXServiceProvider::GetProviderName(m_nServiceId);
    pArray[0] = sServiceName;
    pArray[1] = C2U("com.sun.star.text.TextContent");
    return aRet;
}

void SwXTextField::Invalidate()
{
    if (GetRegisteredIn())
    {
        ((SwModify*)GetRegisteredIn())->Remove(this);
        aLstnrCntnr.Disposing();
        pFmtFld = 0;
        m_pDoc = 0;
    }
}


void SwXTextField::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew)
{
    switch( pOld ? pOld->Which() : 0 )
    {
    case RES_REMOVE_UNO_OBJECT:
    case RES_OBJECTDYING:
        if( (void*)GetRegisteredIn() == ((SwPtrMsgPoolItem *)pOld)->pObject )
            Invalidate();
        break;

    case RES_FMT_CHG:
        // wurden wir an das neue umgehaengt und wird das alte geloscht?
        if( ((SwFmtChg*)pNew)->pChangedFmt == GetRegisteredIn() &&
            ((SwFmtChg*)pOld)->pChangedFmt->IsFmtInDTOR() )
            Invalidate();
        break;
    case RES_FIELD_DELETED:
        if( (void*)pFmtFld == ((SwPtrMsgPoolItem *)pOld)->pObject )
            Invalidate();
        break;
    }
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
const SwField*  SwXTextField::GetField() const
{
    if(GetRegisteredIn() && pFmtFld)
        return  pFmtFld->GetFld();
    return 0;
}
/******************************************************************
 *
 ******************************************************************/
/******************************************************************
 * SwXTextFieldMasters
 ******************************************************************/
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXTextFieldMasters::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXTextFieldMasters");
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwXTextFieldMasters::supportsService(const OUString& rServiceName) throw( RuntimeException )
{
    return rServiceName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(
                            "com.sun.star.text.TextFieldMasters" ));
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
Sequence< OUString > SwXTextFieldMasters::getSupportedServiceNames(void) throw( RuntimeException )
{
    Sequence< OUString > aRet(1);
    OUString* pArray = aRet.getArray();
    pArray[0] = C2U("com.sun.star.text.TextFieldMasters");
    return aRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextFieldMasters::SwXTextFieldMasters(SwDoc* pInDoc) :
    SwUnoCollection(pInDoc)
{
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextFieldMasters::~SwXTextFieldMasters()
{

}
/*-----------------------------------------------------------------------
    Iteration ueber nicht-Standard Feldtypen
    USER/SETEXP/DDE/DATABASE
    Der Name ist demnach:
    "com.sun.star.text.FieldMaster.User" + <Feltypname>
    "com.sun.star.text.FieldMaster.DDE" + <Feltypname>
    "com.sun.star.text.FieldMaster.SetExpression" + <Feltypname>
    "com.sun.star.text.FieldMaster.DataBase" + <Feltypname>

    Falls wir grosszuegig werden wollen, dann koennte man com.sun.star.text
    auch optional weglassen
  -----------------------------------------------------------------------*/

sal_uInt16 lcl_GetIdByName( String& rName, String& rTypeName )
{
    if( rName.EqualsAscii( COM_TEXT_FLDMASTER, 0,
                            RTL_CONSTASCII_LENGTH(COM_TEXT_FLDMASTER )) )
        rName.Erase(0, 30);

    sal_uInt16 nResId = USHRT_MAX;
    xub_StrLen nFound = 0;
    rTypeName = rName.GetToken( 0, '.', nFound );
    if(rTypeName.EqualsAscii("User"))
        nResId = RES_USERFLD;
    else if(rTypeName.EqualsAscii("DDE"))
        nResId = RES_DDEFLD;
    else if(rTypeName.EqualsAscii("SetExpression"))
    {
        nResId = RES_SETEXPFLD;

        String sFldTypName( rName.GetToken( 1, '.' ));
        String sUIName( SwStyleNameMapper::GetSpecialExtraUIName( sFldTypName ) );

        if( sUIName != sFldTypName )
            rName.SetToken( 1, '.', sUIName );
    }
    else if(rTypeName.EqualsAscii("DataBase"))
    {
        rName.Erase( 0, RTL_CONSTASCII_LENGTH( "DataBase." ));
        USHORT nDotCount = rName.GetTokenCount('.');
        if( 2 <= nDotCount )
        {
            rName.SearchAndReplace('.', DB_DELIM);
            rName.SetChar( rName.SearchBackward( '.' ), DB_DELIM );
            rName.InsertAscii( "DataBase.", 0 );
            nResId = RES_DBFLD;
        }
    }
    else if( rTypeName.EqualsAscii("Bibliography"))
        nResId = RES_AUTHORITY;
    return nResId;
}

//-----------------------------------------------------------------------------
uno::Any SwXTextFieldMasters::getByName(const OUString& rName)
    throw( NoSuchElementException, WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!GetDoc())
        throw uno::RuntimeException();

    String sName(rName), sTypeName;
    sal_uInt16 nResId = lcl_GetIdByName( sName, sTypeName );
    if( USHRT_MAX == nResId )
        throw NoSuchElementException();

    sName.Erase(0, sTypeName.Len()+1);
    SwFieldType* pType = GetDoc()->GetFldType(nResId, sName);
    if(!pType)
        throw NoSuchElementException();
    SwXFieldMaster* pMaster = (SwXFieldMaster*)
                SwClientIter(*pType).First(TYPE(SwXFieldMaster));
    if(!pMaster)
        pMaster = new SwXFieldMaster(*pType, GetDoc());
    uno::Reference< XPropertySet >  aRef = pMaster;
    uno::Any aRet(&aRef, ::getCppuType((const uno::Reference<XPropertySet>*)0));
    return aRet;
}
/*-- 06.03.2001 11:29:34,5-------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool SwXTextFieldMasters::getInstanceName(
    const SwFieldType& rFldType, String& rName)
{
    sal_Bool bRet = sal_True;
    switch( rFldType.Which() )
    {
    case RES_USERFLD:
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( COM_TEXT_FLDMASTER ));
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "User."));
        rName += rFldType.GetName();
        break;
    case RES_DDEFLD:
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( COM_TEXT_FLDMASTER ));
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "DDE."));
        rName += rFldType.GetName();
        break;

    case RES_SETEXPFLD:
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( COM_TEXT_FLDMASTER ));
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "SetExpression."));
        rName += String( SwStyleNameMapper::GetSpecialExtraProgName( rFldType.GetName() ) );
        break;

    case RES_DBFLD:
        {
            rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( COM_TEXT_FLDMASTER ));
            rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "DataBase."));
            String sDBName(rFldType.GetName());
            sDBName.SearchAndReplaceAll(DB_DELIM, '.');
            rName += sDBName;
        }
        break;

    case RES_AUTHORITY:
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( COM_TEXT_FLDMASTER ));
        rName.AppendAscii( RTL_CONSTASCII_STRINGPARAM( "Bibliography"));
        break;

    default:
        bRet = sal_False;
    }

    return bRet;
}


/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Sequence< OUString > SwXTextFieldMasters::getElementNames(void)
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!GetDoc())
        throw uno::RuntimeException();

    const SwFldTypes* pFldTypes = GetDoc()->GetFldTypes();
    sal_uInt16 nCount = pFldTypes->Count();

    SvStrings aFldNames;
    String* pString = new String();
    sal_uInt16 i=0;
    for( i = 0; i < nCount; i++)
    {
        SwFieldType& rFldType = *((*pFldTypes)[i]);

        if (SwXTextFieldMasters::getInstanceName(rFldType, *pString))
        {
            aFldNames.Insert(pString, aFldNames.Count());
            pString = new String();
        }
    }
    delete pString;

    uno::Sequence< OUString > aSeq(aFldNames.Count());
    OUString* pArray = aSeq.getArray();
    for(i = 0; i < aFldNames.Count();i++)
    {
        pArray[i] = *aFldNames.GetObject(i);
    }
    aFldNames.DeleteAndDestroy(0, aFldNames.Count());

    return aSeq;

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool SwXTextFieldMasters::hasByName(const OUString& rName) throw( RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!GetDoc())
        throw uno::RuntimeException();

    String sName(rName), sTypeName;
    sal_uInt16 nResId = lcl_GetIdByName( sName, sTypeName );
    sal_Bool bRet = sal_False;
    if( USHRT_MAX != nResId )
    {
        sName.Erase(0, sTypeName.Len()+1);
        bRet = USHRT_MAX != nResId && 0 != GetDoc()->GetFldType(nResId, sName);
    }
    return bRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Type  SwXTextFieldMasters::getElementType(void) throw( uno::RuntimeException )
{
    return ::getCppuType((const uno::Reference<XPropertySet>*)0);

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool SwXTextFieldMasters::hasElements(void) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    return sal_True;
}

/******************************************************************
 *
 ******************************************************************/
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXTextFieldTypes::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXTextFieldTypes");
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwXTextFieldTypes::supportsService(const OUString& rServiceName) throw( RuntimeException )
{
    return rServiceName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(
                            "com.sun.star.text.TextFields" ));
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
Sequence< OUString > SwXTextFieldTypes::getSupportedServiceNames(void) throw( RuntimeException )
{
    Sequence< OUString > aRet(1);
    OUString* pArray = aRet.getArray();
    pArray[0] = C2U("com.sun.star.text.TextFields");
    return aRet;
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextFieldTypes::SwXTextFieldTypes(SwDoc* pInDoc) :
    SwUnoCollection (pInDoc),
    aRefreshCont    ( static_cast< XEnumerationAccess * >(this) )
{
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXTextFieldTypes::~SwXTextFieldTypes()
{
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
void SwXTextFieldTypes::Invalidate()
{
    SwUnoCollection::Invalidate();
    aRefreshCont.Disposing();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Reference< XEnumeration >  SwXTextFieldTypes::createEnumeration(void)
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    return new SwXFieldEnumeration(GetDoc());
}

/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Type  SwXTextFieldTypes::getElementType(void) throw( uno::RuntimeException )
{
    return ::getCppuType((const uno::Reference<XDependentTextField>*)0);
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool SwXTextFieldTypes::hasElements(void) throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    //es gibt sie immer
    return sal_True;
}

void SwXTextFieldTypes::refresh(void)  throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if(!IsValid())
        throw uno::RuntimeException();
    UnoActionContext aContext(GetDoc());
    SwDocStat aDocStat;
    GetDoc()->UpdateDocStat(aDocStat);
    GetDoc()->UpdateFlds(0, sal_False);

    // call refresh listeners
    aRefreshCont.Refreshed();
}

void SwXTextFieldTypes::addRefreshListener(const uno::Reference< util::XRefreshListener > & l)
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if ( !IsValid() )
        throw RuntimeException();
    aRefreshCont.AddListener ( reinterpret_cast < const Reference < lang::XEventListener > &> ( l ));
}

void SwXTextFieldTypes::removeRefreshListener(const uno::Reference< util::XRefreshListener > & l)
     throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    if ( !IsValid() || !aRefreshCont.RemoveListener ( reinterpret_cast < const Reference < lang::XEventListener > &> ( l ) ) )
        throw RuntimeException();
}
/******************************************************************
 * SwXFieldEnumeration
 ******************************************************************/
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
OUString SwXFieldEnumeration::getImplementationName(void) throw( RuntimeException )
{
    return C2U("SwXFieldEnumeration");
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
BOOL SwXFieldEnumeration::supportsService(const OUString& rServiceName) throw( RuntimeException )
{
    return rServiceName.equalsAsciiL( RTL_CONSTASCII_STRINGPARAM(
                            "com.sun.star.text.FieldEnumeration" ));
}
/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
Sequence< OUString > SwXFieldEnumeration::getSupportedServiceNames(void) throw( RuntimeException )
{
    Sequence< OUString > aRet(1);
    OUString* pArray = aRet.getArray();
    pArray[0] = C2U("com.sun.star.text.FieldEnumeration");
    return aRet;
}

SwXFieldEnumeration::SwXFieldEnumeration(SwDoc* pDc) :
    nNextIndex(0),
    pDoc(pDc)
{
    pDoc->GetPageDescFromPool(RES_POOLPAGE_STANDARD)->Add(this);

    // build sequence
    sal_Int32 nSize = 32;
    aItems.realloc( nSize );
    uno::Reference< XTextField > *pItems = aItems.getArray();
    sal_Int32 nFillPos = 0;
    //
    const SwFldTypes* pFldTypes = pDoc->GetFldTypes();
    sal_uInt16 nCount = pFldTypes->Count();
    for(sal_uInt16 nType = 0;  nType < nCount;  ++nType)
    {
        const SwFieldType *pCurType = pFldTypes->GetObject(nType);

        SwClientIter aIter( *(SwFieldType*)pCurType );
        const SwFmtFld* pCurFldFmt = (SwFmtFld*)aIter.First( TYPE( SwFmtFld ));
        while (pCurFldFmt)
        {
            const SwTxtFld *pTxtFld = pCurFldFmt->GetTxtFld();
            // skip fields that are currently not in the document
            // e.g. fields in undo or redo array
            BOOL bSkip = !pTxtFld ||
                         !pTxtFld->GetpTxtNode()->GetNodes().IsDocNodes();
            if (!bSkip)
                pItems[ nFillPos++ ] = new SwXTextField(*pCurFldFmt, pDoc);
            pCurFldFmt = (SwFmtFld*)aIter.Next();

            // enlarge sequence if necessary
            if (aItems.getLength() == nFillPos)
            {
                aItems.realloc( 2 * aItems.getLength() );
                pItems = aItems.getArray();
            }
        }
    }
    // resize sequence to actual used size
    aItems.realloc( nFillPos );
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
SwXFieldEnumeration::~SwXFieldEnumeration()
{

}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
sal_Bool SwXFieldEnumeration::hasMoreElements(void)
    throw( uno::RuntimeException )
{
    SolarMutexGuard aGuard;
    return nNextIndex < aItems.getLength();
}
/*-----------------------------------------------------------------------

  -----------------------------------------------------------------------*/
uno::Any SwXFieldEnumeration::nextElement(void)
    throw( NoSuchElementException, WrappedTargetException, uno::RuntimeException )
{
    SolarMutexGuard aGuard;

    if (!(nNextIndex < aItems.getLength()))
        throw NoSuchElementException();

#if OSL_DEBUG_LEVEL > 1
    uno::Reference< XTextField > *pItems = aItems.getArray();
#endif
    uno::Reference< XTextField >  &rxFld = aItems.getArray()[ nNextIndex++ ];
    uno::Any aRet(&rxFld, ::getCppuType((const uno::Reference<XTextField>*)0));
    rxFld = 0;  // free memory for item that is not longer used
    return aRet;
}

void SwXFieldEnumeration::Modify( SfxPoolItem *pOld, SfxPoolItem *pNew)
{
    ClientModify(this, pOld, pNew);
    if(!GetRegisteredIn())
        pDoc = 0;
}


String& GetString( const ::com::sun::star::uno::Any& rAny, String& rStr )
{
    OUString aStr;
    rAny >>= aStr;
    rStr = String( aStr );
    return rStr;
}

} //namespace binfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
