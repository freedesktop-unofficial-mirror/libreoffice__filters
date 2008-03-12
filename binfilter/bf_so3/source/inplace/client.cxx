/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: client.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:12:51 $
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

#include <stdio.h>

#ifdef WNT
#include <tools/prewin.h>
#include <windows.h>
#include <tools/postwin.h>
#include <vcl/svapp.hxx>
#include <vcl/wrkwin.hxx>
#include <vcl/sysdata.hxx>
#endif

#ifndef _SV_SALBTYPE_HXX
#include <vcl/salbtype.hxx>
#endif

#include <vcl/window.hxx>
#include <bf_so3/client.hxx>
#include <tools/debug.hxx>
#include <tools/urlobj.hxx>
#include <bf_so3/embobj.hxx>
#include "bf_so3/soerr.hxx"

namespace binfilter {

//=========================================================================
TYPEINIT0(SvClientData);

SvClientData::SvClientData( SvEmbeddedClient * pCl, Window * pWin )
    : pClient( pCl )
    , aScaleWidth( 1, 1 )
    , aScaleHeight( 1, 1 )
    , pEditWin( pWin )
    , bInvalidate( pWin != NULL )
{
}

//=========================================================================
SvClientData::~SvClientData()
{
}

//=========================================================================
void SvClientData::Invalidate()
/*	[Beschreibung]

    Der Bereich des Objektes auf dem EditWin wird f"ur ung"ultig
    erkl"art, sodass ein asynchroner PaintEvent generiert wird. Dies
    passiert nur, wenn die Methode <SvClientData::IsInvalidate> TRUE
    liefert.

    [Querverweise]

    <Window::Paint>, <SvClientData::GetEditWin>,
    <SvClientData::SetInvalidate>.
*/
{
    if( bInvalidate )
    {
        Rectangle aR = GetObjArea();
        aR.SetSize( Size( Fraction( aR.GetWidth() ) * aScaleWidth,
                        Fraction( aR.GetHeight() ) * aScaleHeight ) );
        pEditWin->Invalidate( aR );
    }
}

//=========================================================================
Window * SvClientData::GetEditWin() const
/*	[Beschreibung]

    Diese Methode liefert das Fenster in dem das Objekt im
    Container dargestellt wird. Dieses Fenster wird als Parent bei
    InPlace-Aktivit"at benutzt.

    [R"uckgabewert]

    Window *	Das Fenster in dem das Objekt dargestellt wird.
                NULL, wenn das Objekt nciht dargestellt wird oder der
                Client kein Fenster liefert.
*/
{
    return pEditWin;
}

//=========================================================================
void SvClientData::SetSizeScale
(
    const Fraction & rScaleWidth,
    const Fraction & rScaleHeight
)
/*	[Beschreibung]

    Hat das Objekt abweichend vom OutputDevice des EditWin eine andere
    Skalierung, dann muss diese mitgeteilt werden. Die Skalierung ist
    relativ zum Outputdevice und bezieht sich nur auf die Gr"osse des
    Objektes.
*/
{
    aScaleWidth = rScaleWidth;
    aScaleHeight = rScaleHeight;
}

//=========================================================================
BOOL SvClientData::SetObjArea
(
    const Rectangle & rArea
)
/*	[Beschreibung]

    Die Gr"oesse des Objektes innerhalb des Containers in Einheiten
    des EditWin wird gesetzt. Die Methode l"ost ein
    <SvClientData::Invalidate> auf den alten und den neuen Bereich aus,
    wenn sich diese unterscheiden.

    [Querverweise]

    <SvClientData::GetObjArea>, <SvClientData::SetObjAreaPixel>
*/
{
    if( rArea != aObjRect )
    {
        Invalidate(); // auf Alte
        aObjRect = rArea;
        Invalidate(); // auf Neue
        return TRUE; // Bereich hat sich geandert
   }
   return FALSE;  // Bereich hat sich geandert
}

//=========================================================================
Rectangle SvClientData::GetObjArea() const
/*	[Beschreibung]

    [R"uckgabewert]

    Rectangle	Die Gr"oesse des Objektes innerhalb des Containers
                in Einheiten des EditWin wir zur"uckgegeben.

    [Querverweise]

    <SvClientData::SetObjArea>, <SvClientData::GetObjAreaPixel>

*/
{
    return aObjRect;
}

//=========================================================================
Rectangle SvClientData::PixelObjAreaToLogic
(
    const Rectangle & rPixRect
) const
/*	[Beschreibung]

    [R"uckgabewert]

    Rectangle	rPixRect wird in Einheiten des EditWin, unter
                Ber"ucksichtigung der extra Skalierung, umgerechnet.

    [Querverweise]

    <SvClientData::SetSizeScale>, <SvClientData::LogicObjAreaToPixel>

*/
{
/*  Zu frueh, da dies schon in DoVerb passiert! Fuer externe Fenster muss
    der MapMode auf Default stehen
    if( !pEditWin )
        pEditWin = GetEditWin();
*/
    Rectangle aR = rPixRect;
    if( pEditWin )
    {
        aR.SetSize( pEditWin->PixelToLogic( aR.GetSize() ) );
        aR.SetPos( pEditWin->PixelToLogic( aR.TopLeft() ) );
    }
    aR.SetSize( Size( Fraction( aR.GetWidth() )	/ aScaleWidth,
                        Fraction( aR.GetHeight() ) / aScaleHeight ) );

    return aR;
}

//=========================================================================
#include <math.h>

Rectangle SvClientData::LogicObjAreaToPixel
(
    const Rectangle & rRect
) const
/*	[Beschreibung]

    [R"uckgabewert]

    Rectangle	rRect in Einheiten des EditWin wird, unter
                Ber"ucksichtigung der extra Skalierung, in Pixel
                umgerechnet.

    [Querverweise]

    <SvClientData::SetSizeScale>, <SvClientData::PixelObjAreaToLogic>

*/
{
/*  Zu frueh, da dies schon in DoVerb passiert! Fuer externe Fenster muss
    der MapMode auf Default stehen
    if( !pEditWin )
        ((SvClientData *)this)->pEditWin = ((SvClientData *)this)->GetEditWin();
*/
    Rectangle aR( rRect );
    // *must* happen before LogicToPixel conversion, as:
    // scaling down to pixel is integer, which leads to
    // rounding errors (#89984#)
    aR.SetSize( Size( FRound( double(Fraction( aR.GetWidth() ) * aScaleWidth) ),
                      FRound( double(Fraction( aR.GetHeight() ) * aScaleHeight ) ) ) );
    // Wenn kein Window, dann extern und somit Pixel
    if( pEditWin )
    {
        aR.SetSize( pEditWin->LogicToPixel( aR.GetSize() ) );
        aR.SetPos( pEditWin->LogicToPixel( aR.TopLeft() ) );
    }
    return aR;
}

/************** class SvAreaConstrain ***********************************/
/*************************************************************************
|*    SvAreaConstrain::ComputeConstrain()
|*
|*    Beschreibung:
*************************************************************************/
Size SvAreaConstrain::ComputeConstrain( const Size & rSize,
                            Fraction * pWidthScale /*OutParam*/,
                            Fraction * pHeightScale /*OutParam*/ ) const
{
    Size aSize( rSize );
    // Wenn die Schrittweite eingeschraenkt ist
    if( aStepSize.Width() )
    {
        // Breite runden
        aSize.Width() += aStepSize.Width() / 2;
        aSize.Width() /= aStepSize.Width();
        aSize.Width() *= aStepSize.Width();
    }
    if( aStepSize.Height() )
    {
        // Hoehe runden
        aSize.Height() += aStepSize.Height() / 2;
        aSize.Height() /= aStepSize.Height();
        aSize.Height() *= aStepSize.Height();
    }

    // Breite Anpassen
    if( aSize.Width() < aMinSize.Width() )
    {
        if( pWidthScale )
            *pWidthScale = Fraction( aMinSize.Width(), aSize.Width() );
        aSize.Width() = aMinSize.Width();
    }
    else if( aSize.Width() > aMaxSize.Width() )
    {
        if( pWidthScale )
            *pWidthScale = Fraction( aMaxSize.Width(), aSize.Width() );
        aSize.Width() = aMaxSize.Width();
    }

    // Hoehe Anpassen
    if( aSize.Height() < aMinSize.Height() )
    {
        if( pHeightScale )
            *pHeightScale = Fraction( aMinSize.Height(), aSize.Height() );
        aSize.Height() = aMinSize.Height();
    }
    else if( aSize.Height() > aMaxSize.Height() )
    {
        if( pHeightScale )
            *pHeightScale = Fraction( aMaxSize.Height(), aSize.Height() );
        aSize.Height() = aMaxSize.Height();
    }
    return aSize;
}


/************** class SvEmbeddedClient **************************************/
SV_IMPL_FACTORY(SvEmbeddedClientFactory)
    {
    }
};
TYPEINIT1(SvEmbeddedClientFactory,SvFactory);

SO2_IMPL_STANDARD_CLASS1_DLL(SvEmbeddedClient,SvEmbeddedClientFactory,SvObject,
                             0xE4CAFE00L, 0x73AE, 0x101B,
                             0x80,0x4C,0xFD,0xFD,0xFD,0xFD,0xFD,0xFD );

::IUnknown * SvEmbeddedClient::GetMemberInterface( const SvGlobalName & rName )
{
    (void)rName;
    return NULL;
}

void SvEmbeddedClient::TestMemberObjRef( BOOL bFree )
{
    (void)bFree;

#ifdef DBG_UTIL
    if( GetEmbedObj() )
    {
        ByteString aTest = "\t\tGetEmbedObj() == ";
        aTest.Append( ByteString::CreateFromInt32( (ULONG)(SvObject *)GetEmbedObj() ) );
        DBG_TRACE( aTest.GetBuffer() );
    }
#endif
}

#ifdef TEST_INVARIANT
void SvEmbeddedClient::TestMemberInvariant( BOOL bPrint )
{
#ifdef DBG_UTIL
    if( bPrint )
    {
        if( HasViewData() )
        {
            ByteString aTest( "\t\tSvClientData == " );
            aTest.Append( ByteString::CreateFromInt32(  (ULONG)GetClientData() ) );
            DBG_TRACE( aTest.GetBuffer() );
        }
    }
#else
    (void)bPrint;
#endif
}
#endif

/************************************************************************
|*    SvEmbeddedClient::SvEmbeddedClient()
|*
|*    Beschreibung
*************************************************************************/
//=========================================================================
//==============SvEmbeddedClient===========================================
//=========================================================================
#define INIT_CTOR                               \
      pParent           ( NULL )				\
    , nAspect           ( ASPECT_CONTENT )		\
    , bAutoForce        ( TRUE )             	\
    , bDeleteData   	( FALSE )				\
    , bCanPlugIn	   	( FALSE )

SvEmbeddedClient::SvEmbeddedClient()
    : pData( NULL )
    , INIT_CTOR
{
}

//=========================================================================
SvEmbeddedClient::SvEmbeddedClient( Window * pWin )
    : INIT_CTOR
{
    pData = new SvClientData( this, pWin );
    bDeleteData = TRUE;
}

//=========================================================================
SvEmbeddedClient::~SvEmbeddedClient()
{
    if( bDeleteData )
        delete pData;
}

//=========================================================================
void SvEmbeddedClient::MakeViewData()
/*	[Beschreibung]

    Der Client liefert ein View-Environment, der IP-Aktivierung oder
    das Invalidieren des Objektbereichs in der View des Containers
    ermoeglicht. Wenn in dieser virtuellen Methode das Environment
    erzeugt wird, dann muss es mit <SvClientData::SetClientData>
    eingesetzt werden. Von den Klassen <SvClientData> oder
    <SvContainerEnvironment> muss ein Konstruktor gerufen werden, der
    ein <SvEmbeddedClient> !ubergeben bekommt.
    Wenn keine View vorhanden ist, dann wird wird in dieser Methode
    nichts getan oder eine View angelegt.

    [Beispiel]
    // die n"chsten beiden Zeilen sind Optional
    if( !HasView() )
        CreateView();

    if( HasView() )
    {
        SvClientData * pD = new SvClientData( this, aView.GetEditWin() );
        SetViewData( pD );
    }

    [Querverweise]

    <SvEmbeddedClient::HasViewData>, <SvEmbeddedClient::FreeViewData>
*/
{
    if( !Owner() && !pData )
    {
        pData = new SvClientData( this );
        bDeleteData = TRUE;
        // In ImpOleObject::DoVerb "ubergebenes Rectangle
        pData->SetObjAreaPixel( aDoVerbRectPixel );
    }
}

//=========================================================================
void SvEmbeddedClient::FreeViewData
(
    SvClientData * pDataP	/* View-Daten die zerst"ort werden k"onnen */
)
/*	[Beschreibung]

    Die View-Daten k"onnen freigegeben werden. Werden sie zerst"ort,
    dann m"ussen sie vorher mit <SvEmbeddedClient::SetViewData( NULL )>
    ausgetragen werden.

    [Beispiel]
    ...::FreeViewData( SvClientData * pData )
    {
        SetViewData( NULL );
        delete pData;
    }

    [Querverweise]

    <SvEmbeddedClient::HasViewData>, <SvEmbeddedClient::FreeViewData>
*/
{
#ifdef DBG_UTIL
    DBG_ASSERT( pDataP == pData, "pDataP != pData!" )
#else
    (void)pDataP;
#endif
    if( !Owner() && bDeleteData )
    {
        delete pData;
        pData = NULL;
    }
}

//=========================================================================
SvClientData * SvEmbeddedClient::GetClientData()
/*	[Beschreibung]

    Gibt die View-Daten zur"uck. Neue View-Daten werden
    nur angelegt, wenn der Client "Connected" ist.

    [R"uckgabewert]

    SvContainerEnvironment * 	Das Environment zu diesem Client wird
                                zur"uckgegeben.

    [Querverweise]

    <SvProtocol::IsConnect>, <SvEmbeddedClient::MakeViewData>
*/
{
    if( !pData && GetProtocol().IsConnect() )
        MakeViewData();
    return pData;
}

//=========================================================================
BOOL SvEmbeddedClient::CanPlugIn()
{
    return bCanPlugIn;
}

//=========================================================================
ErrCode	SvEmbeddedClient::GetContURL
(
    INetURLObject & rURL	/* Hier wird der URL des Containers
                               abgelegt. */
)
/*	[Beschreibung]

    Die URL des Dokumentes wird zur"uckgegeben. Defaultm"assig wird
    versucht die URL aus dem Moniker zu generieren.

    [R"uckgabewert]

    ERRCODE_NONE,	In rURL steht der URL des Dokumentes.
    ERRCODE_SO_GENERALERROR, rURL ist leer.

    [Querverweise]

    <SvEmbeddedClient::GetObjMoniker()>
*/
{
    (void)rURL;
    ULONG nRet = ERRCODE_SO_GENERALERROR;
    return nRet;
}

/*************************************************************************
|*    SvEmbeddedClient::SetAspect()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedClient::SetAspect( USHORT nAspectP, BOOL bInvalidate )
{
    if( nAspect != nAspectP )
    {
        nAspect = nAspectP;
        if( bInvalidate )
        {
            SvClientData * pD = GetClientData();
            if( pD )
                pD->Invalidate();
        }
   }
}

/*************************************************************************
|*    SvEmbeddedClient::Embedded()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedClient::Embedded( BOOL bEmbed )
{
#ifdef DBG_UTIL_PROT
    String aTest( "Client---Embedded---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bEmbed ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#endif

    if( Owner() )
    {
        if( !bEmbed && pData && pData->pEditWin )
        {
            pData->pEditWin->ToTop( TOTOP_FOREGROUNDTASK );
        }

        SvClientData * pD = GetClientData();
        if( pD )
            pD->Invalidate();
    }
    if( !bEmbed && HasViewData() )
        FreeViewData( pData );
}

//=========================================================================
void SvEmbeddedClient::PlugIn( BOOL bPlugIn )
{
#ifdef DBG_UTIL_PROT
    String aTest( "Client---PlugIn---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bPlugIn ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#else
    (void)bPlugIn;
#endif

}

/*************************************************************************
|*    SvEmbeddedClient::ViewChanged()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedClient::ViewChanged( USHORT nAspectP )
{
    if( Owner() )
    {
        if( GetAspect() == nAspectP )
        {
            SvClientData * pD = GetClientData();
            if( pD )
               pD->Invalidate();
        }
    }
}

/*************************************************************************
|*    SvEmbeddedClient::SaveObject()
|*
|*    Beschreibung
*************************************************************************/
BOOL SvEmbeddedClient::SaveObject()
{
    BOOL bRet = FALSE;
    if( Owner() )
    {
        SvEmbeddedObject * pE = GetEmbedObj();
        if( pE )
        {
            bRet = pE->DoSave();
            pE->DoSaveCompleted();
        }
    }
    return bRet;
}

//=========================================================================
SvEmbeddedObjectRef SvEmbeddedClient::GetContainer()
/*	[Beschreibung]

    Diese Methode liefert den Container (Dokument), in dem das,
    mit dem Client verbundene, Objekt enthalten ist.

    [R"uckgabewert]

    SvEmbeddedObjectRef		Der Container des Objektes oder NULL, wenn
                            das Objekt nirgentwo enthalten ist.
*/
{
    SvEmbeddedObjectRef xCont;
    if( Owner() )
    {
        if( GetParent() )
            xCont = GetParent()->GetEmbedObj();
        else
        {
            SvEmbeddedObject * pE = GetEmbedObj();
            if( pE )
                // nutzt die Hierarchie der SvPersist-Objekte fuer Default
                xCont = SvEmbeddedObjectRef( pE->GetParent() );
        }
    }
    return xCont;
}

//=========================================================================
void SvEmbeddedClient::MakeVisible()
/*	[Beschreibung]

    Das Objekt, mit dem dieser Client verbunden ist, soll in den
    sichtbaren Bereich des Containers geschoben werden.
*/
{
    if( GetParent() )
        GetParent()->MakeVisible();

}

/*************************************************************************
|*    InPlace Protocoll
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedClient::Connected( BOOL bConnect )
{ // Zu dieser Methode gibt es kein Ole2 aequivalent
#ifdef DBG_UTIL_PROT
    String aTest( "Client---Connected---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bConnect ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#endif
    if( !bConnect && HasViewData() )
        FreeViewData( pData );
}

/*************************************************************************
|*    SvEmbeddedClient::Opened()
|*
|*    Beschreibung
*************************************************************************/
void SvEmbeddedClient::Closed()
{
    // genau in diesem muss die InClose-Variable zurueckgesetzt werden
    SvEditObjectProtocol aProt_( GetProtocol() );
    aProt_.SetInClosed( TRUE );
    if( Owner() )
        GetProtocol().Reset();
    aProt_.SetInClosed( FALSE );
}

void SvEmbeddedClient::Opened( BOOL bOpen )
{
#ifdef DBG_UTIL_PROT
    String aTest( "Client---Opened---" );
    aTest += Owner() ? "Intern" : "Extern: ";
    aTest += bOpen ? "TRUE" : "FALSE";
    DBG_TRACE( aTest )
#else
    (void)bOpen;
#endif

}

}

