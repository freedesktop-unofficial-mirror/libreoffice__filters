/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sharedstringsfragment.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:05:49 $
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

#ifndef OOX_XLS_SHAREDSTRINGSFRAGMENT_HXX
#define OOX_XLS_SHAREDSTRINGSFRAGMENT_HXX

#include "oox/xls/ooxfragmenthandler.hxx"

namespace oox {
namespace xls {

// ============================================================================

class OoxSharedStringsFragment : public OoxWorkbookFragmentBase
{
public:
    explicit            OoxSharedStringsFragment(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath );

protected:
    // oox.xls.OoxContextHelper interface -------------------------------------

    virtual bool        onCanCreateContext( sal_Int32 nElement ) const;
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler >
                        onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

    virtual bool        onCanCreateRecordContext( sal_Int32 nRecId );
    virtual void        onStartRecord( RecordInputStream& rStrm );

    // oox.xls.OoxFragmentHandler interface -----------------------------------

    virtual void        finalizeImport();
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif

