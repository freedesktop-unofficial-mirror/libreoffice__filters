/*************************************************************************
 *
 *  $RCSfile: cusshow.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2004-08-03 20:53:57 $
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

#ifndef _SD_CUSSHOW_HXX
#define _SD_CUSSHOW_HXX

// auto strip #ifndef _LIST_HXX //autogen
// auto strip #include <tools/list.hxx>
// auto strip #endif

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

// auto strip #ifndef _STRING_HXX //autogen
// auto strip #include <tools/string.hxx>
// auto strip #endif

#ifndef _CPPUHELPER_WEAKREF_HXX_
#include <cppuhelper/weakref.hxx>
#endif
namespace binfilter {

class SdDrawDocument;

/*************************************************************************
|*
|* CustomShow
|*
\************************************************************************/
class SdCustomShow : public List
{
private:
    String          aName;
    SdDrawDocument* pDoc;

    // this is a weak reference to a possible living api wrapper for this custom show
    ::com::sun::star::uno::WeakReference< ::com::sun::star::uno::XInterface > mxUnoCustomShow;

public:
    SdCustomShow(SdDrawDocument* pDrawDoc);
    SdCustomShow(SdDrawDocument* pDrawDoc, ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > xShow );

    SdCustomShow( const SdCustomShow& rShow );
    virtual ~SdCustomShow();

    void   SetName(const String& rName) { aName = rName; }
    String GetName() const              { return aName; }

    SdDrawDocument* GetDoc() const { return pDoc; }

    friend SvStream& operator << (SvStream& rOut, const SdCustomShow& rCustomShow);
    friend SvStream& operator >> (SvStream& rIn, SdCustomShow& rCustomShow);

    ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > getUnoCustomShow();
};

} //namespace binfilter
#endif      // _SD_CUSSHOW_HXX

