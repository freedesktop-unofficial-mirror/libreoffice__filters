/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: plugin.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2007-10-23 14:26:35 $
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

#ifndef _PLUGIN_HXX
#define _PLUGIN_HXX

#include <bf_so3/ipobj.hxx>
#include <svtools/ownlist.hxx>
#include <bf_so3/ipenv.hxx>

#ifndef INCLUDED_SO3DLLAPI_H
#include "bf_so3/so3dllapi.h"
#endif

//=========================================================================
class Timer;
class INetURLObject;
struct SvPlugInData_Impl;
class SjJScriptPluginObject;
class SjJScriptJavaObject;
class SO3_DLLPUBLIC SvPlugInObject : public SvInPlaceObject
/*	[Beschreibung]

    Die Klasse PlugInObject ist die Abbildung eines InPlace-Objektes
    auf einen PlugIn-Server. Dieses Objekt kann nur InPlace- und
    nicht UI-Aktiviert werden.

    [Probleme]
    Es handelt sich bei diesem Objekt immer um einen Link. Dieser Link
    kann allerdings InPlace aktiviert werden.
*/
{
friend class SvPlugInEnvironment;
friend class Executor_Impl;
private:
    SvPlugInEnvironment * pPlugInEnv;
    SvPlugInData_Impl *	pImpl;
    SvCommandList	aCmdList;
    INetURLObject*	pURL;
    USHORT			nPlugInMode;// nicht ein Enum, wegen header file
                                // und streamen

    DECL_STATIC_LINK( SvPlugInObject, NewPlugInHdl_Impl, Timer * );
    DECL_STATIC_LINK( SvPlugInObject, DataAvailable, void* );

    SO3_DLLPRIVATE void			DataChanged_Impl( BOOL bOnlyEmbedSource );
protected:
    SO3_DLLPRIVATE BOOL			DoStartPlugIn( );
    SO3_DLLPRIVATE BOOL			StartPlugIn( );
    SO3_DLLPRIVATE virtual void    FillClass( SvGlobalName * pClassName,
                               ULONG * pFormat,
                               String * pAppName,
                               String * pFullTypeName,
                               String * pShortTypeName,
                               long nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const;
                    // Protokoll
    SO3_DLLPRIVATE virtual void    Open( BOOL bOpen );
    SO3_DLLPRIVATE virtual void    Embed( BOOL );
    SO3_DLLPRIVATE virtual void    InPlaceActivate( BOOL );
    SO3_DLLPRIVATE virtual ErrCode Verb( long, SvEmbeddedClient * pCallerClient,
                        Window * pWin, const Rectangle * pWorkRectPixel );

                    // Datenaustausch
    SO3_DLLPRIVATE virtual void    SetVisArea( const Rectangle & rVisArea );
    SO3_DLLPRIVATE virtual void    Draw( OutputDevice *,
                          const JobSetup & rSetup,
                          USHORT nAspect = ASPECT_CONTENT );

                    // Laden speichern
    SO3_DLLPRIVATE virtual BOOL    InitNew( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Load( SvStorage * );
    SO3_DLLPRIVATE virtual BOOL    Save();
    SO3_DLLPRIVATE virtual BOOL    SaveAs( SvStorage * );
    SO3_DLLPRIVATE virtual void    HandsOff();
    SO3_DLLPRIVATE virtual BOOL    SaveCompleted( SvStorage * );

    // Spaeter gerne mal virtuell...
    SO3_DLLPRIVATE void            SetMIMEDetectedLink( const Link& rLink );

    SO3_DLLPRIVATE 				~SvPlugInObject();
public:
                    SO2_DECL_BASIC_CLASS_DLL(SvPlugInObject,SOAPP)
                    SvPlugInObject();

    virtual ULONG	GetMiscStatus() const;
    virtual BOOL	IsLink() const;

                    // spezielle Internet Methoden
    void			SetCommandList( const SvCommandList & rList );
    const SvCommandList & GetCommandList() const { return aCmdList; }
    void			SetURL( const INetURLObject & rURL );
    INetURLObject *	GetURL() const { return pURL; }
    void			SetMimeType( const String & rMimeType );
    const String &	GetMimeType() const;
    void			SetPlugInMode( USHORT );
    USHORT  		GetPlugInMode() const { return nPlugInMode; }
};

SO2_DECL_IMPL_REF(SvPlugInObject)

#endif // _PLUGIN_HXX
