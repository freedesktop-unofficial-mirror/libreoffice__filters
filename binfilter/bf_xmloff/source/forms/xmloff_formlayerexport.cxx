/*************************************************************************
 *
 *  $RCSfile: xmloff_formlayerexport.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 19:59:17 $
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
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
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

#include <stdio.h>

// auto strip #ifndef _XMLOFF_FORMLAYEREXPORT_HXX_
// auto strip #include "formlayerexport.hxx"
// auto strip #endif
// auto strip #ifndef _XMLOFF_FORMS_STRINGS_HXX_
// auto strip #include "strings.hxx"
// auto strip #endif
// auto strip #ifndef _XMLOFF_ELEMENTEXPORT_HXX_
// auto strip #include "elementexport.hxx"
// auto strip #endif
// auto strip #ifndef _XMLOFF_XMLNMSPE_HXX
// auto strip #include "xmlnmspe.hxx"
// auto strip #endif
#ifndef _XMLOFF_XMLEXP_HXX
#include "xmlexp.hxx"
#endif
#ifndef _XMLOFF_FORMS_LAYEREXPORT_HXX_
#include "layerexport.hxx"
#endif
// auto strip #ifndef _XMLOFF_FORMS_PROPERTYEXPORT_HXX_
// auto strip #include "propertyexport.hxx"
// auto strip #endif
#ifndef _OSL_DIAGNOSE_H_
#include <osl/diagnose.h>
#endif
// auto strip #ifndef _COMPHELPER_EXTRACT_HXX_
// auto strip #include <comphelper/extract.hxx>
// auto strip #endif
// auto strip #ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
// auto strip #include <com/sun/star/lang/XServiceInfo.hpp>
// auto strip #endif
// auto strip #ifndef _COMPHELPER_STLTYPES_HXX_
// auto strip #include <comphelper/stl_types.hxx>
// auto strip #endif
#ifndef _XMLOFF_FORMS_OFFICEFORMS_HXX_
#include "officeforms.hxx"
#endif
namespace binfilter {


//.........................................................................
namespace xmloff
{
//.........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::awt;
    using namespace ::com::sun::star::beans;
    using namespace ::com::sun::star::container;
    using namespace ::com::sun::star::drawing;
    using namespace ::com::sun::star::frame;

    //=====================================================================
    //= OFormLayerXMLExport
    //=====================================================================

    //---------------------------------------------------------------------
    OFormLayerXMLExport::OFormLayerXMLExport(SvXMLExport& _rContext)
        :m_rContext(_rContext)
        ,m_pImpl(new OFormLayerXMLExport_Impl(_rContext))
    {
    }

    //---------------------------------------------------------------------
    OFormLayerXMLExport::~OFormLayerXMLExport()
    {
        delete m_pImpl;
        m_pImpl = NULL;
    }

    //---------------------------------------------------------------------
    sal_Bool OFormLayerXMLExport::seekPage(const Reference< XDrawPage >& _rxDrawPage)
    {
        return m_pImpl->seekPage(_rxDrawPage);
    }

    //---------------------------------------------------------------------
    ::rtl::OUString OFormLayerXMLExport::getControlId(const Reference< XPropertySet >& _rxControl)
    {
        return m_pImpl->getControlId(_rxControl);
    }

    //---------------------------------------------------------------------
    ::rtl::OUString OFormLayerXMLExport::getControlNumberStyle( const Reference< XPropertySet >& _rxControl )
    {
        return m_pImpl->getControlNumberStyle(_rxControl);
    }

    //---------------------------------------------------------------------
    ::vos::ORef< SvXMLExportPropertyMapper > OFormLayerXMLExport::getStylePropertyMapper()
    {
        return m_pImpl->getStylePropertyMapper();
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::initialize()
    {
        m_pImpl->clear();
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::examineForms(const Reference< XDrawPage >& _rxDrawPage)
    {
        try
        {
            m_pImpl->examineForms(_rxDrawPage);
        }
        catch(Exception&)
        {
            OSL_ENSURE(sal_False, "OFormLayerXMLExport::examine: could not examine the draw page!");
        }
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::exportForms(const Reference< XDrawPage >& _rxDrawPage)
    {
        m_pImpl->exportForms(_rxDrawPage);
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::exportControlNumberStyles()
    {
        m_pImpl->exportControlNumberStyles();
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::exportAutoControlNumberStyles()
    {
        m_pImpl->exportAutoControlNumberStyles();
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::exportAutoStyles()
    {
        m_pImpl->exportAutoStyles();
    }

    //---------------------------------------------------------------------
    void OFormLayerXMLExport::excludeFromExport( const Reference< XControlModel > _rxControl )
    {
        m_pImpl->excludeFromExport( _rxControl );
    }

    //=========================================================================
    //= OOfficeFormsExport
    //=========================================================================
    //-------------------------------------------------------------------------
    OOfficeFormsExport::OOfficeFormsExport( SvXMLExport& _rExp )
        :m_pImpl(NULL)
    {
        m_pImpl = new OFormsRootExport(_rExp);
    }

    //-------------------------------------------------------------------------
    OOfficeFormsExport::~OOfficeFormsExport()
    {
        delete m_pImpl;
    }

//.........................................................................
}	// namespace xmloff
//.........................................................................

/*************************************************************************
 * history:
 *	$Log: not supported by cvs2svn $
 *	Revision 1.1.20.1  2004/07/13 08:48:50  aw
 *	#117295# minimize_includes step2
 *	
 *	Revision 1.1  2003/12/05 09:34:14  aw
 *	Added bf_xmloff files
 *	
 *	Revision 1.13  2002/10/25 07:58:00  fs
 *	#104402# re-introduced exportAutoStyles
 *	
 *	Revision 1.12  2002/09/25 12:02:38  fs
 *	#103597# +excludeFromExport
 *	
 *	Revision 1.11  2001/05/28 14:59:18  fs
 *	#86712# added control number style related functionality
 *	
 *	Revision 1.10  2001/03/20 13:35:38  fs
 *	#83970# +OOfficeFormsExport
 *	
 *	Revision 1.9  2001/03/20 08:04:08  fs
 *	removed exportAutoStyles (was obsolete)
 *	
 *	Revision 1.8  2001/03/16 14:36:39  sab
 *	did the required change (move of extract.hxx form cppuhelper to comphelper)
 *	
 *	Revision 1.7  2001/02/01 09:46:47  fs
 *	no own style handling anymore - the shape exporter is responsible for our styles now
 *
 *	Revision 1.6  2000/12/18 16:22:35  fs
 *	forgot an & on the getControlId parameter
 *
 *	Revision 1.5  2000/12/18 15:14:35  fs
 *	some changes ... now exporting/importing styles
 *
 *	Revision 1.4  2000/12/06 17:28:05  fs
 *	changes for the formlayer import - still under construction
 *
 *	Revision 1.3  2000/12/03 10:57:06  fs
 *	some changes to support more than one page to be examined/exported
 *
 *	Revision 1.2  2000/11/29 10:32:13  mh
 *	add: header for Solaris8
 *
 *	Revision 1.1  2000/11/17 19:02:16  fs
 *	initial checkin - export and/or import the applications form layer
 *
 *
 *	Revision 1.0 13.11.00 14:58:17  fs
 ************************************************************************/

}//end of namespace binfilter
