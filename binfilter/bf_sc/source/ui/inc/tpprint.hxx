/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: tpprint.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 20:23:14 $
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

#ifndef SC_TPPRINT_HXX
#define SC_TPPRINT_HXX

// auto strip #ifndef _SFXTABDLG_HXX 
// auto strip #include <bf_sfx2/tabdlg.hxx>
// auto strip #endif

// auto strip #ifndef _SV_FIXED_HXX 
// auto strip #include <vcl/fixed.hxx>
// auto strip #endif
namespace binfilter {

//===================================================================

//STRIP001 class ScTpPrintOptions : public SfxTabPage
//STRIP001 {
//STRIP001 	FixedLine		aPagesFL;
//STRIP001 	CheckBox		aSkipEmptyPagesCB;
//STRIP001 	FixedLine		aSheetsFL;
//STRIP001 	CheckBox		aSelectedSheetsCB;
//STRIP001 
//STRIP001 			ScTpPrintOptions( Window* pParent, const SfxItemSet& rCoreSet );
//STRIP001 			~ScTpPrintOptions();
//STRIP001 
//STRIP001 public:
//STRIP001 	static SfxTabPage*	Create( Window* pParent, const SfxItemSet& rCoreSet );
//STRIP001 	static USHORT*		GetRanges();
//STRIP001 	virtual BOOL		FillItemSet( SfxItemSet& rCoreSet );
//STRIP001 	virtual void		Reset( const SfxItemSet& rCoreSet );
//STRIP001 	virtual int 		DeactivatePage( SfxItemSet* pSet = NULL );
//STRIP001 };

} //namespace binfilter
#endif

