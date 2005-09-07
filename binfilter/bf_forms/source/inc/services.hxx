/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: services.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:53:52 $
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

#ifndef _FRM_SERVICES_HXX_
#define _FRM_SERVICES_HXX_

#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif

#ifndef _FRM_STRINGS_HXX_
#include "strings.hxx"
#endif
namespace binfilter {

//... namespace frm .......................................................
namespace frm
{
//.........................................................................

// alle serviceNamen
DECLARE_CONSTASCII_USTRING(FRM_NUMBER_FORMATTER);
DECLARE_CONSTASCII_USTRING(FRM_NUMBER_FORMATS_SUPPLIER);

DECLARE_CONSTASCII_USTRING(VCL_CONTROL_EDIT);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_LISTBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_COMBOBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_GROUPBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_COMMANDBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_CHECKBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_IMAGEBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_FILECONTROL);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_DATEFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_FORMATTEDFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROL_IMAGECONTROL);

DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_EDIT);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_LISTBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_COMBOBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_GROUPBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_COMMANDBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_CHECKBOX);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_IMAGEBUTTON);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_FILECONTROL);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_DATEFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_FORMATTEDFIELD);
DECLARE_CONSTASCII_USTRING(VCL_CONTROLMODEL_IMAGECONTROL);

DECLARE_CONSTASCII_USTRING(AWT_CONTROL_TEXTFIELD);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_FORM);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_EDIT);		// alter service name (5.0)
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_TEXTFIELD);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_LISTBOX);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_COMBOBOX);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_GROUPBOX);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_COMMANDBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_CHECKBOX);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_GRID);		// alter service name (5.0)
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_GRIDCONTROL);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_IMAGEBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_FILECONTROL);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_DATEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_FORMATTEDFIELD);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_HIDDEN);	// alter service name (5.0)
DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_HIDDENCONTROL);

DECLARE_CONSTASCII_USTRING(FRM_COMPONENT_IMAGECONTROL);

DECLARE_CONSTASCII_USTRING(FRM_CONTROL_LISTBOX);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_COMBOBOX);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_GROUPBOX);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_CHECKBOX);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_COMMANDBUTTON);

DECLARE_CONSTASCII_USTRING(FRM_CONTROL_GRID);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_GRIDCONTROL);

DECLARE_CONSTASCII_USTRING(FRM_CONTROL_IMAGEBUTTON);

DECLARE_CONSTASCII_USTRING(FRM_CONTROL_EDIT);	  // alt
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_TEXTFIELD);

DECLARE_CONSTASCII_USTRING(FRM_CONTROL_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_DATEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_FILECONTROL);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_IMAGECONTROL);
DECLARE_CONSTASCII_USTRING(FRM_CONTROL_FORMATTEDFIELD);

DECLARE_CONSTASCII_USTRING(SRV_SDB_ROWSET);
DECLARE_CONSTASCII_USTRING(SRV_SDB_CONNECTION);
DECLARE_CONSTASCII_USTRING(SRV_SDBC_STATEMENT);

DECLARE_CONSTASCII_USTRING(SRV_AWT_POINTER);
DECLARE_CONSTASCII_USTRING(SRV_AWT_IMAGEPRODUCER);


DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_FORM);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_HTMLFORM);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_DATAFORM);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_TEXTFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_LISTBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_COMBOBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_GROUPBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_COMMANDBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_CHECKBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_GRIDCONTROL);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_IMAGEBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_FILECONTROL);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_DATEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_HIDDENCONTROL);
DECLARE_CONSTASCII_USTRING(FRM_SUN_COMPONENT_FORMATTEDFIELD);

DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_IMAGECONTROL );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_RADIOBUTTON );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_CHECKBOX );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_LISTBOX );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_COMBOBOX );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_TEXTFIELD );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_DATEFIELD );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_TIMEFIELD );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_NUMERICFIELD );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_CURRENCYFIELD );
DECLARE_CONSTASCII_USTRING( FRM_SUN_COMPONENT_DATABASE_PATTERNFIELD );

DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_TEXTFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_LISTBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_COMBOBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_RADIOBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_GROUPBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_FIXEDTEXT);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_COMMANDBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_CHECKBOX);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_GRIDCONTROL);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_IMAGEBUTTON);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_TIMEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_DATEFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_NUMERICFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_CURRENCYFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_PATTERNFIELD);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_IMAGECONTROL);
DECLARE_CONSTASCII_USTRING(FRM_SUN_CONTROL_FORMATTEDFIELD);

DECLARE_CONSTASCII_USTRING(FRM_SUN_FORMS_COLLECTION);
DECLARE_CONSTASCII_USTRING(FRM_SUN_INTERNATIONAL_INFO);


DECLARE_CONSTASCII_USTRING(FRM_SUN_FORMCOMPONENT);


//.........................................................................
}
//... namespace frm .......................................................

}//end of namespace binfilter
#endif // _FRM_SERVICES_HXX_

