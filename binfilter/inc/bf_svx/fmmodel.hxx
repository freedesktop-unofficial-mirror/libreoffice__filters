/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: fmmodel.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:51:48 $
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

#ifndef _SVX_FMMODEL_HXX
#define _SVX_FMMODEL_HXX

#ifndef _SVDMODEL_HXX
#include <bf_svx/svdmodel.hxx>
#endif
class SbxObject;
class SbxArray;
class SbxValue;
namespace binfilter {

class SvPersist;

class SfxItemPool;
class VCItemPool;
class FmXUndoEnvironment;
class SfxObjectShell;


struct FmFormModelImplData;
class FmFormModel :
    public SdrModel
{
private:
    FmFormModelImplData*	m_pImpl;
//	FmXUndoEnvironment*		pUndoEnv;
    SfxObjectShell*			pObjShell;
    sal_Bool			bStreamingOldVersion;

    sal_Bool			m_bOpenInDesignMode : 1;
    sal_Bool			m_bAutoControlFocus : 1;


public:
    TYPEINFO();

    FmFormModel(const XubString& rPath, SfxItemPool* pPool=NULL,
                SvPersist* pPers=NULL );
    FmFormModel(const XubString& rPath, SfxItemPool* pPool, SvPersist* pPers,
                FASTBOOL bUseExtColorTable);

    virtual ~FmFormModel();

    virtual void     InsertPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemovePage(sal_uInt16 nPgNum);
    virtual void     MovePage(USHORT nPgNum, USHORT nNewPos);
    virtual void     InsertMasterPage(SdrPage* pPage, sal_uInt16 nPos=0xFFFF);
    virtual SdrPage* RemoveMasterPage(sal_uInt16 nPgNum);

    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrIOHeader& rHead, SvStream& rIn);

    virtual SdrLayerID 		GetControlExportLayerId( const SdrObject& rObj ) const;
    SfxObjectShell* 		GetObjectShell() const { return pObjShell; }
    void 					SetObjectShell( SfxObjectShell* pShell );

    sal_Bool GetOpenInDesignMode() const { return m_bOpenInDesignMode; }
    void SetOpenInDesignMode( sal_Bool _bOpenDesignMode );

    sal_Bool	GetAutoControlFocus() const { return m_bAutoControlFocus; }
    void		SetAutoControlFocus( sal_Bool _bAutoControlFocus );

    /** check whether the OpenInDesignMode has been set explicitly or been loaded (<FALSE/>)
        or if it still has the default value from construction (<TRUE/>)
    */
    sal_Bool	OpenInDesignModeIsDefaulted( );

#if _SOLAR__PRIVATE
    void		implSetOpenInDesignMode( sal_Bool _bOpenDesignMode, sal_Bool _bForce );

    sal_Bool IsStreamingOldVersion() const { return bStreamingOldVersion; }
    FmXUndoEnvironment&	GetUndoEnv();

    XubString GetUniquePageId();
#endif

};

}//end of namespace binfilter
#endif          // _FM_FMMODEL_HXX

