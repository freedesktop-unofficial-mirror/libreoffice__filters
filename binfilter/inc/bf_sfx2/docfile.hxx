/*************************************************************************
 *
 *  $RCSfile: docfile.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: obo $ $Date: 2005-07-18 11:50:00 $
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
#ifndef _SFXDOCFILE_HXX
#define _SFXDOCFILE_HXX

#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XMULTISERVICEFACTORY_HPP_
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#endif
#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCONTENT_HPP_
#include <com/sun/star/ucb/XContent.hpp>
#endif
#ifndef _COM_SUN_STAR_UCB_XCOMMANDENVIRONMENT_HPP_
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#endif
#ifndef _COM_SUN_STAR_TASK_XINTERACTIONHANDLER_HPP_
#include <com/sun/star/task/XInteractionHandler.hpp>
#endif
#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif
#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif
#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _LIST_HXX //autogen
#include <tools/list.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif

#include <svtools/cancel.hxx>
#include <cppuhelper/weak.hxx>

#include <bf_sfx2/sfxuno.hxx>
#include <bf_sfx2/docinf.hxx>
class SvKeyValueIterator;
class INetURLObject;
class Timer;
class SfxItemSet;
class DateTime;
class SvStringsDtor;
class SvEaMgr;
namespace binfilter {

class SfxObjectFactory;
class SfxFilter;
class SfxMedium_Impl;
class SfxObjectShell;
class SfxFrame;
class LoadEnvironment_Impl;

class SfxLoadEnvironment;

#define SFX_TFPRIO_SYNCHRON                        0
#define SFX_TFPRIO_DOC                            10
#define SFX_TFPRIO_VISIBLE_LOWRES_GRAPHIC         20
#define SFX_TFPRIO_VISIBLE_HIGHRES_GRAPHIC        21
#define SFX_TFPRIO_PLUGINS                        40
#define SFX_TFPRIO_INVISIBLE_LOWRES_GRAPHIC       50
#define SFX_TFPRIO_INVISIBLE_HIGHRES_GRAPHIC      51
#define SFX_TFPRIO_DOWNLOADS                      60

#if _SOLAR__PRIVATE
#ifndef STRING_LIST
#define STRING_LIST
DECLARE_LIST( StringList, String* )//STRIP008 DECLARE_LIST( StringList, String* );
#endif
#endif

//____________________________________________________________________________________________________________________________________
//	defines for namespaces
//____________________________________________________________________________________________________________________________________

#define	OUSTRING					::rtl::OUString
#define	XMULTISERVICEFACTORY		::com::sun::star::lang::XMultiServiceFactory
#define	XSERVICEINFO				::com::sun::star::lang::XServiceInfo
#define	OWEAKOBJECT					::cppu::OWeakObject
#define	REFERENCE					::com::sun::star::uno::Reference
#define	XINTERFACE					::com::sun::star::uno::XInterface
#define	SEQUENCE					::com::sun::star::uno::Sequence
#define	EXCEPTION					::com::sun::star::uno::Exception
#define	RUNTIMEEXCEPTION			::com::sun::star::uno::RuntimeException
#define	ANY							::com::sun::star::uno::Any

class SfxPoolCancelManager	:	public SfxCancelManager	,
                                public SfxCancellable	,
                                public SfxListener		,
                                public SvRefBase
{
    SfxCancelManagerWeak 	wParent;

                            ~SfxPoolCancelManager();
public:
                            SfxPoolCancelManager( SfxCancelManager* pParent, const String& rName );
    virtual void 			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
    virtual void 			Cancel();
};

SV_DECL_IMPL_REF( SfxPoolCancelManager )

struct SfxVersionInfo
{
    String					aName;
    String					aComment;
    SfxStamp				aCreateStamp;

                            SfxVersionInfo();
                            SfxVersionInfo( const SfxVersionInfo& rInfo )
                            { *this = rInfo; }

    SfxVersionInfo& 		operator=( const SfxVersionInfo &rInfo )
                            {
                                aName = rInfo.aName;
                                aComment = rInfo.aComment;
                                aCreateStamp = rInfo.aCreateStamp;
                                return *this;
                            }
};
DECLARE_LIST( _SfxVersionTable, SfxVersionInfo* )
class SfxVersionTableDtor : public _SfxVersionTable
{
public:
                            SfxVersionTableDtor( const sal_uInt16 nInitSz=0, const sal_uInt16 nReSz=1 )
                                : _SfxVersionTable( nInitSz, nReSz )
                            {}

                            SfxVersionTableDtor( const SfxVersionTableDtor &rCpy )
                            { *this = rCpy; }

                            ~SfxVersionTableDtor()
                            { DelDtor(); }

//STRIP001 	SfxVersionTableDtor& 	operator=( const SfxVersionTableDtor &rCpy );
    void 					DelDtor();
    SvStream&				Read( SvStream & );
    SvStream&				Write( SvStream & ) const;
//STRIP001 	SvStringsDtor*			GetVersions() const;
};

class SfxMedium : public SvRefBase
{
    sal_uInt32          eError;
    sal_Bool            bDirect:1,
                        bRoot:1,
                        bSetFilter:1,
                        bTriedStorage;
    StreamMode          nStorOpenMode;
    INetURLObject*      pURLObj;
    String              aName;
    SvGlobalName        aFilterClass;
    SvStream*			pInStream;
    SvStream*           pOutStream;
    SvStorageRef        aStorage;
    const SfxFilter*	pFilter;
    SfxItemSet*			pSet;
    SfxMedium_Impl*		pImp;
    String           	aLogicName;
    String           	aLongName;
    sal_Bool            bRemote;

#if _SOLAR__PRIVATE
    void                SetIsRemote_Impl();
    void                CloseInStream_Impl();
    sal_Bool            CloseOutStream_Impl();
    DECL_STATIC_LINK( 	SfxMedium, UCBHdl_Impl, sal_uInt32 * );
#endif

public:

    SvCompatWeakHdl*    GetHdl();

                        SfxMedium();
                        SfxMedium( const String &rName,
                                   StreamMode nOpenMode,
                                   sal_Bool bDirect,
                                   const SfxFilter *pFilter = 0,
                                   SfxItemSet *pSet = 0 );
                        SfxMedium( SvStorage *pTheStorage, sal_Bool bRoot = sal_False );
                        SfxMedium( const SfxMedium &rMedium, sal_Bool bCreateTemporary = sal_False );
                        ~SfxMedium();

    void                UseInteractionHandler( BOOL );
    ::com::sun::star::uno::Reference< ::com::sun::star::task::XInteractionHandler >
                        GetInteractionHandler();

    void                SetLoadTargetFrame(SfxFrame* pFrame );
    SfxFrame*           GetLoadTargetFrame() const;
    void                CancelTransfers();

    void                SetReferer( const String& rRefer );
//STRIP001 	const String&       GetReferer( ) const;
    void                SetTransferPriority( sal_uInt16 nPrio );
//STRIP001 	sal_uInt16          GetTransferPriority() const;
    sal_Bool            Exists( sal_Bool bForceSession = sal_True );
    void                SetFilter( const SfxObjectFactory &rFact, const String & rFilter );
    void			    SetFilter(const SfxFilter *pFlt, sal_Bool bResetOrig = sal_False);
    const SfxFilter *   GetFilter() const { return pFilter; }
    const SfxFilter *   GetOrigFilter( sal_Bool bNotCurrent = sal_False ) const;
    const String&       GetOrigURL() const;
    SfxItemSet	*		GetItemSet() const;
//STRIP001 	void				SetItemSet(SfxItemSet *pSet);
    void                Close();
    void                ReOpen();
    const String&       GetName() const {return aLogicName;}
#if defined SINIX && defined GCC && defined C272
    const INetURLObject& GetURLObject();
#else
    const INetURLObject& GetURLObject() const;
#endif
    ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XContent > GetContent() const;
    const String&       GetPhysicalName() const;
//STRIP001 	void                SetTemporary( sal_Bool bTemp );
    sal_Bool            IsTemporary() const;
    sal_Bool            IsRemote();
    sal_Bool            IsOpen() const { return aStorage.Is() || pInStream; }
    void                StartDownload();
    void                DownLoad( const Link& aLink = Link());
    void                SetDoneLink( const Link& rLink );
    Link                GetDoneLink( ) const;
    void                SetDataAvailableLink( const Link& rLink );
    Link                GetDataAvailableLink( ) const;

    void                SetClassFilter( const SvGlobalName & rFilterClass );

    sal_uInt32          GetMIMEAndRedirect( String& );
    sal_uInt32          GetErrorCode() const;
    sal_uInt32          GetError() const
                        { return ERRCODE_TOERROR(GetErrorCode()); }
    sal_uInt32			GetLastStorageCreationState();

    void                SetError( sal_uInt32 nError ) { eError = nError; }

    void                CloseInStream();
    sal_Bool            CloseOutStream();

    sal_Bool            IsRoot() const { return bRoot; }
    void				CloseStorage();

    StreamMode			GetOpenMode() const { return nStorOpenMode; }
    void                SetOpenMode( StreamMode nStorOpen, sal_Bool bDirect, sal_Bool bDontClose = sal_False );
    sal_Bool			IsDirect() const { return bDirect? sal_True: sal_False; }

    SvStream*           GetInStream();
    SvStream*           GetOutStream();

     SvEaMgr*			GetEaMgr();

    sal_Bool            Commit();
    sal_Bool            TryStorage();
//STRIP001 	ErrCode				Unpack_Impl( const String& );
    sal_Bool            IsStorage();
    SvStorage*          GetStorage();
    SvStorage*          GetOutputStorage( BOOL bUCBStorage = FALSE );
    const SvGlobalName& GetClassFilter();
    void				ResetError();
    sal_Bool            UsesCache() const;
    void                SetUsesCache( sal_Bool );
//STRIP001 	sal_Bool            IsExpired() const;
//STRIP001 	void                SetName( const String& rName, sal_Bool bSetOrigURL = sal_False );
    void                SetDontCreateCancellable();
    sal_Bool			IsAllowedForExternalBrowser() const;
    long				GetFileVersion() const;

    const SfxVersionTableDtor* GetVersionList();
    sal_Bool			IsReadOnly();

    ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream >  GetInputStream();

    void				CreateTempFile();
    void				CreateTempFileNoCopy();
    void				TryToSwitchToRepairedTemp();

    void                SetLoadEnvironment( SfxLoadEnvironment* pEnv );
    SfxLoadEnvironment* GetLoadEnvironment() const;

    ::rtl::OUString		GetCharset();
//STRIP001 	void				SetCharset( ::rtl::OUString );
    const String&		GetBaseURL();

#if _SOLAR__PRIVATE
    ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream > GetInputStream_Impl();
    SvStorage*          GetStorage_Impl( BOOL bUCBStorage );
//STRIP001 	void                RefreshName_Impl();
//STRIP001 	sal_uInt16  		AddVersion_Impl( SfxVersionInfo& rVersion );
//STRIP001 	sal_Bool			TransferVersionList_Impl( SfxMedium& rMedium );
//STRIP001 	sal_Bool			SaveVersionList_Impl( sal_Bool bUseXML );
//STRIP001 	sal_Bool			RemoveVersion_Impl( const SfxVersionInfo& rVersion );
    SfxPoolCancelManager*   GetCancelManager_Impl() const;
    void                SetCancelManager_Impl( SfxPoolCancelManager* pMgr );

//STRIP001 	void                SetExpired_Impl( const DateTime& rDateTime );
    SvKeyValueIterator* GetHeaderAttributes_Impl();
//STRIP001 	const String&       GetPreRedirectedURL() const;
    void                SetOrigFilter_Impl( const SfxFilter* pFilter );
    void                SetLoadEnvironment_Impl( LoadEnvironment_Impl* pEnv );
    LoadEnvironment_Impl* GetLoadEnvironment_Impl() const;

    // Diese Protokolle liefern MIME Typen
    sal_Bool            SupportsMIME_Impl() const;

    void                Init_Impl();
    void                ForceSynchronStream_Impl( sal_Bool bSynchron );

    void                GetMedium_Impl();
    void                Transfer_Impl();
    void                CreateFileStream();
    void				SetUpdatePickList(sal_Bool);
    sal_Bool			IsUpdatePickList() const;

    void                SetStorage_Impl( SvStorage* pStor );
    void                SetLongName(const String &rName)
                        { aLongName = rName; }
    const String &      GetLongName() const { return aLongName; }
    ErrCode             CheckOpenMode_Impl( sal_Bool bSilent, sal_Bool bAllowRO = sal_True );
    sal_Bool			IsDownloadDone_Impl();
//STRIP001     sal_Bool            IsPreview_Impl();
    void				ClearBackup_Impl();
    void                Done_Impl( ErrCode );
    void                DataAvailable_Impl();
    void                Cancel_Impl();
    void                SetPhysicalName_Impl(const String& rName);
//STRIP001 	void				MoveTempTo_Impl( SfxMedium* pMedium );

//STRIP001 	void				DoBackup_Impl();
    void				DoInternalBackup_Impl( const ::ucb::Content& aOriginalContent );
    void 				DoInternalBackup_Impl( const ::ucb::Content& aOriginalContent,
                                                const String& aPrefix,
                                                const String& aExtension,
                                                const String& aDestDir );

    sal_Bool 			TransactedTransferForFS_Impl( const INetURLObject& aSource, 
                             const INetURLObject& aDest, 
                             const ::com::sun::star::uno::Reference< ::com::sun::star::ucb::XCommandEnvironment >& xComEnv );

#endif

    static SfxVersionTableDtor* GetVersionList( SvStorage* pStor );
};

SV_DECL_IMPL_REF( SfxMedium )
SV_DECL_COMPAT_WEAK( SfxMedium )

#ifndef SFXMEDIUM_LIST
#define SFXMEDIUM_LIST
DECLARE_LIST( SfxMediumList, SfxMedium* )//STRIP008 DECLARE_LIST( SfxMediumList, SfxMedium* );
#endif

}//end of namespace binfilter
#endif

