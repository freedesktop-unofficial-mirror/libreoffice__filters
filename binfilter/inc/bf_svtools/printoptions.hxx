/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: printoptions.hxx,v $
 * $Revision: 1.3 $
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef INCLUDED_SVTOOLS_PRINTOPTIONS_HXX
#define INCLUDED_SVTOOLS_PRINTOPTIONS_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif
#ifndef _OSL_MUTEX_HXX_
#include <osl/mutex.hxx>
#endif
#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef INCLUDED_SVTOOLS_OPTIONS_HXX
#include <bf_svtools/options.hxx>
#endif

class PrinterOptions;

namespace binfilter
{

class SvtPrintOptions_Impl;

// -----------------------
// - SvtBasePrintOptions -
// -----------------------

class  SvtBasePrintOptions: public Options
{
protected:

    SvtPrintOptions_Impl* m_pDataContainer;

    void        SetDataContainer( SvtPrintOptions_Impl* pDataContainer ) { m_pDataContainer = pDataContainer; }

public:

    static ::osl::Mutex& GetOwnStaticMutex();

public:

                SvtBasePrintOptions();
                virtual ~SvtBasePrintOptions();

    sal_Bool	IsReduceTransparency() const;
    sal_Int16   GetReducedTransparencyMode() const;
    sal_Bool	IsReduceGradients() const;
    sal_Int16   GetReducedGradientMode() const;
    sal_Int16   GetReducedGradientStepCount() const;
    sal_Bool	IsReduceBitmaps() const;
    sal_Int16   GetReducedBitmapMode() const;
    sal_Int16   GetReducedBitmapResolution() const;
    sal_Bool	IsReducedBitmapIncludesTransparency() const;
       sal_Bool	IsConvertToGreyscales() const;

    void        SetReduceTransparency( sal_Bool	bState );
    void        SetReducedTransparencyMode( sal_Int16 nMode );
    void        SetReduceGradients( sal_Bool bState );
    void        SetReducedGradientMode( sal_Int16 nMode );
    void        SetReducedGradientStepCount( sal_Int16 nStepCount );
    void        SetReduceBitmaps( sal_Bool bState );
    void        SetReducedBitmapMode( sal_Int16   bState );
    void        SetReducedBitmapResolution( sal_Int16 nResolution );
    void        SetReducedBitmapIncludesTransparency( sal_Bool bState );
       void        SetConvertToGreyscales( sal_Bool bState );

public:

    void        GetPrinterOptions( PrinterOptions& rOptions ) const;
    void        SetPrinterOptions( const PrinterOptions& rOptions );
};

// ---------------------
// - SvtPrinterOptions -
// ---------------------

class  SvtPrinterOptions : public SvtBasePrintOptions
{
private:

    static SvtPrintOptions_Impl*    m_pStaticDataContainer;	/// impl. data container as dynamic pointer for smaller memory requirements!
    static sal_Int32			    m_nRefCount;	        /// internal ref count mechanism

public:

    SvtPrinterOptions();
    virtual ~SvtPrinterOptions();
};

// -----------------------
// - SvtPrintFileOptions -
// -----------------------

class  SvtPrintFileOptions : public SvtBasePrintOptions
{
private:

    static SvtPrintOptions_Impl*    m_pStaticDataContainer;	/// impl. data container as dynamic pointer for smaller memory requirements!
    static sal_Int32			    m_nRefCount;	        /// internal ref count mechanism

public:

    SvtPrintFileOptions();
    virtual ~SvtPrintFileOptions();
};

}

#endif // INCLUDED_SVTOOLS_PRINTOPTIONS_HXX
