/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drawdoc.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-07-06 11:14:09 $
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

#ifndef _DRAWDOC_HXX
#define _DRAWDOC_HXX

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HDL_
#include <com/sun/star/frame/XModel.hdl>
#endif
#ifndef _SV_PRINT_HXX
#include <vcl/print.hxx>
#endif
#ifndef _FM_FMMODEL_HXX
#include <bf_svx/fmmodel.hxx>
#endif
#ifndef _PRESENTATION_HXX
#include <bf_sd/pres.hxx>
#endif
#ifndef _SVX_PAGEITEM_HXX //autogen
#include <bf_svx/pageitem.hxx>
#endif
#ifndef _UNOTOOLS_CHARCLASS_HXX
#include <unotools/charclass.hxx>
#endif

#include <so3/svstor.hxx>

#ifndef _RSCSFX_HXX
#include <rsc/rscsfx.hxx>
#endif
#ifndef _COM_SUN_STAR_LANG_LOCALE_HPP_
#include <com/sun/star/lang/Locale.hpp>
#endif
#ifndef _COM_SUN_STAR_TEXT_WRITINGMODE_HPP_ 
#include <com/sun/star/text/WritingMode.hpp>
#endif

// #107844#
#ifndef _SVDUNDO_HXX
#include <bf_svx/svdundo.hxx>
#endif
class Timer;
class Graphic;
class Point;
class Window;
namespace binfilter {

class SfxObjectShell;
class SdPage;
class FrameView;
class SdDrawDocShell;
class SdOutliner;
class SdAnimationInfo;
class SdIMapInfo;
class IMapObject;
class SdStyleSheetPool;
class SfxMedium;
class SvxSearchItem;
class SdrOle2Obj;
class EditStatus;
class SdTransferable;
struct SpellCallbackInfo;
struct StyleRequestData;

#ifndef SV_DECL_SDDRAWDOCSHELL_DEFINED
#define SV_DECL_SDDRAWDOCSHELL_DEFINED
SV_DECL_REF(SdDrawDocShell)
#endif

struct StyleReplaceData
{
    SfxStyleFamily  nFamily;
    SfxStyleFamily  nNewFamily;
    String          aName;
    String          aNewName;
};

enum DocCreationMode
{
    NEW_DOC,
    DOC_LOADED
};

//////////////////////////////////////////////////////////////////////////////
// #107844#
// An undo class which is able to set/unset user calls is needed to handle
// the undo/redo of PresObjs correctly. It can also add/remove the object
// from the PresObjList of that page.

class SdrUndoUserCallObj : public SdrUndoObj
{
protected:
    SdPage*							mpOld;
    SdPage*							mpNew;

public:
    SdrUndoUserCallObj(SdrObject& rNewObj, SdPage* pNew);

    virtual void Undo();
    virtual void Redo();
};

//////////////////////////////////////////////////////////////////////////////

// ------------------
// - SdDrawDocument -
// ------------------

class SdDrawDocument : public FmFormModel
{
private:

    SdOutliner* 	    pOutliner;		    // local outliner for outline mode
    SdOutliner* 	    pInternalOutliner;  // internal outliner for creation of text objects
    Timer*			    pWorkStartupTimer;
    Timer*              pOnlineSpellingTimer;
    List*               pOnlineSpellingList;
    List*               pDeletedPresObjList;
    SvxSearchItem*      pOnlineSearchItem;
    List*               pFrameViewList;
    List*               pCustomShowList;
    SdDrawDocShell*     pDocSh;
    SdTransferable *    pCreatingTransferable;
    BOOL                bHasOnlineSpellErrors;
    BOOL                bInitialOnlineSpellingEnabled;
    String              aBookmarkFile; 
    SdDrawDocShellRef   xBookmarkDocShRef; 
    String			    aPresPage;
    BOOL			    bNewOrLoadCompleted;
    BOOL			    bPresAll;
    BOOL			    bPresEndless;
    BOOL			    bPresManual;
    BOOL			    bPresMouseVisible;
    BOOL			    bPresMouseAsPen;
    BOOL			    bStartPresWithNavigator;
    BOOL                bAnimationAllowed;
    BOOL			    bPresLockedPages;
    BOOL			    bPresAlwaysOnTop;
    BOOL                bPresFullScreen;
    sal_uInt32		    nPresPause;
    BOOL			    bPresShowLogo;
    BOOL			    bOnlineSpell;
    BOOL			    bHideSpell;
    BOOL                bCustomShow;
    BOOL                bSummationOfParagraphs;
    bool				mbStartWithPresentation;		// is set to true when starting with command line parameter -start

    sal_uInt32		    nPresFirstPage;
    LanguageType	    eLanguage;
    LanguageType	    eLanguageCJK;
    LanguageType	    eLanguageCTL;
    SvxNumType		    ePageNumType;
    Link			    aOldNotifyUndoActionHdl;
    SdDrawDocShellRef   xAllocedDocShRef;   // => AllocModel()
    BOOL			    bAllocDocSh;		// => AllocModel()
    DocumentType        eDocType;
    UINT16              nFileFormatVersion;
    SotStorage*        	pDocStor;
    SotStorageRef 		xPictureStorage;
    SotStorageStreamRef xDocStream;
    CharClass*		    mpCharClass;
    ::com::sun::star::lang::Locale* mpLocale;

    void                UpdatePageObjectsInNotes(USHORT nStartPos);
    void                FillOnlineSpellingList(SdPage* pPage);
    void                SpellObject(SdrTextObj* pObj);

                        DECL_LINK(NotifyUndoActionHdl, SfxUndoAction*);
                        DECL_LINK(WorkStartupHdl, Timer*);
//STRIP001 	                    DECL_LINK(OnlineSpellingHdl, Timer*);
//STRIP001 	                    DECL_LINK(OnlineSpellEventHdl, EditStatus*);

protected:

    virtual ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > createUnoModel();

public:

    class InsertBookmarkAsPage_PageFunctorBase;

                        TYPEINFO();

                        SdDrawDocument(DocumentType eType, SfxObjectShell* pDocSh);
                        ~SdDrawDocument();

//STRIP001 	virtual SdrModel*   AllocModel() const;
    virtual SdrPage*    AllocPage(FASTBOOL bMasterPage);
//STRIP001 	virtual const SdrModel* LoadModel(const String& rFileName);
    virtual void        DisposeLoadedModels();
//STRIP001 	virtual FASTBOOL    IsReadOnly() const;
    virtual void        SetChanged(FASTBOOL bFlag = TRUE);
    virtual SvStream*   GetDocumentStream(SdrDocumentStreamInfo& rStreamInfo) const;
    virtual void        HandsOff();

    SfxItemPool&	    GetPool() { return( *pItemPool ); }

    SdOutliner* 	    GetOutliner(BOOL bCreateOutliner=TRUE);
    SdOutliner* 	    GetInternalOutliner(BOOL bCreateOutliner=TRUE);

    SdDrawDocShell*     GetDocSh() const { return(pDocSh) ; }

    LanguageType	    GetLanguage( const USHORT nId ) const;
    void			    SetLanguage( const LanguageType eLang, const USHORT nId );

    SvxNumType          GetPageNumType() const;
    void			    SetPageNumType(SvxNumType eType) { ePageNumType = eType; }
    String              CreatePageNumValue(USHORT nNum) const;

    DocumentType        GetDocumentType() const { return eDocType; }

    void			    SetAllocDocSh(BOOL bAlloc);

    void	            CreatingDataObj( SdTransferable* pTransferable ) { pCreatingTransferable = pTransferable; }

    void	            CreateFirstPages();
//STRIP001 	BOOL                CreateMissingNotesAndHandoutPages();

//STRIP001 	void	            MovePage(USHORT nPgNum, USHORT nNewPos);
    void	            InsertPage(SdrPage* pPage, USHORT nPos=0xFFFF);
    void	            DeletePage(USHORT nPgNum);
    SdrPage*            RemovePage(USHORT nPgNum);
    void	            RemoveUnnessesaryMasterPages( SdPage* pMaster=NULL, BOOL bOnlyDuplicatePages=FALSE, BOOL bUndo=TRUE );
//STRIP001 	void 	            SetMasterPage(USHORT nSdPageNum, const String& rLayoutName,
//STRIP001 					    	          SdDrawDocument* pSourceDoc, BOOL bMaster, BOOL bCheckMasters);
//STRIP001                         
//STRIP001 	SdDrawDocument*     OpenBookmarkDoc(const String& rBookmarkFile);
//STRIP001 	SdDrawDocument*     OpenBookmarkDoc(SfxMedium& rMedium);
//STRIP001 	BOOL                InsertBookmark(List* pBookmarkList, List* pExchangeList, BOOL bLink,
//STRIP001 			            				BOOL bReplace, USHORT nPgPos, BOOL bNoDialogs,
//STRIP001 			            				SdDrawDocShell* pBookmarkDocSh, BOOL bCopy,
//STRIP001 			            				Point* pObjPos);

//STRIP001 	bool IsStartWithPresentation() const;
//STRIP001 	void SetStartWithPresentation( bool bStartWithPresentation );

    /** Insert pages into this document

        This method inserts whole pages into this document, either
        selected ones (specified via pBookmarkList/pExchangeList), or
        all from the source document.

        @attention Beware! This method in it's current state does not
        handle all combinations of their input parameters
        correctly. For example, for pBookmarkList=NULL, bReplace=TRUE
        is ignored (no replace happens).

        @param pBookmarkList
        A list of strings, denoting the names of the pages to be copied 

        @param pExchangeList
        A list of strings, denoting the names of the pages to be renamed

        @param bLink
        Whether the inserted pages should be links to the bookmark document

        @param bReplace
        Whether the pages should not be inserted, but replace the pages in 
        the destination document 

        @param nPgPos
        Insertion point/start of replacement

        @param bNoDialogs
        Whether query dialogs are allowed (e.g. for page scaling)

        @param pBookmarkDocSh
        DocShell of the source document (used e.g. to extract the filename 
        for linked pages)

        @param bCopy
        Whether the source document should be treated as immutable (i.e. 
        inserted pages are not removed from it, but cloned)

        @param bMergeMasterPages
        Whether the source document's master pages should be copied, too.

        @param bPreservePageNames
        Whether the replace operation should take the name from the new 
        page, or preserve the old name
     */
//STRIP001 	BOOL                InsertBookmarkAsPage(List* pBookmarkList, List* pExchangeList,
//STRIP001 			            					  BOOL bLink, BOOL bReplace, USHORT nPgPos,
//STRIP001 			            					  BOOL bNoDialogs, SdDrawDocShell* pBookmarkDocSh,
//STRIP001 			            					  BOOL bCopy, BOOL bMergeMasterPages, 
//STRIP001                                               BOOL bPreservePageNames);
//STRIP001 	BOOL                InsertBookmarkAsObject(List* pBookmarkList, List* pExchangeListL,
//STRIP001 			            						BOOL bLink, SdDrawDocShell* pBookmarkDocSh,
//STRIP001 			            						Point* pObjPos);
//STRIP001     void 				IterateBookmarkPages( SdDrawDocument* pBookmarkDoc, List* pBookmarkList, 
//STRIP001                                               USHORT nBMSdPageCount, 
//STRIP001                                               InsertBookmarkAsPage_PageFunctorBase& rPageIterator );
    void	            CloseBookmarkDoc();

//STRIP001 	SdrObject*          GetObj(const String& rObjName) const;

    USHORT	            GetPageByName(const String& rPgName, BOOL& rbIsMasterPage ) const;
    SdPage*             GetSdPage(USHORT nPgNum, PageKind ePgKind) const;
    USHORT	            GetSdPageCount(PageKind ePgKind) const;
    void	            SetSelected(SdPage* pPage, BOOL bSelect);
//STRIP001 	BOOL	            MovePages(USHORT nTargetPage);

    SdPage*             GetMasterSdPage(USHORT nPgNum, PageKind ePgKind);
    USHORT	            GetMasterSdPageCount(PageKind ePgKind) const;

    USHORT	            GetMasterPageUserCount(SdrPage* pMaster) const;

    void			    SetPresPage( const String& rPresPage ) { aPresPage = rPresPage; }
    const String&	    GetPresPage() const { return aPresPage; }

    void                SetPresAll(BOOL bNewPresAll);
    BOOL                GetPresAll() const 		 { return bPresAll; }

    void                SetPresEndless(BOOL bNewPresEndless);
    BOOL                GetPresEndless() const 	 { return bPresEndless; }

    void                SetPresManual(BOOL bNewPresManual);
    BOOL                GetPresManual() const		 { return bPresManual; }

    void                SetPresMouseVisible(BOOL bNewPresMouseVisible);
    BOOL                GetPresMouseVisible() const { return bPresMouseVisible; }

    void                SetPresMouseAsPen(BOOL bNewPresMouseAsPen);
    BOOL                GetPresMouseAsPen() const	 { return bPresMouseAsPen; }

//STRIP001 	void                SetPresFirstPage (ULONG nNewFirstPage);
    ULONG               GetPresFirstPage() const { return nPresFirstPage; }

    void                SetStartPresWithNavigator (BOOL bStart);
    BOOL                GetStartPresWithNavigator() const { return bStartPresWithNavigator; }

    void                SetAnimationAllowed (BOOL bAllowed) { bAnimationAllowed = bAllowed; }
    BOOL                IsAnimationAllowed() const { return bAnimationAllowed; }

    void                SetPresPause( sal_uInt32 nSecondsToWait ) { nPresPause = nSecondsToWait; }
    sal_uInt32          GetPresPause() const { return nPresPause; }

    void                SetPresShowLogo( BOOL bShowLogo ) { bPresShowLogo = bShowLogo; }
    BOOL                IsPresShowLogo() const { return bPresShowLogo; }

    void                SetPresLockedPages (BOOL bLock);
    BOOL                GetPresLockedPages() const { return bPresLockedPages; }

    void                SetPresAlwaysOnTop (BOOL bOnTop);
    BOOL                GetPresAlwaysOnTop() const { return bPresAlwaysOnTop; }

    void                SetPresFullScreen (BOOL bNewFullScreen);
    BOOL                GetPresFullScreen() const { return bPresFullScreen; }

       void                SetSummationOfParagraphs( BOOL bOn = TRUE ) { bSummationOfParagraphs = bOn; }
    const BOOL	        IsSummationOfParagraphs() const { return bSummationOfParagraphs; }

    /** Set the mode that controls whether (and later how) the formatting of the document
        depends on the current printer metrics.
        @param nMode
            Use <const
            scope="com::sun::star::document::PrinterIndependentLayout">ENABLED</const>
            to make formatting printer-independent and <const
            scope="com::sun::star::document::PrinterIndependentLayout">DISABLED</const>
            to make formatting depend on the current printer metrics.
    */
    void SetPrinterIndependentLayout (sal_Int32 nMode);

    /** Get the flag that controls whether the formatting of the document
        depends on the current printer metrics.
        @return
            Use <const
            scope="com::sun::star::document::PrinterIndependentLayout">ENABLED</const>
            when formatting is printer-independent and <const
            scope="com::sun::star::document::PrinterIndependentLayout">DISABLED</const>
            when formatting depends on the current printer metrics.
    */
    sal_Int32 GetPrinterIndependentLayout (void);

    void                SetOnlineSpell( BOOL bIn );
    BOOL                GetOnlineSpell() const { return bOnlineSpell; }
    void                StopOnlineSpelling();
    void                StartOnlineSpelling(BOOL bForceSpelling=TRUE);

    void                ImpOnlineSpellCallback(SpellCallbackInfo* pInfo, SdrObject* pObj, SdrOutliner* pOutl);

    void                InsertObject(SdrObject* pObj, SdPage* pPage);
    void                RemoveObject(SdrObject* pObj, SdPage* pPage);

//STRIP001 	void                SetHideSpell( BOOL bIn );
    BOOL                GetHideSpell() const { return bHideSpell; }

//STRIP001 	ULONG               GetLinkCount();

    List*               GetFrameViewList() const { return pFrameViewList; }
    List*               GetCustomShowList(BOOL bCreate = FALSE);

    void                SetCustomShow(BOOL bCustShow) { bCustomShow = bCustShow; }
    BOOL                IsCustomShow() const { return bCustomShow; }

    void                NbcSetChanged(FASTBOOL bFlag = TRUE);

    void                SetTextDefaults() const;

    void                CreateLayoutTemplates();
    void                RenameLayoutTemplate(const String& rOldLayoutName, const String& rNewName);

    void                StopWorkStartupDelay();

    void                NewOrLoadCompleted(DocCreationMode eMode);
    BOOL                IsNewOrLoadCompleted() const {return bNewOrLoadCompleted; }

    FrameView*          GetFrameView(ULONG nPos) { return (FrameView*) pFrameViewList->GetObject(nPos); }

    SdAnimationInfo*    GetAnimationInfo(SdrObject* pObject) const;

    SdIMapInfo*         GetIMapInfo( SdrObject* pObject ) const;
//STRIP001 	IMapObject*         GetHitIMapObject( SdrObject* pObject, const Point& rWinPoint, const Window& rCmpWnd );

//STRIP001 	Graphic 	        GetGraphicFromOle2Obj( const SdrOle2Obj* pOle2Obj );

//STRIP001 	List*               GetDeletedPresObjList();

    CharClass*	        GetCharClass() const { return mpCharClass; }

    void                RestoreLayerNames();
    void                MakeUniqueLayerNames();

    void	            UpdateAllLinks();

    void                CheckMasterPages();

//STRIP001 	void                Merge(SdrModel& rSourceModel,
//STRIP001 			                    USHORT nFirstPageNum=0, USHORT nLastPageNum=0xFFFF,
//STRIP001 			                    USHORT nDestPos=0xFFFF,
//STRIP001 			                    FASTBOOL bMergeMasterPages=FALSE, FASTBOOL bAllMasterPages=FALSE,
//STRIP001 			                    FASTBOOL bUndo=TRUE, FASTBOOL bTreadSourceAsConst=FALSE);

    ::com::sun::star::text::WritingMode GetDefaultWritingMode() const;
//STRIP001     void SetDefaultWritingMode( ::com::sun::star::text::WritingMode eMode );

public:

    static SdDrawDocument* pDocLockedInsertingLinks;  // static to prevent recursions while resolving links

    friend SvStream&    operator<<(SvStream& rOut, SdDrawDocument& rDoc);
    friend SvStream&    operator>>(SvStream& rIn, SdDrawDocument& rDoc);

    /** This method acts as a simplified front end for the more complex
        <member>CreatePage()</member> method.
        @param nPageNum
            The page number as passed to the <member>GetSdPage()</member>
            method from which to use certain properties for the new pages.
            These include the auto layout.
        @return
            Returns an index of the inserted pages that can be used with the
            <member>GetSdPage()</member> method.
    */
    USHORT CreatePage (USHORT nPageNum);

    /** Create and insert a set of two new pages: a standard (draw) page and
        the associated notes page.  The new pages are inserted direclty
        after the specified page set.
        @param pCurrentPage
            This page is used to retrieve the layout for the page to
            create.
        @param ePageKind
            This specifies whether <argument>pCurrentPage</argument> is a
            standard (draw) page or a notes page.
        @param sStandardPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param sNotesPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param eStandardLayout
            Layout to use for the new standard page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a standard page.  In this case the layout is taken from the
            standard page associated with <argument>pCurrentPage</argument>.
        @param eNotesLayout
            Layout to use for the new notes page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a notes page.  In this case the layout is taken from the
            notes page associated with <argument>pCurrentPage</argument>.
        @param bIsPageBack
            This flag indicates whether to show the background shape.
        @param bIsPageObj
            This flag indicates whether to show the shapes on the master page.

        @return
            Returns an index of the inserted pages that can be used with the
            <member>GetSdPage()</member> method.
    */
    USHORT CreatePage (
        SdPage* pCurrentPage,
        PageKind ePageKind,
        const String& sStandardPageName,
        const String& sNotesPageName,
        AutoLayout eStandardLayout,
        AutoLayout eNotesLayout,
        BOOL bIsPageBack,
        BOOL bIsPageObj);

    /** This method acts as a simplified front end for the more complex
        <member>DuplicatePage()</member> method.
        @param nPageNum
            The page number as passed to the <member>GetSdPage()</member>
            method for which the standard page and the notes page are to be
            copied.
        @return
            Returns an index of the inserted pages that can be used with the
            <member>GetSdPage()</member> method.
    */
    USHORT DuplicatePage (USHORT nPageNum);

    /** Create and insert a set of two new pages that are copies of the
        given <argument>pCurrentPage</argument> and its associated notes
        resp. standard page.  The copies are inserted directly after the
        specified page set.
        @param pCurrentPage
            This page and its associated notes/standard page is copied.
        @param ePageKind
            This specifies whether <argument>pCurrentPage</argument> is a
            standard (draw) page or a notes page.
        @param sStandardPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param sNotesPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param eStandardLayout
            Layout to use for the new standard page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a standard page.  In this case the layout is taken from the
            standard page associated with <argument>pCurrentPage</argument>.
        @param eNotesLayout
            Layout to use for the new notes page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a notes page.  In this case the layout is taken from the
            notes page associated with <argument>pCurrentPage</argument>.
        @param bIsPageBack
            This flag indicates whether to show the background shape.
        @param bIsPageObj
            This flag indicates whether to show the shapes on the master page.

        @return
            Returns an index of the inserted pages that can be used with the
            <member>GetSdPage()</member> method.
    */
    USHORT DuplicatePage (
        SdPage* pCurrentPage,
        PageKind ePageKind,
        const String& sStandardPageName,
        const String& sNotesPageName,
        AutoLayout eStandardLayout,
        AutoLayout eNotesLayout,
        BOOL bIsPageBack,
        BOOL bIsPageObj);

    /** return the document fonts for latin, cjk and ctl according to the current
        languages set at this document */
    void getDefaultFonts( Font& rLatinFont, Font& rCJKFont, Font& rCTLFont );

private:
    /** This member stores the printer independent layout mode.  Please
        refer to <member>SetPrinterIndependentLayout()</member> for its
        values.
    */        
    sal_Int32 mnPrinterIndependentLayout;

    /** Insert a given set of standard and notes page after the given <argument>pCurrentPage</argument>.
        @param pCurrentPage
            This page and its associated notes/standard page is copied.
        @param ePageKind
            This specifies whether <argument>pCurrentPage</argument> is a
            standard (draw) page or a notes page.
        @param sStandardPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param sNotesPageName
            Name of the standard page.  An empty string leads to using an
            automatically created name.
        @param eStandardLayout
            Layout to use for the new standard page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a standard page.  In this case the layout is taken from the
            standard page associated with <argument>pCurrentPage</argument>.
        @param eNotesLayout
            Layout to use for the new notes page.  Note that this layout
            is not used when the given <argument>pCurrentPage</argument> is
            not a notes page.  In this case the layout is taken from the
            notes page associated with <argument>pCurrentPage</argument>.
        @param bIsPageBack
            This flag indicates whether to show the background shape.
        @param bIsPageObj
            This flag indicates whether to show the shapes on the master page.
        @param pStandardPage
            The standard page to insert.
        @param pNotesPage
            The notes page to insert.

        @return
            Returns an index of the inserted pages that can be used with the
            <member>GetSdPage()</member> method.
    */
    USHORT InsertPageSet (
        SdPage* pCurrentPage,
        PageKind ePageKind,
        const String& sStandardPageName,
        const String& sNotesPageName,
        AutoLayout eStandardLayout,
        AutoLayout eNotesLayout,
        BOOL bIsPageBack,
        BOOL bIsPageObj,

        SdPage* pStandardPage,
        SdPage* pNotesPage);

    /** Set up a newly created page and insert it into the list of pages.
        @param pPreviousPage
            A page to take the size and border geometry from.
        @param pPage
            This is the page to set up and insert.
        @param sPageName
            The name of the new page.
        @param nInsertionPoint
            Index of the page before which the new page will be inserted.
        @param bIsPageBack
            This flag indicates whether to show the background shape.
        @param bIsPageObj
            This flag indicates whether to show the shapes on the master
            page.
    */
    void SetupNewPage (
        SdPage* pPreviousPage, 
        SdPage* pPage,
        const String& sPageName,
        USHORT nInsertionPoint,
        BOOL bIsPageBack,
        BOOL bIsPageObj);
};

} //namespace binfilter
#endif // _DRAWDOC_HXX
