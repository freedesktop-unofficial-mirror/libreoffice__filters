#ifndef WPXSVSTREAM_H
#define WPXSVSTREAM_H

#include <sot/storage.hxx>
#include <com/sun/star/io/XInputStream.hpp>

#include <libwpd/WPXStream.h>

class WPXSvInputStream : public WPXInputStream
{
public:
    WPXSvInputStream( ::com::sun::star::uno::Reference<
                      ::com::sun::star::io::XInputStream > xStream );
    virtual ~WPXSvInputStream();

    virtual bool isOLEStream();
    virtual WPXInputStream * getDocumentOLEStream();

    virtual const uint8_t *read(size_t numBytes, size_t &numBytesRead);
    virtual int seek(long offset, WPX_SEEK_TYPE seekType);
    virtual long tell();
    virtual bool atEOS();

private:
    SotStorageRef       mxChildStorage;
    SotStorageStreamRef mxChildStream;
    ::com::sun::star::uno::Reference<
              ::com::sun::star::io::XInputStream > mxStream;
    ::com::sun::star::uno::Sequence< sal_Int8 > maData;
    sal_Int64 mnOffset;
    sal_Int64 mnLength;
};

#endif
