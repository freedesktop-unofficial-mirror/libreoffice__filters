/*************************************************************************
 *
 *  $RCSfile: sch_axisobj.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aw $ $Date: 2003-10-02 14:55:35 $
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

// header for SdrObjListIter
#ifndef _SVDITER_HXX
#include <bf_svx/svditer.hxx>
#endif
// header for SdrHdlList
#ifndef _SVDHDL_HXX
#include <bf_svx/svdhdl.hxx>
#endif

#include "axisobj.hxx"

// ==================== SchAxisObj ====================

/*N*/ TYPEINIT1( SchAxisObj, SchObjGroup );

/*N*/ SchAxisObj::SchAxisObj( ChartModel *pModel ) :
/*N*/ 		SchObjGroup( pModel )
/*N*/ {
/*N*/ }

//STRIP001 void SchAxisObj::AddToHdlList( SdrHdlList& rHdlList ) const
//STRIP001 {
//STRIP001 	// don't use method overloaded by Schgroup
//STRIP001 	SdrObject::AddToHdlList( rHdlList );
//STRIP001 }

//STRIP001 USHORT SchAxisObj::GetHdlCount() const
//STRIP001 {
//STRIP001 	// there are just two handles: the start and end of the main axis line
//STRIP001 	return GetSubList()? 2: 0;
//STRIP001 }

//STRIP001 SdrHdl* SchAxisObj::GetHdl( USHORT nHdlNum ) const
//STRIP001 {
//STRIP001 	// return the handles of the first line in the axis group
//STRIP001 	SdrObjList* pList = GetSubList();
//STRIP001 	if( pList )
//STRIP001 	{
//STRIP001 		SdrObjListIter aListIter( *this );
//STRIP001 		if( aListIter.IsMore() )
//STRIP001 		{
//STRIP001 			return aListIter.Next()->GetHdl( nHdlNum );
//STRIP001 		}
//STRIP001 	}
//STRIP001 
//STRIP001 	return NULL;
//STRIP001 }

// ==================== Sch3dAxisObj ====================

/*N*/ TYPEINIT1( Sch3dAxisObj, SchE3dObject );

/*N*/ Sch3dAxisObj::Sch3dAxisObj()
/*N*/ 		: SchE3dObject()
/*N*/ {
/*N*/ }

//STRIP001 void Sch3dAxisObj::AddToHdlList( SdrHdlList& rHdlList ) const
//STRIP001 {
//STRIP001 	SdrObjList* pList = GetSubList();
//STRIP001 	if( pList &&
//STRIP001 		pList->GetObjCount() )
//STRIP001 	{
//STRIP001 		pList->GetObj( 0 )->AddToHdlList( rHdlList );
//STRIP001 	}
//STRIP001 	else
//STRIP001 		E3dObject::AddToHdlList( rHdlList );
//STRIP001 }

