/*************************************************************************
 *
 *  $RCSfile: app.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-05-05 16:29:56 $
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
#ifndef _SFXAPP_HXX
#define _SFXAPP_HXX

#ifndef TD_NEWDESKTOP
#define TF_NEWDESKTOP 1
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

#if _SOLAR__PRIVATE
#ifndef _TIME_HXX //autogen
#include <tools/time.hxx>
#endif
#ifndef _SV_ACCEL_HXX //autogen
#include <vcl/accel.hxx>
#endif
#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#endif

#include <vcl/svapp.hxx>
#ifndef _SFXSMPLHINT_HXX //autogen
#include <svtools/smplhint.hxx>
#endif
#ifndef _SFXPOOLITEM_HXX //autogen
#include <svtools/poolitem.hxx>
#endif
#ifndef _ERRCODE_HXX //autogen
#include <tools/errcode.hxx>
#endif
#ifndef _REF_HXX //autogen
#include <tools/ref.hxx>
#endif
#ifdef ENABLE_INIMANAGER//MUSTINI
#include <svtools/iniman.hxx>
#endif

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX_
#include <com/sun/star/uno/Reference.hxx>
#endif
#ifndef _COM_SUN_STAR_SCRIPT_XLIBRARYCONTAINER_HPP_
#include <com/sun/star/script/XLibraryContainer.hpp>
#endif

// whatwever will be today's name for explorer/frameset-docs
#define SFX_DESKTOP_HELPFILE_NAME "desktop"

#include <bf_sfx2/shell.hxx>
class BasicManager;
class DdeService;
class ModalDialog;
class OutputDevice;
class KeyEvent;
class Point;
class Rectangle;
class SfxCancelManager;
class SfxHint;
class SfxItemSet;
class StarBASIC;
class SvPseudoObject;
class Menu;
class SvUShorts;
class Window;
class Config;
class INetURLObject;
class SvStringsDtor;
class SimpleResMgr;
namespace so3 {
class SvLinkSource;
};
namespace binfilter {

#define PLUG_BROWSEHACK     42

#define SFX_DEMOKIND_FULL      1
#define SFX_DEMOKIND_COMPACT   2
#define SFX_DEMOKIND_TRYBUY    3
#define SFX_DEMOKIND_DEMO      4
#define SFX_DEMOKIND_INVALID   5
#define SFX_DEMOKIND_OLDTRYBUY 6
#define SFX_DEMOKIND_RUNTIME   7

enum SfxDBNameConvert {INI2NATIONAL, NATIONAL2INI };

#define SFX_BASICLIB_ADDMODE_NORMAL 	0
#define SFX_BASICLIB_ADDMODE_REFERENCE 	1
#define SFX_BASICLIB_ADDMODE_EXTERNAL 	2

class ISfxTemplateCommon;
class TaskBar;
class GenLink;
class IntroWindow_Impl;
class PrinterDialog;
class SfxHelpPI;
class DropEvent;
class AppSettings;

struct SfxChildWinContextFactory;
class SfxAcceleratorManager;
class SfxAppData_Impl;
class SfxApplication;
class SfxBasicTestWin;
class SfxBindings;
class SfxChildWinFactArr_Impl;
class SfxChildWindow;
class SfxConfigManager;
class SfxDispatcher;
class SfxEventConfiguration;
class SfxEventHint;
class SfxFilter;
class SfxImageManager;
class SfxInterface;
class SfxItemHandle;
class SfxMacroConfig;
class SfxMedium;
class SfxMediumList;
class SfxMenuBarManager;
class SfxMenuCtrlFactArr_Impl;
class SfxNewFileDialog;
class SfxObjectFactory;
class SfxObjectFactoryArr_Impl;
class SfxObjectShell;
class SfxObjectShellArr_Impl;
class SfxOptions;
class SfxProgress;
class SfxResourceManager;
class SfxShellObject;
class SfxSlot;
class SfxSlotPool;
class SfxStatusBarManager;
class SfxStbCtrlFactArr_Impl;
class SfxTabDialog;
class SfxTbxCtrlFactArr_Impl;
class SfxTemplateDialog;
class SfxToolBoxConfig;
class SfxViewFrame;
class SfxViewFrameArr_Impl;
class SfxViewShell;
class SfxViewShellArr_Impl;
class SvData;
class HelpPI;
class SfxWorkWindow;
class SfxFilterMatcher;
class SfxFrame;
class SfxModule;
class SfxModuleArr_Impl;
class ISfxModule;
class SfxObjectShellLock;
class TaskStatusBar;
class SfxMiscCfg;
struct SfxConstant;
struct SfxChildWinFactory;
struct SfxMenuCtrlFactory;
struct SfxStbCtrlFactory;
struct SfxTbxCtrlFactory;
class SfxApplicationWindow;
//STRIP008 namespace so3 {
//STRIP008 class SvLinkSource;
//STRIP008 };
#define STARAPP_VERB "STARAPP"
#define PRESENTATION_LIVEMODE       ((USHORT)0x1000)
#define DYNAMIC_USERID_OFFSET	1000

//--------------------------------------------------------------------

/* [Beschreibung]

   Beim html Filter steht mit der Auswahl des Filter noch nicht die
   ObjectFactory fest. Daher wird zunaechst eine Writer Shell angelegt
   (bzw. die FilterDetection ist derart anzupassen, dass dies
   geschieht).  Das im ConvertFrom uebergebene Medium enthaelt im
   ItemSet unter SID_LOADENVIRONMENT ein SfxRefItem, welches ein
   SfxLoadEnvironment enthaelt. Dort ist dann ein DataAvailableLink zu
   setzen, ueber den der Import vom Vorliegen weiterer Daten Kenntnis
   erhaelt.

   Gelangt das ConvertFrom zu einer Entscheidung ueber die vorliegende
   Objectshell und ist dies eine FramesetObjectshell, so wird das
   Frameset asynchron bis zum Ende durchgeparsed anschliessend
   DocumentDetected mit der ObjectShell, bzw. mit einem Fehlercode und
   pObjSh = 0, falls zu diesem Zeitpunkt bereits eine Fehler
   aufgetreten ist, aufgerufen. Liegt ein Writer HTML Doc vor, wird direkt
   DocumentDetected gerufen.

   Daraufhin erzeugt der Sfx eine View auf das uebergebene Dokument
   und nimmt seine Referenz auf die WriterObjectShell fort, falls eine
   FramesetObjectshell uebergeben wurde (Der Parser muss also selbst
   eine halten, falls er sie noch braucht). Ausserdem wird das Item
   SID_LOADENVIRONMENT aus dem Itemset genommen (Also auch hier eine
   eigene Referenz halten, damit der DataAvailableLink weiter gerufen
   werden kann!)

*/

// class SfxLoadEnvironment ------------------------------------------

class LoadEnvironment_Impl;
class SfxLoadEnvironment : public SvRefBase
{
    LoadEnvironment_Impl* _pImpl;
public:
    SfxLoadEnvironment( LoadEnvironment_Impl* pImpl );
    ~SfxLoadEnvironment();
//STRIP001     void     SetDataAvailableLink( const Link& rLink );
//STRIP001     ErrCode  DocumentDetected( SfxObjectShell* pObjSh, ErrCode nError );
};

// class SfxSysChangeHint --------------------------------------------

class SfxSysChangeHint : public SfxHint
{
    USHORT              _nType;
    AppSettings&        _rAppSettings;
public:
                        TYPEINFO();
                        SfxSysChangeHint(USHORT nType, const AppSettings &rSet )
                        : _nType(nType), _rAppSettings((AppSettings&) rSet) {}
    USHORT              GetChangeType() const { return _nType; }
    const AppSettings&  GetAppSettings() const { return _rAppSettings; }
};

//--------------------------------------------------------------------

/*  [Beschreibung]

    Kurzschreibweise f"ur SfxGetpApp(). Liefert den Pointer auf die
    SfxApplication Instanz.
*/

#define SFX_APP() SfxGetpApp()

//====================================================================

class SfxLinkItem : public SfxPoolItem
{
    Link aLink;
public:
    virtual SfxPoolItem*     Clone( SfxItemPool *pPool = 0 ) const
    {   return new SfxLinkItem( *this ); }
    virtual int              operator==( const SfxPoolItem& rL) const
    {   return ((SfxLinkItem&)rL).aLink == aLink; }
    SfxLinkItem( USHORT nWhich, const Link& rValue ) : SfxPoolItem( nWhich )
    {   aLink = rValue; }
    const Link&              GetValue() const { return aLink; }
};

DECL_OBJHINT( SfxStringHint, String );

typedef SfxPoolItem* (*SfxItemCreateFunc)();

class SfxItemFactory_Impl;
class SfxItemFactoryList
{
    List aList;
public:
    ~SfxItemFactoryList();

    SfxItemFactory_Impl* GetFactory_Impl( const SvGlobalName& rName ) const;
    SfxItemFactory_Impl* GetFactory_Impl( TypeId ) const;
    const SvGlobalName* GetGlobalName( const SfxPoolItem* pItem ) const;
    SfxPoolItem* Create(
        const SvGlobalName& rName, USHORT nId, SvStream* pStrm = 0) const;
    void         RegisterItemFactory(
        const SvGlobalName& rName, SfxItemCreateFunc );
};

#define REGISTER_ITEM( ItemClass, aGlobName )                                 \
RegisterItemFactory( aGlobName, ( SfxItemCreateFunc) ItemClass::StaticType() );

#ifndef SFX_DECL_OBJECTSHELL_DEFINED
#define SFX_DECL_OBJECTSHELL_DEFINED
SV_DECL_REF(SfxObjectShell)
SV_DECL_LOCK(SfxObjectShell)
#endif

void RegisterServices();

struct SfxApplication_Impl;
class SfxApplication: public SfxShell

/*  [Beschreibung]

    Die Klasse SfxApplication bietet eine erweiterte Funktionalit"at
    der StarView-Klasse MDIApplication und mu?als Basisklasse f�r
    Applikationen, die das StarFramework verwenden wollen,
    eingesetzt werden.

    Sie bietet verschiedene Factories und Hooks in Form von
    virtuellen Methoden, um das default-Verhalten zu modifizieren.

    [Anmerkung]
    Von dieser Klasse mu?jede StarFramework-Applikation genau
    eine Instanz anlegen.
*/

{
    static SfxApplication*		pApp;
    struct SfxApplication_Impl* pImp;

    ULONG                       _nFeatures;
    SfxViewFrame*               pViewFrame;
    SfxSlotPool*                pSlotPool;
    SfxResourceManager*         pResMgr;
    SfxDispatcher*              pAppDispat;     // Dispatcher falls kein Doc
    SfxMenuBarManager*          pMenuMgr;
    SfxAcceleratorManager*      pAcceleratorMgr;
    SfxStatusBarManager*        pStatusBarMgr;
    SfxConfigManager*           pCfgMgr;    	// bin"are Config, "ubergreifend
    SfxImageManager*            pImageMgr;
    SfxOptions*                 pOptions;
    SfxAppData_Impl*            pAppData_Impl;

    USHORT                      nInterfaces;
    SfxInterface**              pInterfaces;

    BOOL                        bDispatcherLocked:1;    // nichts ausf"uhren
    BOOL                        bInInit:1;    // TRUE solange in Initialisierung
    BOOL                        bInExit:1;    // TRUE solange in Deinit.
    BOOL                        bDowning:1;   // TRUE ab Exit und danach
    BOOL						bCreatedExternal : 1;

#if _SOLAR__PRIVATE
    DECL_LINK(					AutoStart_Impl, void* );
    DECL_LINK(					SpecialService_Impl, void* );
//STRIP001     void                        HandleConfigError_Impl(USHORT nErrId) const;
    DECL_LINK(					AutoSaveHdl_Impl, Timer* );
//STRIP001     BOOL                        SaveAll_Impl(BOOL bPrompt = FALSE, BOOL bAutoSave = FALSE);
//STRIP001     void                        UpdateAutoSave_Impl();
//STRIP001     short                       QuerySave_Impl(SfxObjectShell &, BOOL bAutoSave = FALSE);
    void                        TestFreeResources_Impl();
//STRIP001 	void						InitializeDisplayName_Impl();
#endif

    static SfxApplication*      Create();

protected:
    void                		SettingsChange( USHORT, const AppSettings & );
//STRIP001     FASTBOOL            		IsDemo();

    virtual void                Init();
    virtual void                Exit();

    static void					SetApp( SfxApplication *pDerived );

public:
//STRIP001     void                		OpenClients();
                                TYPEINFO();
                                SFX_DECL_INTERFACE(SFX_INTERFACE_SFXAPP);

                                SfxApplication();
                                ~SfxApplication();

    virtual void                Main( );

    void                		PreInit( );
    static SfxApplication*		GetOrCreate();
    void                		Quit();
    void						InitLabelResMgr( const char* );
    void						HandleAppEvent( const ApplicationEvent& rAppEvent );
//STRIP001 	void						FocusChanged();

    BOOL                        HasFeature( ULONG nFeature ) const;
    void 						SetFeatures( ULONG nFeatures )
                                {
                                    _nFeatures = nFeatures;
                                }

//STRIP001     ULONG                       LoadTemplate( SfxObjectShellLock& xDoc, const String& rFileName, BOOL bCopy=TRUE, SfxItemSet* pArgs = 0 );

    String&                     GetSaveAsTargetURLHack();
    SfxFilterMatcher&           GetFilterMatcher();

    SfxViewFrame*       		CreateViewFrame( SfxObjectShell& rDoc,
                                                 USHORT nViewId=0,
                                                 BOOL bHidden=FALSE );

//STRIP001     ULONG                       DetectFilter( const String &rFileName,
//STRIP001                                               const SfxFilter **pFilter,
//STRIP001                                               USHORT nFilterClass=USHRT_MAX );

    virtual void            	FillStatusBar( StatusBar& );

//STRIP001     PrinterDialog*      		CreatePrinterDialog();
//STRIP001     ModalDialog*        		CreateAboutDialog();
//STRIP001     SfxNewFileDialog*   		CreateNewDialog();

//STRIP001     ULONG               		DetectFilter( SfxMedium& rMedium,
//STRIP001                             	                  const SfxFilter **pFilter,
//STRIP001                             	                  USHORT nFilterClass=USHRT_MAX );

//STRIP001     SfxMedium*          		InsertDocumentDialog( ULONG nFlags, const SfxObjectFactory& rFact);
    SfxMedium*          		InsertDocumentDialog( ULONG nFlags, const SfxObjectFactory& rFact, ULONG nHelpId);
    SfxMediumList*          	InsertDocumentsDialog( ULONG nFlags, const SfxObjectFactory& rFact);
    SfxMediumList*          	InsertDocumentsDialog( ULONG nFlags, const SfxObjectFactory& rFact, ULONG nHelpId);
//STRIP001     long                		DdeExecute( const String& rCmd );
//STRIP001 	long						DdeGetData( const String& rItem,
//STRIP001 											const String& rMimeType,
//STRIP001 										::com::sun::star::uno::Any & rValue );
//STRIP001 	long						DdeSetData( const String& rItem,
//STRIP001 											const String& rMimeType,
//STRIP001 								const ::com::sun::star::uno::Any & rValue );
//STRIP001     ::so3::SvLinkSource*        DdeCreateLinkSource( const String& rItem );

    BOOL                        InitializeDde();
//STRIP001     const DdeService*           GetDdeService() const;
    DdeService*                 GetDdeService();
//STRIP001     void                        AddDdeTopic( SfxObjectShell* );
    void                        RemoveDdeTopic( SfxObjectShell* );
    BOOL                        RestoreWorkingSet();

//STRIP001     ISfxTemplateCommon*         GetCurrentTemplateCommon();
    ISfxTemplateCommon*         GetCurrentTemplateCommon( SfxBindings& );

//STRIP001     void                        LockDispatcher( BOOL bLock );
    BOOL                        IsDispatcherLocked() const
                                { return bDispatcherLocked; }
    void                        SetViewFrame(SfxViewFrame *pViewFrame);
    SfxViewFrame*               GetViewFrame();

    SfxSlotPool&                GetSlotPool( SfxViewFrame *pFrame=NULL ) const;
    SfxResourceManager&         GetResourceManager() const
                                { return *pResMgr; }

//STRIP001     BOOL                        IsInException() const;

    BasicManager*               GetBasicManager();
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::script::XLibraryContainer >
//STRIP001 								GetDialogContainer();
    ::com::sun::star::uno::Reference< ::com::sun::star::script::XLibraryContainer >
                                GetBasicContainer();
    StarBASIC*                  GetBasic();
    USHORT                      SaveBasicManager() const;
    USHORT                      SaveBasicContainer() const;
    USHORT                      SaveDialogContainer() const;
    void                        EnterBasicCall();
//STRIP001     FASTBOOL                    IsInBasicCall() const;
    void                        LeaveBasicCall();
//STRIP001     void                        RegisterBasicConstants( const char *pPrefix,
//STRIP001                                                         const SfxConstant *pConsts,
//STRIP001                                                         USHORT nCount );
    SfxCancelManager*           GetCancelManager() const;

//STRIP001     void                        IntroSlide();
    BOOL                        IsInInit() const { return bInInit; }
    BOOL                        IsInExit() const { return bInExit; }
    BOOL                        IsDowning() const { return bDowning; }

//STRIP001     SfxObjectShell*             GetActiveObjectShell() const;
    SfxModule*                  GetActiveModule( SfxViewFrame* pFrame=NULL ) const;
    Window*                     GetWindowAtScreenPosPixel( const Point& rPos ) const;

    SfxStatusBarManager*        GetStatusBarManager() const;
//STRIP001     SfxMenuBarManager*          GetMenuBarManager() const;
//STRIP001     SfxAcceleratorManager*      GetAcceleratorManager() const;
    SfxAcceleratorManager*      GetGlobalAcceleratorManager() const;

    SfxMacroConfig*             GetMacroConfig() const;

    ResMgr*                     CreateResManager( const char *pPrefix );
    ResMgr*                     GetSfxResManager();
//STRIP001     ResMgr*                     GetLabelResManager() const;
//STRIP001 	SimpleResMgr*				CreateSimpleResManager();
//STRIP001 	SimpleResMgr*				GetSimpleResManager();

    void                        RegisterToolBoxControl( SfxModule*, SfxTbxCtrlFactory*);
    void                        RegisterChildWindow(SfxModule*, SfxChildWinFactory*);
    void                        RegisterChildWindowContext(SfxModule*, USHORT, SfxChildWinContextFactory*);
    void                        RegisterStatusBarControl(SfxModule*, SfxStbCtrlFactory*);
    void                        RegisterMenuControl(SfxModule*, SfxMenuCtrlFactory*);

    const SfxFilter*            GetFilter(const SfxObjectFactory &rFact, const String &rFilterName) const;

    SfxProgress*                GetProgress() const;
//STRIP001     BOOL                        IsStandalone() const;
//STRIP001     BOOL                        IsSecureURL( const INetURLObject &rURL, const String *pReferer ) const;

//STRIP001     SfxTemplateDialog*          GetTemplateDialog();
    SfxHelpPI*                  GetHelpPI();
//STRIP001     const String&               GetLastSaveDirectory() const;

    SfxInterface*               GetInterfaceByIdImpl( SfxInterfaceId eId ) const
                                { return pInterfaces[ USHORT(eId) ]; }
    void                        SetInterfaceByIdImpl( SfxInterfaceId eId, SfxInterface* pIF );
    SfxOptions&                 GetOptions() { return *pOptions; }
    const USHORT*               GetOptionsRanges() const;
    const SfxOptions&           GetOptions() const { return *pOptions; }
    BOOL                        GetOptions(SfxItemSet &);
    void                        SetOptions(const SfxItemSet &);

//STRIP001     ResId                       GetCurrentObjectBar( USHORT nPosId ) const;

//STRIP001     void                        SetDefFocusWindow( Window *pWin );
//STRIP001     void                        GrabFocus( Window *pAlternate );

    Window*                     GetTopWindow() const;
//STRIP001     void                        SetTopWindow(WorkWindow *);
    USHORT                      GetFreeIndex();
    void                        ReleaseIndex(USHORT i);

//STRIP001     static SfxObjectShellRef    DocAlreadyLoaded( const String &rName,
//STRIP001                                                   BOOL bSilent,
//STRIP001                                                   BOOL bActivate,
//STRIP001                                                   BOOL bForbidVisible = FALSE,
//STRIP001                                                   const String* pPostStr = 0);

    void                        NotifyEvent(const SfxEventHint& rEvent, FASTBOOL bSynchron = TRUE );
    SfxEventConfiguration*      GetEventConfig() const;

    void                        SaveConfiguration() const;
//STRIP001     USHORT                      GetDemoKind() const;
//STRIP001     void                        SpoilDemoOutput(OutputDevice &, const Rectangle &) const;
    void                        InsertLateInitHdl(const Link&);
//STRIP001     String                      LocalizeDBName( SfxDBNameConvert eConvert, const String& rList, char aDel=';' ) const;
//STRIP001 	void						SetUserEMailAddress( const String &rEMail );

    static sal_Bool				IsPlugin();
//STRIP001     Config*                     GetFilterIni();
    SfxMiscCfg*					GetMiscConfig();
//STRIP001     USHORT                		Exception( USHORT nError );
    void						StartupScreen( const char* );
    void                        Deinitialize();
//STRIP001     const SfxObjectFactory&     GetDefaultFactory() const;

    virtual void                Invalidate(USHORT nId = 0);

#if _SOLAR__PRIVATE
    SfxImageManager*            GetImageManager_Impl() const { return pImageMgr; }
    SfxConfigManager*           GetConfigManager_Impl() const { return pCfgMgr; }
    SfxDispatcher*              GetAppDispatcher_Impl()
                                { return pAppDispat; }
//STRIP001     SfxDispatcher*              GetDispatcher_Impl();
    USHORT                      ParseCommandLine_Impl();
//STRIP001 	UniqueIndex*				GetEventHandler_Impl();
    DECL_LINK(					StartWelcomeScreenHdl_Impl, void* );

    SfxAcceleratorManager*      GetAppAccel_Impl() const
                                { return pAcceleratorMgr; }

    SfxObjectShellLock          NewDoc_Impl( const String& rFactory, const SfxItemSet* pSet = NULL );
    BOOL                		QueryExit_Impl();
    SfxFrame*                   GetTargetFrame_Impl( const SfxItemSet* pSet, BOOL& rOwnsFrame );

//STRIP001     void                        SetOptions_Impl(const SfxItemSet &);
    BOOL                        CheckTryBuy_Impl();
    void                        ForcePendingInitFactories();

    Timer*                      GetAutoSaveTimer_Impl();
//STRIP001     void                        LoadEa_Impl(SfxMedium &, SfxObjectShell &rObj);

    BOOL                        IsReadOnly_Impl(const String &rFile) const;
    FASTBOOL                    Initialize_Impl();

    const Accelerator&          GetAccelerator_Impl() const;
    SfxAppData_Impl*            Get_Impl() const { return pAppData_Impl; }

    // Object-Factories
    SfxTbxCtrlFactArr_Impl&     GetTbxCtrlFactories_Impl() const;
    SfxStbCtrlFactArr_Impl&     GetStbCtrlFactories_Impl() const;
    SfxMenuCtrlFactArr_Impl&    GetMenuCtrlFactories_Impl() const;
    SfxChildWinFactArr_Impl&    GetChildWinFactories_Impl() const;
    SfxViewFrameArr_Impl&       GetViewFrames_Impl() const;
    SfxViewShellArr_Impl&       GetViewShells_Impl() const;
    SfxObjectShellArr_Impl&     GetObjectShells_Impl() const;
//STRIP001     void                        SetProgress_Impl(SfxProgress *);
    const String&               GetLastDir_Impl() const;
    void                        SetLastDir_Impl( const String & );
//STRIP001     const String&               GetLastFilter_Impl() const;
    void                        SetLastFilter_Impl( const String & );
    void                        BuildBasicData_Impl();
//STRIP001     void                        PlayMacro_Impl( SfxRequest &rReq,
//STRIP001                                                 StarBASIC *pBas );
    StarBASIC*					GetBasic_Impl() const;
    void                        MiscExec_Impl(SfxRequest &){DBG_BF_ASSERT(0, "STRIP");}//STRIP001 void                        MiscExec_Impl(SfxRequest &);
    void                        MiscState_Impl(SfxItemSet &){DBG_BF_ASSERT(0, "STRIP");}//STRIP001 void                        MiscState_Impl(SfxItemSet &);
//STRIP001     void                        MailExec_Impl(SfxRequest &);
//STRIP001     void                        MailState_Impl(SfxItemSet &);
    void                        PropExec_Impl(SfxRequest &);
    void                        PropState_Impl(SfxItemSet &);
    void                        MacroExec_Impl(SfxRequest &);
    void                        MacroState_Impl(SfxItemSet &);
    void                        NewDocExec_Impl(SfxRequest &);
//STRIP001     void                        NewFramesetExec_Impl(SfxRequest &);
    void                        NewDocDirectExec_Impl(SfxRequest &);
    void                        OpenDocExec_Impl(SfxRequest &);
    void                        DocManagerExec_Impl(SfxRequest &);
    void                        INetExecute_Impl(SfxRequest &);
    void                        INetState_Impl(SfxItemSet &);
    void                        ExplorerExec_Impl(SfxRequest & );
    void                        ExplorerState_Impl(SfxItemSet & );

//STRIP001     SfxViewFrame*               CreateView_Impl( SfxRequest&,
//STRIP001                                                  SfxObjectShell *pDoc,
//STRIP001                                                  FASTBOOL bForceNewView = FALSE,
//STRIP001                                                  FASTBOOL bHidden = FALSE );
//STRIP001     SfxViewFrame*               CreateView_Impl( const SfxItemSet* pArgs,
//STRIP001                                                  SfxObjectShell *pDoc,
//STRIP001                                                  FASTBOOL bForceNewView = FALSE,
//STRIP001                                                  FASTBOOL bHidden = FALSE );
    void                        CreateDocState_Impl(SfxItemSet &);

    void                        BasicExec_Impl(SfxRequest &);
    void                        BasicState_Impl(SfxItemSet &);

//STRIP001     void                        ToolboxExec_Impl(SfxRequest &);
//STRIP001     void                        ToolboxState_Impl(SfxItemSet &);

//STRIP001     void                        EventExec_Impl(SfxRequest &, SfxObjectShell*);
//STRIP001     void                        EventState_Impl(USHORT,SfxItemSet &, SfxObjectShell*);

//STRIP001     void                        EnterAsynchronCall_Impl();
    FASTBOOL                    IsInAsynchronCall_Impl() const;
//STRIP001     void                        LeaveAsynchronCall_Impl();
    void                        Registrations_Impl();
    void                        InvalidateWinSlots_Impl();
    SvVerbList*                 GetVerbList_Impl() const;
    SfxWorkWindow*              GetWorkWindow_Impl(const SfxViewFrame *pFrame=0) const;
    DECL_LINK                   (LateInitTimerHdl_Impl, void*);
    DECL_LINK                   (LateInitNewMenu_Impl, void*);
    DECL_LINK                   (LateInitBmkMenu_Impl, void*);
    DECL_LINK                   (LateInitWizMenu_Impl, void*);
    DECL_LINK                   (LateInitOLEReg_Impl, void*);
    DECL_LINK                   (LateInitCHAOSReg_Impl, void*);

    SvUShorts*                  GetDisabledSlotList_Impl();
    static SfxObjectShellLock   CreateObject_Impl( SfxMedium* pMedium, const String& rUrl );
    SfxSlotPool&                GetAppSlotPool_Impl() const
                                { return *pSlotPool; }
    DECL_STATIC_LINK( 			SfxApplication, CookieAlertHdl_Impl, void* );
//STRIP001 	void						BasicLibExec_Impl( SfxRequest& rReq, BasicManager* pMgr );
//STRIP001     SfxModule*                  GetModule_Impl();
#endif
};

//--------------------------------------------------------------------

inline SfxApplication* SfxGetpApp()
{
    return SfxApplication::GetOrCreate();
}

//--------------------------------------------------------------------

//! Dummies f"ur zu implementierende Items
#define SfxApplicationItem SfxVoidItem
#define SfxDocumentListItem SfxVoidItem

}//end of namespace binfilter
#endif

