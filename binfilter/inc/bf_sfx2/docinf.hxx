/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: docinf.hxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:35:37 $
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
#ifndef _SFXDOCINF_HXX
#define _SFXDOCINF_HXX

#ifndef _SFXHINT_HXX //autogen
#include <bf_svtools/hint.hxx>
#endif

#include <bf_svtools/stritem.hxx>

class SvStream; 

#include "timestamp.hxx"

namespace binfilter {

class SvStorage;
// SfxStamp changed to "tools/TimeStamp" !!!
typedef TimeStamp SfxStamp ;

#define TIMESTAMP_INVALID_DATETIME    	( DateTime ( Date ( 1, 1, 1601 ), Time ( 0, 0, 0 ) ) )	/// Invalid value for date and time to create invalid instance of TimeStamp.

class SfxDocUserKey
{
private:
friend class SfxDocumentInfo;

#define SFXDOCUSERKEY_LENMAX 19

    String		aTitle;
    String		aWord;

    void		AdjustTitle_Impl();

public:
    SfxDocUserKey() {}
    SfxDocUserKey( const String& rTitle, const String& rWord );

    // Benoetigt der BCC OS/2
    const SfxDocUserKey& operator=(const SfxDocUserKey &rCopy);

    int operator==( const SfxDocUserKey& rCmp ) const
            { return aTitle == rCmp.aTitle && aWord == rCmp.aWord; }
    int operator!=( const SfxDocUserKey& rCmp ) const { return !operator==( rCmp ); }

    const String&	GetTitle() const { return aTitle; }
    const String&	GetWord() const { return aWord; }

    BOOL 			Load( SvStream& rStrm );
    BOOL 			Save( SvStream& rStrm ) const;
};

const BYTE MAXDOCUSERKEYS  = 4;
const int  MAXDOCMAILINFOS = 256;

class SfxDocumentInfo_Impl;

class SfxDocumentInfo
{
private:
    CharSet eFileCharSet;               // Zeichensatz der Infos

    BOOL    bPasswd : 1,            // Dokument ist verschluesselt
            bPortableGraphics : 1,  // Grafiken portabel Speichern
            bQueryTemplate : 1,     // Nachladen von Vorlage abfragen
            bTemplateConfig : 1,    // Vorlage enthaelt Konfiguration
            bReadOnly : 1,
            bSaveGraphicsCompressed : 1,
            bSaveOriginalGraphics : 1,
            bSaveVersionOnClose : 1;

#define SFXDOCINFO_TITLELENMAX		63
#define SFXDOCINFO_THEMELENMAX		63
#define SFXDOCINFO_COMMENTLENMAX	255
#define SFXDOCINFO_KEYWORDLENMAX	127

    SfxStamp aCreated;
    SfxStamp aChanged;
    SfxStamp aPrinted;

    String   aTitle;
    String   aTheme;
    String   aComment;
    String   aKeywords;

    SfxDocUserKey aUserKeys[MAXDOCUSERKEYS];

    String   aTemplateName;             // Name der Dokumentvorlage
    String   aTemplateFileName;         // Dateiname der Dokumentvorlage

    String   aDefaultTarget;
    String   aReloadURL;
    BOOL     bReloadEnabled;
    sal_uInt32 nReloadSecs;

    DateTime aTemplateDate;	// Stamp der Dokumentvorlage

    USHORT	nUserDataSize;
    USHORT	nDocNo;			// schon mal rein: Dokumentnummer, was immer das sein mag
    void*	pUserData;		// Benutzer Daten, z.B. Doc-Statistik
    long	lTime;

    SfxDocumentInfo_Impl*	pImp;

    void	Free();
    String	AdjustTextLen_Impl( const String& rText, USHORT nMax );

protected:
    virtual BOOL Load( SvStream& );
    virtual BOOL Save( SvStream& ) const;

public:
    SfxDocumentInfo( const SfxDocumentInfo& );
    const SfxDocumentInfo& operator=( const SfxDocumentInfo& );
    SfxDocumentInfo();
    virtual ~SfxDocumentInfo();

    int operator==( const SfxDocumentInfo& ) const;
    const SfxDocumentInfo& CopyUserData( const SfxDocumentInfo& rSource );

    BOOL Load( SvStorage* );
    ErrCode Load(const String&);
    ULONG LoadPropertySet( SvStorage* );
    BOOL Save( SvStorage* ) const;
    BOOL SavePropertySet( SvStorage* ) const;

    void SetReloadURL( const String& rString );
    const String& GetReloadURL() const;
    BOOL IsReloadEnabled() const;
    void EnableReload( BOOL bEnable );
    const String& GetDefaultTarget() const;
    void SetDefaultTarget( const String& rString );
    ULONG GetReloadDelay() const;
    void SetReloadDelay( ULONG nDelay );

    BOOL IsReadOnly() const             { return bReadOnly; }
    BOOL IsPasswd() const               { return bPasswd; }
    BOOL IsPortableGraphics() const     { return bPortableGraphics; }
    BOOL IsSaveOriginalGraphics() const { return bSaveOriginalGraphics; }
    BOOL IsSaveGraphicsCompressed() const { return bSaveGraphicsCompressed; }
    BOOL IsQueryLoadTemplate() const    { return bQueryTemplate; }

    void SetReadOnly( BOOL b )  { bReadOnly = b; }
    void SetPasswd( BOOL b )  { bPasswd = b; }
    void SetPortableGraphics( BOOL b )  { bPortableGraphics = b; }
    void SetSaveOriginalGraphics( BOOL b ) { bSaveOriginalGraphics = b; }
    void SetSaveGraphicsCompressed( BOOL b ) { bSaveGraphicsCompressed = b; }
    void SetQueryLoadTemplate( BOOL b ) { bQueryTemplate = b; }

    const SfxStamp& GetCreated() const  { return aCreated;  }
    const SfxStamp& GetChanged() const  { return aChanged;  }
    const SfxStamp& GetPrinted() const  { return aPrinted;  }
    void  SetCreated( const SfxStamp& rStamp ) { aCreated = rStamp; }
    void  SetChanged( const SfxStamp& rStamp ) { aChanged = rStamp; }
    void  SetPrinted( const SfxStamp& rStamp ) { aPrinted = rStamp; }

    const String& GetTemplateName() const   { return aTemplateName; }
    const String& GetTemplateFileName() const   { return aTemplateFileName; }
    const DateTime& GetTemplateDate() const { return aTemplateDate; }
    void  SetTemplateName( const String& rName )  { aTemplateName = rName; bQueryTemplate = 1; }
    void  SetTemplateFileName( const String& rFileName )  { aTemplateFileName = rFileName; bQueryTemplate = 1;  }
    void  SetTemplateDate(const DateTime& rDate) { aTemplateDate = rDate; bQueryTemplate = 1; }

    const String&  GetTitle()   const   { return aTitle;    }
    const String&  GetTheme()   const   { return aTheme;    }
    const String&  GetComment() const   { return aComment;  }
    const String&  GetKeywords()const   { return aKeywords; }

    void  SetTitle( const String& rVal );
    void  SetTheme( const String& rVal );
    void  SetComment( const String& rVal );
    void  SetKeywords( const String& rVal );

    void  SetChanged( const String& rChanger ) { SetChanged( SfxStamp( rChanger ) ); }
    void  SetCreated( const String& rCreator ) { SetCreated( SfxStamp( rCreator ) ); }

    USHORT GetUserKeyCount() const { return MAXDOCUSERKEYS; }
    const  SfxDocUserKey& GetUserKey( USHORT n ) const;
    void   SetUserKey( const SfxDocUserKey& rKey, USHORT n );

    void   SetSaveVersionOnClose( BOOL bSet ) { bSaveVersionOnClose = bSet; }
    BOOL   IsSaveVersionOnClose() const { return bSaveVersionOnClose; }

    void   SetTime(long l) { lTime = l; }
    long   GetTime() const { return IsUseUserData() ? lTime : 0L; }

    void*  GetUserData() const { return pUserData; }
    USHORT GetUserDataSize() const { return nUserDataSize; }
    void   SetUserData(USHORT nSize, void *pData);

    USHORT GetDocumentNumber() const { return IsUseUserData() ? nDocNo : (USHORT) 0; }
    void   SetDocumentNumber(USHORT nNo) { nDocNo = nNo; }
    void   IncDocumentNumber() { ++nDocNo; }
    void   SetTemplateConfig (BOOL bConfig)
           { bTemplateConfig = bConfig ? 1 : 0; }
    BOOL   HasTemplateConfig () const
           { return bTemplateConfig; }

    String GetCopiesTo() const;
    void SetCopiesTo( const String& rStr );
    String GetOriginal() const;
    void SetOriginal( const String& rStr );
    String GetReferences() const;
    void SetReferences( const String& rStr );
    String GetRecipient() const;
    void SetRecipient( const String& rStr );
    String GetReplyTo() const;
    void SetReplyTo( const String& rStr );
    String GetBlindCopies() const;
    void SetBlindCopies( const String& rStr );
    String GetInReplyTo() const;
    void SetInReplyTo( const String& rStr );
    String GetNewsgroups() const;
    void SetNewsgroups( const String& rStr );
    String GetSpecialMimeType() const;
    void SetSpecialMimeType( const String& rStr );
    USHORT GetPriority() const;
    void SetPriority( USHORT nPrio );
    BOOL IsUseUserData() const;
    void SetUseUserData( BOOL bNew );

    void	DeleteUserData( BOOL bUseAuthor );

    void Clear();
};

DECL_PTRHINT(/*empty*/, SfxDocumentInfoHint, SfxDocumentInfo);

// class SfxDocumentInfoItem ---------------------------------------------

class SfxDocumentInfoItem : public SfxStringItem
{
private:
    SfxDocumentInfo         aDocInfo;
    FASTBOOL                bHasTemplate;
    FASTBOOL                bOwnFormat;

public:
    TYPEINFO();
    SfxDocumentInfoItem();
};

}//end of namespace binfilter
#endif

