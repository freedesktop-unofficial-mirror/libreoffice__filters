/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw6par.hxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2006-11-08 15:45:57 $
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
#ifndef _SW6PAR_HXX
#define _SW6PAR_HXX


#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _VCL_VCLENUM_HXX
#include <vcl/vclenum.hxx>
#endif
#ifndef _SVX_SVXENUM_HXX //autogen
#include <bf_svx/svxenum.hxx>
#endif


#ifndef _TOXE_HXX
#include <toxe.hxx>
#endif
#ifndef _SW6FILE_HXX
#include <sw6file.hxx>
#endif
class SfxPoolItem; 
namespace binfilter {


class SwDoc;
class SwPaM;
class SwNodeIndex;
class SvxTabStopItem;
 
class SwFmt;

// Enthaelt die Dokument-Info. Groesse des Structs muss genau
// stimmen, wird beim Einlesen als Record verwendet...

struct DOCINFOTYPE {
    String Autor;               // String fuer Autorennamen
    String Kateg;               // Kategorie zum Suchen
    String Thema[4];            // Thematik-String
    String Keys[4];             // Allerlei Schluesselworte
};

// Die Funktion ReadLn filtert alle harten Formatsteuerzeichen
// raus und legt sie in einer Verketteten Liste ab. Diese Liste
// kann man nach ReadLn dann durchgehen und bearbeiten.

struct HFORM {
    HFORM *pNxt;                        // Naechste Info
    USHORT nOfs;                        // Offset des Textes wo Info gueltig
    USHORT nXtd;                        // Gemerkter Addierer bei Druckzchn
    BYTE   cDat[256];                   // Daten fuer diese Info
};


class Sw6Layout:public Sw6File
{

private:
    const String *pMyName;              // Mein Filename fuer Dateirefs

    struct MYSTAT
    {
        BYTE   cFrst;                   // Falls nur CtrlL oder CtrlG
        short  nAlay;                   // Status der Layouts bei ReadLn
        BOOL   bSlay;                   // Soll neues Slay gesetzt werden?
        short  nSLft;                   // Nummern f�r linke Seitenlayouts
        short  nSRgt;                   // dto. f�r rechtes Seiten
        short  nSFst;                   // Erstseitenlayout
        short  nBlay;
        short  nKopf;
        short  nFuss;
        USHORT nPage;                   // Pagenummer fuer Gerade/Ungerade
        short  nAddo;                   // Adder fuer HFORM-nOfs
        HFORM *pFrmt;                   // Fuer harte Forminfo aus ReadLn
        MYSTAT (void):
            cFrst('\0'),nAlay(0),bSlay(FALSE),
            nSLft(0),nSRgt(0),nSFst(0),
            nBlay(0),nKopf(0),nFuss(0),
            nPage(0),nAddo(0),pFrmt(NULL){}
    } aSta;

    BOOL Glieder[5];                    // Welche Giederebenen genutzt

    Sw6Stack aStk;                      // Stack fuer Push/Popstat
    LAYDESC *pLay;                      // Halter fuer Gesamtlayout
    DOCINFOTYPE *pDocInfo;              // Allgemeine Dokument-Info
    USHORT nLastFontMatch;


    BOOL   ReadBool(void);
    void   DelHForm(void);
    void   AddHForm(const sal_Char *pCtrl,short nPos,short nAnz,short nAdd=0);
    short  ZchnZahl(sal_Char Ch1,sal_Char Ch2) const;

    sal_Char   UpCaseOEM(sal_Char c) const;
    void   AddXForm(sal_Char cLead,ByteString &rTmp,String &rStr);

    void   ScanLayoutB(short &rnLay,BLAY *pKey[],const sal_Char c1,
                       const sal_Char c2,const short nAnz) const;
    void   ScanLayoutA(short &rnLay,ALAY *pKey[],const sal_Char c1,
                       const sal_Char c2,const short nAnz) const;
    void   ScanLayoutS(short &rnLay,SLAY *pKey[],const sal_Char c1,
                       const sal_Char c2,const short nAnz) const;
    void   ScanLayoutKF(short &rnLay,KOFU *pKey[],const sal_Char c1,
                        const sal_Char c2,const short nAnz) const;
    BOOL   ScanKreuz(const sal_Char *pPatt,const sal_Char *pOrig,size_t &rIgnr,sal_Char *pPara=NULL);
    BOOL   TextBefehl(const sal_Char *pPatt,const sal_Char *pOrig);

    SvxAdjust   TransAdj(SATZTYP eForm);
    SfxPoolItem *TransAtt(ATTRBITS eAttr,BOOL bEin,SwTwips nSiz);
    void       TransFnt(short nFnt,FontFamily &rFam,FontPitch &rPit,CharSet &rSet,String &rNam);
    BOOL       TransFSA(SwFmt &rFmt, short nFnt, short nSiz, ATTRS nAtt);

    void   InsertTOX(SwDoc &rDoc,SwPaM &rPaM,USHORT nLen,HFORM *pTmp,TOXTypes eTyp);
    void   InsertTab(USHORT nTab,TABU &rTab,SvxTabStopItem &rTabs,SwTwips nKor);
    void   InsertExtra(SwDoc &rDoc,SwPaM &rPaM,const SwNodeIndex &rWohin,long lFPos,sal_Char *pcAKey=NULL);
    BOOL   InsertNote(SwDoc &rDoc,SwPaM &rPaM,USHORT nNote,BOOL bFuss);
    void   InsertAttr(SwDoc &rDoc,SwPaM &rPaM,ATTRBITS eAttr,BOOL bEin,SwTwips nSiz);
    void   InsertAForm(SwDoc &rDoc,SwPaM &rPaM,BYTE  *pCtrl);
    void   SetFollow(short nVon,short nNach,SwDoc &rDoc);

    // virtual muss nicht mehr sein, es gibt nur noch den Parser!
    virtual size_t PutRest(String &rStr,sal_Char *pCtrl);
    /*virtual*/ void   PushStat(long nFPos);
    /*virtual*/ void   PopStat(void);

protected:

    long       lLin;                    // Mitlaufende Zeilenzahl (in ReadLn++)

    void   SetSlay(SwDoc &rDoc,SwPaM &rPaM);
    BOOL   TstSlay(void) {return aSta.bSlay;}

public:

    /*virtual*/ BOOL ReadLn(String &rStr);

    enum Bereich {Kopf,Fuss,FNot,ENot,ANot,Text};

    void MerkeNoten(Bereich eNot);
    void SetGpmFile(const String& rGpm);
    void SetAlayTrans(void);
    void ResetLay(SwDoc &rDoc);
    void SetDocInfo(DOCINFOTYPE *pInfo) {pDocInfo=pInfo;}
    BOOL IgnExtra(BOOL bNote,short nAnzl=0,SwTwips *plHoch=NULL);
    BOOL LeseKoFu(BOOL Kopf);
    BOOL LeseLayInfo(BOOL Konv);

    SwTxtFmtColl *GetAlay(void);        // Holt die gerade gueltige FmtColl
    void InsertLayouts(SwDoc &rDoc,SwPaM*);
    BOOL InsertLine(SwDoc &rDoc,SwPaM &rPam,String &rStg,BOOL bLast=FALSE);

    BOOL Sw6LayoutOk(void)
    {
        return (pLay!=NULL);
    }
    Sw6Layout(SvStream &rInp, ULONG *pErrno, const String *pFileName=NULL); //$ istream
   ~Sw6Layout(void);
};

// Gesamter Describtor einer Datei

struct DATEIDESC {
    String  LayName;                    // Layoutdateiname
    String  PassWord;                   // Passwort fuer Datei
    DOCINFOTYPE DocInfo;                // Allgemeine Dokument-Info
};

// einige Forward-Deklaratioen
class SwPaM;
class SwDoc;
#ifdef __MWERKS__
class SwSw6Parser : public Sw6Layout // Fehler im MWerks-Compiler, sorry
#else
class SwSw6Parser:private Sw6Layout
#endif
{

private:
    DATEIDESC *pDat;                    // Dateidescribtor
    SwPaM     *pPaM;                    // WriterG-Einfuegepos
    SwDoc     *pDoc;                    // WriterG-Dokumentzugriff
    BOOL       bNew;                    // Darf es was neues sein?

    BOOL Ueberlese(const long Blk);
    BOOL ReadDocInfo(void);

public:
    BOOL CallParser(void);

    SwSw6Parser(SwDoc *pSwDoc,const SwPaM &rSwPaM,SvStream *pIstream,
                BOOL bNewDoc, ULONG * pErrno, const String *pFileName );
    ~SwSw6Parser(void);
};


} //namespace binfilter
#endif _SW6PAR_HXX
