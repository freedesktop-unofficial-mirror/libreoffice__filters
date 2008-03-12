/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svt_jpegc.c,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-03-12 08:43:12 $
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

#include <stdio.h>
#include <stdlib.h>
#include "setjmp.h"
#include "jpeglib.h"
#include "jerror.h"
#include "jpeg.h"

struct my_error_mgr
{
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};

void jpeg_svstream_src (j_decompress_ptr cinfo, void* infile);
void jpeg_svstream_dest (j_compress_ptr cinfo, void* outfile);

METHODDEF( void )
my_error_exit (j_common_ptr cinfo)
{
    my_error_ptr myerr = (my_error_ptr) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}


METHODDEF( void )
my_output_message (j_common_ptr cinfo)
{
    char buffer[JMSG_LENGTH_MAX];
    (*cinfo->err->format_message) (cinfo, buffer);
}

/* TODO: when incompatible changes are possible again
   the preview size hint should be redone */
static int nPreviewWidth = 0;
static int nPreviewHeight = 0;
void SetJpegPreviewSizeHint( int nWidth, int nHeight )
{
    nPreviewWidth = nWidth;
    nPreviewHeight = nHeight;
}

void ReadJPEG( void* pJPEGReader, void* pIStm, long* pLines )
{
    struct jpeg_decompress_struct	cinfo;
    struct my_error_mgr				jerr;
    struct JPEGCreateBitmapParam    aCreateBitmapParam;
    HPBYTE							pDIB;
    HPBYTE							pTmp;
    long                            nWidth;
    long                            nHeight;
    long                            nAlignedWidth;
    // declare bDecompCreated volatile because of gcc
    // warning: variable 'bDecompCreated' might be clobbered by `longjmp' or `vfork'
    volatile long					bDecompCreated = 0;

    /* Falls der Stream nicht ausreicht (IO_PENDING)
     wird ueber ein longjmp in der Schleife nach Exit
     gesprungen, wir geben dann die Anzahl
     der bisher bearbeiteten Scanlines zurueck*/
    if ( setjmp( jerr.setjmp_buffer ) )
        goto Exit;

    cinfo.err = jpeg_std_error( &jerr.pub );
    jerr.pub.error_exit = my_error_exit;
    jerr.pub.output_message = my_output_message;

    jpeg_create_decompress( &cinfo );
    bDecompCreated = 1;
        jpeg_svstream_src( &cinfo, pIStm );
    jpeg_read_header( &cinfo, TRUE );

    cinfo.scale_num = 1;
    cinfo.scale_denom = 1;
    cinfo.output_gamma = 1.0;
    cinfo.raw_data_out = FALSE;
    cinfo.quantize_colors = FALSE;
    if ( cinfo.jpeg_color_space != JCS_GRAYSCALE )
        cinfo.out_color_space = JCS_RGB;

    /* change scale for preview import */
    if( nPreviewWidth || nPreviewHeight )
    {
        if( nPreviewWidth == 0 ) {
            nPreviewWidth = ( cinfo.image_width*nPreviewHeight )/cinfo.image_height;
            if( nPreviewWidth <= 0 )
                nPreviewWidth = 1;
        } else if( nPreviewHeight == 0 ) {
            nPreviewHeight = ( cinfo.image_height*nPreviewWidth )/cinfo.image_width;
            if( nPreviewHeight <= 0 )
                nPreviewHeight = 1;
        }

        for( cinfo.scale_denom = 1; cinfo.scale_denom < 8; cinfo.scale_denom *= 2 )
        {
            if( cinfo.image_width < nPreviewWidth * cinfo.scale_denom )
                break;
            if( cinfo.image_height < nPreviewHeight * cinfo.scale_denom )
                break;
        }

        if( cinfo.scale_denom > 1 )
        {
            cinfo.dct_method            = JDCT_FASTEST;
            cinfo.do_fancy_upsampling   = FALSE;
            cinfo.do_block_smoothing    = FALSE;
        }
    }

    jpeg_start_decompress( &cinfo );

    nWidth = cinfo.output_width;
    nHeight = cinfo.output_height;
    aCreateBitmapParam.nWidth = nWidth;
    aCreateBitmapParam.nHeight = nHeight;

    aCreateBitmapParam.density_unit = cinfo.density_unit;
    aCreateBitmapParam.X_density = cinfo.X_density;
    aCreateBitmapParam.Y_density = cinfo.Y_density;
    aCreateBitmapParam.bGray = cinfo.output_components == 1;
    pDIB = CreateBitmap( pJPEGReader, &aCreateBitmapParam );
    nAlignedWidth = aCreateBitmapParam.nAlignedWidth;
    if( pDIB )
    {
        if( aCreateBitmapParam.bTopDown )
            pTmp = pDIB;
        else
        {
            pTmp = pDIB + ( nHeight - 1 ) * nAlignedWidth;
            nAlignedWidth = -nAlignedWidth;
        }

        for ( *pLines = 0; *pLines < nHeight; (*pLines)++ )
        {
            jpeg_read_scanlines( &cinfo, (JSAMPARRAY) &pTmp, 1 );

            /* PENDING ??? */
            if ( cinfo.err->msg_code == 113 )
                break;

            pTmp += nAlignedWidth;
        }
    }

    jpeg_finish_decompress( &cinfo );

Exit:

    if( bDecompCreated )
        jpeg_destroy_decompress( &cinfo );
}

long WriteJPEG( void* pJPEGWriter, void* pOStm,
                long nWidth, long nHeight,
                long nQualityPercent, void* pCallbackData )
{
    struct jpeg_compress_struct	cinfo;
    struct my_error_mgr			jerr;
    void*						pScanline;
    long						nY;
    // declare bCompCreated, bRet volatile because of gcc
    // warning: variable 'bCompCreated' might be clobbered by `longjmp' or `vfork'
    volatile long				bCompCreated = 0;
    volatile long				bRet = 0;

    if ( setjmp( jerr.setjmp_buffer ) )
        goto Exit;

    cinfo.err = jpeg_std_error( &jerr.pub );
    jerr.pub.error_exit = my_error_exit;
    jerr.pub.output_message = my_output_message;

    jpeg_create_compress( &cinfo );
    bCompCreated = 1;

    jpeg_svstream_dest( &cinfo, pOStm );

    cinfo.image_width = (JDIMENSION) nWidth;
    cinfo.image_height = (JDIMENSION) nHeight;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults( &cinfo );
    jpeg_set_quality( &cinfo, (int) nQualityPercent, FALSE );

    if ( ( nWidth > 128 ) || ( nHeight > 128 ) )
        jpeg_simple_progression( &cinfo );

    jpeg_start_compress( &cinfo, TRUE );

    for( nY = 0; nY < nHeight; nY++ )
    {
        pScanline = GetScanline( pJPEGWriter, nY );

        if( pScanline )
            jpeg_write_scanlines( &cinfo, (JSAMPARRAY) &pScanline, 1 );

        if( JPEGCallback( pCallbackData, nY * 100L / nHeight ) )
            goto Exit;
    }

    bRet = 1;

    jpeg_finish_compress(&cinfo);

Exit:

    if ( bCompCreated )
        jpeg_destroy_compress( &cinfo );

    return bRet;
}

