/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ParseContext.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:59:50 $
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
#ifndef SVX_QUERYDESIGNCONTEXT_HXX
#define SVX_QUERYDESIGNCONTEXT_HXX

#ifndef CONNECTIVITY_IPARSECONTEXT_HXX
#include <connectivity/IParseContext.hxx>
#endif

// auto strip #ifndef _STRING_HXX
// auto strip #include <tools/string.hxx>
// auto strip #endif
#ifndef _UNOTOOLS_LOCALEDATAWRAPPER_HXX 
#include <unotools/localedatawrapper.hxx>
#endif
namespace binfilter {

namespace svxform
{
    //==========================================================================
    //= OSystemParseContext
    //==========================================================================
    class OSystemParseContext : public ::connectivity::IParseContext
    {
    private:
        ByteString m_aSQLInternationals;

    public:
        OSystemParseContext();

        virtual ~OSystemParseContext();
        // retrieves language specific error messages
        virtual ::rtl::OUString getErrorMessage(ErrorCode _eCodes) const;

        // retrieves language specific keyword strings (only ASCII allowed)
        virtual ::rtl::OString getIntlKeywordAscii(InternationalKeyCode _eKey) const;

        // finds out, if we have an international keyword (only ASCII allowed)
        virtual InternationalKeyCode getIntlKeyCode(const ::rtl::OString& rToken) const;

        /** get's a locale instance which should be used when parsing in the context specified by this instance
            <p>if this is not overridden by derived classes, it returns the static default locale.</p>
        */
        virtual ::com::sun::star::lang::Locale getPreferredLocale( ) const;

    public:
        // helper methods to ease access to some of the characteristics of the locale
        sal_Unicode getNumDecimalSep( ) const;
        sal_Unicode getNumThousandSep( ) const;
    };

    //==========================================================================
    //= OParseContextClient
    //==========================================================================
    /** helper class which needs access to a (shared and ref-counted) OSystemParseContext
        instance.
    */
    class OParseContextClient
    {
    protected:
        OParseContextClient();
        virtual ~OParseContextClient();

        const OSystemParseContext* getParseContext() const;
    };
}
}//end of namespace binfilter
#endif // SVX_QUERYDESIGNCONTEXT_HXX

