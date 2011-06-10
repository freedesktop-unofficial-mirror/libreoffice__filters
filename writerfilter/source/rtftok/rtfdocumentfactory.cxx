#include <rtfdocumentimpl.hxx>

namespace writerfilter {
namespace rtftok {

RTFDocument::Pointer_t RTFDocumentFactory::createDocument(uno::Reference< uno::XComponentContext > const & xContext,
        uno::Reference< io::XInputStream > const & xInputStream,
        uno::Reference< lang::XComponent > const & xDstDoc)
{
    return RTFDocument::Pointer_t(new RTFDocumentImpl(xContext, xInputStream, xDstDoc));
}

} // namespace rtftok
} // namespace writerfilter

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
