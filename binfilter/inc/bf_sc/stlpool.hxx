/*************************************************************************
 *
 *  $RCSfile: stlpool.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:03 $
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

#ifndef SC_STLPOOL_HXX
#define SC_STLPOOL_HXX

#ifndef _SFXSTYLE_HXX //autogen
#include <svtools/style.hxx>
#endif
namespace binfilter {


class ScStyleSheet;
class ScDocument;

class ScStyleSheetPool : public ::SfxStyleSheetPool
{
public:
                        ScStyleSheetPool( SfxItemPool&	rPool,
                                          ScDocument*	pDocument );
    virtual 			~ScStyleSheetPool();

    void				SetDocument( ScDocument* pDocument );
    ScDocument*			GetDocument() const { return pDoc; }

//STRIP001 	virtual void		Erase( ::SfxStyleSheetBase* pStyle );

    void				SetActualStyleSheet ( ::SfxStyleSheetBase* pActStyleSheet )
                                { pActualStyleSheet = pActStyleSheet; }

    ::SfxStyleSheetBase*	GetActualStyleSheet ()
                                { return pActualStyleSheet; }

    void				CreateStandardStyles();
//STRIP001 	void				CopyStdStylesFrom( ScStyleSheetPool* pSrcPool );
    void				UpdateStdNames();

//STRIP001 	void				CopyStyleFrom( ScStyleSheetPool* pSrcPool,
//STRIP001 										const String& rName, SfxStyleFamily eFamily );

//STRIP001 	ScStyleSheet*		FindCaseIns( const String& rName, SfxStyleFamily eFam );

    void				SetForceStdName( const String* pSet );
    const String*		GetForceStdName() const	{ return pForceStdName; }

    virtual ::SfxStyleSheetBase& Make( const String&, SfxStyleFamily eFam,
                                     USHORT nMask = 0xffff, USHORT nPos = 0xffff );

    void                ConvertFontsAfterLoad();     // old binary file format

protected:
    virtual ::SfxStyleSheetBase* Create( const String&	rName,
                                       SfxStyleFamily	eFamily,
                                       USHORT			nMask);
    virtual ::SfxStyleSheetBase* Create( const SfxStyleSheetBase& rStyle );

private:
    ::SfxStyleSheetBase*	pActualStyleSheet;
    ScDocument*			pDoc;
    const String*		pForceStdName;
};

} //namespace binfilter
#endif	   // SC_STLPOOL_HXX

