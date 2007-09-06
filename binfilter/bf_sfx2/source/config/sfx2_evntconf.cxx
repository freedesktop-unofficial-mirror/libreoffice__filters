/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sfx2_evntconf.cxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 11:27:08 $
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

#ifdef _MSC_VER
#pragma hdrstop
#endif

#ifndef _RTL_USTRING_
#include <rtl/ustring.h>
#endif



#include "macrconf.hxx"
#include "objsh.hxx"
#include "eventsupplier.hxx"

#include "sfxsids.hrc"
#include "app.hxx"


#ifndef _LEGACYBINFILTERMGR_HXX
#include <legacysmgr/legacy_binfilters_smgr.hxx>	//STRIP002 
#endif
namespace binfilter {

// -----------------------------------------------------------------------

#define PROPERTYVALUE           ::com::sun::star::beans::PropertyValue
#define XNAMEREPLACE            ::com::sun::star::container::XNameReplace
#define XEVENTSSUPPLIER         ::com::sun::star::document::XEventsSupplier
#define ANY                     ::com::sun::star::uno::Any
#define REFERENCE               ::com::sun::star::uno::Reference
#define SEQUENCE                ::com::sun::star::uno::Sequence
#define UNO_QUERY               ::com::sun::star::uno::UNO_QUERY

#define OUSTRING                ::rtl::OUString

// -----------------------------------------------------------------------

static const USHORT nCompatVersion = 3;
static const USHORT nOldVersion = 4;
static const USHORT nVersion = 5;

/*N*/ TYPEINIT1(SfxEventHint, SfxHint);

// class SfxEventList_Impl -----------------------------------------------

/*N*/ struct EventNames_Impl
/*N*/ {
/*N*/     USHORT  mnId;
/*N*/     String  maEventName;
/*N*/     String  maUIName;
/*N*/ 
/*N*/             EventNames_Impl( USHORT nId,
/*N*/                              const String& rEventName,
/*N*/                              const String& rUIName )
/*N*/                 : mnId( nId )
/*N*/                 , maEventName( rEventName )
/*N*/                 , maUIName( rUIName ) {}
/*N*/ };

/*?*/ DECLARE_LIST( SfxEventList_Impl, EventNames_Impl* )//STRIP008 ;
/*?*/ 
/*?*/ SfxEventList_Impl   *gp_Id_SortList = NULL;
/*?*/ SfxEventList_Impl   *gp_Name_SortList = NULL;

//==========================================================================

/*N*/ SfxEventConfiguration::SfxEventConfiguration()
/*N*/  : pDocEventConfig( NULL )
/*N*/  , pAppEventConfig( NULL )
/*N*/ {
/*N*/     bIgnoreConfigure = sal_False;
/*N*/ 
/*N*/     // Array zum Ermitteln der Bindungen
/*N*/     pEventArr = new SfxEventArr_Impl;
/*N*/ 
/*N*/     // Einen default entry eingf"ugen
/*N*/     const SfxEvent_Impl *pEvent = new SfxEvent_Impl(String(), 0);
/*N*/     pEventArr->Insert(pEvent, 0);
/*N*/ }

//==========================================================================

/*N*/ SfxEventConfiguration::~SfxEventConfiguration()
/*N*/ {
/*N*/     for (USHORT n=0; n<pEventArr->Count(); n++)
/*N*/         delete (*pEventArr)[n];
/*N*/     delete pEventArr;
/*N*/     delete pAppEventConfig;
/*N*/ 
/*N*/     if ( gp_Id_SortList )
/*N*/     {
/*N*/         EventNames_Impl* pData = gp_Id_SortList->First();
/*N*/         while ( pData )
/*N*/         {
/*N*/             delete pData;
/*N*/             pData = gp_Id_SortList->Next();
/*N*/         }
/*N*/         delete gp_Id_SortList;
/*N*/         delete gp_Name_SortList;
/*N*/ 
/*N*/         gp_Id_SortList = NULL;
/*N*/         gp_Name_SortList = NULL;
/*N*/     }
/*N*/ }

//==========================================================================

/*N*/ void SfxEventConfiguration::RegisterEvent(USHORT nId, const String& rName)
/*N*/ {
/*N*/     USHORT nCount = pEventArr->Count();
/*N*/     const SfxEvent_Impl *pEvent = new SfxEvent_Impl(rName, nId);
/*N*/     pEventArr->Insert(pEvent, nCount);
/*N*/ }

//==========================================================================

/*?*/ String SfxEventConfiguration::GetEventName(USHORT nId) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return String();//STRIP001 
/*?*/ }

//==========================================================================

/*?*/ USHORT SfxEventConfiguration::GetEventId(const String& rName) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*?*/     return SFX_NO_EVENT;
/*?*/ }

/*N*/ void SfxEventConfiguration::ConfigureEvent( USHORT nId, const SvxMacro& rMacro, SfxObjectShell *pDoc )
/*N*/ {
/*N*/     if ( bIgnoreConfigure )
/*N*/         return;
/*?*/ 
/*?*/     SvxMacro *pMacro = NULL;
/*?*/     if ( rMacro.GetMacName().Len() )
/*?*/         pMacro = new SvxMacro( rMacro.GetMacName(), rMacro.GetLibName(), rMacro.GetScriptType() );
/*?*/     if ( pDoc )
/*?*/         PropagateEvent_Impl( pDoc, nId, pMacro );
/*N*/ }

//==========================================================================

/*?*/ const SvxMacro* SfxEventConfiguration::GetMacroForEventId
/*?*/ (
/*?*/     USHORT          nId,
/*?*/     SfxObjectShell* pDoc
/*?*/ )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 
/*?*/ }

/*?*/ const SfxMacroInfo* SfxEventConfiguration::GetMacroInfo
/*?*/ (
/*?*/     USHORT          nId,
/*?*/     SfxObjectShell* pDoc
/*?*/ ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 
/*?*/ }

//==========================================================================

/*N*/ SfxEventConfigItem_Impl::SfxEventConfigItem_Impl( USHORT nConfigId,
/*N*/     SfxEventConfiguration *pCfg,
/*N*/     SfxObjectShell *pObjSh)
/*N*/     : SfxConfigItem( nConfigId, pObjSh ? NULL : SFX_APP()->GetConfigManager_Impl() )
/*N*/     , aMacroTable( 2, 2 )
/*N*/     , pEvConfig( pCfg )
/*N*/     , pObjShell( pObjSh )
/*N*/ 	, bInitialized( FALSE )
/*N*/ {
/*N*/ 	bInitialized = TRUE;
/*N*/ }

/*
void SfxEventConfigItem_Impl::Init( SfxConfigManager *pMgr )
{
    if ( GetConfigManager() == pMgr )
        Initialize();
    else
        ReInitialize( pMgr );
}
*/

//==========================================================================

/*N*/ int SfxEventConfigItem_Impl::Load(SvStream& rStream)
/*N*/ {
/*N*/     USHORT nFileVersion;
/*N*/     rStream >> nFileVersion;
/*N*/     if ( nFileVersion < nCompatVersion || nFileVersion > nVersion )
/*?*/         return SfxConfigItem::WARNING_VERSION;
/*N*/ 
/*N*/     SvxMacroTableDtor aLocalMacroTable;
/*N*/     if ( nFileVersion <= nOldVersion )
/*N*/     {
/*?*/         if ( nFileVersion > nCompatVersion )
/*?*/         {
/*?*/             USHORT nWarn;
/*?*/             rStream >> nWarn;
/*?*/             bWarning = ( nWarn & 0x01 ) != 0;
/*?*/             bAlwaysWarning = ( nWarn & 0x02 ) != 0;
/*?*/         }
/*?*/         else
/*?*/             bWarning = bAlwaysWarning = FALSE;
/*?*/ 
/*?*/         USHORT nCount, nEventCount = pEvConfig->GetEventCount();
/*?*/         rStream >> nCount;
/*?*/ 
/*?*/         USHORT i;
/*?*/         for (i=0; i<nCount; i++)
/*?*/         {
/*?*/         	USHORT nId;
/*?*/             SfxMacroInfo aInfo( pObjShell );
/*?*/             rStream >> nId >> aInfo;
/*?*/ 
/*?*/             for (USHORT n=0; n<nEventCount; n++)
/*?*/             {
/*?*/ 				USHORT nEventId = (*pEvConfig->pEventArr)[n+1]->nEventId;
/*?*/                 if ( nEventId == nId )
/*?*/                 {
/*?*/                 	SvxMacro *pMacro = new SvxMacro( aInfo.GetQualifiedName(), aInfo.GetBasicName(), STARBASIC );
/*?*/                 	aLocalMacroTable.Insert( nEventId, pMacro );
/*?*/                     break;
/*?*/                 }
/*?*/             }
/*?*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         USHORT nWarn;
/*N*/         rStream >> nWarn;
/*N*/         bWarning = ( nWarn & 0x01 ) != 0;
/*N*/         bAlwaysWarning = ( nWarn & 0x02 ) != 0;
/*N*/         aLocalMacroTable.Read( rStream );
/*N*/     }
/*N*/ 
/*N*/     if ( pObjShell && pEvConfig )
/*N*/         pEvConfig->PropagateEvents_Impl( pObjShell, aLocalMacroTable );
/*N*/ 
/*N*/     return SfxConfigItem::ERR_OK;
/*N*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::LoadXML( SvStream& rInStream )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 
/*?*/ }

//==========================================================================

/*?*/ BOOL SfxEventConfigItem_Impl::Store(SvStream& rStream)
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 
/*?*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::StoreXML( SvStream& rOutStream )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 
/*?*/ }

//==========================================================================

/*?*/ String SfxEventConfigItem_Impl::GetStreamName() const
/*?*/ {
/*?*/     return SfxConfigItem::GetStreamName( GetType() );
/*?*/ }

//==========================================================================

/*N*/ void SfxEventConfigItem_Impl::UseDefault()
/*N*/ {
/*N*/     bWarning = TRUE;
/*N*/     bAlwaysWarning = FALSE;
/*N*/ 
/*N*/     aMacroTable.DelDtor();
/*N*/     SetDefault( TRUE );
/*N*/     pEvConfig->PropagateEvents_Impl( pObjShell, aMacroTable );
/*N*/ }

/*?*/ int SfxEventConfigItem_Impl::Load( SotStorage& rStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return 0;//STRIP001 
/*?*/ }

/*?*/ BOOL SfxEventConfigItem_Impl::Store( SotStorage& rStorage )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); return FALSE;//STRIP001 
/*?*/ }


//==========================================================================

/*N*/ SfxEventConfigItem_Impl::~SfxEventConfigItem_Impl()
/*N*/ {
/*N*/ }

//==========================================================================

/*N*/ void SfxEventConfigItem_Impl::ConfigureEvent( USHORT nId, SvxMacro *pMacro )
/*N*/ { 
/*N*/     if ( aMacroTable.Seek( nId ) )
/*N*/     {
/*?*/         if ( pMacro )
/*?*/             aMacroTable.Replace( nId, pMacro );
/*?*/         else
/*?*/             aMacroTable.Remove( nId );
/*N*/     }
/*N*/     else if ( pMacro )
/*N*/         aMacroTable.Insert( nId, pMacro );
/*N*/     SetDefault(FALSE);
/*N*/ }

/*?*/ void SfxEventConfiguration::AddEvents( SfxMacroTabPage* pPage ) const
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*?*/ }

/*N*/ SvxMacroTableDtor* SfxEventConfiguration::GetDocEventTable( SfxObjectShell*pDoc )
/*N*/ {
/*N*/     pDocEventConfig = pDoc ? pDoc->GetEventConfig_Impl() : NULL;
/*N*/     if ( pDocEventConfig )
/*N*/         return &pDocEventConfig->aMacroTable;
/*?*/     return NULL;
/*N*/ }

/*?*/ void SfxEventConfiguration::SetAppEventTable( const SvxMacroTableDtor& rTable )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*?*/ }

/*?*/ void SfxEventConfiguration::SetDocEventTable( SfxObjectShell *pDoc,
/*?*/     const SvxMacroTableDtor& rTable )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*?*/ }

//--------------------------------------------------------------------------
/*N*/ void SfxEventConfiguration::PropagateEvents_Impl( SfxObjectShell *pDoc,
/*N*/     const SvxMacroTableDtor& rTable )
/*N*/ {
/*N*/     REFERENCE< XEVENTSSUPPLIER > xSupplier;
/*N*/ 	if ( pDoc )
/*N*/ 	{
/*N*/ 		xSupplier = REFERENCE< XEVENTSSUPPLIER >( pDoc->GetModel(), UNO_QUERY );
/*N*/ 	}
/*N*/ 	else
/*N*/ 	{
/*N*/ 		xSupplier = REFERENCE< XEVENTSSUPPLIER >
/*N*/                 ( ::legacy_binfilters::getLegacyProcessServiceFactory()->createInstance(
/*N*/                         ::rtl::OUString::createFromAscii("com.sun.star.frame.GlobalEventBroadcaster" )), UNO_QUERY );
/*N*/ 	}
/*N*/ 
/*N*/     if ( xSupplier.is() )
/*N*/     {
/*N*/         SvxMacro   *pMacro;
/*N*/         ULONG       nCount;
/*N*/         ULONG       nID, i;
/*N*/ 
/*N*/         REFERENCE< XNAMEREPLACE > xEvents = xSupplier->getEvents();
/*N*/ 
/*N*/         bIgnoreConfigure = sal_True;
/*N*/ 
/*N*/         // Erase old values first, because we don't know anything about the
/*N*/         // changes here
/*N*/ 
/*N*/         SEQUENCE < PROPERTYVALUE > aProperties;
/*N*/         SEQUENCE < OUSTRING > aEventNames = xEvents->getElementNames();
/*N*/         OUSTRING*   pNames  = aEventNames.getArray();
/*N*/         ANY aEmpty;
/*N*/ 
/*N*/         aEmpty <<= aProperties;
/*N*/         nCount  = aEventNames.getLength();
/*N*/ 
/*N*/         for ( i=0; i<nCount; i++ )
/*N*/         {
/*N*/             try
/*N*/             {
/*N*/                 xEvents->replaceByName( pNames[i], aEmpty );
/*N*/             }
/*N*/             catch( ::com::sun::star::lang::IllegalArgumentException )
/*N*/             { DBG_ERRORFILE( "PropagateEvents_Impl: caught IllegalArgumentException" ) }
/*N*/             catch( ::com::sun::star::container::NoSuchElementException )
/*N*/             { DBG_ERRORFILE( "PropagateEvents_Impl: caught NoSuchElementException" ) }
/*N*/         }
/*N*/ 
/*N*/         // now set the new values
/*N*/ 
/*N*/         nCount = rTable.Count();
/*N*/ 
/*N*/         for ( i=0; i<nCount; i++ )
/*N*/         {
/*N*/             pMacro = rTable.GetObject( i );
/*N*/             nID = rTable.GetObjectKey( i );
/*N*/             OUSTRING aEventName = GetEventName_Impl( nID );
/*N*/ 
/*N*/             if ( aEventName.getLength() )
/*N*/             {
/*N*/                 ANY aEventData = CreateEventData_Impl( pMacro );
/*N*/                 try
/*N*/                 {
/*N*/                     xEvents->replaceByName( aEventName, aEventData );
/*N*/                 }
/*N*/                 catch( ::com::sun::star::lang::IllegalArgumentException )
/*N*/                 { DBG_ERRORFILE( "PropagateEvents_Impl: caught IllegalArgumentException" ) }
/*N*/                 catch( ::com::sun::star::container::NoSuchElementException )
/*N*/                 { DBG_ERRORFILE( "PropagateEvents_Impl: caught NoSuchElementException" ) }
/*N*/             }
/*N*/             else
/*N*/                 DBG_WARNING( "PropagateEvents_Impl: Got unkown event" );
/*N*/         }
/*N*/ 
/*N*/         bIgnoreConfigure = sal_False;
/*N*/     }
/*N*/ }

//--------------------------------------------------------------------------
/*?*/ void SfxEventConfiguration::PropagateEvent_Impl( SfxObjectShell *pDoc,
/*?*/                                                  USHORT nId,
/*?*/                                                  const SvxMacro* pMacro )
/*?*/ {DBG_BF_ASSERT(0, "STRIP"); //STRIP001 
/*?*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ANY SfxEventConfiguration::CreateEventData_Impl( const SvxMacro *pMacro )
/*N*/ {
/*
    This function converts a SvxMacro into an Any containing three
    properties. These properties are EventType and Script. Possible
    values for EventType ar StarBasic, JavaScript, ...
    The Script property should contain the URL to the macro and looks
    like "macro://./standard.module1.main()"

    If pMacro is NULL, we return an empty property sequence, so PropagateEvent_Impl
    can delete an event binding.
*/
/*N*/     ANY aEventData;
/*N*/ 
/*N*/     if ( pMacro )
/*N*/     {
/*N*/         if ( pMacro->GetScriptType() == STARBASIC )
/*N*/         {
/*N*/             SEQUENCE < PROPERTYVALUE > aProperties(3);
/*N*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*N*/ 
/*N*/             OUSTRING    aType   = OUSTRING::createFromAscii( STAR_BASIC );;
/*N*/             OUSTRING    aLib    = pMacro->GetLibName();
/*N*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*N*/ 
/*N*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*N*/             pValues[ 0 ].Value <<= aType;
/*N*/ 
/*N*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_LIBRARY );
/*N*/             pValues[ 1 ].Value <<= aLib;
/*N*/ 
/*N*/             pValues[ 2 ].Name = OUSTRING::createFromAscii( PROP_MACRO_NAME );
/*N*/             pValues[ 2 ].Value <<= aMacro;
/*N*/ 
/*N*/             aEventData <<= aProperties;
/*N*/         }
/*N*/         else if ( pMacro->GetScriptType() == EXTENDED_STYPE )
/*N*/         {
/*?*/             SEQUENCE < PROPERTYVALUE > aProperties(2);
/*?*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*?*/ 
/*?*/             OUSTRING    aLib    = pMacro->GetLibName();
/*?*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*?*/ 
/*?*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*?*/             pValues[ 0 ].Value <<= aLib;
/*?*/ 
/*?*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_SCRIPT );
/*?*/             pValues[ 1 ].Value <<= aMacro;
/*?*/ 
/*?*/             aEventData <<= aProperties;
/*N*/ 		}
/*N*/         else if ( pMacro->GetScriptType() == JAVASCRIPT )
/*N*/         {
/*?*/             SEQUENCE < PROPERTYVALUE > aProperties(2);
/*?*/             PROPERTYVALUE  *pValues = aProperties.getArray();
/*?*/ 
/*?*/             OUSTRING    aMacro  = pMacro->GetMacName();
/*?*/ 
/*?*/             pValues[ 0 ].Name = OUSTRING::createFromAscii( PROP_EVENT_TYPE );
/*?*/             pValues[ 0 ].Value <<= ::rtl::OUString::createFromAscii(SVX_MACRO_LANGUAGE_JAVASCRIPT);
/*?*/ 
/*?*/             pValues[ 1 ].Name = OUSTRING::createFromAscii( PROP_MACRO_NAME );
/*?*/             pValues[ 1 ].Value <<= aMacro;
/*?*/ 
/*?*/             aEventData <<= aProperties;
/*N*/ 		}
/*N*/         else
/*N*/         {
/*N*/             DBG_ERRORFILE( "CreateEventData_Impl(): ScriptType not supported!");
/*N*/         }
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         SEQUENCE < PROPERTYVALUE > aProperties;
/*N*/         aEventData <<= aProperties;
/*N*/     }
/*N*/ 
/*N*/     return aEventData;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetPos_Impl( USHORT nId, sal_Bool &rFound )
/*N*/ {
/*N*/     rFound = sal_False;
/*N*/ 
/*N*/     if ( ! gp_Id_SortList->Count() )
/*N*/         return 0;
/*N*/ 
/*N*/     // use binary search to find the correct position
/*N*/     // in the list
/*N*/ 
/*N*/     int     nCompVal = 1;
/*N*/     long    nStart = 0;
/*N*/     long    nEnd = gp_Id_SortList->Count() - 1;
/*N*/     long    nMid;
/*N*/ 
/*N*/     EventNames_Impl* pMid;
/*N*/ 
/*N*/     rFound = sal_False;
/*N*/ 
/*N*/     while ( nCompVal && ( nStart <= nEnd ) )
/*N*/     {
/*N*/         nMid = ( nEnd - nStart ) / 2 + nStart;
/*N*/         pMid = gp_Id_SortList->GetObject( (USHORT) nMid );
/*N*/ 
/*N*/         nCompVal = pMid->mnId - nId;
/*N*/ 
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nStart = nMid + 1;
/*N*/         else
/*N*/             nEnd = nMid - 1;
/*N*/     }
/*N*/ 
/*N*/     if ( nCompVal == 0 )
/*N*/     {
/*N*/         rFound = sal_True;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nMid++;
/*N*/     }
/*N*/ 
/*N*/     return (USHORT) nMid;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetPos_Impl( const String& rName, sal_Bool &rFound )
/*N*/ {
/*N*/     rFound = sal_False;
/*N*/ 
/*N*/     if ( ! gp_Name_SortList->Count() )
/*N*/         return 0;
/*N*/ 
/*N*/     // use binary search to find the correct position
/*N*/     // in the list
/*N*/ 
/*N*/     int     nCompVal = 1;
/*N*/     long    nStart = 0;
/*N*/     long    nEnd = gp_Name_SortList->Count() - 1;
/*N*/     long    nMid;
/*N*/ 
/*N*/     EventNames_Impl* pMid;
/*N*/ 
/*N*/     rFound = sal_False;
/*N*/ 
/*N*/     while ( nCompVal && ( nStart <= nEnd ) )
/*N*/     {
/*N*/         nMid = ( nEnd - nStart ) / 2 + nStart;
/*N*/         pMid = gp_Name_SortList->GetObject( (USHORT) nMid );
/*N*/ 
/*N*/         nCompVal = rName.CompareTo( pMid->maEventName );
/*N*/ 
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nStart = nMid + 1;
/*N*/         else
/*N*/             nEnd = nMid - 1;
/*N*/     }
/*N*/ 
/*N*/     if ( nCompVal == 0 )
/*N*/     {
/*N*/         rFound = sal_True;
/*N*/     }
/*N*/     else
/*N*/     {
/*N*/         if ( nCompVal < 0 )     // pMid < pData
/*N*/             nMid++;
/*N*/     }
/*N*/ 
/*N*/     return (USHORT) nMid;
/*N*/ }

//--------------------------------------------------------------------------------------------------------
/*N*/ OUSTRING SfxEventConfiguration::GetEventName_Impl( ULONG nID )
/*N*/ {
/*N*/     OUSTRING    aRet;
/*N*/ 
/*N*/     if ( gp_Id_SortList )
/*N*/     {
/*N*/         sal_Bool    bFound;
/*N*/         ULONG       nPos = GetPos_Impl( (USHORT) nID, bFound );
/*N*/ 
/*N*/         if ( bFound )
/*N*/         {
/*N*/             EventNames_Impl *pData = gp_Id_SortList->GetObject( nPos );
/*N*/             aRet = pData->maEventName;
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/     return aRet;
/*N*/ }

//--------------------------------------------------------------------------------------------------------
/*N*/ ULONG SfxEventConfiguration::GetEventId_Impl( const OUSTRING& rEventName )
/*N*/ {
/*N*/     ULONG nRet = 0;
/*N*/ 
/*N*/     if ( gp_Name_SortList )
/*N*/     {
/*N*/         sal_Bool    bFound;
/*N*/         ULONG       nPos = GetPos_Impl( rEventName, bFound );
/*N*/ 
/*N*/         if ( bFound )
/*N*/         {
/*N*/             EventNames_Impl *pData = gp_Name_SortList->GetObject( nPos );
/*N*/             nRet = pData->mnId;
/*N*/         }
/*N*/     }
/*N*/ 
/*N*/     return nRet;
/*N*/ }

// -------------------------------------------------------------------------------------------------------
/*N*/ void SfxEventConfiguration::RegisterEvent( USHORT nId,
/*N*/                                            const String& rUIName,
/*N*/                                            const String& rMacroName )
/*N*/ {
/*N*/     if ( ! gp_Id_SortList )
/*N*/     {
/*N*/         gp_Id_SortList = new SfxEventList_Impl;
/*N*/         gp_Name_SortList = new SfxEventList_Impl;
/*N*/     }
/*N*/ 
/*N*/     sal_Bool    bFound = sal_False;
/*N*/     ULONG       nPos = GetPos_Impl( nId, bFound );
/*N*/ 
/*N*/     if ( bFound )
/*N*/     {
/*?*/         DBG_ERRORFILE( "RegisterEvent: Event already registered?" );
/*?*/         return;
/*N*/     }
/*N*/ 
/*N*/     EventNames_Impl *pData;
/*N*/ 
/*N*/     pData = new EventNames_Impl( nId, rMacroName, rUIName );
/*N*/     gp_Id_SortList->Insert( pData, nPos );
/*N*/ 
/*N*/     nPos = GetPos_Impl( rMacroName, bFound );
/*N*/     DBG_ASSERT( !bFound, "RegisterEvent: Name in List, but ID not?" );
/*N*/ 
/*N*/     gp_Name_SortList->Insert( pData, nPos );
/*N*/ 
/*N*/     SFX_APP()->GetEventConfig()->RegisterEvent( nId, rUIName );
/*N*/ }

/*N*/ BOOL SfxEventConfiguration::Import( SvStream& rInStream, SvStream* pOutStream, SfxObjectShell* pDoc )
/*N*/ {
/*N*/     if ( pDoc )
/*N*/     {
/*N*/         // load events, they are automatically propagated to the document
/*N*/         DBG_ASSERT( !pOutStream, "DocEventConfig must not be converted!" );
/*N*/         SfxEventConfigItem_Impl* pCfg = pDoc->GetEventConfig_Impl( TRUE );
/*N*/ 		if ( pCfg )
/*N*/ 			return ( pCfg->Load( rInStream ) == SfxConfigItem::ERR_OK );
/*N*/ 		DBG_ERROR("Couldn't create EventConfiguration!");
/*N*/ 		return FALSE;
/*N*/     }
/*?*/ 
/*?*/     DBG_ERROR( "No OutStream!" );
/*?*/     return FALSE;
/*N*/ }



}
