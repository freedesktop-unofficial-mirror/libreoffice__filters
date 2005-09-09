/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdfilter.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:02:29 $
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

#ifndef _SD_SDFILTER_HXX
#define _SD_SDFILTER_HXX

// auto strip #include <tools/gen.hxx>
#include <rtl/ustring>

#ifndef _COM_SUN_STAR_FRAME_XMODEL_HPP_
#include <com/sun/star/frame/XModel.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATOR_HPP_
// auto strip #include <com/sun/star/task/XStatusIndicator.hpp>
// auto strip #endif
#ifndef _COM_SUN_STAR_TASK_XSTATUSINDICATORSUPPLIER_HPP_
#include <com/sun/star/task/XStatusIndicatorSupplier.hpp>
#endif
namespace vos { class OModule; }
namespace binfilter {

// ------------
// - SdFilter -
// ------------

class SfxMedium;
class SdDrawDocShell;
class SdDrawDocument;
class SfxProgress;

class SdFilter
{
private:

    ::rtl::OUString				ImplGetFullLibraryName( const ::rtl::OUString& rLibraryName ) const;

protected:

    ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >				mxModel;
    ::com::sun::star::uno::Reference< ::com::sun::star::task::XStatusIndicator >	mxStatusIndicator;

protected:

    SfxMedium&					mrMedium;
    SdDrawDocShell&				mrDocShell;
    SdDrawDocument&				mrDocument;
    SfxProgress*				mpProgress;
    sal_Bool					mbIsDraw : 1;
    sal_Bool					mbShowProgress : 1;

    ::vos::OModule*				OpenLibrary( const ::rtl::OUString& rLibraryName ) const;
    void						CreateStatusIndicator();
    void						CreateProgress();

public:
    
                                SdFilter( SfxMedium& rMedium, SdDrawDocShell& rDocShell, sal_Bool bShowProgress );
                                ~SdFilter();

    virtual sal_Bool			Import();
    virtual sal_Bool			Export();

    sal_Bool					IsProgress() const { return mbShowProgress; }
    sal_Bool					IsDraw() const { return mbIsDraw; }
    sal_Bool					IsImpress() const { return !mbIsDraw; }
};

} //namespace binfilter
#endif // _SD_SDFILTER_HXX
