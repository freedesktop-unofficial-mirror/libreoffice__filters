/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: config.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 11:47:14 $
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
#ifndef CONFIG_HXX
#define CONFIG_HXX

#ifndef _SFXBRDCST_HXX //autogen
#include <bf_svtools/brdcst.hxx>
#endif
#ifndef _SFXLSTNER_HXX //autogen
#include <bf_svtools/lstner.hxx>
#endif
#ifndef _SFXCFGITEM_HXX //autogen
#include <bf_sfx2/cfgitem.hxx>
#endif

#ifndef _FORMAT_HXX
#include "format.hxx"
#endif

#include "cfgitem.hxx"
namespace binfilter {

class SfxItemSet; 

class SmPreferenceDialog;
class SmPrintDialog;
class SmPrintOptionDialog;


class SmConfig : public SmMathConfig, public SfxBroadcaster
{
    SmFontPickList	vFontPickList[7];

public:
    SmConfig();
    virtual ~SmConfig();

    SmFontPickList & GetFontPickList(USHORT nIdent) { return vFontPickList[nIdent]; }
    
    void ConfigToItemSet(SfxItemSet &rSet) const;
};

} //namespace binfilter
#endif


