#ifndef _RTFDOCUMENT_HXX_
#define _RTFDOCUMENT_HXX_

#include <resourcemodel/WW8ResourceModel.hxx>
#include <com/sun/star/io/XInputStream.hpp>

namespace writerfilter {
    namespace rtftok {
        /// The RTFDocument opens and resolves the RTF document.
        class WRITERFILTER_RTFTOK_DLLPUBLIC RTFDocument
            : public writerfilter::Reference<Stream>
        {
            public:
                /// Pointer to this stream.
                typedef ::boost::shared_ptr<RTFDocument> Pointer_t;

                virtual ~RTFDocument() { }

                /// Resolves this document to a stream handler.
                virtual void resolve(Stream & rHandler) = 0;

                /// Returns string representation of the type of this reference. (Debugging purpose only.)
                virtual ::std::string getType() const = 0;
        };

        /// Interface to create an RTFDocument instance.
        class WRITERFILTER_RTFTOK_DLLPUBLIC RTFDocumentFactory
        {
            public:
                static RTFDocument::Pointer_t
                    createDocument(
                            ::com::sun::star::uno::Reference< ::com::sun::star::io::XInputStream >
                            const & xInputStream );
        };
    } // namespace rtftok
} // namespace writerfilter

#endif // _RTFDOCUMENT_HXX_

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
