/*************************************************************************
 *
 *  $RCSfile: tphf.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 07:30:13 $
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

#ifndef SC_TPHF_HXX
#define SC_TPHF_HXX


#ifndef _SVX_HDFT_HXX //autogen
#include <bf_svx/hdft2.hxx>
#endif
namespace binfilter {

class ScStyleDlg;

//========================================================================

class ScHFPage : public SvxHFPage
{
public:
    virtual			~ScHFPage();

    virtual void	Reset( const SfxItemSet& rSet );
    virtual BOOL 	FillItemSet( SfxItemSet& rOutSet );

    void			SetPageStyle( const String& rName )    { aStrPageStyle = rName; }
    void			SetStyleDlg ( const ScStyleDlg* pDlg ) { pStyleDlg = pDlg; }

protected:
                    ScHFPage( Window* pParent,
                              USHORT nResId,
                              const SfxItemSet& rSet,
                              USHORT nSetId );

    virtual void	ActivatePage( const SfxItemSet& rSet );
    virtual int		DeactivatePage( SfxItemSet* pSet = 0 );

private:
    PushButton			aBtnEdit;
    SfxItemSet			aDataSet;
    String				aStrPageStyle;
    USHORT				nPageUsage;
    const ScStyleDlg*	pStyleDlg;

#ifdef _TPHF_CXX
private:
    DECL_LINK( BtnHdl, PushButton* );
    DECL_LINK( HFEditHdl, void* );
    DECL_LINK( TurnOnHdl, CheckBox* );
#endif
};

//========================================================================

class ScHeaderPage : public ScHFPage
{
public:
    static SfxTabPage* 	Create(	Window* pParent, const SfxItemSet& rSet );
    static USHORT*		GetRanges();

private:
    ScHeaderPage( Window* pParent, const SfxItemSet& rSet );
};

//========================================================================

class ScFooterPage : public ScHFPage
{
public:
    static SfxTabPage* 	Create(	Window* pParent, const SfxItemSet& rSet );
    static USHORT*		GetRanges();

private:
    ScFooterPage( Window* pParent, const SfxItemSet& rSet );
};


} //namespace binfilter
#endif // SC_TPHF_HXX

