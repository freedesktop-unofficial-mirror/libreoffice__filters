/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hiodev.h,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-20 00:54:06 $
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

/**
 * hwpio.h
 * (C) 1999 Mizi Research, All rights are reserved
 *
 * $Id: hiodev.h,v 1.4 2006-06-20 00:54:06 hr Exp $
 */

#ifndef _HIODEV_H_
#define _HIODEV_H_

#ifdef __GNUG__
#pragma interface
#endif

#include <stdio.h>
#include "hwplib.h"
/**
 * @short Abstract IO class
 */
class DLLEXPORT HIODev
{
    protected:
        bool compressed;
        virtual void init();
    public:
        HIODev();
        virtual ~HIODev();

        virtual bool open() = 0;
        virtual void close() = 0;
        virtual void flush() = 0;
        virtual int  state() const = 0;
/* gzip routine wrapper */
        virtual bool setCompressed( bool ) = 0;

        virtual int read1b() = 0;
        virtual int read2b() = 0;
        virtual long read4b() = 0;
        virtual int readBlock( void *ptr, int size ) = 0;
        virtual int skipBlock( int size ) = 0;

        virtual int read1b( void *ptr, int nmemb );
        virtual int read2b( void *ptr, int nmemb );
        virtual int read4b( void *ptr, int nmemb );
};

struct gz_stream;

/* ���� ����� ��ġ */

/**
 * This controls the HStream given by constructor
 * @short Stream IO device
 */
class HStreamIODev : public HIODev
{
    private:
/* zlib���� ������ Ǯ�� ���� �ڷ� ���� */
        gz_stream *_gzfp;
        HStream& _stream;
    public:
        HStreamIODev(HStream& stream);
        virtual ~HStreamIODev();
/**
 * Check whether the stream is available
 */
        virtual bool open();
/**
 * Free stream object
 */
        virtual void close();
/**
 * If the stream is gzipped, flush the stream.
 */
        virtual void flush();
/**
 * Not implemented.
 */
        virtual int  state() const;
/**
 * Set whether the stream is compressed or not
 */
        virtual bool setCompressed( bool );
/**
 * Read one byte from stream
 */
        using HIODev::read1b;
        virtual int read1b();
/**
 * Read 2 bytes from stream
 */
        using HIODev::read2b;
        virtual int read2b();
/**
 * Read 4 bytes from stream
 */
        using HIODev::read4b;
        virtual long read4b();
/**
 * Read some bytes from stream to given pointer as amount of size
 */
        virtual int readBlock( void *ptr, int size );
/**
 * Move current pointer of stream as amount of size
 */
        virtual int skipBlock( int size );
    protected:
/**
 * Initialize this object
 */
        virtual void init();
};

/* �޸� ����� ��ġ */
/**
 * The HMemIODev class controls the Input/Output device.
 * @short Memory IO device
 */
class HMemIODev : public HIODev
{
    uchar *ptr;
    int pos, length;
    public:
        HMemIODev(char *s, int len);
        virtual ~HMemIODev();

        virtual bool open();
        virtual void close();
        virtual void flush();
        virtual int  state() const;
/* gzip routine wrapper */
        virtual bool setCompressed( bool );
        using HIODev::read1b;
        virtual int read1b();
        using HIODev::read2b;
        virtual int read2b();
        using HIODev::read4b;
        virtual long read4b();
        virtual int readBlock( void *ptr, int size );
        virtual int skipBlock( int size );
    protected:
        virtual void init();
};
#endif                                            /* _HIODEV_H_*/
