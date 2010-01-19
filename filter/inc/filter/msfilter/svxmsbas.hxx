/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: svxmsbas.hxx,v $
 * $Revision: 1.6 $
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

#ifndef _SVXMSBAS_HXX
#define _SVXMSBAS_HXX

#include <tools/solar.h>
#include "filter/msfilter/msfilterdllapi.h"

#include <sot/storage.hxx>

class SfxObjectShell;

/* Construct with the root storage of the MS document, with bImportCode
 * set the visual basic code will be imported into the stardocument when Import
 * is called, with bCopyStorage set, the visual basic storage tree will be
 * copied completely into staroffice, so that any future export to a msoffice
 * format will retain the vba code, allowing a lossless roundtrip from
 * msoffice to staroffice and back.
 *
 * Setting bAsComment to true in Import will import the visual basic as a
 * starbasic comment. Which is currently necessary, as vb is not valid sb.
 *
 * Setting bStripped will remove the "Attribute" lines from the vb, msoffice
 * does this itself when it shows the vb code in the vbeditor, so this is
 * probably what the user expects to see when viewing the code
 */

class MSFILTER_DLLPUBLIC SvxImportMSVBasic
{
public:
    SvxImportMSVBasic( SfxObjectShell &rDocS, SotStorage &rRoot,
                        BOOL bImportCode = TRUE, BOOL bCopyStorage = TRUE )
        :	xRoot(&rRoot), rDocSh(rDocS),
            bImport(bImportCode), bCopy(bCopyStorage)
        {}
    // returns the status of import:
    // 0 - nothing has done
    // bit 0 = 1 -> any code is imported to the SO-Basic
    // bit 1 = 1 -> the VBA - storage is copy to the ObjectShell storage
    int Import( const String& rStorageName, const String &rSubStorageName,
                BOOL bAsComment=TRUE, BOOL bStripped=TRUE );

    // only for the export - copy or delete the saved VBA-macro-storage
    // form the ObjectShell
    // - returns a warning code if a modified basic exist, in all other
    //   cases return ERRCODE_NONE.
    ULONG SaveOrDelMSVBAStorage( BOOL bSaveInto, const String& rStorageName );

    // check if the MS-VBA-Storage exist in the RootStorage of the DocShell.
    // If it exist, then return the WarningId for loosing the information.
    static ULONG GetSaveWarningOfMSVBAStorage( SfxObjectShell &rDocS );

    static String GetMSBasicStorageName();
private:
    SotStorageRef xRoot;
    SfxObjectShell &rDocSh;
    BOOL bImport;
    BOOL bCopy;

    MSFILTER_DLLPRIVATE BOOL ImportCode_Impl( const String& rStorageName,
                          const String &rSubStorageName,
                          BOOL bAsComment, BOOL bStripped);
    MSFILTER_DLLPRIVATE bool ImportForms_Impl(const String& rStorageName, 
        const String &rSubStorageName);
    MSFILTER_DLLPRIVATE BOOL CopyStorage_Impl( const String& rStorageName,
                           const String &rSubStorageName);
};

#endif
