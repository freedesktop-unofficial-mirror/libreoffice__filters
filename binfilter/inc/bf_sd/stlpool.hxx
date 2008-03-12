/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: stlpool.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:33:42 $
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

#ifndef _SD_STLPOOL_HXX
#define _SD_STLPOOL_HXX


#ifndef _SFXSTYLE_HXX //autogen
#include <bf_svtools/style.hxx>
#endif
namespace binfilter {

class SdStyleSheet;
class SdDrawDocument;


class SdStyleSheetPool : public SfxStyleSheetPool
{
private:
    SfxStyleSheetBase* pActualStyleSheet;
    SdDrawDocument*    pDoc;

protected:
    virtual SfxStyleSheetBase* Create(const String& rName,
                                      SfxStyleFamily eFamily,
                                      USHORT nMask);

public:
                        SdStyleSheetPool(SfxItemPool& rPool, SdDrawDocument* pDocument);
    virtual 			~SdStyleSheetPool();

    void				SetActualStyleSheet(SfxStyleSheetBase* pActStyleSheet)
                                       { pActualStyleSheet = pActStyleSheet; }
    SfxStyleSheetBase*	GetActualStyleSheet()	 { return pActualStyleSheet; }

    SfxStyleSheetBase*  GetTitleSheet(const String& rLayoutName);

                            // Caller muss Liste loeschen
    List*               CreateOutlineSheetList(const String& rLayoutName);

    /** creates all layout style sheets for the givin layout name if they
        don't exist yet.

        @param rLayoutName	Must be the name of a master page
        @param bCheck		If set to true, the debug version will assert if a style
                            had to be created. This is used to assert errors in documents
                            when styles are missing.
    */
    void                CreateLayoutStyleSheets(const String& rLayoutName, sal_Bool bCheck = sal_False );

    void                CreatePseudosIfNecessary();
    void				UpdateStdNames();
    void 				AdjustLRSpaceItems();
    static void			PutNumBulletItem( SfxStyleSheetBase* pSheet, Font& rBulletFont );
    Font                GetBulletFont() const;

    SdDrawDocument* 	GetDoc() const { return pDoc; }
};

} //namespace binfilter
#endif	   // _SD_STLPOOL_HXX



