/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmshimp.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-27 21:09:20 $
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
#ifndef _SVX_FMSHIMP_HXX
#define _SVX_FMSHIMP_HXX


#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
#ifndef _COM_SUN_STAR_UTIL_XMODIFYLISTENER_HPP_
#include <com/sun/star/util/XModifyListener.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORM_HPP_
#include <com/sun/star/form/XForm.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_XFORMCONTROLLER_HPP_
#include <com/sun/star/form/XFormController.hpp>
#endif
#ifndef _COM_SUN_STAR_FORM_NAVIGATIONBARMODE_HPP_
#include <com/sun/star/form/NavigationBarMode.hpp>
#endif
#ifndef _COM_SUN_STAR_VIEW_XSELECTIONCHANGELISTENER_HPP_
#include <com/sun/star/view/XSelectionChangeListener.hpp>
#endif



#ifndef _SVDMARK_HXX
#include "svdmark.hxx"
#endif

#ifndef _SVX_SVXIDS_HRC
#include "svxids.hrc"
#endif


#define _SVSTDARR_BOOLS
#define _SVSTDARR_BYTES
#define _SVSTDARR_LONGS
#define _SVSTDARR_ULONGS
#define _SVSTDARR_USHORTS

#ifndef _SFXMNUITEM_HXX //autogen
#include <bf_sfx2/mnuitem.hxx>
#endif
#ifndef _SVX_FMTOOLS_HXX
#include "fmtools.hxx"
#endif
#ifndef _FMSEARCH_HXX
#include "fmsearch.hxx"
#endif
#ifndef _CPPUHELPER_COMPBASE6_HXX_
#include <cppuhelper/compbase6.hxx>
#endif
#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif
#ifndef SVX_DBTOOLSCLIENT_HXX
#include "dbtoolsclient.hxx"
#endif

#include <queue>
namespace binfilter {

SV_DECL_PTRARR(SdrObjArray, SdrObject*, 32, 16)//STRIP008 ;
//	SV_DECL_OBJARR(FmFormArray, ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>, 32, 16);
DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm > ,FmFormArray);

// catch databse exceptions if occur
#define DO_SAFE(statement) try { statement; } catch( const Exception& ) { DBG_ERROR("unhandled exception (I tried to move a cursor (or something like that).)"); }

#define GA_DISABLE_SYNC		1
#define GA_FORCE_SYNC		2
#define GA_ENABLE_SYNC		3
#define GA_SYNC_MASK		3
#define GA_DISABLE_ROCTRLR	4
#define GA_ENABLE_ROCTRLR	8


// flags for controlling the behaviour when calling loadForms
#define FORMS_LOAD			0x0000		// default: simply load
#define FORMS_SYNC			0x0000		// default: do in synchronous

#define FORMS_UNLOAD		0x0001		// unload
#define FORMS_RESET			0x0002		// reset after the load/unload
#define FORMS_ASYNC			0x0004		// do this async

// forward declarations
class FmFormShell;

//==============================================================================
// FmFormNavigationDispatcher - a dispatcher responsible for a form navigation slot
//==============================================================================

class FmFormNavigationDispatcher : public FmSlotDispatch
{
};

//==============================================================================
// a class iterating through all fields of a form which are bound to a field
// sub forms are ignored, grid columns (where the grid is a direct child of the form) are included

//========================================================================
// I would prefer this to be a struct local to FmXFormShell but unfortunately local structs/classes
// are somewhat difficult with some of our compilers
class FmCursorActionThread;
struct CursorActionDescription
{
    FmCursorActionThread*	pThread;
    sal_uInt32					nFinishedEvent;
        // we want to do the cleanup of the thread in the main thread so we post an event to ourself
    sal_Bool					bCanceling;
        // this thread is being canceled

    CursorActionDescription() : pThread(NULL), nFinishedEvent(0), bCanceling(sal_False) { }
};

class FmFormPage;
//========================================================================
struct FmLoadAction
{
    FmFormPage*	pPage;
    sal_uInt32	nEventId;
    sal_uInt16	nFlags;

    FmLoadAction( ) : pPage( NULL ), nFlags( 0 ), nEventId( 0 ) { }
    FmLoadAction( FmFormPage* _pPage, sal_uInt16 _nFlags, sal_uInt32 _nEventId )
        :pPage( _pPage ), nFlags( _nFlags ), nEventId( _nEventId )
    {
    }
};

//========================================================================
class SfxViewFrame;
typedef ::cppu::WeakComponentImplHelper6<	::com::sun::star::sdbc::XRowSetListener,         
                                            ::com::sun::star::beans::XPropertyChangeListener,
                                            ::com::sun::star::util::XModifyListener,         
                                            ::com::sun::star::container::XContainerListener, 
                                            ::com::sun::star::view::XSelectionChangeListener,
                                            ::com::sun::star::form::XFormControllerListener> FmXFormShell_BD_BASE;

//========================================================================
class FmXFormShell_Base_Disambiguation : public FmXFormShell_BD_BASE
{
protected:
    FmXFormShell_Base_Disambiguation( ::osl::Mutex& _rMutex ); 
    virtual void SAL_CALL disposing();
};

//========================================================================
typedef FmXFormShell_Base_Disambiguation	FmXFormShell_BASE;
typedef ::utl::ConfigItem					FmXFormShell_CFGBASE;

class FmXFormShell	:public FmXFormShell_BASE
                    ,public FmXFormShell_CFGBASE
                    ,public FmDispatchInterceptor
                    ,public ::binfilter::svxform::OStaticDataAccessTools//STRIP008 					,public ::svxform::OStaticDataAccessTools
{
    friend class FmFormShell;
    friend class FmFormView;
    friend class WizardUsageConfigItem;

    class SuspendPropertyTracking;
    friend class SuspendPropertyTracking;

    // Timer um verzoegerte Markierung vorzunehmen
    Timer			   m_aMarkTimer;
    SdrObjArray			m_arrSearchedControls;
        // We enable a permanent cursor for the grid we found a searched text, it's disabled in the next "found" event.
    FmFormArray			m_arrSearchContexts;

        // some typedefs :
    // all dispatchers belonging to a form
    DECLARE_STL_VECTOR(FmFormNavigationDispatcher*, SingleFormDispatchers);

    // a map from a form access path (like "1/4/2") to the dispatchers array for this form
    DECLARE_STL_USTRINGACCESS_MAP(SingleFormDispatchers, FormsDispatchers);
    FormsDispatchers		m_aNavigationDispatcher;

    ::binfilter::form::OImplementationIdsRef	m_aHoldImplIdHelper;//STRIIP008 ::form::OImplementationIdsRef	m_aHoldImplIdHelper;
    
    SvUShorts	m_arrInvalidSlots;
    SvBytes		m_arrInvalidSlots_Flags;
        // we explicitly switch off the propbrw before leaving the design mode
        // this flag tells us if we have to switch it on again when reentering

    DECLARE_STL_USTRINGACCESS_MAP(CursorActionDescription, CursorActions);
    CursorActions	m_aCursorActions;
        // all actions on async cursors

    SvBools		m_aControlLocks;
        // while doing a async cursor action we have to lock all controls of the active controller.
        // m_aControlLocks remembers the previous lock states to be restored afterwards.
    ::osl::Mutex	m_aAsyncSafety;
        // secure the access to our thread related members
    ::osl::Mutex	m_aInvalidationSafety;
        // secure the access to all our slot invalidation related members

    ::com::sun::star::form::NavigationBarMode   m_eNavigate;				// Art der Navigation

        // da ich beim Suchen fuer die Behandlung des "gefunden" ein SdrObject markieren will, besorge ich mir vor dem
        // Hochreissen des Suchen-Dialoges alle relevanten Objekte
        // (das Array ist damit auch nur waehrend des Suchvorganges gueltig)
    SvLongs				m_arrRelativeGridColumn;

    ::osl::Mutex	m_aMutex;
    sal_uInt32		m_nInvalidationEvent;
    ::std::queue< FmLoadAction >
                    m_aLoadingPages;

    FmFormShell*	m_pShell;

    // aktuelle Form, Controller
    // nur im alive mode verfuegbar
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>	m_xActiveController;
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>	m_xNavigationController;
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>			m_xActiveForm;
    ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer> m_xParser;

    // Aktueller container einer Page
    // nur im designmode verfuegbar
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess> m_xForms;

    // aktuell selektiertes Object (Form oder Control)
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>	   m_xSelObject;

    // aktuelles Control, keine Form
    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>	   m_xCurControl;

    // aktuelle Form
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>		   m_xCurForm;

    
        // und das ist ebenfalls fuer's 'gefunden' : Beim Finden in GridControls brauche ich die Spalte, bekomme aber
        // nur die Nummer des Feldes, die entspricht der Nummer der Spalte + <offset>, wobei der Offset von der Position
        // des GridControls im Formular abhaengt. Also hier eine Umrechnung.
    ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>			m_xLastGridFound;
        // we want to be a DispatchInterceptor within our frame
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame>				m_xAttachedFrame;
        // Administration of external form views (see the SID_FM_VIEW_AS_GRID-slot)
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XController>			m_xExternalViewController;		// the controller for the external form view
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>		m_xExtViewTriggerController;	// the nav controller at the time the external display was triggered
    ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>			m_xExternalDisplayedForm;		// the form which the external view is based on

    FmXDispatchInterceptorImpl*		m_pMainFrameInterceptor;
    FmXDispatchInterceptorImpl*		m_pExternalViewInterceptor;

    sal_Int16		m_nLockSlotInvalidation;
    sal_Bool		m_bHadPropBrw:1;

    sal_Bool		m_bTrackProperties	: 1;
        // soll ich (bzw. der Owner diese Impl-Klasse) mich um die Aktualisierung des ::com::sun::star::beans::Property-Browsers kuemmern ?

    sal_Bool		m_bUseWizards : 1;

    sal_Bool		m_bActiveModified	: 1;	// Controller modifiziert
    sal_Bool		m_bDatabaseBar		: 1;	// Gibt es eine Datenbankleiste
    sal_Bool		m_bInActivate		: 1;	// Wird ein Controller aktiviert
    sal_Bool		m_bSetFocus			: 1;	// Darf der Focus umgesetzt werden
    sal_Bool		m_bFilterMode		: 1;	// Wird gerade ein Filter auf die Controls angesetzt
    sal_Bool		m_bChangingDesignMode:1;	// sal_True within SetDesignMode
    sal_Bool		m_bPreparedClose	: 1;	// for the current modification state of the current form
                                                //  PrepareClose had been called and the user denied to save changes

public:
    FmXFormShell(FmFormShell* _pShell, SfxViewFrame* _pViewFrame);
    ~FmXFormShell();

    // UNO Anbindung
    DECLARE_UNO3_DEFAULTS(FmXFormShell, FmXFormShell_BASE);
    virtual ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId() throw(::com::sun::star::uno::RuntimeException);

// EventListener
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::container::XContainerListener
    virtual void SAL_CALL elementInserted(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL elementReplaced(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL elementRemoved(const ::com::sun::star::container::ContainerEvent& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// XSelectionChangeListener
    virtual void SAL_CALL selectionChanged(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::beans::XPropertyChangeListener
    virtual void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::sdbc::XRowSetListener
    virtual void SAL_CALL cursorMoved(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL rowChanged(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException ) { }    
    virtual void SAL_CALL rowSetChanged(const ::com::sun::star::lang::EventObject& event) throw( ::com::sun::star::uno::RuntimeException ) { }

// ::com::sun::star::util::XModifyListener    -> modify setzen
    virtual void SAL_CALL modified(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::frame::XDispatchProviderInterceptor
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::frame::XDispatch> interceptedQueryDispatch(sal_uInt16 _nId,
        const  ::com::sun::star::util::URL& aURL, const ::rtl::OUString& aTargetFrameName, sal_Int32 nSearchFlags) throw( ::com::sun::star::uno::RuntimeException );
    virtual ::osl::Mutex* getInterceptorMutex() { return &m_aAsyncSafety; }

// ::com::sun::star::form::XFormControllerListener
    virtual void SAL_CALL formActivated(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );
    virtual void SAL_CALL formDeactivated(const ::com::sun::star::lang::EventObject& rEvent) throw( ::com::sun::star::uno::RuntimeException );

// OComponentHelper
    virtual void SAL_CALL disposing();

    void EnableTrackProperties( sal_Bool bEnable) { m_bTrackProperties = bEnable; }
    sal_Bool IsTrackPropertiesEnabled() {return m_bTrackProperties;}

public:
    // activation handling
            void		viewActivated( FmFormView* _pCurrentView, sal_Bool _bSyncAction = sal_False );
            void		viewDeactivated( FmFormView* _pCurrentView, sal_Bool _bDeactivateController = sal_True );

protected:
    // form handling
    /// load or unload the forms on a page
            void		loadForms( FmFormPage* _pPage, const sal_uInt16 _nBehaviour = FORMS_LOAD | FORMS_SYNC );


    // stuff
    void ResetForms(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>& _xForms = ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess>(), sal_Bool bInvalidate = sal_False);
    void AddElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);
    void RemoveElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);






        // liefert das Control, welches das angegebene Model hat
        // sammelt in strNames die Namen aller Formulare, fuegt die entsprechenden XFormRefs in m_arrSearchContexts ein


public:
    static sal_Bool CommitCurrent(const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController);

    // methode fuer nicht designmode (alive mode)
    void setActiveController( const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& _xController, sal_Bool _bNoSaveOldContent = sal_False );
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getActiveController() const {return m_xActiveController;}
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getActiveInternalController() const { return m_xActiveController == m_xExternalViewController ? m_xExtViewTriggerController : m_xActiveController; }
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getActiveForm() const {return m_xActiveForm;}
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XFormController>& getNavController() const {return m_xNavigationController;}
    ::com::sun::star::uno::Reference< ::com::sun::star::sdb::XSQLQueryComposer> getParser() const { return m_xParser; }

    // nur im design mode verwenden, aktuell selektiertes Formular oder Control
    void	setCurControl(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xObj);
    void	setCurControl(const SdrMarkList& rMarkList);
    void	setSelObject(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xObj);

    const	::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getCurForm() const {return m_xCurForm;}
    const	::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& getCurControl() const {return m_xCurControl;}
    const	::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& getSelObject() const {return m_xSelObject;}

    sal_Bool hasForms() const {return m_xForms.is() && m_xForms->getCount() != 0;}
    sal_Bool isActiveModified() const {return m_bActiveModified;}
    sal_Bool hasDatabaseBar() const {return m_bDatabaseBar;}
    sal_Bool canNavigate() const	{return m_xNavigationController.is();}
    sal_Bool isParsable() const		{return m_xParser.is() && m_xParser->getQuery().getLength();}
    sal_Bool hasFilter() const		{ return isParsable() &&
                                        (m_xParser->getFilter().getLength() || m_xParser->getOrder().getLength()); }

    sal_Bool IsPropBrwOpen() const;

    void DetermineSelection(const SdrMarkList& rMarkList);
    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm> DetermineCurForm(const SdrMarkList& rMarkList, sal_Bool&);
    void SetSelection(const SdrMarkList& rMarkList);
    void SetSelectionDelayed(FmFormView* pView);

    void SetDesignMode(sal_Bool bDesign);

    sal_Bool	GetWizardUsing() const { return m_bUseWizards; }

        // Setzen des Filtermodus
    sal_Bool isInFilterMode() const {return m_bFilterMode;}

        // ein Menue, das alle ControlConversion-Eintraege enthaelt
        // umwandeln eines Controls
        // ein gueltiger ControlConversionSlot
        // Konvertierung der Komponente mit geg. Slot moeglich
        // iteriertes IsConversionPossible
        // verkapptes ConvertControlTo

private:


    DECL_LINK(OnFoundData, FmFoundRecordInformation*);
    DECL_LINK(OnCanceledNotFound, FmFoundRecordInformation*);
    DECL_LINK(OnSearchContextRequest, FmSearchContext*);
    DECL_LINK(OnTimeOut, void*);


    // das Setzen des curObject/selObject/curForm erfolgt verzoegert (SetSelectionDelayed), mit den folgenden
    // Funktionen laesst sich das abfragen/erzwingen
    inline sal_Bool	IsSelectionUpdatePending();

    // Invalidierung von Slots
    // Locking der Invalidierung - wenn der interne Locking-Counter auf 0 geht, werden alle aufgelaufenen Slots
    // (asynchron) invalidiert

    DECL_LINK(OnInvalidateSlots, void*);

        // if the form belongs to the controller (extern) displaying a grid, the according internal form will
        // be displayed, _xForm else

    void	CloseExternalFormViewer();
        // closes the task-local beamer displaying a grid view for a form

    // ConfigItem related stuff
    void implAdjustConfigCache();

    // ---------------------------------------------------
    // asyncronous cursor actions/navigation slot handling

        // (de)activate all dispatchers belonging to the form with the given access path
    DECL_LINK(OnExecuteNavSlot, FmFormNavigationDispatcher*);

        // return the access path of the given form (if rAssumedPagePrefix the current page's id is taken as page prefix)
        // return the forms collection of the page with the given id
        // get the id of the page to which's forms collection _xForms belongs




    enum CURSOR_ACTION { CA_MOVE_TO_LAST, CA_MOVE_ABSOLUTE };

    sal_Bool HasAnyPendingCursorAction() const;


    DECL_LINK(OnCursorActionDone, FmCursorActionThread*);
    DECL_LINK(OnCursorActionDoneMainThread, FmCursorActionThread*);

    DECL_LINK( OnLoadForms, FmFormPage* );
};

//------------------------------------------------------------------------------
inline sal_Bool FmXFormShell::IsSelectionUpdatePending()
{
    return m_aMarkTimer.IsActive();
}

// ========================================================================
// = ein Iterator, der ausgehend von einem Interface ein Objekt sucht, dessen
// = ::com::sun::star::beans::Property-Set eine ControlSource- sowie eine BoundField-Eigenschaft hat,
// = wobei letztere einen Wert ungleich NULL haben muss.
// = Wenn das Interface selber diese Bedingung nicht erfuellt, wird getestet,
// = ob es ein Container ist (also ueber eine ::com::sun::star::container::XIndexAccess verfuegt), dann
// = wird dort abgestiegen und fuer jedes Element des Containers das selbe
// = versucht (wiederum eventuell mit Abstieg).
// = Wenn irgendein Objekt dabei die geforderte Eigenschaft hat, entfaellt
// = der Teil mit dem Container-Test fuer dieses Objekt.
// =


// ========================================================================
SV_DECL_PTRARR_DEL(StatusForwarderArray, SfxStatusForwarder*, 16, 0)
class ControlConversionMenuController : public SfxMenuControl
{
protected:
    StatusForwarderArray	m_aStatusForwarders;
    Menu*					m_pMainMenu;
    PopupMenu*				m_pConversionMenu;

public:
    ControlConversionMenuController(sal_uInt16 nId, Menu& rMenu, SfxBindings& rBindings);
    SFX_DECL_MENU_CONTROL();

};

//==================================================================
// FmCursorActionThread
//==================================================================


//------------------------------------------------------------------------------

#define DECL_CURSOR_ACTION_THREAD(classname)			\
                                                        \
class classname : public FmCursorActionThread			\
{														\
public:													\
    classname(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDataSource,		\
            const UniString& _rPath);						\
protected:												\
    virtual void RunImpl();								\
};														\


//------------------------------------------------------------------------------

#define IMPL_CURSOR_ACTION_THREAD(classname, caption, action)	\
                                                                \
classname::classname(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XResultSet>& _xDataSource,			\
        const UniString& _rPath)									\
    :FmCursorActionThread(_xDataSource, caption, _rPath)		\
{																\
}																\
                                                                \
void classname::RunImpl()										\
{																\
    m_xDataSource->action;										\
}																\



}//end of namespace binfilter
#endif          // _SVX_FMSHIMP_HXX
