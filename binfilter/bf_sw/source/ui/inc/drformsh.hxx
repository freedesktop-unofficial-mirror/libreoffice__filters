/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: drformsh.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 05:29:33 $
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

#ifndef _SWDRWFORMSH_HXX
#define _SWDRWFORMSH_HXX

#include "drwbassh.hxx"
namespace binfilter {

class SdrObject;
class SwDrawBaseShell;

class SwDrawFormShell: public SwDrawBaseShell
{
public:
    SFX_DECL_INTERFACE(SW_DRAWFORMSHELL);
//STRIP001 	TYPEINFO();

    SwDrawFormShell(SwView &rView):SwDrawBaseShell(rView){DBG_BF_ASSERT(0, "STRIP");} ;//STRIP001 				SwDrawFormShell(SwView &rView);
//STRIP001 	virtual		~SwDrawFormShell();

//STRIP001 	void		Execute(SfxRequest &);
//STRIP001 	void		GetState(SfxItemSet &);
};

} //namespace binfilter
#endif
