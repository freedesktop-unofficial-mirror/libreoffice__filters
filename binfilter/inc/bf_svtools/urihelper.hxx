/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: urihelper.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 12:37:37 $
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

#ifndef SVTOOLS_URIHELPER_HXX
#define SVTOOLS_URIHELPER_HXX

#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/uri/XUriReference.hpp>
#include <com/sun/star/uno/RuntimeException.hpp>

#include <rtl/textenc.h>
#include <rtl/ustring.hxx>

#include <unotools/charclass.hxx>
#include <tools/link.hxx>
#include <tools/solar.h>
#include <tools/urlobj.hxx>
#include <tools/string.hxx>


//============================================================================
namespace binfilter
{

/**
   @ATT
   Calling this function with defaulted arguments rMaybeFileHdl = Link() and
   bCheckFileExists = true often leads to results that are not intended:
   Whenever the given rTheBaseURIRef is a file URL, the given rTheRelURIRef is
   relative, and rTheRelURIRef could also be smart-parsed as a non-file URL
   (e.g., the relative URL "foo/bar" can be smart-parsed as "http://foo/bar"),
   then SmartRel2Abs called with rMaybeFileHdl = Link() and bCheckFileExists =
   true returns the non-file URL interpretation.  To avoid this, either pass
   some non-null rMaybeFileHdl if you want to check generated file URLs for
   existence (see GetMaybeFileHdl), or use bCheckFileExists = false
   if you want to generate file URLs without checking for their existence.
*/
 UniString
SmartRel2Abs(INetURLObject const & rTheBaseURIRef,
             ByteString const & rTheRelURIRef,
             Link const & rMaybeFileHdl = Link(),
             bool bCheckFileExists = true,
             bool bIgnoreFragment = false,
             INetURLObject::EncodeMechanism eEncodeMechanism
                 = INetURLObject::WAS_ENCODED,
             INetURLObject::DecodeMechanism eDecodeMechanism
                 = INetURLObject::DECODE_TO_IURI,
             rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
             bool bRelativeNonURIs = false,
             INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

/**
   @ATT
   Calling this function with defaulted arguments rMaybeFileHdl = Link() and
   bCheckFileExists = true often leads to results that are not intended:
   Whenever the given rTheBaseURIRef is a file URL, the given rTheRelURIRef is
   relative, and rTheRelURIRef could also be smart-parsed as a non-file URL
   (e.g., the relative URL "foo/bar" can be smart-parsed as "http://foo/bar"),
   then SmartRel2Abs called with rMaybeFileHdl = Link() and bCheckFileExists =
   true returns the non-file URL interpretation.  To avoid this, either pass
   some non-null rMaybeFileHdl if you want to check generated file URLs for
   existence (see GetMaybeFileHdl), or use bCheckFileExists = false
   if you want to generate file URLs without checking for their existence.
*/
 UniString
SmartRel2Abs(INetURLObject const & rTheBaseURIRef,
             UniString const & rTheRelURIRef,
             Link const & rMaybeFileHdl = Link(),
             bool bCheckFileExists = true,
             bool bIgnoreFragment = false,
             INetURLObject::EncodeMechanism eEncodeMechanism
                 = INetURLObject::WAS_ENCODED,
             INetURLObject::DecodeMechanism eDecodeMechanism
                 = INetURLObject::DECODE_TO_IURI,
             rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
             bool bRelativeNonURIs = false,
             INetURLObject::FSysStyle eStyle = INetURLObject::FSYS_DETECT);

//============================================================================
 void SetMaybeFileHdl(Link const & rTheMaybeFileHdl);

//============================================================================
 Link GetMaybeFileHdl();

/**
   Converts a URI reference to a relative one, ignoring certain differences (for
   example, treating file URLs for case-ignoring file systems
   case-insensitively).

   @param context a component context; must not be null

   @param baseUriReference a base URI reference

   @param uriReference a URI reference

   @return a URI reference representing the given uriReference relative to the
   given baseUriReference; if the given baseUriReference is not an absolute,
   hierarchical URI reference, or the given uriReference is not a valid URI
   reference, null is returned

   @exception std::bad_alloc if an out-of-memory condition occurs

   @exception com::sun::star::uno::RuntimeException if any error occurs
 */
 com::sun::star::uno::Reference< com::sun::star::uri::XUriReference >
normalizedMakeRelative(
    com::sun::star::uno::Reference< com::sun::star::uno::XComponentContext >
    const & context,
    rtl::OUString const & baseUriReference, rtl::OUString const & uriReference);

/**
   A variant of normalizedMakeRelative with a simplified interface.

   Internally calls normalizedMakeRelative with the default component context.

   @param baseUriReference a base URI reference, passed to
   normalizedMakeRelative

   @param uriReference a URI reference, passed to normalizedMakeRelative

   @return if the XUriReference returnd by normalizedMakeRelative is empty,
   uriReference is returned unmodified; otherwise, the result of calling
   XUriReference::getUriReference on the XUriReference returnd by
   normalizedMakeRelative is returned

   @exception std::bad_alloc if an out-of-memory condition occurs

   @exception com::sun::star::uno::RuntimeException if any error occurs

   @deprecated
   No code should rely on the default component context.
*/
 rtl::OUString simpleNormalizedMakeRelative(
    rtl::OUString const & baseUriReference, rtl::OUString const & uriReference);

//============================================================================
 UniString
FindFirstURLInText(UniString const & rText,
                   xub_StrLen & rBegin,
                   xub_StrLen & rEnd,
                   CharClass const & rCharClass,
                   INetURLObject::EncodeMechanism eMechanism
                       = INetURLObject::WAS_ENCODED,
                   rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8,
                   INetURLObject::FSysStyle eStyle
                       = INetURLObject::FSYS_DETECT);

//============================================================================
/** Remove any password component from both absolute and relative URLs.

    @ATT  The current implementation will not remove a password from a
    relative URL that has an authority component (e.g., the password is not
    removed from the relative ftp URL <//user:password@domain/path>).  But
    since our functions to translate between absolute and relative URLs never
    produce relative URLs with authority components, this is no real problem.

    @ATT  For relative URLs (or anything not recognized as an absolute URI),
    the current implementation will return the input unmodified, not applying
    any translations implied by the encode/decode parameters.

    @param rURI  An absolute or relative URI reference.

    @param eEncodeMechanism  See the general discussion for INetURLObject set-
    methods.

    @param eDecodeMechanism  See the general discussion for INetURLObject get-
    methods.

    @param eCharset  See the general discussion for INetURLObject get- and
    set-methods.

    @return  The input URI with any password component removed.
 */
 UniString
removePassword(UniString const & rURI,
               INetURLObject::EncodeMechanism eEncodeMechanism
                   = INetURLObject::WAS_ENCODED,
               INetURLObject::DecodeMechanism eDecodeMechanism
                   = INetURLObject::DECODE_TO_IURI,
               rtl_TextEncoding eCharset = RTL_TEXTENCODING_UTF8);

//============================================================================
/** Query the notational conventions used in the file system provided by some
    file content provider.

    @param rFileUrl  This file URL determines which file content provider is
    used to query the desired information.  (The UCB's usual mapping from URLs
    to content providers is used.)

    @param bAddConvenienceStyles  If true, the return value contains not only
    the style bit corresponding to the queried content provider's conventions,
    but may also contain additional style bits that make using this function
    more convenient in certain situations.  Currently, the effect is that
    FSYS_UNX is extended with FSYS_VOS, and both FSYS_DOS and FSYS_MAC are
    extended with FSYS_VOS and FSYS_UNX (i.e., the---unambiguous---detection
    of VOS style and Unix style file system paths is always enabled); also, in
    case the content provider's conventions cannot be determined, FSYS_DETECT
    is returned instead of FSysStyle(0).

    @return  The style bit corresponding to the queried content provider's
    conventions, or FSysStyle(0) if these cannot be determined.
 */
 INetURLObject::FSysStyle queryFSysStyle(UniString const & rFileUrl,
                                        bool bAddConvenienceStyles = true)
    throw (com::sun::star::uno::RuntimeException);

}

#endif // SVTOOLS_URIHELPER_HXX
