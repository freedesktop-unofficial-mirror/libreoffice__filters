/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: fmobj.hxx,v $
 * $Revision: 1.5 $
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




    /** returns the type of this form object. See fmglob.hxx
    */
    sal_Int32	getType() const;

protected:
    virtual void     WriteData(SvStream& rOut) const;
    virtual void     ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);

    DECL_LINK(OnCreate, void* );
};


}//end of namespace binfilter
#endif // _FM_FMOBJ_HXX

