/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmundo.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-08 06:05:21 $
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
#ifndef _SVX_FMUNDO_HXX
#define _SVX_FMUNDO_HXX

// auto strip #ifndef _SVDUNDO_HXX
// auto strip #include "svdundo.hxx"
// auto strip #endif

// auto strip #ifndef _COM_SUN_STAR_BEANS_XPROPERTYSET_HPP_
// auto strip #include <com/sun/star/beans/XPropertySet.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_BEANS_XPROPERTYCHANGELISTENER_HPP_
#include <com/sun/star/beans/XPropertyChangeListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_BEANS_PROPERTYCHANGEEVENT_HPP_
// auto strip #include <com/sun/star/beans/PropertyChangeEvent.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_SCRIPTEVENT_HPP_
// auto strip #include <com/sun/star/script/ScriptEvent.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_SCRIPT_XSCRIPTLISTENER_HPP_
#include <com/sun/star/script/XScriptListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_SCRIPT_SCRIPTEVENTDESCRIPTOR_HPP_
// auto strip #include <com/sun/star/script/ScriptEventDescriptor.hpp>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
// auto strip #include <com/sun/star/container/XIndexContainer.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_CONTAINER_XCONTAINERLISTENER_HPP_
#include <com/sun/star/container/XContainerListener.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_CONTAINER_CONTAINEREVENT_HPP_
// auto strip #include <com/sun/star/container/ContainerEvent.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE3_HXX_
#include <cppuhelper/implbase3.hxx>
#endif



// auto strip #ifndef _SFXLSTNER_HXX //autogen
// auto strip #include <svtools/lstner.hxx>
// auto strip #endif

#ifndef _SVDOUNO_HXX //autogen wg. SdrUnoObj
#include "svdouno.hxx"
#endif

#ifndef _COMPHELPER_UNO3_HXX_
#include <comphelper/uno3.hxx>
#endif
FORWARD_DECLARE_INTERFACE(awt,XControl)
FORWARD_DECLARE_INTERFACE(awt,XControlContainer)
namespace binfilter {

class FmFormModel;
class FmFormObj;
class SdrObject;
class FmXFormView;

//STRIP008 FORWARD_DECLARE_INTERFACE(awt,XControl)
//STRIP008 FORWARD_DECLARE_INTERFACE(awt,XControlContainer)
//FORWARD_DECLARE_INTERFACE(uno,Reference)

//==================================================================
// FmUndoPropertyAction
//==================================================================
//STRIP001 class FmUndoPropertyAction: public SdrUndoAction
//STRIP001 {
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet> xObj;
//STRIP001 	::rtl::OUString			aPropertyName;
//STRIP001 	::com::sun::star::uno::Any			aNewValue;
//STRIP001 	::com::sun::star::uno::Any			aOldValue;
//STRIP001 
//STRIP001 public:
//STRIP001 	FmUndoPropertyAction(FmFormModel& rMod, const ::com::sun::star::beans::PropertyChangeEvent& evt);
//STRIP001 
//STRIP001 	virtual void Undo();
//STRIP001 	virtual void Redo();
//STRIP001 
//STRIP001 	virtual String			GetComment() const;
//STRIP001 
//STRIP001 };

//==================================================================
// FmUndoContainerAction
//==================================================================
//STRIP001 class FmUndoContainerAction: public SdrUndoAction
//STRIP001 {
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer>	xContainer;
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>		xElement;
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>		xOwnElement;	// Object das der Action gehoert
//STRIP001 	sal_Int32				nIndex;
//STRIP001 	::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor > aEvts;  // events des Objects
//STRIP001 
//STRIP001 public:
//STRIP001 	enum Action
//STRIP001 	{
//STRIP001 		Inserted = 1,
//STRIP001 		Removed	 = 2
//STRIP001 	};
//STRIP001 
//STRIP001 private:
//STRIP001 	Action				eAction;
//STRIP001 
//STRIP001 public:
//STRIP001 	FmUndoContainerAction(FmFormModel& rMod,
//STRIP001 						  Action _eAction,
//STRIP001 						  const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer>& xCont,
//STRIP001 						  const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& xElem,
//STRIP001 						  sal_Int32 nIdx = -1);
//STRIP001 	~FmUndoContainerAction();
//STRIP001 
//STRIP001 	virtual void Undo();
//STRIP001 	virtual void Redo();
//STRIP001 };

//==================================================================
// FmUndoModelReplaceAction
//==================================================================
//STRIP001 class FmUndoModelReplaceAction : public SdrUndoAction
//STRIP001 {
//STRIP001 	::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>	m_xReplaced;
//STRIP001 	SdrUnoObj*			m_pObject;
//STRIP001 
//STRIP001 public:
//STRIP001 	FmUndoModelReplaceAction(FmFormModel& rMod, SdrUnoObj* pObject, const ::com::sun::star::uno::Reference< ::com::sun::star::awt::XControlModel>& xReplaced);
//STRIP001 	~FmUndoModelReplaceAction();
//STRIP001 
//STRIP001 	virtual void Undo();
//STRIP001 	virtual void Redo()	{ Undo(); }
//STRIP001 
//STRIP001 	virtual String			GetComment() const;
//STRIP001 };

//========================================================================
class FmXUndoEnvironment
    : public ::cppu::WeakImplHelper3<	::com::sun::star::beans::XPropertyChangeListener
                                    ,	::com::sun::star::container::XContainerListener
                                    ,	::com::sun::star::script::XScriptListener
                                    >
    , public SfxListener
                           //	public ::cppu::OWeakObject
{
    friend class FmFormModel;
    friend class FmXFormView;
    FmFormModel& rModel;

    void*		m_pPropertySetCache;
    sal_uInt32	nLocks;
    sal_Bool	bReadOnly;


//STRIP001 	void firing_Impl( const  ::com::sun::star::script::ScriptEvent& evt, ::com::sun::star::uno::Any *pSyncRet=0 );

public:
    FmXUndoEnvironment(FmFormModel& _rModel);
    ~FmXUndoEnvironment();

    // UNO Anbindung
    //	SMART_UNO_DECLARATION(FmXUndoEnvironment, ::cppu::OWeakObject);
    //	virtual sal_Bool queryInterface(UsrUik, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>&);
    //	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::reflection::XIdlClass>>	getIdlClasses(void);

    void Lock() {nLocks++;}
    void UnLock() {nLocks--;}
    sal_Bool IsLocked() const {return nLocks != 0;}

protected:
// ::com::sun::star::lang::XEventListener
    virtual void SAL_CALL disposing(const ::com::sun::star::lang::EventObject& Source) throw( ::com::sun::star::uno::RuntimeException );

// ::com::sun::star::beans::XPropertyChangeListener
    virtual void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt) throw(::com::sun::star::uno::RuntimeException);

// ::com::sun::star::container::XContainerListener
    virtual void SAL_CALL elementInserted(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL elementReplaced(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL elementRemoved(const ::com::sun::star::container::ContainerEvent& rEvent) throw(::com::sun::star::uno::RuntimeException);

// XScriptListener
    virtual void SAL_CALL firing(const  ::com::sun::star::script::ScriptEvent& evt) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Any SAL_CALL approveFiring(const  ::com::sun::star::script::ScriptEvent& evt) throw(::com::sun::star::reflection::InvocationTargetException, ::com::sun::star::uno::RuntimeException);

    virtual void Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

// Einfuegen von Objekten
    void AddForms(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& rForms);
    void RemoveForms(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& rForms);

    void SetReadOnly(sal_Bool bRead) {bReadOnly = bRead;}
    sal_Bool IsReadOnly() const {return bReadOnly;}

    void ModeChanged();
//STRIP001 	void Clear();

private:
    void AddElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);
    void RemoveElement(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);
    void AlterPropertyListening(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& Element);

public:
    // Methoden zur Zuordnung von Controls zu Forms,
    // werden von der Seite und der UndoUmgebung genutzt
    void Inserted(SdrObject* pObj);
    void Removed(SdrObject* pObj);

    void Inserted(FmFormObj* pObj);
    void Removed(FmFormObj* pObj);
};


}//end of namespace binfilter
#endif	//_SVX_FMUNDO_HXX

