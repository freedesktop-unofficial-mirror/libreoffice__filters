/*************************************************************************
 *
 *  $RCSfile: modcfg.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:19:59 $
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
#ifndef _MODOPT_HXX
#define _MODOPT_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _SV_WINTYPES_HXX
#include <vcl/wintypes.hxx>
#endif
#ifndef _SV_FIELD_HXX
#include <vcl/field.hxx>
#endif
#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#include "authratr.hxx"
#include "caption.hxx"
#include "tblenum.hxx"

#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

//-----------------------------------------------------------------------------

typedef InsCaptionOpt* InsCaptionOptPtr;
SV_DECL_PTRARR_SORT_DEL(InsCapOptArr, InsCaptionOptPtr, 0, 5)

class InsCaptionOptArr : public InsCapOptArr
{
    friend class SwModuleOptions;
    friend class SwInsertConfig;
protected:
    InsCaptionOpt* Find(const SwCapObjType eType, const SvGlobalName *pOleId = 0) const;
};

/* -----------------------------10.10.00 16:14--------------------------------

 ---------------------------------------------------------------------------*/
class SwModuleOptions;
class SwRevisionConfig : public utl::ConfigItem
{
    friend class SwModuleOptions;

    AuthorCharAttr	aInsertAttr;	//Revision/TextDisplay/Insert/Attribute  // Redlining: Author-Zeichenattribute
                                    //Revision/TextDisplay/Insert/Color
    AuthorCharAttr	aDeletedAttr;	//Revision/TextDisplay/Delete/Attribute
                                    //Revision/TextDisplay/Delete/Color
    AuthorCharAttr	aFormatAttr;    //Revision/TextDisplay/ChangeAttribute/Attribute
                                    //Revision/TextDisplay/ChangeAttribute/Color
    USHORT			nMarkAlign;		//Revision/LinesChanged/Mark
    Color			aMarkColor;     //Revision/LinesChanged/Color

    const com::sun::star::uno::Sequence<rtl::OUString>& GetPropertyNames();
    public:
        SwRevisionConfig();
        ~SwRevisionConfig();

//STRIP001 	virtual void			Commit();
    void					Load();
    void 					SetModified(){ConfigItem::SetModified();}
};
/* -----------------------------11.10.00 09:00--------------------------------

 ---------------------------------------------------------------------------*/
class SwInsertConfig : public utl::ConfigItem
{
    friend class SwModuleOptions;

    InsCaptionOptArr* 	pCapOptions;
    InsCaptionOpt* 		pOLEMiscOpt;

    SvGlobalName		aGlobalNames[5];

    sal_Bool 			bInsWithCaption;	   //Insert/Caption/Automatic	// Objekte beschriftet einfuegen
    sal_uInt16			nInsTblFlags;			//Insert/Table/Header	 	// Flags fuer Tabellen einfuegen
                                                //Insert/Table/RepeatHeader
                                                //Insert/Table/Split
                                                //Insert/Table/Border
    sal_Bool 			bIsWeb;

    const com::sun::star::uno::Sequence<rtl::OUString>& GetPropertyNames();
    public:
        SwInsertConfig(sal_Bool bWeb);
        ~SwInsertConfig();

//STRIP001 	virtual void			Commit();
    void					Load();
    void 					SetModified(){ConfigItem::SetModified();}
};
/* -----------------------------11.10.00 09:00--------------------------------

 ---------------------------------------------------------------------------*/
class SwTableConfig : public utl::ConfigItem
{
    friend class SwModuleOptions;

    USHORT		nTblHMove;  		//int Table/Shift/Row
    USHORT 		nTblVMove;          //int Table/Shift/Column
    USHORT 		nTblHInsert;        //int Table/Insert/Row
    USHORT		nTblVInsert;        //int Table/Insert/Column
    TblChgMode	eTblChgMode;    	//int Table/Change/Effect

    sal_Bool	bInsTblFormatNum;		// Table/Input/NumberRecognition 		// Automatische Zahlenerkennung
    sal_Bool	bInsTblChangeNumFormat; // Table/Input/NumberFormatRecognition 	// Automatische Zahlenformaterkennung
    sal_Bool	bInsTblAlignNum;		// Table/Input/Alignment				// Zahlen ausrichten

    const com::sun::star::uno::Sequence<rtl::OUString>& GetPropertyNames();
    public:
        SwTableConfig(sal_Bool bWeb);
        ~SwTableConfig();

//STRIP001 	virtual void			Commit();
    void					Load();
    void 					SetModified(){ConfigItem::SetModified();}
};
/* -----------------------------18.01.01 16:57--------------------------------

 ---------------------------------------------------------------------------*/
class SwMiscConfig : public utl::ConfigItem
{
    friend class SwModuleOptions;

    String		sWordDelimiter;				// Statistics/WordNumber/Delimiter
    BOOL		bDefaultFontsInCurrDocOnly; // DefaultFont/Document
    BOOL 		bShowIndexPreview ;  		// Index/ShowPreview
    BOOL		bGrfToGalleryAsLnk; 		// Misc/GraphicToGalleryAsLink
    BOOL		bNumAlignSize;				// Numbering/Graphic/KeepRatio
    BOOL		bSinglePrintJob;			// FormLetter/PrintOutput/SinglePrintJobs
    BOOL		bIsNameFromColumn;          // FormLetter/FileOutput/FileName/Generation
    sal_Int16	nMailingFormats;			// FormLetter/MailingOutput/Formats
    String		sNameFromColumn;			// FormLetter/FileOutput/FileName/FromDatabaseField (string!)
    String		sMailingPath;				// FormLetter/FileOutput/Path
    String		sMailName;					// FormLetter/FileOutput/FileName/FromManualSetting (string!)

    const com::sun::star::uno::Sequence<rtl::OUString>& GetPropertyNames();
    public:
        SwMiscConfig();
        ~SwMiscConfig();

//STRIP001 	virtual void			Commit();
    void					Load();
    void 					SetModified(){ConfigItem::SetModified();}
};

/* ---------------------------------------------------------------------------

 ---------------------------------------------------------------------------*/
class SwModuleOptions
{
    SwRevisionConfig 				aRevisionConfig;
    SwInsertConfig					aInsertConfig;
    SwInsertConfig					aWebInsertConfig;

    SwTableConfig					aTableConfig;
    SwTableConfig					aWebTableConfig;

    SwMiscConfig					aMiscConfig;

    //fiscus: don't show tips of text fields - it's not part of the configuration!
    BOOL 		bHideFieldTips : 1;

public:
    SwModuleOptions();

    TblChgMode	GetTblMode() const { return aTableConfig.eTblChgMode;}
    void		SetTblMode( TblChgMode  eSet ) { aTableConfig.eTblChgMode = eSet;
                                                aTableConfig.SetModified();}

    USHORT		GetTblHMove() const { return aTableConfig.nTblHMove;}
    void		SetTblHMove( USHORT nSet ) { 	aTableConfig.nTblHMove = nSet;
                                                aTableConfig.SetModified();}

    USHORT 		GetTblVMove() const { return aTableConfig.nTblVMove;}
    void 		SetTblVMove( USHORT nSet ) { 	aTableConfig.nTblVMove = nSet;
                                                aTableConfig.SetModified();}

    USHORT 		GetTblHInsert() const {return aTableConfig.nTblHInsert;}
    void 		SetTblHInsert( USHORT nSet ) {	aTableConfig.nTblHInsert = nSet;
                                                aTableConfig.SetModified();}

    USHORT		GetTblVInsert() const {return aTableConfig.nTblVInsert;}
    void 		SetTblVInsert( USHORT nSet ) {	aTableConfig.nTblVInsert = nSet;
                                                aTableConfig.SetModified();}

    const AuthorCharAttr	&GetInsertAuthorAttr() const { return aRevisionConfig.aInsertAttr; }
    void 		SetInsertAuthorAttr( AuthorCharAttr &rAttr ) {	aRevisionConfig.aInsertAttr = rAttr;
                                                                aRevisionConfig.SetModified();}

    const AuthorCharAttr	&GetDeletedAuthorAttr() const { return aRevisionConfig.aDeletedAttr; }
    void 		SetDeletedAuthorAttr( AuthorCharAttr &rAttr ) {	aRevisionConfig.aDeletedAttr = rAttr;
                                                                aRevisionConfig.SetModified();}

    const AuthorCharAttr	&GetFormatAuthorAttr() const { return aRevisionConfig.aFormatAttr; }
    void 		SetFormatAuthorAttr( AuthorCharAttr &rAttr ) {	aRevisionConfig.aFormatAttr = rAttr;
                                                                aRevisionConfig.SetModified();}

    USHORT			GetMarkAlignMode()	const				{ return aRevisionConfig.nMarkAlign; }
    void			SetMarkAlignMode(USHORT nMode)			{ aRevisionConfig.nMarkAlign = nMode;
                                                              aRevisionConfig.SetModified();}

    const Color&	GetMarkAlignColor()	const				{ return aRevisionConfig.aMarkColor; }
    void 			SetMarkAlignColor(const Color &rColor)	{ aRevisionConfig.aMarkColor = rColor;
                                                              aRevisionConfig.SetModified();}

    BOOL		IsInsWithCaption(BOOL bHTML) const
                        { return bHTML ? FALSE : aInsertConfig.bInsWithCaption; }
    void		SetInsWithCaption( BOOL bHTML, BOOL b )
                    { 	if(!bHTML)
                            aInsertConfig.bInsWithCaption = b;
                        aInsertConfig.SetModified();}

    BOOL		IsInsTblFormatNum(BOOL bHTML) const
                    { return bHTML ? aWebTableConfig.bInsTblFormatNum : aTableConfig.bInsTblFormatNum; }
    void		SetInsTblFormatNum( BOOL bHTML, BOOL b )
                    { bHTML ? (aWebTableConfig.bInsTblFormatNum = b) : (aTableConfig.bInsTblFormatNum = b);
                      bHTML ? aWebTableConfig.SetModified() : aTableConfig.SetModified();}

    BOOL		IsInsTblChangeNumFormat(BOOL bHTML) const
                    { return bHTML ? aWebTableConfig.bInsTblChangeNumFormat : aTableConfig.bInsTblChangeNumFormat; }
    void		SetInsTblChangeNumFormat( BOOL bHTML, BOOL b )
                    { bHTML ? (aWebTableConfig.bInsTblChangeNumFormat = b) : (aTableConfig.bInsTblChangeNumFormat = b);
                      bHTML ? aWebTableConfig.SetModified() : aTableConfig.SetModified();}


    BOOL		IsInsTblAlignNum(BOOL bHTML) const
                    { return bHTML ? aWebTableConfig.bInsTblAlignNum : aTableConfig.bInsTblAlignNum; }
    void		SetInsTblAlignNum( BOOL bHTML, BOOL b )
                    { bHTML ? (aWebTableConfig.bInsTblAlignNum = b) : (aTableConfig.bInsTblAlignNum = b);
                        bHTML ? aWebTableConfig.SetModified() : aTableConfig.SetModified();;}

    USHORT		GetInsTblFlags(BOOL bHTML) const
                    { return bHTML ? aWebInsertConfig.nInsTblFlags : aInsertConfig.nInsTblFlags;}
    void		SetInsTblFlags( BOOL bHTML, USHORT nSet )	{
                    bHTML ? (aWebInsertConfig.nInsTblFlags = nSet) : (aInsertConfig.nInsTblFlags = nSet);
                    bHTML ? aWebInsertConfig.SetModified() : aInsertConfig.SetModified();}

//STRIP001 	const InsCaptionOpt* GetCapOption(BOOL bHTML, const SwCapObjType eType, const SvGlobalName *pOleId);
//STRIP001 	BOOL		SetCapOption(BOOL bHTML, const InsCaptionOpt* pOpt);


    BOOL		IsGrfToGalleryAsLnk() const 	{ return aMiscConfig.bGrfToGalleryAsLnk; }
    void		SetGrfToGalleryAsLnk( BOOL b )  { aMiscConfig.bGrfToGalleryAsLnk = b;
                                                  aMiscConfig.SetModified();}

    sal_Int16	GetMailingFormats() const 		{ return aMiscConfig.nMailingFormats;}
    void 		SetMailingFormats( sal_Int16 nSet )	{ aMiscConfig.nMailingFormats = nSet;
                                                  aMiscConfig.SetModified();}

    BOOL		IsSinglePrintJob() const 		{ return aMiscConfig.bSinglePrintJob; }
    void		SetSinglePrintJob( BOOL b )  	{ aMiscConfig.bSinglePrintJob = b;
                                                  aMiscConfig.SetModified();}

    BOOL		IsNumAlignSize() const 			{ return aMiscConfig.bNumAlignSize; }
    void		SetNumAlignSize( BOOL b )  		{ aMiscConfig.bNumAlignSize = b;
                                                  aMiscConfig.SetModified();}

    BOOL		IsNameFromColumn() const		{ return aMiscConfig.bIsNameFromColumn; }
    void		SetIsNameFromColumn( BOOL bSet )  	{ aMiscConfig.bIsNameFromColumn = bSet;}

    const String&	GetNameFromColumn() const		{ return aMiscConfig.sNameFromColumn; }
    void			SetNameFromColumn( const String& rSet )  	{ aMiscConfig.sNameFromColumn = rSet;
                                                                  aMiscConfig.SetModified();}

    String		GetMailingPath() const			{ return aMiscConfig.sMailingPath; }
    void		SetMailingPath(const String& sPath)	{ aMiscConfig.sMailingPath = sPath;
                                                      aMiscConfig.SetModified();}

    String		GetMailName() const				{ return aMiscConfig.sMailName; }
    void		SetMailName(const String& sName){ aMiscConfig.sMailName = sName;
                                                  aMiscConfig.SetModified();}

    const String	&GetWordDelimiter() const			{ return aMiscConfig.sWordDelimiter; }
    void		SetWordDelimiter(const String& sDelim)	{ aMiscConfig.sWordDelimiter = sDelim;
                                                          aMiscConfig.SetModified();}

    //convert word delimiter from or to user interface
    static String ConvertWordDelimiter(const String& rDelim, BOOL bFromUI);

    BOOL 		IsShowIndexPreview() const {return  aMiscConfig.bShowIndexPreview;}
    void		SetShowIndexPreview(BOOL bSet)
                    {aMiscConfig.bShowIndexPreview = bSet;
                    aMiscConfig.SetModified();}

    BOOL		IsDefaultFontInCurrDocOnly() const { return aMiscConfig.bDefaultFontsInCurrDocOnly;}
    void 		SetDefaultFontInCurrDocOnly(BOOL bSet)
                    {
                        aMiscConfig.bDefaultFontsInCurrDocOnly = bSet;
                        aMiscConfig.SetModified();
                    }

    BOOL 		IsHideFieldTips() const {return bHideFieldTips;}
    void		SetHideFieldTips(BOOL bSet) {bHideFieldTips = bSet;}
};
#endif

