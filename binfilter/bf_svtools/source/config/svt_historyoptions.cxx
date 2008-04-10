/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svt_historyoptions.cxx,v $
 * $Revision: 1.3 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove

#ifndef GCC
#endif

//_________________________________________________________________________________________________________________
//	includes
//_________________________________________________________________________________________________________________

#include <bf_svtools/historyoptions.hxx>

#ifndef _UTL_CONFIGMGR_HXX_
#include <unotools/configmgr.hxx>
#endif

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_ANY_HXX_
#include <com/sun/star/uno/Any.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_SEQUENCE_HXX_
#include <com/sun/star/uno/Sequence.hxx>
#endif

#ifndef __SGI_STL_DEQUE
#include <deque>
#endif

#ifndef __SGI_STL_ALGORITHM
#include <algorithm>
#endif

#include <rtl/logfile.hxx>
#include "itemholder1.hxx"

//_________________________________________________________________________________________________________________
//	namespaces
//_________________________________________________________________________________________________________________

using namespace ::std					;
using namespace ::utl					;
using namespace ::rtl					;
using namespace ::osl					;
using namespace ::com::sun::star::uno	;
using namespace ::com::sun::star::beans	;

namespace binfilter
{

//_________________________________________________________________________________________________________________
//	const
//_________________________________________________________________________________________________________________

#define	ROOTNODE_HISTORY						OUString(RTL_CONSTASCII_USTRINGPARAM("Office.Common/History/"	))

#define DEFAULT_PICKLISTSIZE                    4
#define	DEFAULT_HISTORYSIZE						10
#define DEFAULT_HELPBOOKMARKSIZE                100

#define	PATHDELIMITER							OUString(RTL_CONSTASCII_USTRINGPARAM("/"						))

#define PROPERTYNAME_PICKLISTSIZE               OUString(RTL_CONSTASCII_USTRINGPARAM("PickListSize"             ))
#define	PROPERTYNAME_HISTORYSIZE				OUString(RTL_CONSTASCII_USTRINGPARAM("Size"						))
#define PROPERTYNAME_HELPBOOKMARKSIZE           OUString(RTL_CONSTASCII_USTRINGPARAM("HelpBookmarkSize"         ))

#define PROPERTYNAME_PICKLIST                   OUString(RTL_CONSTASCII_USTRINGPARAM("PickList"                 ))
#define	PROPERTYNAME_HISTORY			   		OUString(RTL_CONSTASCII_USTRINGPARAM("List"						))
#define PROPERTYNAME_HELPBOOKMARKS              OUString(RTL_CONSTASCII_USTRINGPARAM("HelpBookmarks"            ))

#define PROPERTYNAME_HISTORYITEM_URL            HISTORY_PROPERTYNAME_URL
#define	PROPERTYNAME_HISTORYITEM_FILTER			HISTORY_PROPERTYNAME_FILTER
#define	PROPERTYNAME_HISTORYITEM_TITLE			HISTORY_PROPERTYNAME_TITLE
#define	PROPERTYNAME_HISTORYITEM_PASSWORD		HISTORY_PROPERTYNAME_PASSWORD

#define OFFSET_URL                              0
#define	OFFSET_FILTER							1
#define	OFFSET_TITLE							2
#define	OFFSET_PASSWORD							3

#define PROPERTYHANDLE_PICKLISTSIZE             0
#define PROPERTYHANDLE_HISTORYSIZE              1
#define PROPERTYHANDLE_HELPBOOKMARKSIZE         2

#define FIXPROPERTYCOUNT                        3 // counts PROPERYHANDLE_PICKLISTSIZE ... PROPERTYHANDLE_HELPBOOKMARKSIZE!

#define	FIXP									OUString(RTL_CONSTASCII_USTRINGPARAM("p"						))
#define	FIXH									OUString(RTL_CONSTASCII_USTRINGPARAM("h"						))
#define FIXB                                    OUString(RTL_CONSTASCII_USTRINGPARAM("b"                        ))

//_________________________________________________________________________________________________________________
//	private declarations!
//_________________________________________________________________________________________________________________

struct IMPL_THistoryItem
{
    IMPL_THistoryItem()
    {
    }

    IMPL_THistoryItem(	const	OUString&	sNewURL			,
                        const	OUString&	sNewFilter		,
                        const	OUString&	sNewTitle		,
                        const	OUString&	sNewPassword	)
    {
        sURL		= sNewURL		;
        sFilter		= sNewFilter	;
        sTitle		= sNewTitle		;
        sPassword	= sNewPassword	;
    }

    sal_Bool operator==( const OUString& sSearchedURL )
    {
        return( sURL == sSearchedURL );
    }

    OUString	sURL		;
    OUString	sFilter		;
    OUString	sTitle		;
    OUString	sPassword	;
};

class SvtHistoryOptions_Impl : public ConfigItem
{
    //-------------------------------------------------------------------------------------------------------------
    //	public methods
    //-------------------------------------------------------------------------------------------------------------

    public:

        //---------------------------------------------------------------------------------------------------------
        //	constructor / destructor
        //---------------------------------------------------------------------------------------------------------

         SvtHistoryOptions_Impl();
        ~SvtHistoryOptions_Impl();

        //---------------------------------------------------------------------------------------------------------
        //	overloaded methods of baseclass
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		called for notify of configmanager
            @descr		These method is called from the ConfigManager before application ends or from the
                         PropertyChangeListener if the sub tree broadcasts changes. You must update your
                        internal values.

            @seealso	baseclass ConfigItem

            @param		"seqPropertyNames" is the list of properties which should be updated.
            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

        virtual void Notify( const Sequence< OUString >& seqPropertyNames );

        /*-****************************************************************************************************//**
            @short		write changes to configuration
            @descr		These method writes the changed values into the sub tree
                        and should always called in our destructor to guarantee consistency of config data.

            @seealso	baseclass ConfigItem

            @param		-
            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

        virtual void Commit();

        //---------------------------------------------------------------------------------------------------------
        //	public interface
        //---------------------------------------------------------------------------------------------------------

        /*-****************************************************************************************************//**
            @short		base implementation of public interface for "SvtHistoryOptions"!
            @descr		These class is used as static member of "SvtHistoryOptions" ...
                        => The code exist only for one time and isn't duplicated for every instance!

            @seealso	-

            @param		-
            @return		-

            @onerror	-
        *//*-*****************************************************************************************************/

        sal_uInt32                              GetSize     (           EHistoryType    eHistory    );
        void									SetSize		(			EHistoryType	eHistory	,
                                                                        sal_uInt32      nSize       );
        void                                    Clear       (           EHistoryType    eHistory    );
        Sequence< Sequence< PropertyValue > >   GetList     (           EHistoryType    eHistory    );
        void									AppendItem	(			EHistoryType	eHistory	,
                                                                const	OUString&		sURL		,
                                                                const	OUString&		sFilter		,
                                                                const	OUString&		sTitle		,
                                                                const   OUString&       sPassword   );

    //-------------------------------------------------------------------------------------------------------------
    //	private methods
    //-------------------------------------------------------------------------------------------------------------

    private:

        /*-****************************************************************************************************//**
            @short		return list of key names of ouer configuration management which represent oue module tree
            @descr		These methods return the current list of key names! We need it to get needed values from our
                        configuration management and support dynamical history lists!

            @seealso	-

            @param		-
            @return		A list of configuration key names is returned.

            @onerror	-
        *//*-*****************************************************************************************************/

        Sequence< OUString > impl_GetPropertyNames( sal_uInt32& nPicklistCount     ,
                                                    sal_uInt32& nHistoryCount      ,
                                                    sal_uInt32& nHelpBookmarkCount );

        /*-****************************************************************************************************//**
            @short		convert routine
            @descr		Intern we hold ouer values in a deque. Sometimes we need his content as a return sequence.
                        Then we must convert ouer internal format to extern.
                        That is the reason for these method!

            @seealso	-

            @param		"aList" list in deque format.
            @return		A list which right format is returned.

            @onerror	-
        *//*-*****************************************************************************************************/

        Sequence< Sequence< PropertyValue > > impl_GetSequenceFromList( const deque< IMPL_THistoryItem >& aList );

        /*-****************************************************************************************************//**
            @short      helper
            @descr      Some code is the same for different internal history list. So we can get a pointer as an access to
                        right internal member list by calling this method with right enum value.
                        Returned pointer can be used to implement some functionality on this list then.
                        By the way - we return max size of these list too ...

            @seealso    using!

            @param      "eType" describe, which list should be returned as pointer
            @return     A pointer to one of our internal member lists.

            @onerror    We return NULL.
        *//*-*****************************************************************************************************/

        void impl_GetListInfo( EHistoryType                 eType     ,
                               deque< IMPL_THistoryItem >** ppList    ,
                               sal_uInt32**                 ppMaxSize );

    //-------------------------------------------------------------------------------------------------------------
    //	private member
    //-------------------------------------------------------------------------------------------------------------

    private:

        deque< IMPL_THistoryItem >  m_aPicklist         ;
        sal_uInt32                  m_nPicklistSize     ;
        deque< IMPL_THistoryItem >  m_aHistory          ;
        sal_uInt32                  m_nHistorySize      ;
        deque< IMPL_THistoryItem >  m_aHelpBookmarks    ;
        sal_uInt32                  m_nHelpBookmarkSize ;
};

//_________________________________________________________________________________________________________________
//	definitions
//_________________________________________________________________________________________________________________

//*****************************************************************************************************************
//	constructor
//*****************************************************************************************************************
SvtHistoryOptions_Impl::SvtHistoryOptions_Impl()
    // Init baseclasses first
    :	ConfigItem			( ROOTNODE_HISTORY		)
    // Init member then...
{
    // Use our list snapshot of configuration keys to get his values.
    // See impl_GetPropertyNames() for further informations.
    sal_uInt32 nPicklistCount       = 0;
    sal_uInt32 nHistoryCount        = 0;
    sal_uInt32 nHelpBookmarkCount   = 0;
    Sequence< OUString >    seqNames    = impl_GetPropertyNames ( nPicklistCount     ,
                                                                  nHistoryCount      ,
                                                                  nHelpBookmarkCount );
    Sequence< Any >         seqValues   = GetProperties         ( seqNames           );

    // Safe impossible cases.
    // We need values from ALL configuration keys.
    // Follow assignment use order of values in relation to our list of key names!
    DBG_ASSERT( !(seqNames.getLength()!=seqValues.getLength()), "SvtHistoryOptions_Impl::SvtHistoryOptions_Impl()\nI miss some values of configuration keys!\n" );

    // Copy values from list in right order to ouer internal member.
    // Attention: List for names and values have an internal construction pattern!
    // zB:
    //		Name						Value
    //		/Picklist/Size				2
    //		/History/Size				3
    //		/Picklist/List/1/URL		"file://a"
    //		/Picklist/List/1/Filter		"writer-..."
    //		/Picklist/List/1/Title		"Test1"
    //		/Picklist/List/1/Password	"lysemyf1"
    //		/Picklist/List/2/URL		"file://b"
    //		/Picklist/List/2/Filter		"calc-..."
    //		/Picklist/List/2/Title		"Test2"
    //		/Picklist/List/2/Password	"lysemyf2"
    //		/History/List/2/URL			"http://blub"
    //		/History/List/2/Filter		"html-..."
    //		/History/List/2/Title		"blub"
    //		/History/List/2/Password	"xxx"
    //		... and so on ...

    // First we must read sizes of ouer history lists => the first to values.
    // We need these informations to work correctly with follow keys!
    seqValues[PROPERTYHANDLE_PICKLISTSIZE    ] >>= m_nPicklistSize     ;
    seqValues[PROPERTYHANDLE_HISTORYSIZE     ] >>= m_nHistorySize      ;
    seqValues[PROPERTYHANDLE_HELPBOOKMARKSIZE] >>= m_nHelpBookmarkSize ;

    // Safe impossible cases.
    // I think a size of 0 isn't relay meaningful.
    if( m_nPicklistSize < 1 )
    {
        m_nPicklistSize = DEFAULT_PICKLISTSIZE;
        DBG_ASSERT( sal_False, "SvtHistoryOptions_Impl::SvtHistoryOptions_Impl()\nI think a picklist size of 0 isn't relay meaningful! Set new value to 4 entries.\n" );
    }
    if( m_nHistorySize < 1 )
    {
        m_nHistorySize = DEFAULT_HISTORYSIZE;
        DBG_ASSERT( sal_False, "SvtHistoryOptions_Impl::SvtHistoryOptions_Impl()\nI think a history size of 0 isn't relay meaningful! Set new value to 10 entries.\n" );
    }
    if( m_nHelpBookmarkSize < 1 )
    {
        m_nHelpBookmarkSize = DEFAULT_HELPBOOKMARKSIZE;
        DBG_ASSERT( sal_False, "SvtHistoryOptions_Impl::SvtHistoryOptions_Impl()\nI think a help bookmark size of 0 isn't relay meaningful! Set new value to 100 entries.\n" );
    }

    IMPL_THistoryItem aItem;
    sal_uInt32 nPosition = FIXPROPERTYCOUNT; // step over first three readed size values! but count begins at 0!
    // Get names/values for picklist.
    // 4 subkeys for every item!
    OUString sName;
    sal_uInt32 nItem;
    for( nItem=0; nItem<nPicklistCount; ++nItem )
    {
        seqValues[nPosition] >>= aItem.sURL			;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sFilter		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sTitle		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sPassword	;
        ++nPosition;
        m_aPicklist.push_back( aItem );
    }

    // Attention: Don't reset nPosition here!

    // Get names/values for picklist.
    // 4 subkeys for every item!
    for( nItem=0; nItem<nHistoryCount; ++nItem )
    {
        seqValues[nPosition] >>= aItem.sURL			;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sFilter		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sTitle		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sPassword	;
        ++nPosition;
        m_aHistory.push_back( aItem );
    }

    // Get names/values for help bookmarks.
    // 4 subkeys for every item!
    for( nItem=0; nItem<nHelpBookmarkCount; ++nItem )
    {
        seqValues[nPosition] >>= aItem.sURL			;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sFilter		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sTitle		;
        ++nPosition;
        seqValues[nPosition] >>= aItem.sPassword	;
        ++nPosition;
        m_aHelpBookmarks.push_back( aItem );
    }

/*TODO: Not used in the moment! see Notify() ...
    // Enable notification mechanism of ouer baseclass.
    // We need it to get information about changes outside these class on ouer used configuration keys!
    Sequence< OUString > seqNotifications( seqNames );
    sal_Int32 nNotifyCount = seqNames.getLength();
    seqNotifications.realloc( nNotifyCount+PROPERTYCOUNT_LISTNODES );
    seqNotification[nNotifyCount  ] = PROPERTYNAME_PICKLIST;
    seqNotification[nNotifyCount+1] = PROPERTYNAME_HISTORY ;
    EnableNotification( seqNotification );
*/
}

//*****************************************************************************************************************
//	destructor
//*****************************************************************************************************************
SvtHistoryOptions_Impl::~SvtHistoryOptions_Impl()
{
    // We must save our current values .. if user forget it!
    if( IsModified() == sal_True )
    {
        Commit();
    }
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::Notify( const Sequence< OUString >& )
{
    DBG_ASSERT( sal_False, "SvtHistoryOptions_Impl::Notify()\nNot implemented yet! I don't know how I can handle a dynamical list of unknown properties ...\n" );
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::Commit()
{
    // First write fix properties.
    Sequence< OUString >    seqFixPropertyNames ( FIXPROPERTYCOUNT );
    Sequence< Any >         seqFixPropertyValues( FIXPROPERTYCOUNT );
    seqFixPropertyNames [PROPERTYHANDLE_PICKLISTSIZE    ]   = PROPERTYNAME_PICKLISTSIZE     ;
    seqFixPropertyNames [PROPERTYHANDLE_HISTORYSIZE     ]   = PROPERTYNAME_HISTORYSIZE      ;
    seqFixPropertyNames [PROPERTYHANDLE_HELPBOOKMARKSIZE]   = PROPERTYNAME_HELPBOOKMARKSIZE ;
    seqFixPropertyValues[PROPERTYHANDLE_PICKLISTSIZE    ] <<= m_nPicklistSize               ;
    seqFixPropertyValues[PROPERTYHANDLE_HISTORYSIZE     ] <<= m_nHistorySize                ;
    seqFixPropertyValues[PROPERTYHANDLE_HELPBOOKMARKSIZE] <<= m_nHelpBookmarkSize           ;
    PutProperties( seqFixPropertyNames, seqFixPropertyValues );

    // Write set of dynamic properties then.
    ClearNodeSet( PROPERTYNAME_PICKLIST      );
    ClearNodeSet( PROPERTYNAME_HISTORY       );
    ClearNodeSet( PROPERTYNAME_HELPBOOKMARKS );

    IMPL_THistoryItem			aItem					;
    OUString					sNode					;
    Sequence< PropertyValue >	seqPropertyValues( 4 )	;

    // Copy picklist entries to save-list!
    sal_uInt32 nPicklistCount = m_aPicklist.size();
    sal_uInt32 nItem;
    for( nItem=0; nItem<nPicklistCount; ++nItem )
    {
        aItem	= m_aPicklist[nItem];
        sNode	= PROPERTYNAME_PICKLIST + PATHDELIMITER + FIXP + OUString::valueOf( (sal_Int32)nItem ) + PATHDELIMITER;
        seqPropertyValues[OFFSET_URL		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_URL		;
        seqPropertyValues[OFFSET_FILTER		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_FILTER		;
        seqPropertyValues[OFFSET_TITLE		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_TITLE		;
        seqPropertyValues[OFFSET_PASSWORD	].Name  =	sNode + PROPERTYNAME_HISTORYITEM_PASSWORD	;
        seqPropertyValues[OFFSET_URL		].Value <<=	aItem.sURL									;
        seqPropertyValues[OFFSET_FILTER		].Value <<=	aItem.sFilter								;
        seqPropertyValues[OFFSET_TITLE		].Value <<=	aItem.sTitle								;
        seqPropertyValues[OFFSET_PASSWORD	].Value <<=	aItem.sPassword								;

        SetSetProperties( PROPERTYNAME_PICKLIST, seqPropertyValues );
    }

    // Copy URL-list entries to save-list!
    sal_uInt32 nHistoryCount = m_aHistory.size();
    for( nItem=0; nItem<nHistoryCount; ++nItem )
    {
        aItem	= m_aHistory[nItem];
        sNode	= PROPERTYNAME_HISTORY + PATHDELIMITER + FIXH + OUString::valueOf( (sal_Int32)nItem ) + PATHDELIMITER;
        seqPropertyValues[OFFSET_URL		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_URL		;
        seqPropertyValues[OFFSET_FILTER		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_FILTER		;
        seqPropertyValues[OFFSET_TITLE		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_TITLE		;
        seqPropertyValues[OFFSET_PASSWORD	].Name  =	sNode + PROPERTYNAME_HISTORYITEM_PASSWORD	;
        seqPropertyValues[OFFSET_URL		].Value <<=	aItem.sURL									;
        seqPropertyValues[OFFSET_FILTER		].Value <<=	aItem.sFilter								;
        seqPropertyValues[OFFSET_TITLE		].Value <<=	aItem.sTitle								;
        seqPropertyValues[OFFSET_PASSWORD	].Value <<=	aItem.sPassword								;

        SetSetProperties( PROPERTYNAME_HISTORY, seqPropertyValues );
    }

    // Copy HelpBookmark-list entries to save-list!
    sal_uInt32 nHelpBookmarkCount = m_aHelpBookmarks.size();
    for( nItem=0; nItem<nHelpBookmarkCount; ++nItem )
    {
        aItem   = m_aHelpBookmarks[nItem];
        sNode   = PROPERTYNAME_HELPBOOKMARKS + PATHDELIMITER + FIXB + OUString::valueOf( (sal_Int32)nItem ) + PATHDELIMITER;
        seqPropertyValues[OFFSET_URL		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_URL		;
        seqPropertyValues[OFFSET_FILTER		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_FILTER		;
        seqPropertyValues[OFFSET_TITLE		].Name  =	sNode + PROPERTYNAME_HISTORYITEM_TITLE		;
        seqPropertyValues[OFFSET_PASSWORD	].Name  =	sNode + PROPERTYNAME_HISTORYITEM_PASSWORD	;
        seqPropertyValues[OFFSET_URL		].Value <<=	aItem.sURL									;
        seqPropertyValues[OFFSET_FILTER		].Value <<=	aItem.sFilter								;
        seqPropertyValues[OFFSET_TITLE		].Value <<=	aItem.sTitle								;
        seqPropertyValues[OFFSET_PASSWORD	].Value <<=	aItem.sPassword								;

        SetSetProperties( PROPERTYNAME_HELPBOOKMARKS, seqPropertyValues );
    }
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
sal_uInt32 SvtHistoryOptions_Impl::GetSize( EHistoryType eHistory )
{
    // Attention: We return the max. size of our internal lists - That is the capacity not the size!

    // Set default return value if method failed!
    sal_uInt32 nSize = 0;
    // Get size of searched history list.
    switch( eHistory )
    {
        case ePICKLIST      :   nSize = m_nPicklistSize;
                                break;
        case eHISTORY       :   nSize = m_nHistorySize;
                                break;
        case eHELPBOOKMARKS :   nSize = m_nHistorySize;
                                break;
    }
    // Return result of operation.
    return nSize;
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::SetSize( EHistoryType eHistory, sal_uInt32 nSize )
{
    // Attention: We set the max. size of our internal lists - That is the capacity not the size!
    // Set size of searched history list.
    deque< IMPL_THistoryItem >* pList    = NULL;
    sal_uInt32*                 pMaxSize = NULL;
    impl_GetListInfo( eHistory, &pList, &pMaxSize );

    if( pList!=NULL && pMaxSize!=NULL )
    {
        // If to much items in current list ...
        // truncate the oldest items BEFORE you set the new one.
        if( nSize<pList->size() )
        {
            sal_uInt32 nOldItemCount = pList->size()-nSize;
            while( nOldItemCount>0 )
            {
                pList->pop_back();
                --nOldItemCount;
            }
        }
        *pMaxSize = nSize;
        Commit();
    }
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::Clear( EHistoryType eHistory )
{
    // Clear specified history list.
    deque< IMPL_THistoryItem >* pList    = NULL;
    sal_uInt32*                 pMaxSize = NULL;
    impl_GetListInfo( eHistory, &pList, &pMaxSize );

    if( pList!=NULL && pMaxSize!=NULL )
    {
        pList->clear();
        Commit();
    }
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
Sequence< Sequence< PropertyValue > > SvtHistoryOptions_Impl::GetList( EHistoryType eHistory )
{
    // Set default return value.
    Sequence< Sequence< PropertyValue > > seqReturn;

    deque< IMPL_THistoryItem >* pList    = NULL;
    sal_uInt32*                 pMaxSize = NULL;
    impl_GetListInfo( eHistory, &pList, &pMaxSize );

    if( pList!=NULL && pMaxSize!=NULL )
        seqReturn = impl_GetSequenceFromList( *pList );

    return seqReturn;
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::AppendItem(			EHistoryType	eHistory	,
                                            const	OUString&		sURL		,
                                            const	OUString&		sFilter		,
                                            const	OUString&		sTitle		,
                                            const	OUString&		sPassword	)
{
    // create new list item with given values
    IMPL_THistoryItem aItem( sURL, sFilter, sTitle, sPassword );

    // search for right internal list by given enum
    deque< IMPL_THistoryItem >* pList    = NULL;
    sal_uInt32*                 pMaxSize = NULL;
    impl_GetListInfo( eHistory, &pList, &pMaxSize );

    // work on these list
    if( pList!=NULL && pMaxSize!=NULL )
    {
        deque< IMPL_THistoryItem >::iterator pItem = ::std::find( pList->begin(), pList->end(), sURL );
        if( pItem == pList->end() )
        {
            // If current list full ... delete the oldest item.
            if( pList->size() >= *pMaxSize )
                pList->pop_back();
            // Append new item to list.
            pList->push_front( aItem );
            Commit();
        }
        else if (pItem != pList->begin())
        {
            IMPL_THistoryItem aTempItem = *pItem;
            pList->erase(pItem);
            pList->push_front(aTempItem);
            Commit();
        }
    }
}

//*****************************************************************************************************************
//	private method
//*****************************************************************************************************************
Sequence< OUString > SvtHistoryOptions_Impl::impl_GetPropertyNames( sal_uInt32& nPicklistCount     ,
                                                                    sal_uInt32& nHistoryCount      ,
                                                                    sal_uInt32& nHelpBookmarkCount )
{
    /* TODO
        Index basiert einf�gen !!! => p0 => 0 p1 => 1 ...
    */

    // First get ALL names of current existing list items in configuration!
    Sequence< OUString > seqPicklistItems     = GetNodeNames( PROPERTYNAME_PICKLIST      );
    Sequence< OUString > seqHistoryItems      = GetNodeNames( PROPERTYNAME_HISTORY       );
    Sequence< OUString > seqHelpBookmarkItems = GetNodeNames( PROPERTYNAME_HELPBOOKMARKS );

    // Get information about list counts ...
    nPicklistCount      = seqPicklistItems.getLength    ();
    nHistoryCount       = seqHistoryItems.getLength     ();
    nHelpBookmarkCount  = seqHelpBookmarkItems.getLength();
    // ... and create a property list with right size! (+2...see fix properties below!)
    Sequence< OUString > seqProperties( FIXPROPERTYCOUNT       +
                                        (nPicklistCount    *4) +
                                        (nHistoryCount     *4) +
                                        (nHelpBookmarkCount*4)   );

    // Add names of fix properties to list.
    seqProperties[PROPERTYHANDLE_PICKLISTSIZE    ]  =   PROPERTYNAME_PICKLISTSIZE     ;
    seqProperties[PROPERTYHANDLE_HISTORYSIZE     ]  =   PROPERTYNAME_HISTORYSIZE      ;
    seqProperties[PROPERTYHANDLE_HELPBOOKMARKSIZE]  =   PROPERTYNAME_HELPBOOKMARKSIZE ;

    sal_uInt32 nPosition = FIXPROPERTYCOUNT; // step over three fix properties for sizes! but count begins at 0!
    // Add names for picklist to list.
    // 4 subkeys for every item!
    // nPosition is the start point of an history item, nItem an index into right list of node names!
    sal_uInt32 nItem;
    for( nItem=0; nItem<nPicklistCount; ++nItem )
    {
        seqProperties[nPosition] = PROPERTYNAME_PICKLIST + PATHDELIMITER + seqPicklistItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_URL		;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_PICKLIST + PATHDELIMITER + seqPicklistItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_FILTER	;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_PICKLIST + PATHDELIMITER + seqPicklistItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_TITLE     ;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_PICKLIST + PATHDELIMITER + seqPicklistItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_PASSWORD	;
        ++nPosition;
    }

    // Attention: Don't reset nPosition here!

    // Add names for URL-list to list.
    // 4 subkeys for every item!
    // nPosition is the start point of an history item, nItem an index into right list of node names!
    for( nItem=0; nItem<nHistoryCount; ++nItem )
    {
        seqProperties[nPosition] = PROPERTYNAME_HISTORY + PATHDELIMITER + seqHistoryItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_URL         ;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HISTORY + PATHDELIMITER + seqHistoryItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_FILTER		;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HISTORY + PATHDELIMITER + seqHistoryItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_TITLE		;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HISTORY + PATHDELIMITER + seqHistoryItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_PASSWORD	;
        ++nPosition;
    }

    // Attention: Don't reset nPosition here!

    // Add names for HelpBookmark-list to list.
    // 4 subkeys for every item!
    // nPosition is the start point of an bokmark item, nItem an index into right list of node names!
    for( nItem=0; nItem<nHelpBookmarkCount; ++nItem )
    {
        seqProperties[nPosition] = PROPERTYNAME_HELPBOOKMARKS + PATHDELIMITER + seqHelpBookmarkItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_URL         ;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HELPBOOKMARKS + PATHDELIMITER + seqHelpBookmarkItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_FILTER      ;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HELPBOOKMARKS + PATHDELIMITER + seqHelpBookmarkItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_TITLE       ;
        ++nPosition;
        seqProperties[nPosition] = PROPERTYNAME_HELPBOOKMARKS + PATHDELIMITER + seqHelpBookmarkItems[nItem] + PATHDELIMITER + PROPERTYNAME_HISTORYITEM_PASSWORD    ;
        ++nPosition;
    }

    // Return result.
    return seqProperties;
}

//*****************************************************************************************************************
//	private method
//*****************************************************************************************************************
Sequence< Sequence< PropertyValue > > SvtHistoryOptions_Impl::impl_GetSequenceFromList( const deque< IMPL_THistoryItem >& aList )
{
    // Initialize return sequence with right size.
    sal_uInt32 nCount = aList.size();
    Sequence< Sequence< PropertyValue > >	seqResult( nCount );
    Sequence< PropertyValue >				seqProperties( 4 );
    // Copy items from given to return list.
    for( sal_uInt32 nItem=0; nItem<nCount; ++nItem )
    {
        seqProperties[OFFSET_URL		].Name  =	HISTORY_PROPERTYNAME_URL		;
        seqProperties[OFFSET_FILTER		].Name  =	HISTORY_PROPERTYNAME_FILTER		;
        seqProperties[OFFSET_TITLE		].Name  =	HISTORY_PROPERTYNAME_TITLE		;
        seqProperties[OFFSET_PASSWORD	].Name  =	HISTORY_PROPERTYNAME_PASSWORD	;
        seqProperties[OFFSET_URL		].Value <<=	aList[nItem].sURL				;
        seqProperties[OFFSET_FILTER		].Value <<=	aList[nItem].sFilter			;
        seqProperties[OFFSET_TITLE		].Value <<=	aList[nItem].sTitle				;
        seqProperties[OFFSET_PASSWORD	].Value <<=	aList[nItem].sPassword			;
        seqResult[nItem] = seqProperties;
    }
    return seqResult;
}

//*****************************************************************************************************************
//	private method
//*****************************************************************************************************************
void SvtHistoryOptions_Impl::impl_GetListInfo( EHistoryType                 eType     ,
                                               deque< IMPL_THistoryItem >** ppList    ,
                                               sal_uInt32**                 ppMaxSize )
{
    *ppList    = NULL ;
    *ppMaxSize = NULL ;
    switch( eType )
    {
        case ePICKLIST      :   {
                                    *ppList    = &m_aPicklist    ;
                                    *ppMaxSize = &m_nPicklistSize;
                                }
                                break;
        case eHISTORY       :   {
                                    *ppList    = &m_aHistory    ;
                                    *ppMaxSize = &m_nHistorySize;
                                }
                                break;
        case eHELPBOOKMARKS :   {
                                    *ppList    = &m_aHelpBookmarks   ;
                                    *ppMaxSize = &m_nHelpBookmarkSize;
                                }
                                break;
    }
}

//*****************************************************************************************************************
//	initialize static member
//	DON'T DO IT IN YOUR HEADER!
//	see definition for further informations
//*****************************************************************************************************************
SvtHistoryOptions_Impl*		SvtHistoryOptions::m_pDataContainer	= NULL	;
sal_Int32					SvtHistoryOptions::m_nRefCount		= 0		;

//*****************************************************************************************************************
//	constructor
//*****************************************************************************************************************
SvtHistoryOptions::SvtHistoryOptions()
{
    // Global access, must be guarded (multithreading!).
    MutexGuard aGuard( GetOwnStaticMutex() );
    // Increase ouer refcount ...
    ++m_nRefCount;
    // ... and initialize ouer data container only if it not already exist!
    if( m_pDataContainer == NULL )
    {
        RTL_LOGFILE_CONTEXT(aLog, "svtools ( ??? ) ::SvtHistoryOptions_Impl::ctor()");
        m_pDataContainer = new SvtHistoryOptions_Impl;
        
        ItemHolder1::holdConfigItem(E_HISTORYOPTIONS);
    }
}

//*****************************************************************************************************************
//	destructor
//*****************************************************************************************************************
SvtHistoryOptions::~SvtHistoryOptions()
{
    // Global access, must be guarded (multithreading!)
    MutexGuard aGuard( GetOwnStaticMutex() );
    // Decrease ouer refcount.
    --m_nRefCount;
    // If last instance was deleted ...
    // we must destroy ouer static data container!
    if( m_nRefCount <= 0 )
    {
        delete m_pDataContainer;
        m_pDataContainer = NULL;
    }
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
sal_uInt32 SvtHistoryOptions::GetSize( EHistoryType eHistory ) const
{
    MutexGuard aGuard( GetOwnStaticMutex() );
    return m_pDataContainer->GetSize( eHistory );
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions::SetSize( EHistoryType eHistory, sal_uInt32 nSize )
{
    MutexGuard aGuard( GetOwnStaticMutex() );
    m_pDataContainer->SetSize( eHistory, nSize );
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions::Clear( EHistoryType eHistory )
{
    MutexGuard aGuard( GetOwnStaticMutex() );
    m_pDataContainer->Clear( eHistory );
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
Sequence< Sequence< PropertyValue > > SvtHistoryOptions::GetList( EHistoryType eHistory ) const
{
    MutexGuard aGuard( GetOwnStaticMutex() );
    return m_pDataContainer->GetList( eHistory );
}

//*****************************************************************************************************************
//	public method
//*****************************************************************************************************************
void SvtHistoryOptions::AppendItem(			EHistoryType	eHistory	,
                                    const	OUString&		sURL		,
                                    const	OUString&		sFilter		,
                                    const	OUString&		sTitle		,
                                    const	OUString&		sPassword	)
{
    MutexGuard aGuard( GetOwnStaticMutex() );
    m_pDataContainer->AppendItem( eHistory, sURL, sFilter, sTitle, sPassword );
}

//*****************************************************************************************************************
//	private method
//*****************************************************************************************************************
Mutex& SvtHistoryOptions::GetOwnStaticMutex()
{
    // Initialize static mutex only for one time!
    static Mutex* pMutex = NULL;
    // If these method first called (Mutex not already exist!) ...
    if( pMutex == NULL )
    {
        // ... we must create a new one. Protect follow code with the global mutex -
        // It must be - we create a static variable!
        MutexGuard aGuard( Mutex::getGlobalMutex() );
        // We must check our pointer again - because it can be that another instance of ouer class will be fastr then these!
        if( pMutex == NULL )
        {
            // Create the new mutex and set it for return on static variable.
            static Mutex aMutex;
            pMutex = &aMutex;
        }
    }
    // Return new created or already existing mutex object.
    return *pMutex;
}
}
