/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: rubylist.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 16:22:33 $
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
#ifndef _RUBYLIST_HXX
#define _RUBYLIST_HXX

// auto strip #ifndef _SVARRAY_HXX
// auto strip #include <svtools/svarray.hxx>
// auto strip #endif

#ifndef _SWTYPES_HXX
#include <swtypes.hxx>
#endif
#ifndef _FMTRUBY_HXX
#include <fmtruby.hxx>
#endif
namespace binfilter {

class SwRubyListEntry
{
    String sText;
    SwFmtRuby aRubyAttr;
public:
    SwRubyListEntry() : aRubyAttr( aEmptyStr ) {}
    ~SwRubyListEntry();

    const String& GetText() const 				{ return sText; }
    void SetText( const String& rStr ) 			{ sText = rStr; }

    const SwFmtRuby& GetRubyAttr() const		{ return aRubyAttr; }
           SwFmtRuby& GetRubyAttr() 				{ return aRubyAttr; }
     void SetRubyAttr( const SwFmtRuby& rAttr )	{ aRubyAttr = rAttr; }
};

typedef SwRubyListEntry* SwRubyListEntryPtr;
SV_DECL_PTRARR_DEL( SwRubyList, SwRubyListEntryPtr, 0, 32 )


} //namespace binfilter
#endif	//_RUBYLIST_HXX
