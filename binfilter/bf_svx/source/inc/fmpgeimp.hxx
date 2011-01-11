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
#ifndef _SVX_FMUNOPGE_HXX
#define _SVX_FMUNOPGE_HXX

#include <com/sun/star/sdbc/XDataSource.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/form/XFormComponent.hpp>
#include <com/sun/star/form/XForm.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>

#include <tools/list.hxx>
#include <vector>

#include <comphelper/uno3.hxx>
FORWARD_DECLARE_INTERFACE(io,XObjectOutputStream)
FORWARD_DECLARE_INTERFACE(io,XObjectInputStream)
FORWARD_DECLARE_INTERFACE(container,XIndexContainer)
class SvStream;
namespace binfilter {

class SdrIOHeader;
class FmFormObj;
class FmFormPage;
class SdrObject;

class SdrObjList;

typedef ::std::vector< FmFormObj* > FmObjectList;

//==================================================================
// FmFormPageImpl
// lauscht an allen Containern, um festzustellen, wann Objecte
// eingefuegt worden sind und wann diese entfernt wurden
//==================================================================

class FmFormPageImpl
{
    friend class FmFormPage;
    friend class FmFormObj;
    friend class FmXFormShell;

    ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>				xCurrentForm;	// aktuelles Formular
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>	xForms;			// Liste aller Forms
    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel>				xModel;
    FmFormPage*				pPage;
    UniString				m_sPageId;

    sal_Bool		m_bFirstActivation	: 1;

protected:
    FmFormPageImpl(FmFormPage* _pPage);
    FmFormPageImpl(FmFormPage* _pPage, const FmFormPageImpl& rImpl);
    ~FmFormPageImpl();

    void Init();

public:
    //	nur wichtig fuer den DesignMode
    const ::com::sun::star::uno::Reference< ::com::sun::star::form::XForm>& getCurForm() {return xCurrentForm;}

    // Defaults fuer ein Object setzen
    // Eindeutigen Namen, Zuordnen zu einer Form falls noch nicht erfolgt

    UniString GetPageId() const { return m_sPageId; }

    // activation handling
    inline	sal_Bool	hasEverBeenActivated( ) const { return !m_bFirstActivation; }
    inline	void		setHasBeenActivated( ) { m_bFirstActivation = sal_False; }

protected:
    // lesen und schreiben der Objecte
    void WriteData(SvStream& rOut) const; //
    void ReadData(const SdrIOHeader& rHead, SvStream& rIn); //

    void write(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectOutputStream>& OutStream) const;
    void read(const ::com::sun::star::uno::Reference< ::com::sun::star::io::XObjectInputStream>& InStream);

    const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer>& getForms() {return xForms;}

    void fillList(FmObjectList& rList, const SdrObjList& rObjList, sal_Bool bConnected) const;



public:


};


}//end of namespace binfilter
#endif // _SVX_FMUNOPGE_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
