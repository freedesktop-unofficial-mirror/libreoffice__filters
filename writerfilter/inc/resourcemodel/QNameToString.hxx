/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: QNameToString.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hbrinkm $ $Date: 2007-04-16 09:00:24 $
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
#ifndef INCLUDED_QNAME_TO_STRING_HXX
#define INCLUDED_QNAME_TO_STRING_HXX

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <odiapi/qname/QName.hxx>

namespace writerfilter
{
using namespace ::std;

class WRITERFILTER_DLLPUBLIC QNameToString
{
    typedef boost::shared_ptr<QNameToString> Pointer_t;

    static Pointer_t pInstance;

    map < writerfilter::QName_t, string > mMap;

protected:
    /**
       Generated.
     */
    QNameToString();

public:
    static Pointer_t Instance();

    string operator()(writerfilter::QName_t qName);
};

class SprmIdToString
{
    typedef boost::shared_ptr<SprmIdToString> Pointer_t;

    static Pointer_t pInstance;

    map<sal_uInt32, string> mMap;

protected:
    /**
       Generated automatically.
    */
    SprmIdToString();

public:
    static Pointer_t Instance();
    string operator()(sal_uInt32 nId);
};

}

#endif // INCLUDED_QNAME_TO_STRING_HXX
