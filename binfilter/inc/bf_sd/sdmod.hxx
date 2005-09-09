/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdmod.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:03:35 $
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

#ifndef _SDMOD_HXX
#define _SDMOD_HXX


#ifndef _SDDLL_HXX
#define _SD_DLL             // fuer SD_MOD()
#include "sddll.hxx"        // fuer SdModuleDummy
#endif
#ifndef _SD_GLOB_HXX
#include "glob.hxx"
#endif
#ifndef _PRESENTATION_HXX
#include "pres.hxx"
#endif
#ifndef _SVSTOR_HXX
#include <so3/svstor.hxx>
#endif
#ifndef _SFXLSTNER_HXX
#include <svtools/lstner.hxx>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_ 
#include <com/sun/star/text/WritingMode.hpp>
#endif
class SvFactory;
class SvNumberFormatter;
class SfxErrorHandler;
class OutputDevice;
namespace binfilter {

class SdOptions;
class BasicIDE;
class SvxSearchItem;
class SdAppLinkHdl; //STRIP008 ;
class SvxErrorHandler;
class EditFieldInfo;
class SdTransferable;
class SdDrawDocShell;
class SdView;
class SdPage;
class SdDrawDocument;
// ----------------------
// - SdOptionStreamMode -
// ----------------------

enum SdOptionStreamMode
{
    SD_OPTION_LOAD = 0,
    SD_OPTION_STORE = 1
};

/*************************************************************************
|*
|* This subclass of <SfxModule> (which is a subclass of <SfxShell>) is
|* linked to the DLL. One instance of this class exists while the DLL is
|* loaded.
|*
|* SdModule is like to be compared with the <SfxApplication>-subclass.
|*
|* Remember: Don`t export this class! It uses DLL-internal symbols.
|*
\************************************************************************/

class SdModule : public SdModuleDummy, public SfxListener
{
protected:

    SdOptions*				pImpressOptions;
    SdOptions*				pDrawOptions;
    SvxSearchItem*			pSearchItem;
    SvNumberFormatter*      pNumberFormatter;
    SvStorageRef			xOptionStorage;
    BOOL					bAutoSave;
    BOOL					bWaterCan;
    SfxErrorHandler*		mpErrorHdl;
    /** This device is used for printer independent layout.  It is virtual
        in the sense that it does not represent a printer.  The pointer may
        be NULL when the virtual device could not be created.
    */
    OutputDevice*           mpVirtualRefDevice;

    virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

public:

                            TYPEINFO();
                            SFX_DECL_INTERFACE(SD_IF_SDAPP);
                            DECL_LINK( CalcFieldValueHdl, EditFieldInfo* );

                            SdModule(SvFactory* pDrawObjFact, SvFactory* pGraphicObjFact);
    virtual					~SdModule();

    SdTransferable*			pTransferClip;
    SdTransferable*			pTransferDrag;
    SdTransferable*			pTransferSelection;

    void					Execute(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	void					Execute(SfxRequest& rReq);
    void					GetState(SfxItemSet&){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	void					GetState(SfxItemSet&);

    virtual SfxModule*		Load();
    virtual void			Free();

//STRIP001 	virtual void			FillStatusBar(StatusBar& rBar);

    SdOptions*				GetSdOptions(DocumentType eDocType);
//STRIP001 	SvStorageStreamRef		GetOptionStream( const String& rOptionName, SdOptionStreamMode eMode );

    BOOL					GetWaterCan() const { return bWaterCan; }
    void					SetWaterCan( BOOL bWC ) { bWaterCan = bWC; }

    SvxSearchItem*			GetSearchItem() { return (pSearchItem); }
    void					SetSearchItem(SvxSearchItem* pItem) { pSearchItem = pItem; }

    /** Return the virtual device that can be used for printer independent
        layout.
        @return
            The returned pointer is NULL when the device could not be
            created when this modules was instantiated.
    */
    OutputDevice* GetVirtualRefDevice (void);

    /** Deprecated alias to <member>GetVirtualRefDevice</member>.
        @param rDocShell
            Unused dummy parameter.
    */
    OutputDevice* GetRefDevice (SdDrawDocShell& rDocShell);

    SvNumberFormatter*		GetNumberFormatter();

    ::com::sun::star::text::WritingMode GetDefaultWritingMode() const;

    //virtuelle Methoden fuer den Optionendialog
//STRIP001 	virtual SfxItemSet*	 CreateItemSet( USHORT nId );
//STRIP001 	virtual void		 ApplyItemSet( USHORT nId, const SfxItemSet& rSet );
//STRIP001 	virtual	SfxTabPage*	 CreateTabPage( USHORT nId, Window* pParent, const SfxItemSet& rSet );

private:

    /** Create a new summary page.  When the document has been created in
        the kiosk mode with automatical transitions then this method adds
        this kind of transition to the new summary page.
        @param pViewFrame
            The view frame that is used to execute the slot for creating the
            summary page.
        @param pDocument
            The document which will contain the summary page and from which
            the information about the default transition is retrieved.
    */
    void AddSummaryPage (SfxViewFrame* pViewFrame, SdDrawDocument* pDocument);
};




#ifndef SD_MOD
#define SD_MOD() ( *(SdModule**) GetAppData(BF_SHL_DRAW) )
#endif

} //namespace binfilter
#endif                                 // _SDMOD_HXX

