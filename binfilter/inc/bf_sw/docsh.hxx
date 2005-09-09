/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docsh.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 15:55:13 $
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
#ifndef _SWDOCSH_HXX
#define _SWDOCSH_HXX

#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif
#ifndef _SFX_OBJFAC_HXX //autogen
#include <bf_sfx2/docfac.hxx>
#endif
#ifndef _SFX_INTERNO_HXX //autogen
#include <bf_sfx2/interno.hxx>
#endif
#ifndef _SFX_OBJSH_HXX //autogen
#include <bf_sfx2/objsh.hxx>
#endif
#ifndef SW_SWDLL_HXX
#include <swdll.hxx>
#endif
#ifndef _SHELLID_HXX
#include <shellid.hxx>
#endif
class	SfxStyleSheetBasePool; 
class	FontList; 
class	PushButton; 
class	FixedText; 

namespace binfilter {

class	SwDoc;
class	Sw3Io;
class	SfxDocumentInfoDialog;
class	SwView;
class	SwWrtShell;
class	SwFEShell;
class	Reader;
class	SwReader;
class	SwCrsrShell;
class 	SwSrcView;
class 	SwPaM;
class	SwgReaderOption;

class SwDocShell: public SfxObjectShell, public SfxInPlaceObject,
                  public SfxListener
{
    SwDoc*					pDoc;			// Document
    Sw3Io*					pIo;			// Reader / Writer
    SfxStyleSheetBasePool*	pBasePool;		// Durchreiche fuer Formate
    FontList*				pFontList;		// aktuelle FontListe

    // Nix geht ohne die WrtShell (historische Gruende)
    // RuekwaertsPointer auf die View (historische Gruende)
    // Dieser gilt solange bis im Activate ein neuer gesetzt wird
    // oder dieser im Dtor der View geloescht wird
    //
    SwView* 				pView;
    SwWrtShell* 			pWrtShell;

    Timer					aFinishedTimer;	// Timer fuers ueberpriefen der
                                            // Grafik-Links. Sind alle da,
                                            // dann ist Doc voll. geladen

    SvPersistRef			xOLEChildList;	// fuers RemoveOLEObjects
    sal_Int16               nUpdateDocMode; // contains the ::com::sun::star::document::UpdateDocMode

    // Methoden fuer den Zugriff aufs Doc
    void					AddLink();
    void					RemoveLink();

    // Hint abfangen fuer DocInfo
    virtual void			Notify( SfxBroadcaster& rBC, const SfxHint& rHint );

    // FileIO
    virtual BOOL			InitNew(SvStorage* pNewStor);
    virtual BOOL			Load(SvStorage* pStor);
    virtual BOOL			LoadFrom(SvStorage* pStor);
//STRIP001 	virtual BOOL			ConvertFrom( SfxMedium &rMedium );
    virtual void			HandsOff();
    virtual BOOL			SaveAs(SvStorage * pNewStor );
//STRIP001 	virtual BOOL			ConvertTo(SfxMedium &rMedium );
    virtual BOOL			SaveCompleted(SvStorage * pNewStor );
//STRIP001 	virtual USHORT			PrepareClose( BOOL bUI = TRUE, BOOL bForBrowsing = FALSE );

    // DocInfo dem Doc melden
    //
//STRIP001 	virtual SfxDocumentInfoDialog* CreateDocumentInfoDialog(
//STRIP001 									Window *pParent, const SfxItemSet &);
    // OLE-Geraffel
//STRIP001 	virtual void			Draw( OutputDevice*, const JobSetup&, USHORT);

    // Methoden fuer StyleSheets
//STRIP001 	USHORT					Edit( const String &rName, const String& rParent, USHORT nFamily,
//STRIP001 									USHORT nMask, BOOL bNew,
//STRIP001 									BOOL bColumn = FALSE,
//STRIP001 									SwWrtShell* pActShell = 0,
//STRIP001 									BOOL bBasic = FALSE );
//STRIP001 	USHORT					Delete(const String &rName, USHORT nFamily);
//STRIP001 	USHORT					ApplyStyles(const String &rName, USHORT nFamily, SwWrtShell* pShell = 0,
//STRIP001 										USHORT nMode = 0 );
//STRIP001 	USHORT					DoWaterCan( const String &rName, USHORT nFamily);
//STRIP001 	USHORT					UpdateStyle(const String &rName, USHORT nFamily, SwWrtShell* pShell = 0);
//STRIP001 	USHORT					MakeByExample(const String &rName,
//STRIP001 											USHORT nFamily, USHORT nMask, SwWrtShell* pShell = 0);

    void					InitDraw();
    void					SubInitNew();   // fuer InitNew und HtmlSourceModus
    inline void 			SetWrtShell(SwWrtShell* pShell)
                                { pWrtShell = pShell; }

    void 					RemoveOLEObjects();
    void					CalcLayoutForOLEObjects();

    void                    Init_Impl();
    DECL_STATIC_LINK( SwDocShell, IsLoadFinished, void* );

public:

    // aber selbst implementieren
    SFX_DECL_INTERFACE(SW_DOCSHELL);
    SFX_DECL_OBJECTFACTORY_DLL(SwDocShell, SW_DLL());
    TYPEINFO();

    static SfxInterface *_GetInterface() { return _GetInterfaceImpl(); }

    //Das Doc wird fuer SO-Datenaustausch benoetigt!
    SwDocShell(SfxObjectCreateMode eMode = SFX_CREATE_MODE_EMBEDDED);
    SwDocShell( SwDoc *pDoc, SfxObjectCreateMode eMode = SFX_CREATE_MODE_STANDARD );
    ~SwDocShell();

    // OLE 2.0-Benachrichtigung
    DECL_LINK( Ole2ModifiedHdl, void * );

    // OLE-Geraffel
    virtual void	  SetVisArea( const Rectangle &rRect );
    virtual Rectangle GetVisArea( USHORT nAspect ) const;
    virtual Printer  *GetDocumentPrinter();
    virtual OutputDevice* GetDocumentRefDev();
    virtual void	  OnDocumentPrinterChanged( Printer * pNewPrinter );
    virtual ULONG	  GetMiscStatus() const;

//STRIP001 	virtual void			PrepareReload();
    virtual void			SetModified( BOOL = TRUE );

    // Dispatcher
    void					Execute(SfxRequest &);
    void					ExecStyleSheet(SfxRequest&);
    void					ExecDB(SfxRequest&);

    void					GetState(SfxItemSet &);
    void					StateAlways(SfxItemSet &);
    void					StateStyleSheet(SfxItemSet&, SwWrtShell* pSh = 0 );

    // Doc rausreichen aber VORSICHT
    inline SwDoc*			GetDoc() { return pDoc; }
    void					UpdateFontList();
    void					UpdateChildWindows();

    // DocumentInfo neu setzen
//STRIP001 	BOOL					SetDocumentInfo(const SfxDocumentInfo& rInfo);

    // globaler IO
    virtual BOOL			Save();
    inline BOOL					SaveAsChilds( SvStorage *pStor );
    inline BOOL					SaveCompletedChilds( SvStorage *pStor );

    // fuer VorlagenPI
    virtual SfxStyleSheetBasePool*	GetStyleSheetPool();

    // Fuer Organizer
//STRIP001 	virtual BOOL Insert(SfxObjectShell &rSource,
//STRIP001 						USHORT	nSourceIdx1,
//STRIP001 						USHORT	nSourceIdx2,
//STRIP001 						USHORT	nSourceIdx3,
//STRIP001 						USHORT& nIdx1,
//STRIP001 						USHORT& nIdx2,
//STRIP001 						USHORT& nIdx3,
//STRIP001 						USHORT& nRemovedIdx);

//STRIP001 	virtual BOOL Remove(USHORT nIdx1,
//STRIP001 						USHORT nIdx2 = INDEX_IGNORE,
//STRIP001 						USHORT nIdx3 = INDEX_IGNORE);

//STRIP001 		virtual Bitmap 		GetStyleFamilyBitmap( SfxStyleFamily eFamily, BmpColorMode eColorMode );

    // View setzen fuer Aktionen ueber Shell
    void 		  SetView(SwView* pVw);
    const SwView *GetView() const { return pView; }
    SwView       *GetView()       { return pView; }

    // Zugriff auf die zur SwView gehoerige SwWrtShell
          SwWrtShell *GetWrtShell() 	  { return pWrtShell; }
    const SwWrtShell *GetWrtShell() const { return pWrtShell; }

    // fuer die Core - die kennt die DocShell aber keine WrtShell!
//STRIP001 		  SwFEShell *GetFEShell();
    const SwFEShell *GetFEShell() const
                { return ((SwDocShell*)this)->GetFEShell(); }


    // Fuer Einfuegen Dokument
    Reader* StartConvertFrom(SfxMedium& rMedium, SwReader** ppRdr,
                        SwCrsrShell* pCrsrSh = 0, SwPaM* pPaM = 0);

    // Anforderung der pIo-Struktur fuer den Zugriff auf Substorages
    // und Streams
    Sw3Io* GetIoSystem() { return pIo; }

//STRIP001 	virtual long DdeGetData( const String& rItem, const String& rMimeType,
//STRIP001 							 ::com::sun::star::uno::Any & rValue );
//STRIP001 	virtual long DdeSetData( const String& rItem, const String& rMimeType,
//STRIP001 								const ::com::sun::star::uno::Any & rValue );
//STRIP001 	virtual ::so3::SvLinkSource* DdeCreateLinkSource( const String& rItem );
    virtual void FillClass( SvGlobalName * pClassName,
                                   ULONG * pClipFormat,
                                   String * pAppName,
                                   String * pLongUserName,
                                   String * pUserName,
                                   long nVersion = SOFFICE_FILEFORMAT_CURRENT ) const;

//STRIP001 	virtual void LoadStyles( SfxObjectShell& rSource );
//STRIP001     void _LoadStyles( SfxObjectShell& rSource, BOOL bPreserveCurrentDocument );

    // Seitenvorlagedialog anzeigen, ggf. auf Spaltenpage
//STRIP001 	void FormatPage( const String& rPage,
//STRIP001 						BOOL bColumn = FALSE,
//STRIP001 						SwWrtShell* 	pActShell = 0 );

    // Timer starten fuers ueberpruefen der Grafik-Links. Sind alle
    // vollstaendig geladen, dann ist das Doc fertig
    void StartLoadFinishedTimer();

    // eine Uebertragung wird abgebrochen (wird aus dem SFX gerufen)
    virtual void CancelTransfers();

    // Doc aus Html-Source neu laden
//STRIP001 	void	ReloadFromHtml( const String& rStreamName, SwSrcView* pSrcView );

    // embedded alle lokalen Links (Bereiche/Grafiken)
//STRIP001 	BOOL EmbedAllLinks();
    sal_Int16   GetUpdateDocMode() const {return nUpdateDocMode;}

    //Activate wait cursor for all windows of this document
    //Optionally all dispatcher could be Locked
    //Usually locking should be done using the class: SwWaitObject!
    void EnterWait( BOOL bLockDispatcher );
    void LeaveWait( BOOL bLockDispatcher );

    void ToggleBrowserMode(BOOL bOn, SwView* pView = 0);

    ULONG LoadStylesFromFile( const String& rURL, SwgReaderOption& rOpt,
                                BOOL bUnoCall );
//STRIP001 	void InvalidateModel();
//STRIP001 	void ReactivateModel();

#if SUPD>620
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString >	GetEventNames();
#endif
};

inline BOOL	SwDocShell::SaveAsChilds( SvStorage *pStor )
{
    return SfxInPlaceObject::SaveAsChilds( pStor );
}

inline BOOL	SwDocShell::SaveCompletedChilds( SvStorage *pStor )
{
    return SfxInPlaceObject::SaveCompletedChilds( pStor );
}
} //namespace binfilter
#endif
