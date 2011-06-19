/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#include "oox/helper/binaryoutputstream.hxx"

#include <com/sun/star/io/XOutputStream.hpp>
#include <com/sun/star/io/XSeekable.hpp>
#include <osl/diagnose.h>
#include <string.h>

namespace oox {

// ============================================================================

using namespace ::com::sun::star::io;
using namespace ::com::sun::star::uno;

namespace {

const sal_Int32 OUTPUTSTREAM_BUFFERSIZE     = 0x8000;

} // namespace

// ============================================================================

BinaryXOutputStream::BinaryXOutputStream( const Reference< XOutputStream >& rxOutStrm, bool bAutoClose ) :
    BinaryStreamBase( Reference< XSeekable >( rxOutStrm, UNO_QUERY ).is() ),
    BinaryXSeekableStream( Reference< XSeekable >( rxOutStrm, UNO_QUERY ) ),
    maBuffer( OUTPUTSTREAM_BUFFERSIZE ),
    mxOutStrm( rxOutStrm ),
    mbAutoClose( bAutoClose && rxOutStrm.is() )
{
    mbEof = !mxOutStrm.is();
}

BinaryXOutputStream::~BinaryXOutputStream()
{
    close();
}

void BinaryXOutputStream::close()
{
    OSL_ENSURE( !mbAutoClose || mxOutStrm.is(), "BinaryXOutputStream::close - invalid call" );
    if( mxOutStrm.is() ) try
    {
        mxOutStrm->flush();
        mxOutStrm->closeOutput();
    }
    catch( Exception& )
    {
        OSL_FAIL( "BinaryXOutputStream::close - closing output stream failed" );
    }
    mxOutStrm.clear();
    mbAutoClose = false;
    BinaryXSeekableStream::close();
}

void BinaryXOutputStream::writeData( const StreamDataSequence& rData, size_t /*nAtomSize*/ )
{
    if( mxOutStrm.is() ) try
    {
        mxOutStrm->writeBytes( rData );
    }
    catch( Exception& )
    {
        OSL_FAIL( "BinaryXOutputStream::writeData - stream read error" );
    }
}

void BinaryXOutputStream::writeMemory( const void* pMem, sal_Int32 nBytes, size_t nAtomSize )
{
    if( mxOutStrm.is() && (nBytes > 0) )
    {
        sal_Int32 nBufferSize = getLimitedValue< sal_Int32, sal_Int32 >( nBytes, 0, (OUTPUTSTREAM_BUFFERSIZE / nAtomSize) * nAtomSize );
        const sal_uInt8* pnMem = reinterpret_cast< const sal_uInt8* >( pMem );
        while( nBytes > 0 )
        {
            sal_Int32 nWriteSize = getLimitedValue< sal_Int32, sal_Int32 >( nBytes, 0, nBufferSize );
            maBuffer.realloc( nWriteSize );
            memcpy( maBuffer.getArray(), pnMem, static_cast< size_t >( nWriteSize ) );
            writeData( maBuffer, nAtomSize );
            pnMem += nWriteSize;
            nBytes -= nWriteSize;
        }
    }
}

// ============================================================================

SequenceOutputStream::SequenceOutputStream( StreamDataSequence& rData ) :
    BinaryStreamBase( true ),
    SequenceSeekableStream( rData )
{
}

void SequenceOutputStream::writeData( const StreamDataSequence& rData, size_t nAtomSize )
{
    if( mpData && rData.hasElements() )
        writeMemory( rData.getConstArray(), rData.getLength(), nAtomSize );
}

void SequenceOutputStream::writeMemory( const void* pMem, sal_Int32 nBytes, size_t /*nAtomSize*/ )
{
    if( mpData && (nBytes > 0) )
    {
        if( mpData->getLength() - mnPos < nBytes )
            const_cast< StreamDataSequence* >( mpData )->realloc( mnPos + nBytes );
        memcpy( const_cast< StreamDataSequence* >( mpData )->getArray() + mnPos, pMem, static_cast< size_t >( nBytes ) );
        mnPos += nBytes;
    }
}

// ============================================================================

} // namespace oox

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
