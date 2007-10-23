/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: linksrc.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:25:37 $
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
#ifndef _LINKSRC_HXX
#define _LINKSRC_HXX

#ifndef _TOOLS_REF_HXX
#include <tools/ref.hxx>
#endif
#ifndef _RTTI_HXX
#include <tools/rtti.hxx>
#endif

#ifndef _SAL_CONFIG_H
#include <sal/config.h>
#define _SAL_CONFIG_H
#endif

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

namespace com { namespace sun { namespace star { namespace uno
{
    class Any;
    //class Type;
}}}}
class Window;
class String;

#ifndef ADVISEMODE_NODATA
// Muessen die gleichen Werte wie Ole2 ADVF_* sein
#define ADVISEMODE_NODATA       0x01
//#define ADVISEMODE_PRIMEFIRST   0x02
#define ADVISEMODE_ONLYONCE     0x04
//#define ADVISEMODE_DATAONSTOP   0x40
#endif

namespace so3
{

class SvBaseLink;
struct SvLinkSource_Impl;

class SO3_DLLPUBLIC SvLinkSource : public SvRefBase
{
private:
    SvLinkSource_Impl *	pImpl; // compatible area
public:
                        TYPEINFO();

                        SvLinkSource();
    virtual				~SvLinkSource();

//	SvBaseLink*			GetDataBaseLink() const;
    BOOL				HasDataLinks( const SvBaseLink* = 0 ) const;

    void				Closed();

    ULONG 				GetUpdateTimeout() const;
    void				SetUpdateTimeout( ULONG nTime );
                        // notify the sink, the mime type is not
                        // a selection criterion
    void				DataChanged( const String & rMimeType,
                                    const ::com::sun::star::uno::Any & rVal );
    void				SendDataChanged();
    void				NotifyDataChanged();

    virtual BOOL		Connect( SvBaseLink * );
    virtual BOOL		GetData( ::com::sun::star::uno::Any & rData /*out param*/,
                                const String & rMimeType,
                                BOOL bSynchron = FALSE );

                        // TRUE => waitinmg for data
    virtual BOOL		IsPending() const;
                        // TRUE => data complete loaded
    virtual BOOL		IsDataComplete() const;

    virtual String		Edit( Window *, SvBaseLink * );

    void				AddDataAdvise( SvBaseLink *, const String & rMimeType,
                                        USHORT nAdviceMode );
    void				RemoveAllDataAdvise( SvBaseLink * );

    void				AddConnectAdvise( SvBaseLink * );
    void				RemoveConnectAdvise( SvBaseLink * );
};

SV_DECL_IMPL_REF(SvLinkSource);

}

#endif
