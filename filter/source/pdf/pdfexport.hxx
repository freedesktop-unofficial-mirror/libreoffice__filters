/*************************************************************************
 *
 *  $RCSfile: pdfexport.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: vg $ $Date: 2005-03-08 13:34:11 $
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

#ifndef PDFEXPORT_HXX
#define PDFEXPORT_HXX

#include "pdffilter.hxx"
#include <tools/multisel.hxx>
#include <vcl/pdfwriter.hxx>
#include <vcl/pdfextoutdevdata.hxx>
#ifndef _COM_SUN_STAR_VIEW_XRENDERABLE_HPP_
#include <com/sun/star/view/XRenderable.hpp>
#endif

class SvEmbeddedObject;
class GDIMetaFile;
class VirtualDevice;
class PolyPolygon;
class Gradient;
class BitmapEx;
class Point;
class Size;

namespace vcl {	class PDFWriter; }

// -------------
// - PDFExport -
// -------------

class PDFExport
{
private:

    Reference< XComponent >	mxSrcDoc;
    Reference< task::XStatusIndicator > mxStatusIndicator;

    sal_Bool				mbUseTaggedPDF;
    sal_Bool				mbExportNotes;
    sal_Bool				mbExportNotesPages;
    sal_Bool				mbUseTransitionEffects;

    sal_Bool				mbUseLosslessCompression;
    sal_Bool				mbReduceImageResolution;
    sal_Bool                mbSkipEmptyPages;
    sal_Int32				mnMaxImageResolution;
    sal_Int32				mnQuality;
    sal_Int32				mnFormsFormat;
    sal_Int32				mnProgressValue;

    sal_Bool                ImplExportPage( ::vcl::PDFWriter& rWriter, ::vcl::PDFExtOutDevData& rPDFExtOutDevData,
                                                const GDIMetaFile& rMtf );
    sal_Bool                ImplWriteActions( ::vcl::PDFWriter& rWriter, ::vcl::PDFExtOutDevData* pPDFExtOutDevData,
                                                const GDIMetaFile& rMtf, VirtualDevice& rDummyVDev );
    void                    ImplWriteGradient( ::vcl::PDFWriter& rWriter, const PolyPolygon& rPolyPoly,
                                                const Gradient& rGradient, VirtualDevice& rDummyVDev );
    void					ImplWriteBitmapEx( ::vcl::PDFWriter& rWriter, VirtualDevice& rDummyVDev,
                                                const Point& rPoint, const Size& rSize, const BitmapEx& rBitmap );

public:

                            PDFExport( const Reference< XComponent >& rxSrcDoc, Reference< task::XStatusIndicator >& xStatusIndicator );
                            ~PDFExport();

    sal_Bool                ExportSelection( vcl::PDFWriter& rPDFWriter, Reference< com::sun::star::view::XRenderable >& rRenderable, Any& rSelection,
                                MultiSelection aMultiSelection, Sequence< PropertyValue >& rRenderOptions );

    sal_Bool                Export( const OUString& rFile, const Sequence< PropertyValue >& rFilterData );
};

#endif
