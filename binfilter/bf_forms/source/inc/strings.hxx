/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: strings.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:54:07 $
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

#ifndef _FRM_STRINGS_HXX_
#define _FRM_STRINGS_HXX_

namespace binfilter {
//.........................................................................
namespace frm
{
//.........................................................................

struct ConstAsciiString
{
    const sal_Char*	ascii;
    sal_Int32		length;

    inline	operator const ::rtl::OUString () const;
    inline	operator const sal_Char* () const { return ascii; }

    inline ConstAsciiString(const sal_Char* _pAsciiZeroTerminated, const sal_Int32 _nLength);
    inline ~ConstAsciiString();

private:
    mutable ::rtl::OUString*	ustring;
};

//------------------------------------------------------------
inline ConstAsciiString::ConstAsciiString(const sal_Char* _pAsciiZeroTerminated, const sal_Int32 _nLength)
    :ascii(_pAsciiZeroTerminated)
    ,length(_nLength)
    ,ustring(NULL)
{
}

//------------------------------------------------------------
inline ConstAsciiString::~ConstAsciiString()
{
    delete ustring;
    ustring = NULL;
}

//------------------------------------------------------------
inline ConstAsciiString::operator const ::rtl::OUString () const
{
    if (!ustring)
        ustring = new ::rtl::OUString(ascii, length, RTL_TEXTENCODING_ASCII_US);
    return *ustring;
}

#define DECLARE_CONSTASCII_USTRING(name)	\
    extern ::binfilter::frm::ConstAsciiString name

#define IMPLEMENT_CONSTASCII_USTRING(name, asciivalue)	\
    ::binfilter::frm::ConstAsciiString name(asciivalue, sizeof(asciivalue) - 1)

//#define DECLARE_CONSTASCII_USTRING(name)					extern ::rtl::OUString name;
//#define IMPLEMENT_CONSTASCII_USTRING(name, asciivalue)	::rtl::OUString name = ::rtl::OUString::createFromAscii(asciivalue)

//.........................................................................
}	// namespace frm
//.........................................................................

}//end of namespace binfilter
#endif _FRM_STRINGS_HXX_

