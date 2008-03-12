/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xpmread.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:40:53 $
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

#ifndef _XPMREAD_HXX
#define _XPMREAD_HXX

#ifndef _BITMAP_HXX
#include <vcl/bitmap.hxx>
#endif

class BitmapWriteAccess;
class Graphic;

namespace binfilter
{

#ifdef _XPMPRIVATE

#define XPMTEMPBUFSIZE		0x00008000
#define XPMSTRINGBUF		0x00008000

#define XPMIDENTIFIER		0x00000001			// mnIdentifier includes on of the six phases
#define XPMDEFINITION		0x00000002			// the XPM format consists of
#define XPMVALUES			0x00000003
#define XPMCOLORS			0x00000004
#define XPMPIXELS			0x00000005
#define XPMEXTENSIONS		0x00000006
#define XPMENDEXT			0x00000007


#define XPMREMARK			0x00000001			// defines used by mnStatus
#define XPMDOUBLE			0x00000002
#define XPMSTRING			0x00000004
#define XPMFINISHED			0x00000008

#define XPMCASESENSITIVE	0x00000001
#define XPMCASENONSENSITIVE 0x00000002

// ---------
// - Enums -
// ---------

enum ReadState
{
    XPMREAD_OK,
    XPMREAD_ERROR,
    XPMREAD_NEED_MORE
};

// -------------
// - XPMReader -
// -------------

class XPMReader : public GraphicReader
{
private:

    SvStream&			mrIStm;
    Bitmap				maBmp;
    BitmapWriteAccess*	mpAcc;
    Bitmap				maMaskBmp;
    BitmapWriteAccess*	mpMaskAcc;
    long				mnLastPos;

    ULONG				mnWidth;
    ULONG				mnHeight;
    ULONG				mnColors;
    ULONG				mnCpp;								// characters per pix
    BOOL				mbTransparent;
    BOOL				mbStatus;
    ULONG				mnStatus;
    ULONG				mnIdentifier;
    BYTE				mcThisByte;
    BYTE				mcLastByte;
    ULONG				mnTempAvail;
    BYTE*				mpTempBuf;
    BYTE*				mpTempPtr;
    BYTE*				mpFastColorTable;
    BYTE*				mpColMap;
    ULONG				mnStringSize;
    BYTE*				mpStringBuf;
    ULONG				mnParaSize;
    BYTE*				mpPara;

    BOOL				ImplGetString( void );
    BOOL				ImplGetColor( ULONG );
    BOOL				ImplGetScanLine( ULONG );
    BOOL				ImplGetColSub( BYTE* );
    BOOL				ImplGetColKey( BYTE );
    void				ImplGetRGBHex( BYTE*, ULONG );
    BOOL				ImplGetPara( ULONG numb );
    BOOL				ImplCompare( BYTE*, BYTE*, ULONG, ULONG nmode = XPMCASENONSENSITIVE );
    ULONG				ImplGetULONG( ULONG nPara );

public:
                        XPMReader( SvStream& rStm );
    virtual				~XPMReader();

    ReadState			ReadXPM( Graphic& rGraphic );
};

#endif // _XPMPRIVATE

// -------------
// - ImportXPM -
// -------------

BOOL ImportXPM( SvStream& rStream, Graphic& rGraphic );

}

#endif // _XPMREAD_HXX
