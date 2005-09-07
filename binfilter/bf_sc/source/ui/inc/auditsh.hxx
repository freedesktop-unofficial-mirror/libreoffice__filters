/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: auditsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:33:32 $
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

#ifndef SC_AUDITSH_HXX
#define SC_AUDITSH_HXX

#ifndef _SFX_SHELL_HXX //autogen
#include <bf_sfx2/shell.hxx>
#endif
#ifndef _SFXMODULE_HXX //autogen
#include <bf_sfx2/module.hxx>
#endif

#include "shellids.hxx"
namespace binfilter {

class ScViewData;

class ScAuditingShell : public SfxShell
{
//STRIP001 private:
//STRIP001 	ScViewData*	pViewData;
//STRIP001 	USHORT		nFunction;

public:
//STRIP001 	TYPEINFO();
    SFX_DECL_INTERFACE(SCID_AUDITING_SHELL);

    ScAuditingShell(ScViewData* pData);
//STRIP001 					~ScAuditingShell();

    void	Execute(SfxRequest& rReq){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 void	Execute(SfxRequest& rReq);
    void	GetState(SfxItemSet& rSet){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	void	GetState(SfxItemSet& rSet);
};



} //namespace binfilter
#endif


