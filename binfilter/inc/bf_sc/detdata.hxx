/*************************************************************************
 *
 *  $RCSfile: detdata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: er $ $Date: 2004-03-25 14:46:23 $
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

#ifndef SC_DETDATA_HXX
#define SC_DETDATA_HXX

#ifndef _SVARRAY_HXX //autogen
#include <svtools/svarray.hxx>
#endif

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
namespace binfilter {


//------------------------------------------------------------------------

#define SC_DETOP_GROW	4

//------------------------------------------------------------------------
enum ScDetOpType
{
    SCDETOP_ADDSUCC,
    SCDETOP_DELSUCC,
    SCDETOP_ADDPRED,
    SCDETOP_DELPRED,
    SCDETOP_ADDERROR
};

//------------------------------------------------------------------------

class ScDetOpData
{
    ScAddress		aPos;
    ScDetOpType		eOperation;

public:
                        ScDetOpData( const ScAddress& rP, ScDetOpType eOp ) :
                            aPos(rP), eOperation(eOp) {}

                        ScDetOpData( const ScDetOpData& rData ) :
                            aPos(rData.aPos), eOperation(rData.eOperation) {}

    const ScAddress&	GetPos() const			{ return aPos; }
    ScDetOpType			GetOperation() const	{ return eOperation; }

    // fuer UpdateRef:
    void				SetPos(const ScAddress& rNew)	{ aPos=rNew; }

    int operator==		( const ScDetOpData& r ) const
                            { return eOperation == r.eOperation && aPos == r.aPos; }
};

//------------------------------------------------------------------------

//
//	Liste der Operationen
//

typedef ScDetOpData* ScDetOpDataPtr;

SV_DECL_PTRARR_DEL(ScDetOpArr_Impl, ScDetOpDataPtr, SC_DETOP_GROW, SC_DETOP_GROW)//STRIP008 ;

class ScDetOpList : public ScDetOpArr_Impl
{
    BOOL	bHasAddError;		// updated in Append

public:
        ScDetOpList() : bHasAddError(FALSE) {}
        ScDetOpList(const ScDetOpList& rList);
        ~ScDetOpList() {}

/*N*/ 	void	UpdateReference( ScDocument* pDoc, UpdateRefMode eUpdateRefMode,
/*N*/ 								const ScRange& rRange, short nDx, short nDy, short nDz );

//STRIP001 	BOOL	operator==( const ScDetOpList& r ) const;		// fuer Ref-Undo

    void	Append( ScDetOpData* pData );

    void	Load( SvStream& rStream );
    void	Store( SvStream& rStream ) const;

    BOOL	HasAddError() const		{ return bHasAddError; }
};



} //namespace binfilter
#endif
