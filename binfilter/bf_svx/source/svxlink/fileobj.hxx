/*************************************************************************
 *
 *  $RCSfile: fileobj.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 16:34:33 $
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
#ifndef _FILEOBJ_HXX
#define _FILEOBJ_HXX

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif
#ifndef _LINKSRC_HXX //autogen
#include <so3/linksrc.hxx>
#endif
#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif
class Graphic;
namespace binfilter {

struct Impl_DownLoadData;


class SvFileObject : public ::so3::SvLinkSource
{
    String sFileNm;
    String sFilter;
    String sReferer;
    SfxMediumRef xMed;
    Impl_DownLoadData* pDownLoadData;

    BYTE nType;

    BOOL bProgress : 1;
    BOOL bLoadAgain : 1;
    BOOL bSynchron : 1;
    BOOL bLoadError : 1;
    BOOL bWaitForData : 1;
    BOOL bInNewData : 1;
    BOOL bDataReady : 1;
    BOOL bMedUseCache : 1;
    BOOL bNativFormat : 1;
    BOOL bClearMedium : 1;
    BOOL bStateChangeCalled : 1;
    BOOL bInCallDownLoad : 1;

    BOOL GetGraphic_Impl( Graphic&, SvStream* pStream = 0 );
    BOOL LoadFile_Impl();
    void SendStateChg_Impl( USHORT nState );

    DECL_STATIC_LINK( SvFileObject, DelMedium_Impl, SfxMediumRef* );
    DECL_STATIC_LINK( SvFileObject, LoadGrfReady_Impl, void* );
    DECL_STATIC_LINK( SvFileObject, LoadGrfNewData_Impl, void* );
protected:
    virtual ~SvFileObject();

public:
    SvFileObject();

    virtual BOOL GetData( ::com::sun::star::uno::Any & rData /*out param*/,
                            const String & rMimeType,
                            BOOL bSynchron = FALSE );

    virtual BOOL Connect( ::so3::SvBaseLink* );
//STRIP001 	virtual String Edit( Window*, ::so3::SvBaseLink* );

    // erfrage ob das man direkt auf die Daten zugreifen kann oder ob das
    // erst angestossen werden muss
//STRIP001 	virtual BOOL IsPending() const;
//STRIP001 	virtual BOOL IsDataComplete() const;

    void CancelTransfers();
//STRIP001 	void SetTransferPriority( USHORT nPrio );
};


}//end of namespace binfilter
#endif

