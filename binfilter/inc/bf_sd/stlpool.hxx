/*************************************************************************
 *
 *  $RCSfile: stlpool.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:28 $
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

#ifndef _SD_STLPOOL_HXX
#define _SD_STLPOOL_HXX


#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif

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
//STRIP001 	virtual SfxStyleSheetBase* Create(const SdStyleSheet& rStyle);

public:
                        SdStyleSheetPool(SfxItemPool& rPool, SdDrawDocument* pDocument);
    virtual 			~SdStyleSheetPool();

    void				SetActualStyleSheet(SfxStyleSheetBase* pActStyleSheet)
                                       { pActualStyleSheet = pActStyleSheet; }
    SfxStyleSheetBase*	GetActualStyleSheet()	 { return pActualStyleSheet; }

    SfxStyleSheetBase*  GetTitleSheet(const String& rLayoutName);
//STRIP001 	String				GetLayoutName() const;

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
//STRIP001 	void                EraseLayoutStyleSheets(const String& rLayoutName);
//STRIP001 	List*               CreateLayoutSheetNames(const String& rLayoutName) const;
//STRIP001 	List*               CreateLayoutSheetList(const String& rLayoutName);
//STRIP001 	void                CopyLayoutSheets(const String& rLayoutName,
//STRIP001 										 SdStyleSheetPool& rSourcePool,
//STRIP001 										 List* pCreatedSheets = NULL);
//STRIP001 	void                CopyGraphicSheets(SdStyleSheetPool& rSourcePool);

    void                CreatePseudosIfNecessary();
    void				UpdateStdNames();
    void 				AdjustLRSpaceItems();
    static void			PutNumBulletItem( SfxStyleSheetBase* pSheet, Font& rBulletFont );
    Font                GetBulletFont() const;

    SdDrawDocument* 	GetDoc() const { return pDoc; }
};

#endif	   // _SD_STLPOOL_HXX



