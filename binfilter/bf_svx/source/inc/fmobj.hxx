/*************************************************************************
 *
 *  $RCSfile: fmobj.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:44:25 $
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
#ifndef _SVX_FMOBJ_HXX
#define _SVX_FMOBJ_HXX

#ifndef _SVDOUNO_HXX
#include "svdouno.hxx"
#endif

#ifndef _COM_SUN_STAR_SCRIPT_SCRIPTEVENTDESCRIPTOR_HPP_
#include <com/sun/star/script/ScriptEventDescriptor.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XINDEXCONTAINER_HPP_
#include <com/sun/star/container/XIndexContainer.hpp>
#endif
namespace binfilter {

class FmFormView;

//==================================================================
// FmFormObj
//==================================================================
class FmXForms;
class FmFormObj: public SdrUnoObj
{
    friend class FmForm;
    friend class FmFormPage;
    friend class FmFormPageImpl;
    friend class FmFormObjFactory;
    friend class FmXUndoEnvironment;
    friend class SvxFmDrawPage;
    friend class SvxFmMSFactory;

    ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >	aEvts;  // events des Objects
    ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor>	m_aEventsHistory;
                // valid if and only if m_pEnvironmentHistory != NULL, this are the events which we're set when
                // m_pEnvironmentHistory was created

    FmFormView* pTempView;
    sal_uInt32		nEvent;

    // Informationen fuer die Controlumgebung
    // werden nur vorgehalten, wenn ein Object sich nicht in einer Objectliste befindet
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer>		xParent;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer >	m_xEnvironmentHistory;
    sal_Int32			nPos;
    sal_Int32			m_nType;

public:
    TYPEINFO();

protected:
//STRIP001 	FmFormObj(const ::rtl::OUString& rModelName,sal_Int32 _nType);
    FmFormObj(sal_Int32 _nType);

    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer>& GetParent() const {return xParent;}
    void  SetObjEnv(const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer>& xForm, sal_Int32 nIdx = -1,
                    const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& rEvts= ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >());
    const ::com::sun::star::uno::Sequence< ::com::sun::star::script::ScriptEventDescriptor >& GetEvents() const {return aEvts;}
    sal_Int32 GetPos() const {return nPos;}

public:
    virtual ~FmFormObj();
    virtual void SetPage(SdrPage* pNewPage);

    virtual sal_uInt32 GetObjInventor() const;
    virtual sal_uInt16 GetObjIdentifier() const;

//STRIP001 	virtual SdrObject*	Clone() const;
//STRIP001 	virtual SdrObject*	Clone(SdrPage* pPage, SdrModel* pModel) const;
//STRIP001 	virtual void		operator= (const SdrObject& rObj);

//STRIP001 	virtual void clonedFrom(const FmFormObj* _pSource);

//STRIP001 	static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface> ensureModelEnv(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface>& _rSourceContainer, const ::com::sun::star::uno::Reference< ::com::sun::star::container::XIndexContainer> _rTopLevelDestContainer);

    /** returns the type of this form object. See fmglob.hxx
    */
    sal_Int32	getType() const;

protected:
    virtual void     WriteData(SvStream& rOut) const;
    virtual void     ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
//STRIP001 	virtual FASTBOOL EndCreate(SdrDragStat& rStat, SdrCreateCmd eCmd);

    DECL_LINK(OnCreate, void* );
};


}//end of namespace binfilter
#endif // _FM_FMOBJ_HXX

