 /*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: impswfdialog.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-17 07:39:20 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_filter.hxx"

#include "impswfdialog.hxx"
#include "impswfdialog.hrc"

using namespace rtl;
using namespace com::sun::star::uno;
using namespace com::sun::star::beans;

// ----------------
// - ImpPDFDialog -
// ----------------

ImpSWFDialog::ImpSWFDialog( Window* pParent, ResMgr& rResMgr, Sequence< PropertyValue >& rFilterData ) :
    ModalDialog( pParent, ResId( DLG_OPTIONS, &rResMgr ) ),
    maFiDescr( this, ResId( FI_DESCR ) ),
    maNumFldQuality( this, ResId( NUM_FLD_QUALITY ) ),
    maFiExportAllDescr( this, ResId( FI_EXPORT_ALL_DESCR ) ),
    maCheckExportAll( this, ResId( BOOL_EXPORT_ALL ) ),
    maFiExportBackgroundsDescr( this, ResId( FI_EXPORT_BACKGROUNDS_DESCR ) ),
    maCheckExportBackgrounds( this, ResId( BOOL_EXPORT_BACKGROUNDS ) ),
    maFiExportBackgroundObjectsDescr( this, ResId( FI_EXPORT_BACKGROUND_OBJECTS_DESCR ) ),
    maCheckExportBackgroundObjects( this, ResId( BOOL_EXPORT_BACKGROUND_OBJECTS ) ),
    maFiExportSlideContentsDescr( this, ResId( FI_EXPORT_SLIDE_CONTENTS_DESCR ) ),
    maCheckExportSlideContents( this, ResId( BOOL_EXPORT_SLIDE_CONTENTS ) ),
    maFiExportSoundDescr( this, ResId( FI_EXPORT_SOUND_DESCR ) ),
    maCheckExportSound( this, ResId( BOOL_EXPORT_SOUND ) ),
    maFiExportOLEAsJPEGDescr( this, ResId( FI_EXPORT_OLE_AS_JPEG_DESCR ) ),
    maCheckExportOLEAsJPEG( this, ResId( BOOL_EXPORT_OLE_AS_JPEG ) ),
    maFiExportMultipleFilesDescr( this, ResId( FI_EXPORT_MULTIPLE_FILES_DESCR ) ),
    maCheckExportMultipleFiles( this, ResId( BOOL_EXPORT_MULTIPLE_FILES ) ),

    maBtnOK( this, ResId( BTN_OK ) ),
    maBtnCancel( this, ResId( BTN_CANCEL ) ),
    maBtnHelp( this, ResId( BTN_HELP ) ),
    maConfigItem( String( RTL_CONSTASCII_USTRINGPARAM( "Office.Common/Filter/Flash/Export/" ) ), &rFilterData )
{
    const ULONG nCompressMode = maConfigItem.ReadInt32( String( RTL_CONSTASCII_USTRINGPARAM( "CompressMode" ) ), 75 );
    maNumFldQuality.SetValue( nCompressMode );

    maCheckExportAll.Check();
    maCheckExportSlideContents.Check();
    maCheckExportSound.Check();

    maCheckExportAll.SetToggleHdl( LINK( this, ImpSWFDialog, OnToggleCheckbox ) );

    maCheckExportBackgrounds.Disable(); maFiExportBackgroundsDescr.Disable();
    maCheckExportBackgroundObjects.Disable(); maFiExportBackgroundObjectsDescr.Disable();
    maCheckExportSlideContents.Disable(); maFiExportSlideContentsDescr.Disable();

#ifdef AUGUSTUS
    maCheckExportMultipleFiles.Check();
#endif

    FreeResource();
}

// -----------------------------------------------------------------------------

ImpSWFDialog::~ImpSWFDialog()
{
}

// -----------------------------------------------------------------------------

Sequence< PropertyValue > ImpSWFDialog::GetFilterData()
{
    sal_Int32 nCompressMode = (sal_Int32)maNumFldQuality.GetValue();
    maConfigItem.WriteInt32( OUString( RTL_CONSTASCII_USTRINGPARAM( "CompressMode" ) ), nCompressMode );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportAll" ) ), maCheckExportAll.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportBackgrounds" ) ), maCheckExportBackgrounds.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportBackgroundObjects" ) ), maCheckExportBackgroundObjects.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportSlideContents" ) ), maCheckExportSlideContents.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportSound" ) ), maCheckExportSound.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportOLEAsJPEG" ) ), maCheckExportOLEAsJPEG.IsChecked() );
    maConfigItem.WriteBool( OUString( RTL_CONSTASCII_USTRINGPARAM( "ExportMultipleFiles" ) ), maCheckExportMultipleFiles.IsChecked() );

    Sequence< PropertyValue > aRet( maConfigItem.GetFilterData() );

    return aRet;
}

// AS: This is called whenever the user toggles one of the checkboxes
IMPL_LINK( ImpSWFDialog, OnToggleCheckbox, CheckBox*, pBox )
{
    if (pBox == &maCheckExportAll)
    {
        maCheckExportBackgrounds.Enable(!maCheckExportBackgrounds.IsEnabled()); 
        maFiExportBackgroundsDescr.Enable(!maFiExportBackgroundsDescr.IsEnabled());
        maCheckExportBackgroundObjects.Enable(!maCheckExportBackgroundObjects.IsEnabled()); 
        maFiExportBackgroundObjectsDescr.Enable(!maFiExportBackgroundObjectsDescr.IsEnabled());
        maCheckExportSlideContents.Enable(!maCheckExportSlideContents.IsEnabled()); 
        maFiExportSlideContentsDescr.Enable(!maFiExportSlideContentsDescr.IsEnabled());
    }

    return 0;
}
