/*************************************************************************
 *
 *  $RCSfile: forms_FormattedFieldWrapper.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:25:07 $
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

#ifndef _FRM_FORMATTED_FIELD_WRAPPER_HXX_
#include "FormattedFieldWrapper.hxx"
#endif
#ifndef _FORMS_EDIT_HXX_
#include "Edit.hxx"
#endif
#ifndef _FORMS_FORMATTEDFIELD_HXX_
#include "FormattedField.hxx"
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif
#ifndef _FORMS_EDITBASE_HXX_
#include "EditBase.hxx"
#endif
#ifndef _FRM_SERVICES_HXX_
#include "services.hxx"
#endif
#ifndef _CONNECTIVITY_DBTOOLS_HXX_
#include <connectivity/dbtools.hxx>
#endif

#ifndef _ISOLANG_HXX
#include <tools/isolang.hxx>
#endif
#ifndef _SV_SVAPP_HXX
#include <vcl/svapp.hxx>
#endif
#ifndef _TOOLS_INTN_HXX
#include <tools/intn.hxx>
#endif
namespace binfilter {

//.........................................................................
namespace frm
{
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::sdb;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::awt;
using namespace ::com::sun::star::io;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::util;

//==================================================================
// OFormattedFieldWrapper
//==================================================================
DBG_NAME(OFormattedFieldWrapper)
//------------------------------------------------------------------
InterfaceRef SAL_CALL OFormattedFieldWrapper_CreateInstance_ForceFormatted(const Reference<XMultiServiceFactory>& _rxFactory)
{
    return *(new OFormattedFieldWrapper(_rxFactory, sal_True));
}

//------------------------------------------------------------------
InterfaceRef SAL_CALL OFormattedFieldWrapper_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory)
{
    return *(new OFormattedFieldWrapper(_rxFactory, sal_False));
}

//------------------------------------------------------------------
OFormattedFieldWrapper::OFormattedFieldWrapper(const Reference<XMultiServiceFactory>& _rxFactory, sal_Bool _bActAsFormatted)
    :m_pEditPart(NULL)
    ,m_xServiceFactory(_rxFactory)
{
    DBG_CTOR(OFormattedFieldWrapper, NULL);

    if (_bActAsFormatted)
    {
        increment(m_refCount);
        {
            // instantiate an FormattedModel
            InterfaceRef  xFormattedModel;
            // (instantiate it directly ..., as the OFormattedModel isn't registered for any service names anymore)
            OFormattedModel* pModel = new OFormattedModel(m_xServiceFactory);
            query_interface(static_cast<XWeak*>(pModel), xFormattedModel);

            m_xAggregate = Reference<XAggregation> (xFormattedModel, UNO_QUERY);
            DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::OFormattedFieldWrapper : the OFormattedModel didn't have an XAggregation interface !");

            // _before_ setting the delegator, give it to the member references
            query_interface(xFormattedModel, m_xFormattedPart);
            m_pEditPart = new OEditModel(m_xServiceFactory);
            m_pEditPart->acquire();
        }
        if (m_xAggregate.is())
        {	// has to be in it's own block because of the temporary variable created by *this
            m_xAggregate->setDelegator(static_cast<XWeak*>(this));
        }
        decrement(m_refCount);
    }
}

//------------------------------------------------------------------
OFormattedFieldWrapper::OFormattedFieldWrapper( const OFormattedFieldWrapper* _pCloneSource )
    :m_xServiceFactory( _pCloneSource->m_xServiceFactory )
    ,m_pEditPart( NULL )
{
    Reference< XCloneable > xCloneAccess;
    query_aggregation( _pCloneSource->m_xAggregate, xCloneAccess );

    // clone the aggregate
    if ( xCloneAccess.is() )
    {
        increment( m_refCount );
        {
            Reference< XCloneable > xClone = xCloneAccess->createClone();
            m_xAggregate = Reference< XAggregation >( xClone, UNO_QUERY );
            DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::OFormattedFieldWrapper : invalid aggregate clone!");

            query_interface( Reference< XInterface >( xClone.get() ), m_xFormattedPart );

            if ( _pCloneSource->m_pEditPart )
                m_pEditPart = new OEditModel( _pCloneSource->m_pEditPart, _pCloneSource->m_xServiceFactory );
        }
        if ( m_xAggregate.is() )
        {	// has to be in it's own block because of the temporary variable created by *this
            m_xAggregate->setDelegator( static_cast< XWeak* >( this ) );
        }
        decrement( m_refCount );
    }
    else
    {	// the clone source does not yet have an aggregate -> we don't yet need one, too
    }
}

//------------------------------------------------------------------
OFormattedFieldWrapper::~OFormattedFieldWrapper()
{
    // release the aggregated object (if any)
    if (m_xAggregate.is())
        m_xAggregate->setDelegator(InterfaceRef ());

    if (m_pEditPart)
        m_pEditPart->release();

    DBG_DTOR(OFormattedFieldWrapper, NULL);
}

//------------------------------------------------------------------
Any SAL_CALL OFormattedFieldWrapper::queryAggregation(const Type& _rType) throw (RuntimeException)
{
    Any aReturn;

    if (_rType.equals( ::getCppuType( static_cast< Reference< XTypeProvider >* >(NULL) ) ) )
    {	// a XTypeProvider interface needs a working aggregate - we don't want to give the type provider
        // of our base class (OFormattedFieldWrapper_Base) to the caller as it supplies nearly nothing
        ensureAggregate();
        if (m_xAggregate.is())
            aReturn = m_xAggregate->queryAggregation(_rType);
    }

    if (!aReturn.hasValue())
    {
        aReturn = OFormattedFieldWrapper_Base::queryAggregation(_rType);

        if ((_rType.equals( ::getCppuType( static_cast< Reference< XServiceInfo >* >(NULL) ) ) ) && aReturn.hasValue())
        {	// somebody requested an XServiceInfo interface and our base class provided it
            // check our aggregate if it has one, too
            ensureAggregate();
        }

        if (!aReturn.hasValue())
        {
            aReturn = ::cppu::queryInterface( _rType,
                static_cast< XPersistObject* >( this ),
                static_cast< XCloneable* >( this )
            );

            if (!aReturn.hasValue())
            {
                // somebody requests an interface other than the basics (XInterface) and other than
                // the two we can supply without an aggregate. So ensure
                // the aggregate exists.
                ensureAggregate();
                if (m_xAggregate.is())
                    aReturn = m_xAggregate->queryAggregation(_rType);
            }
        }
    }

    return aReturn;
}

//------------------------------------------------------------------
::rtl::OUString SAL_CALL OFormattedFieldWrapper::getServiceName() throw(RuntimeException)
{
    // return the old compatibility name for an EditModel
    return FRM_COMPONENT_EDIT;
}

//------------------------------------------------------------------
::rtl::OUString SAL_CALL OFormattedFieldWrapper::getImplementationName(  ) throw (RuntimeException)
{
    return ::rtl::OUString::createFromAscii("com.sun.star.comp.forms.OFormattedFieldWrapper");
}

//------------------------------------------------------------------
sal_Bool SAL_CALL OFormattedFieldWrapper::supportsService( const ::rtl::OUString& _rServiceName ) throw (RuntimeException)
{
    DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::supportsService: should never have made it 'til here without an aggregate!");
    Reference< XServiceInfo > xSI;
    m_xAggregate->queryAggregation(::getCppuType(static_cast< Reference< XServiceInfo >* >(NULL))) >>= xSI;
    return xSI->supportsService(_rServiceName);
}

//------------------------------------------------------------------
Sequence< ::rtl::OUString > SAL_CALL OFormattedFieldWrapper::getSupportedServiceNames(  ) throw (RuntimeException)
{
    DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::getSupportedServiceNames: should never have made it 'til here without an aggregate!");
    Reference< XServiceInfo > xSI;
    m_xAggregate->queryAggregation(::getCppuType(static_cast< Reference< XServiceInfo >* >(NULL))) >>= xSI;
    return xSI->getSupportedServiceNames();
}

//------------------------------------------------------------------
void SAL_CALL OFormattedFieldWrapper::write(const Reference<XObjectOutputStream>& _rxOutStream) throw( IOException, RuntimeException )
{
    // can't write myself
    ensureAggregate();

    // if we act as real edit field, we can simple forward this write request
    if (!m_xFormattedPart.is())
    {
        Reference<XPersistObject>  xAggregatePersistence;
        query_aggregation(m_xAggregate, xAggregatePersistence);
        DBG_ASSERT(xAggregatePersistence.is(), "OFormattedFieldWrapper::write : don't know how to handle this : can't write !");
            // oops ... We gave an XPersistObject interface to the caller but now we aren't an XPersistObject ...
        if (xAggregatePersistence.is())
            xAggregatePersistence->write(_rxOutStream);
        return;
    }

    // else we have to write an edit part first
    DBG_ASSERT(m_pEditPart, "OFormattedFieldWrapper::write : formatted part without edit part ?");

    // for this we transfer the current props of the formatted part to the edit part
    Reference<XPropertySet>  xFormatProps(m_xFormattedPart, UNO_QUERY);
    Reference<XPropertySet>  xEditProps;
    query_interface(static_cast<XWeak*>(m_pEditPart), xEditProps);

    Locale aAppLanguage = Application::GetSettings().GetUILocale();
    dbtools::TransferFormComponentProperties(xFormatProps, xEditProps, aAppLanguage);

    // then write the edit part, after switching to "fake mode"
    m_pEditPart->enableFormattedWriteFake();
    m_pEditPart->write(_rxOutStream);
    m_pEditPart->disableFormattedWriteFake();

    // and finally write the formatted part we're really interested in
    m_xFormattedPart->write(_rxOutStream);
}

//------------------------------------------------------------------
void SAL_CALL OFormattedFieldWrapper::read(const Reference<XObjectInputStream>& _rxInStream) throw( IOException, RuntimeException )
{
    if (m_xAggregate.is())
    {	//  we alread did a decision if we're an EditModel or a FormattedModel

        // if we act as formatted, we have to read the edit part first
        if (m_xFormattedPart.is())
        {
            // two possible cases:
            // a) the stuff was written by a version which didn't work with an Edit header (all intermediate
            //		versions >5.1 && <=568)
            // b) it was written by a version using edit headers
            // as we can distinguish a) from b) only after we have read the edit part, we need to remember the
            // position
            Reference<XMarkableStream>  xInMarkable(_rxInStream, UNO_QUERY);
            DBG_ASSERT(xInMarkable.is(), "OFormattedFieldWrapper::read : can only work with markable streams !");
            sal_Int32 nBeforeEditPart = xInMarkable->createMark();

            m_pEditPart->read(_rxInStream);
                // this only works because an edit model can read the stuff written by a formatted model (maybe with
                // some assertions) , but not vice versa
            if (!m_pEditPart->lastReadWasFormattedFake())
            {	// case a), written with a version without the edit part fake, so seek to the start position, again
                xInMarkable->jumpToMark(nBeforeEditPart);
            }
            xInMarkable->deleteMark(nBeforeEditPart);
        }

        Reference<XPersistObject>  xAggregatePersistence;
        query_aggregation(m_xAggregate, xAggregatePersistence);
        DBG_ASSERT(xAggregatePersistence.is(), "OFormattedFieldWrapper::read : don't know how to handle this : can't read !");
            // oops ... We gave an XPersistObject interface to the caller but now we aren't an XPersistObject ...

        if (xAggregatePersistence.is())
            xAggregatePersistence->read(_rxInStream);
        return;
    }

    // we have to decide from the data within the stream whether we should be an EditModel or a FormattedModel
    OEditBaseModel* pNewAggregate = NULL;

    // let an OEditModel do the reading
    OEditModel* pBasicReader = new OEditModel(m_xServiceFactory);
    pBasicReader->read(_rxInStream);

    // was it really an edit model ?
    if (!pBasicReader->lastReadWasFormattedFake())
        // yes -> all fine
        pNewAggregate = pBasicReader;
    else
    {	// no -> substitute it with a formatted model

        // let the formmatted model do the reading
        OFormattedModel* pFormattedReader = new OFormattedModel(m_xServiceFactory);
        pFormattedReader->read(_rxInStream);

        // for the next write (if any) : the FormattedModel and the EditModel parts
        query_interface(static_cast<XWeak*>(pFormattedReader), m_xFormattedPart);
        m_pEditPart = pBasicReader;
        m_pEditPart->acquire();

        // aggregate the formatted part below
        pNewAggregate = pFormattedReader;
    }

    // do the aggregation
    increment(m_refCount);
    {
        query_interface(static_cast<XWeak*>(pNewAggregate), m_xAggregate);
        DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::read : the OEditModel didn't have an XAggregation interface !");
    }
    if (m_xAggregate.is())
    {	// has to be in it's own block because of the temporary variable created by *this
        m_xAggregate->setDelegator(static_cast<XWeak*>(this));
    }
    decrement(m_refCount);
}

//------------------------------------------------------------------
Reference< XCloneable > SAL_CALL OFormattedFieldWrapper::createClone(  ) throw (RuntimeException)
{
    ensureAggregate();

    return new OFormattedFieldWrapper( this );
}

//------------------------------------------------------------------
void OFormattedFieldWrapper::ensureAggregate()
{
    if (m_xAggregate.is())
        return;

    increment(m_refCount);
    {
        // instantiate an EditModel (the only place where we are allowed to decide that we're an FormattedModel
        // is in ::read)
        InterfaceRef  xEditModel = m_xServiceFactory->createInstance(FRM_SUN_COMPONENT_TEXTFIELD);
        if (!xEditModel.is())
        {
            // arghhh ... instantiate it directly ... it's dirty, but we really need this aggregate
            OEditModel* pModel = new OEditModel(m_xServiceFactory);
            query_interface(static_cast<XWeak*>(pModel), xEditModel);
        }

        m_xAggregate = Reference<XAggregation> (xEditModel, UNO_QUERY);
        DBG_ASSERT(m_xAggregate.is(), "OFormattedFieldWrapper::ensureAggregate : the OEditModel didn't have an XAggregation interface !");

        {
            Reference< XServiceInfo > xSI(m_xAggregate, UNO_QUERY);
            if (!xSI.is())
            {
                DBG_ERROR("OFormattedFieldWrapper::ensureAggregate: the aggregate has nbo XServiceInfo!");
                m_xAggregate.clear();
            }
        }
    }
    if (m_xAggregate.is())
    {	// has to be in it's own block because of the temporary variable created by *this
        m_xAggregate->setDelegator(static_cast<XWeak*>(this));
    }
    decrement(m_refCount);
}

//.........................................................................
}
//.........................................................................


}
