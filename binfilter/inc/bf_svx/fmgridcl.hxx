/*************************************************************************
 *
 *  $RCSfile: fmgridcl.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:35 $
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
#ifndef _SVX_FMGRIDCL_HXX
#define _SVX_FMGRIDCL_HXX

#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif

#ifndef _COM_SUN_STAR_FORM_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif

// alles nur fuer stl
#ifndef _SVX_GRIDCTRL_HXX
#include <bf_svx/gridctrl.hxx>
#endif
#ifndef _TRANSFER_HXX
#include <svtools/transfer.hxx>
#endif

//==================================================================
// FmGridHeader
//==================================================================
struct FmGridHeaderData;
class FmGridHeader
            :public ::svt::EditBrowserHeader
            ,public DropTargetHelper
{
protected:
    FmGridHeaderData*		m_pImpl;

    // trigger context menu execution
    void	triggerColumnContextMenu( const ::Point& _rPreferredPos );

public:
    FmGridHeader( BrowseBox* pParent, WinBits nWinBits = WB_STDHEADERBAR | WB_DRAG );
    ~FmGridHeader();

public:
    struct AccessControl { friend class FmGridControl; private: AccessControl() { } };

    inline	void	triggerColumnContextMenu( const ::Point& _rPreferredPos, const AccessControl& )
    {
        triggerColumnContextMenu( _rPreferredPos );
    }

protected:
    virtual void Command( const CommandEvent& rCEvt );
    virtual void RequestHelp( const HelpEvent& rHEvt );
    virtual void Select();

    /**	the value returned by GetItemPos is meaningless for the grid model if there are hidden columns,
        so use GetModelColumnPos instead
    */
    sal_uInt16 GetModelColumnPos(sal_uInt16 nId) const;

    /**	This is called before executing a context menu for a column. rMenu contains the initial entries
        handled by this base class' method (which always has to be called).
        Derived classes may alter the menu in any way and handle any additional entries in
        PostExecuteColumnContextMenu.
        All disabled entries will be removed before executing the menu, so be careful with separators
        near entries you probably wish to disable ...
    */
    virtual void	PreExecuteColumnContextMenu(sal_uInt16 nColId, PopupMenu& rMenu);
    /**	After executing the context menu for a column this method is called.
    */
    virtual	void	PostExecuteColumnContextMenu(sal_uInt16 nColId, const PopupMenu& rMenu, sal_uInt16 nExecutionResult);

    // DropTargetHelper
    virtual sal_Int8	AcceptDrop( const AcceptDropEvent& rEvt );
    virtual sal_Int8	ExecuteDrop( const ExecuteDropEvent& rEvt );

    /** selects the column at the selection supplier.
        @param	nColumnId
            The column id.
    */
    void notifyColumnSelect(sal_uInt16 nColumnId);
private:
    DECL_LINK( OnAsyncExecuteDrop, void* );
};

//==================================================================
// FmGridControl
//==================================================================
class FmGridControl : public DbGridControl

{
    friend class FmGridHeader;
    friend class FmXGridPeer;

    FmXGridPeer*		m_pPeer;
    sal_Int32			m_nCurrentSelectedColumn;	// this is the column model (not the view) posisition ...
    sal_uInt16			m_nMarkedColumnId;
    sal_Bool			m_bSelecting;
    sal_Bool			m_bInColumnMove	: 1;

public:
    FmGridControl(
        ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >,
        Window* pParent,
        FmXGridPeer* _pPeer,
        WinBits nBits);

    // Window
    virtual void KeyInput( const KeyEvent& rKEvt );

    // ::com::sun::star::beans::XPropertyChangeListener
    void SAL_CALL propertyChange(const ::com::sun::star::beans::PropertyChangeEvent& evt);

    // ::com::sun::star::form::XPositioningListener
    void positioned(const ::com::sun::star::lang::EventObject& rEvent);

    // XBound
    sal_Bool commit();

    // ::com::sun::star::form::XInsertListener
    void inserted(const ::com::sun::star::lang::EventObject& rEvent);

    // ::com::sun::star::form::XRestoreListener
    void restored(const ::com::sun::star::lang::EventObject& rEvent);

    void markColumn(sal_uInt16 nId);
    sal_Bool isColumnMarked(sal_uInt16 nId) const;

    sal_Int32	GetSelectedColumn() const;

    /** return the name of the specified object. 
        @param	eObjType
            The type to ask for
        @param	_nPosition
            The position of a tablecell (index position), header bar  colum/row cell
        @return  
            The name of the specified object. 
    */
    virtual ::rtl::OUString GetAccessibleName( ::svt::AccessibleBrowseBoxObjType eObjType,sal_Int32 _nPosition = -1) const;

    /** return the description of the specified object. 
        @param	eObjType
            The type to ask for
        @param	_nPosition
            The position of a tablecell (index position), header bar  colum/row cell
        @return  
            The description of the specified object. 
    */
    virtual ::rtl::OUString GetAccessibleDescription( ::svt::AccessibleBrowseBoxObjType eObjType,sal_Int32 _nPosition = -1) const;

protected:
    virtual void Command(const CommandEvent& rEvt);

    virtual BrowserHeader* imp_CreateHeaderBar(BrowseBox* pParent);
    virtual void ColumnResized(sal_uInt16 nId);
    virtual void ColumnMoved(sal_uInt16 nId);
    virtual void DeleteSelectedRows();
    virtual void SetDesignMode(sal_Bool bMode);
    virtual void CellModified();
    virtual void HideColumn(sal_uInt16 nId);
    virtual void ShowColumn(sal_uInt16 nId);

    sal_Bool	IsInColumnMove() const {return m_bInColumnMove;}

    virtual void BeginCursorAction();
    virtual void EndCursorAction();
    virtual void Select();

    // Initialisieren der Spalten
    // a.) nur ueber Spaltenbeschreibung
    virtual void InitColumnsByModels(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >& xColumns);
    // b.) im alivemode ueber Datenbankfelder
    virtual void InitColumnsByFields(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >& xFields);

            // some kind of impl version (for one single column) of our version of InitColumnsByFields
            void InitColumnByField(
                    DbGridColumn* _pColumn,
                    const ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& _rxColumnModel,
                    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >& _rxFieldsByNames,
                    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexAccess >& _rxFieldsByIndex
                );

    FmXGridPeer* GetPeer() const {return m_pPeer;}

    ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>
            getSelectionBookmarks();
    sal_Bool selectBookmarks(const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Any>& _rBookmarks);

    /** returns if a column is selected
        @param	nColumnId
            The column id.
        @param	_pColumn
            The column to compare with.
        @return
            <TRUE/> if the column is selected, otherwise <FALSE/>
    */
    sal_Bool isColumnSelected(sal_uInt16 nColumnId,DbGridColumn* _pColumn);
};

#endif // _SVX_FMGRIDCL_HXX

