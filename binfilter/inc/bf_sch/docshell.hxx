/*************************************************************************
 *
 *  $RCSfile: docshell.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:27 $
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

#ifndef _SCH_DOCSHELL_HXX
#define _SCH_DOCSHELL_HXX

#ifndef _SCHDLL0_HXX //autogen
#include "schdll0.hxx"
#endif

#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif

#ifndef _SFX_SHELL_HXX //autogen
#include <bf_sfx2/shell.hxx>
#endif

#ifndef _SVX_FLSTITEM_HXX //autogen
#include <bf_svx/flstitem.hxx>
#endif

#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SCHDLL0_HXX //autogen
#include <schdll0.hxx>
#endif
#ifndef _SFXREQUEST_HXX //autogen
#include <bf_sfx2/request.hxx>
#endif

#ifndef _SVSTOR_HXX //autogen
#include <so3/svstor.hxx>
#endif

#ifndef _CHTMODEL_HXX
#include "chtmodel.hxx"
#endif

#ifndef _SFXDOCFILE_HXX //autogen
#include <bf_sfx2/docfile.hxx>
#endif

#include "glob.hxx"

#ifndef SO2_DECL_SVSTORAGESTREAM_DEFINED
#define SO2_DECL_SVSTORAGESTREAM_DEFINED
SO2_DECL_REF(SvStorageStream)
#endif

#ifndef _COM_SUN_STAR_CHART_CHARTDATACHANGEEVENT_HPP_
#include <com/sun/star/chart/ChartDataChangeEvent.hpp>
#endif
class SfxStyleSheetBasePool;
class FontList;
class SfxUndoManager;
namespace binfilter {

class SdStyleSheetPool;
class SfxProgress;
class SfxPrinter;
class SfxMenuBarManager;
class SvInPlaceMenuBar;

/*************************************************************************
|*
|* Document-Shell fuer Draw-Dokumente
|*
\************************************************************************/

class SchChartDocShell: public SfxObjectShell, public SfxInPlaceObject
{
 private:
    ChartModel*			pChDoc;
    SfxUndoManager* 	pUndoManager;
    SfxPrinter* 		pPrinter;
    FontList*			pFontList;
    SfxProgress*		pProgress;
    BOOL 				bInitNewNoNewDoc;
    BOOL 				bOwnPrinter;
    BOOL				mbClipboardExport;

    void Construct() throw();

     // #61907# bei deaktivierung des InPlaceEdit evtl. gebufferte neue Daten
    // �bernehmen
 protected:
//STRIP001 	 virtual void        InPlaceActivate( BOOL b ) throw();

 public:
    TYPEINFO();
    SFX_DECL_INTERFACE(SCH_IF_DOCSHELL);
    SFX_DECL_OBJECTFACTORY_DLL(SchChartDocShell,SCH_MOD());

    SchChartDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED) throw();
//STRIP001 	SchChartDocShell(ChartModel* pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED) throw();
    ~SchChartDocShell() throw();

//STRIP001 	virtual void Activate() throw();
//STRIP001 	virtual void Deactivate() throw();

    virtual BOOL InitNew(SvStorage*) throw();
    virtual BOOL Load(SvStorage*) throw();
//STRIP001 	virtual sal_Bool ConvertFrom( SfxMedium &rMedium );
//STRIP001 	virtual sal_Bool ConvertTo( SfxMedium &rMedium );
//STRIP001 	virtual void HandsOff() throw();
    virtual BOOL Save() throw();
    virtual BOOL SaveAs(SvStorage* pNewStor) throw();
    virtual BOOL SaveCompleted(SvStorage* pNewStor) throw();

    virtual Rectangle GetVisArea(USHORT nAspect) const throw();
    virtual void SetVisArea(const Rectangle& rRect) throw();

//STRIP001 	virtual void Draw(OutputDevice*, const JobSetup& rSetup,
//STRIP001 					  USHORT nAspect = ASPECT_CONTENT) throw();

    virtual SfxUndoManager* GetUndoManager() throw();

    SfxPrinter* GetPrinter() throw();
    void SetPrinter( SfxPrinter *pNewPrinter, BOOL bIsDeletedHere = FALSE ) throw();

//STRIP001 	virtual Printer* GetDocumentPrinter() throw();
    virtual void     OnDocumentPrinterChanged(Printer* pNewPrinter) throw();

    /** @return if the chart is embedded in a document, this may be a virtual
                device for layout, or a printer, according to what is set in the
                container.  Otherwise GetPrinter() is called.
     */
    OutputDevice * GetRefDevice();

    void Execute(SfxRequest& rReq) throw();
    void GetState(SfxItemSet&) throw();

    ChartModel& GetDoc() { return *pChDoc; }
    ChartModel* GetModelPtr() { return pChDoc; }
    void SetModelPtr( ChartModel* pModel ) { pChDoc = pModel; }

    virtual SfxStyleSheetBasePool* GetStyleSheetPool() throw();

//STRIP001 	virtual BOOL Insert(SfxObjectShell &rSource, USHORT nSourceIdx1,
//STRIP001 						USHORT nSourceIdx2, USHORT nSourceIdx3,
//STRIP001 						USHORT& nIdx1, USHORT& nIdx2, USHORT& nIdx3,
//STRIP001 						USHORT& nDeleted) throw();

//STRIP001 	virtual BOOL Remove(USHORT nIdx1, USHORT nIdx2 = INDEX_IGNORE,
//STRIP001 						USHORT nIdx3 = INDEX_IGNORE) throw();

//STRIP001 	void UpdateChart(OutputDevice* pOut) throw();
    void UpdateTablePointers() throw();

    virtual void FillClass(SvGlobalName* pClassName,
                           ULONG*  pFormat,
                           String* pAppName,
                           String* pFullTypeName,
                           String* pShortTypeName,
                           long    nFileFormat = SOFFICE_FILEFORMAT_CURRENT ) const throw();

    virtual ULONG GetMiscStatus() const throw();

    virtual void    SetModified( BOOL = TRUE ) throw();

    void DataModified( ::com::sun::star::chart::ChartDataChangeEvent& ) throw();

    /// if this flag is set the XML export always exports the table
    void SetClipboardExport( BOOL bSet = sal_False )
        { mbClipboardExport = bSet; }
    BOOL GetClipboardExport() const
        { return mbClipboardExport; }
    
};

SO2_DECL_IMPL_REF(SchChartDocShell)

} //namespace binfilter
#endif		// _SCH_DOCSHELL_HXX
