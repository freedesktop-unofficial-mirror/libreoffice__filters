/*************************************************************************
 *
 *  $RCSfile: streamwrap.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: aidan $ $Date: 2002-04-09 09:03:43 $
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
#ifndef _OSL_FILE_WRAPPER_HXX_
#define _OSL_FILE_WRAPPER_HXX_

#ifndef _OSL_MUTEX_HXX_ //autogen wg. ::osl::Mutex
#include <osl/mutex.hxx>
#endif

#ifndef _COM_SUN_STAR_IO_XOUTPUTSTREAM_HPP_
#include <com/sun/star/io/XOutputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XINPUTSTREAM_HPP_
#include <com/sun/star/io/XInputStream.hpp>
#endif
#ifndef _COM_SUN_STAR_IO_XSEEKABLE_HPP_ 
#include <com/sun/star/io/XSeekable.hpp>
#endif

#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif

#define DECLARE_UNO3_AGG_DEFAULTS(classname, baseclass) \
virtual void            SAL_CALL acquire() throw() { baseclass::acquire(); } \
virtual void            SAL_CALL release() throw() { baseclass::release(); }    \
virtual ::com::sun::star::uno::Any  SAL_CALL queryInterface(const ::com::sun::star::uno::Type& _rType) throw (::com::sun::star::uno::RuntimeException) \
{ return baseclass::queryInterface(_rType); } \
void            SAL_CALL PUT_SEMICOLON_AT_THE_END()

namespace osl
{
    class File;
}

namespace foo
{
    namespace stario	= ::com::sun::star::io;
    namespace staruno	= ::com::sun::star::uno;

//==================================================================
//= OInputFileWrapper
//==================================================================
typedef ::cppu::WeakImplHelper1	<	stario::XInputStream
                                > InputStreamWrapper_Base;
    // needed for some compilers
/// helper class for wrapping a File into an <type scope="com.sun.star.io">XInputStream</type>
class OInputStreamWrapper : public InputStreamWrapper_Base
{
protected:
    ::osl::Mutex	m_aMutex;
    ::osl::File*		m_pSvStream;
    sal_Bool		m_bSvStreamOwner : 1;

public:
    OInputStreamWrapper(::osl::File& _rStream);
    OInputStreamWrapper(::osl::File* pStream, sal_Bool bOwner=sal_False);
    virtual ~OInputStreamWrapper();

// UNO Anbindung
    DECLARE_UNO3_AGG_DEFAULTS(OInputStreamWrapper, InputStreamWrapper_Base);

// stario::XInputStream
    virtual sal_Int32	SAL_CALL	readBytes(staruno::Sequence< sal_Int8 >& aData, sal_Int32 nBytesToRead) throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
    virtual sal_Int32	SAL_CALL	readSomeBytes(staruno::Sequence< sal_Int8 >& aData, sal_Int32 nMaxBytesToRead) throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
    virtual void		SAL_CALL	skipBytes(sal_Int32 nBytesToSkip) throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
    virtual sal_Int32	SAL_CALL	available() throw(stario::NotConnectedException, staruno::RuntimeException);
    virtual void		SAL_CALL	closeInput() throw(stario::NotConnectedException, staruno::RuntimeException);

protected:
    /// throws a NotConnectedException if the object is not connected anymore
    void checkConnected() const;
    /// throws an exception according to the error flag of m_pSvStream
    void checkError() const;
};

//==================================================================
//= OSeekableInputFIleWrapper
//==================================================================
typedef ::cppu::ImplHelper1	<	::com::sun::star::io::XSeekable
                            >	OSeekableInputStreamWrapper_Base;
/** helper class for wrapping an File into an <type scope="com.sun.star.io">XInputStream</type>
    which is seekable (i.e. supports the <type scope="com.sun.star.io">XSeekable</type> interface).
*/
class OSeekableInputStreamWrapper
                :public OInputStreamWrapper
                ,public OSeekableInputStreamWrapper_Base
{
public:
    OSeekableInputStreamWrapper(::osl::File& _rStream);
    OSeekableInputStreamWrapper(::osl::File* _pStream, sal_Bool _bOwner = sal_False);

    // disambiguate XInterface
    virtual ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& _rType ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL acquire(  ) throw ();
    virtual void SAL_CALL release(  ) throw ();

    // XSeekable
    virtual void SAL_CALL seek( sal_Int64 _nLocation ) throw (::com::sun::star::lang::IllegalArgumentException, ::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Int64 SAL_CALL getPosition(  ) throw (::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
    virtual sal_Int64 SAL_CALL getLength(  ) throw (::com::sun::star::io::IOException, ::com::sun::star::uno::RuntimeException);
};

//==================================================================
//= OOutputStreamWrapper
//==================================================================
typedef ::cppu::WeakImplHelper1<stario::XOutputStream> OutputStreamWrapper_Base;
    // needed for some compilers
class OOutputStreamWrapper : public OutputStreamWrapper_Base
{
    ::osl::File&		rStream;

public:
    OOutputStreamWrapper(::osl::File& _rStream) :rStream(_rStream) { }

// UNO Anbindung
    DECLARE_UNO3_AGG_DEFAULTS(OOutputStreamWrapper, OutputStreamWrapper_Base);

// stario::XOutputStream
    virtual void SAL_CALL writeBytes(const staruno::Sequence< sal_Int8 >& aData) throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
    virtual void SAL_CALL flush() throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
    virtual void SAL_CALL closeOutput() throw(stario::NotConnectedException, stario::BufferSizeExceededException, staruno::RuntimeException);
};

}	// namespace utl


#endif // _UTL_STREAM_WRAPPER_HXX_

