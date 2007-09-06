/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sw_portox.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: kz $ $Date: 2007-09-06 12:36:46 $
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


#ifdef _MSC_VER
#pragma hdrstop
#endif


#include "portox.hxx"
namespace binfilter {

/*************************************************************************
 *               virtual SwToxPortion::Paint()
 *************************************************************************/


/*************************************************************************
 *                      class SwIsoToxPortion
 *************************************************************************/

/*N*/ SwLinePortion *SwIsoToxPortion::Compress() { return this; }
/*N*/ 
/*N*/ SwIsoToxPortion::SwIsoToxPortion() : nViewWidth(0)
/*N*/ {
/*N*/ 	SetLen(1);
/*N*/ 	SetWhichPor( POR_ISOTOX );
/*N*/ }

/*************************************************************************
 *				 virtual SwIsoToxPortion::GetViewWidth()
 *************************************************************************/


/*************************************************************************
 *                 virtual SwIsoToxPortion::Format()
 *************************************************************************/

/*N*/ sal_Bool SwIsoToxPortion::Format( SwTxtFormatInfo &rInf )
/*N*/ {
/*N*/ 	const sal_Bool bFull = SwLinePortion::Format( rInf );
/*N*/ 	return bFull;
/*N*/ }

/*************************************************************************
 *               virtual SwIsoToxPortion::Paint()
 *************************************************************************/


/*************************************************************************
 *              virtual SwIsoToxPortion::HandlePortion()
 *************************************************************************/


}
