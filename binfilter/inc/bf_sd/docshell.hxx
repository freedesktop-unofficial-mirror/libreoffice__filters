/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docshell.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:28:55 $
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

#ifndef _SD_DOCSHELL_HXX
#define _SD_DOCSHELL_HXX

#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#include <sot/factory.hxx>
#include <bf_so3/factory.hxx>

#ifndef _SD_GLOB_HXX
#include "glob.hxx"
#endif
#ifndef _SDMOD_HXX
#include "sdmod.hxx"
#endif
#ifndef _PRESENTATION_HXX
#include "pres.hxx"
#endif
class SvStream;

namespace binfilter {
class FontList;
class SfxStyleSheetBasePool;

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif

class SfxStatusBarManager;
class SdStyleSheetPool;
class FrameView;
class SdDrawDocument;
class SdView;
class FuPoor;
class SdPage;
class SfxPrinter;
struct SdrDocumentStreamInfo;
struct SpellCallbackInfo;
class SvxNameDialog;

// ------------------
// - SdDrawDocShell -
// ------------------

class SdDrawDocShell : public SfxObjectShell, public SfxInPlaceObject
{
protected:
    
    SfxProgress*		   	pProgress;
    SdDrawDocument* 		pDoc;
    SfxPrinter* 			pPrinter;
    DocumentType            eDocType;
    UINT16					nStyleFamily;
    const USHORT*           pFilterSIDs;    
    USHORT                  nFilterCount;   
    BOOL                    bFilterEnable;  
    BOOL					bUIActive;
    BOOL					bSdDataObj;
    BOOL                    bInDestruction;
    BOOL 					bOwnPrinter;
    BOOL                    mbNewDocument;

    void					Construct();

public:
    void                    UpdateRefDevice();
    virtual void	        Deactivate( BOOL bMDI );
    virtual BOOL	        InitNew( SvStorage * );
    virtual BOOL	        Load( SvStorage * );
    virtual void	        HandsOff();
    virtual BOOL	        Save();
    virtual BOOL	        SaveAs( SvStorage * pNewStor );
    virtual BOOL            SaveAsOwnFormat( SfxMedium& rMedium );
    virtual BOOL	        SaveCompleted( SvStorage * pNewStor );
    virtual void	        SetVisArea(const Rectangle& rRect);
    virtual Rectangle       GetVisArea(USHORT nAspect) const;
    virtual Printer*        GetDocumentPrinter();
    virtual SfxStyleSheetBasePool* GetStyleSheetPool();
    virtual void            FillClass(SvGlobalName* pClassName, ULONG*  pFormat, String* pAppName, String* pFullTypeName, String* pShortTypeName, long nFileFormat = SOFFICE_FILEFORMAT_CURRENT) const;
    virtual void            SetModified( BOOL = TRUE );

    static SfxPrinter* CreatePrinter( SvStream& rIn, SdDrawDocument& rDoc );
public:
    
                            TYPEINFO();
                            SFX_DECL_OBJECTFACTORY_DLL(SdDrawDocShell, SD_MOD());

                            SdDrawDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED, BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_IMPRESS);
                            SdDrawDocShell(SdDrawDocument* pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED, BOOL bSdDataObj=FALSE, DocumentType=DOCUMENT_TYPE_IMPRESS);
                            ~SdDrawDocShell();

    SdDrawDocument*         GetDoc();
    DocumentType            GetDocumentType() const { return eDocType; }

    SfxPrinter*             GetPrinter(BOOL bCreate);
    void			        SetPrinter(SfxPrinter *pNewPrinter);

    BOOL					IsUIActive() { return bUIActive; }
    BOOL                    IsInDestruction() const { return bInDestruction; }

                            
    void			        UpdateTablePointers();

    void                    SetSlotFilter(BOOL bEnable = FALSE, USHORT nCount = 0, const USHORT* pSIDs = NULL) { bFilterEnable = bEnable; nFilterCount = nCount; pFilterSIDs = pSIDs; }

    UINT16	                GetStyleFamily() const { return nStyleFamily; }
    void	                SetStyleFamily( UINT16 nSF ) { nStyleFamily = nSF; }

    bool                    IsNewPageNameValid( String & rInOutPageName, bool bResetStringIfStandardName = false );

    virtual OutputDevice* GetDocumentRefDev (void);

    DECL_LINK( RenameSlideHdl, SvxNameDialog* );

};

#ifndef SV_DECL_SDDRAWDOCSHELL_DEFINED
#define SV_DECL_SDDRAWDOCSHELL_DEFINED
SV_DECL_REF(SdDrawDocShell)
#endif

SV_IMPL_REF (SdDrawDocShell)

} //namespace binfilter
#endif // _SD_DOCSHELL_HXX
