/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: detdata.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:07:11 $
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
