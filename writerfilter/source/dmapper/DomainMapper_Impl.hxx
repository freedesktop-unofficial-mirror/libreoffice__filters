/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DomainMapper_Impl.hxx,v $
 *
 *  $Revision: 1.13 $
 *
 *  last change: $Author: fridrich_strba $ $Date: 2007-05-30 10:43:21 $
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
#ifndef INCLUDED_DMAPPER_DOMAINMAPPER_IMPL_HXX
#define INCLUDED_DMAPPER_DOMAINMAPPER_IMPL_HXX

#include <com/sun/star/text/XTextDocument.hpp>
#include <com/sun/star/text/XTextCursor.hpp>
#include <com/sun/star/text/XTextAppendAndConvert.hpp>
#ifndef _COM_SUN_STAR_STYLE_TABSTOP_HPP_
#include <com/sun/star/style/TabStop.hpp>
#endif
#ifndef _COM_SUN_STAR_CONTAINER_XNAMECONTAINER_HPP_
#include <com/sun/star/container/XNameContainer.hpp>
#endif
#include <vector>
#include <stack>

#ifndef INCLUDED_RESOURCESIDS
#include <doctok/resourceids.hxx>
#include <ooxml/resourceids.hxx>
#endif
#ifndef INCLUDED_DOMAIN_MAPPER_TABLE_MANAGER_HXX
#include <DomainMapperTableManager.hxx>
#endif
#ifndef INCLUDED_DMAPPER_PROPERTYMAP_HXX
#include <PropertyMap.hxx>
#endif
#ifndef INCLUDED_FONTTABLE_HXX
#include <FontTable.hxx>
#endif
#ifndef INCLUDED_LISTTABLE_HXX
#include <ListTable.hxx>
#endif
#ifndef INCLUDED_LFOTABLE_HXX
#include <LFOTable.hxx>
#endif
#ifndef INCLUDED_STYLESHEETTABLE_HXX
#include <StyleSheetTable.hxx>
#endif
#ifndef INCLUDED_GRAPHICIMPORT_HXX
#include <GraphicImport.hxx>
#endif

namespace com{ namespace sun{ namespace star{
        namespace lang{
            class XMultiServiceFactory;
            struct Locale;
        }
        namespace text{ class XTextField;}
        namespace beans{ class XPropertySet;}
}}}

namespace dmapper {

using namespace writerfilter;
using namespace com::sun::star;

//#define TWIP_TO_MM100(TWIP)     ((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
//sal_Int32 lcl_convertToMM100(sal_Int32 _t);

/*-- 14.06.2006 07:42:52---------------------------------------------------
    property stack element
  -----------------------------------------------------------------------*/
enum ContextType
{
    CONTEXT_SECTION,
    CONTEXT_PARAGRAPH,
    CONTEXT_CHARACTER,
    NUMBER_OF_CONTEXTS
};
/*-----------------29.01.2007 11:47-----------------
   field stack element
 * --------------------------------------------------*/
class FieldContext
{
    bool                                                                            m_bFieldCommandCompleted;
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange >          m_xStartRange;

    ::rtl::OUString                                                                 m_sCommand;

    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextField >          m_xTextField;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >       m_xTOC;//TOX
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >       m_xTC;//TOX entry
    ::rtl::OUString                                                                 m_sHyperlinkURL;

public:
    FieldContext(::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > xStart);
    ~FieldContext();

    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange > GetStartRange() const { return m_xStartRange; }

    void                    AppendCommand(const ::rtl::OUString& rPart);
    const ::rtl::OUString&  GetCommand() const {return m_sCommand; }

    void                    SetCommandCompleted() { m_bFieldCommandCompleted = true; }
    bool                    IsCommandCompleted() const { return m_bFieldCommandCompleted;    }

    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextField >      GetTextField() const { return m_xTextField;}
    void    SetTextField(::com::sun::star::uno::Reference< ::com::sun::star::text::XTextField > xTextField) { m_xTextField = xTextField;}

    void    SetTOC( ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xTOC ) { m_xTOC = xTOC; }
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >   GetTOC() { return m_xTOC; }

    void    SetTC( ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > xTC ) { m_xTC = xTC; }
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >   GetTC( ) { return m_xTC; }

    void    SetHyperlinkURL( const ::rtl::OUString& rURL ) { m_sHyperlinkURL = rURL; }
    const ::rtl::OUString&                                                      GetHyperlinkURL() { return m_sHyperlinkURL; }

};

typedef boost::shared_ptr<FieldContext>  FieldContextPtr;

typedef std::stack<ContextType>                 ContextStack;
typedef std::stack<PropertyMapPtr>              PropertyStack;
typedef boost::shared_ptr< StyleSheetTable >    StyleSheetTablePtr;
typedef std::stack< ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextAppendAndConvert > >
                                                TextAppendStack;
typedef std::stack<FieldContextPtr>                FieldStack;

/*-- 18.07.2006 08:49:08---------------------------------------------------

  -----------------------------------------------------------------------*/
class FIB
{
    sal_Int32   aFIBData[ NS_rtf::LN_LCBSTTBFUSSR - NS_rtf::LN_WIDENT + 1];
    sal_Int32   nLNCHS;
    public:
        FIB() :
            nLNCHS( 0 )
            {
                memset(&aFIBData, 0x00, sizeof(aFIBData));
            }

        sal_Int32 GetLNCHS() const {return nLNCHS;}
        void      SetLNCHS(sal_Int32 nValue) {nLNCHS = nValue;}
        sal_Int32 GetData( doctok::Id nName );
        void      SetData( doctok::Id nName, sal_Int32 nValue );
};

/*-- 17.07.2006 09:14:13---------------------------------------------------
    extended tab stop struct
  -----------------------------------------------------------------------*/
struct DeletableTabStop : public ::com::sun::star::style::TabStop
{
    bool bDeleted;
    DeletableTabStop() :
        bDeleted( false ){}
    DeletableTabStop( const ::com::sun::star::style::TabStop& rTabStop ) :
        TabStop( rTabStop ),
            bDeleted( false ){}
};
/*-- 09.06.2006 10:15:20---------------------------------------------------

  -----------------------------------------------------------------------*/
class DomainMapper;
class DomainMapper_Impl
{
public:
    typedef doctok::TableManager< ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange >, PropertyMapPtr > TableManager_t;
    typedef doctok::TableDataHandler< ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange >, PropertyMapPtr > TableDataHandler_t;

private:
    DomainMapper&                                                                   m_rDMapper;
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextDocument >       m_xTextDocument;
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >       m_xDocumentSettings;
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > m_xTextFactory;
    ::com::sun::star::uno::Reference < com::sun::star::uno::XComponentContext >     m_xComponentContext;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > m_xPageStyles;
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XText >               m_xBodyText;

    TextAppendStack                                                                 m_aTextAppendStack;

    FieldStack                                                                      m_aFieldStack;
    bool                                                                            m_bFieldMode;
    bool                                                                            m_bSetUserFieldContent;
    bool                                                                            m_bIsFirstSection;

    DomainMapperTableManager m_TableManager;

    //each context needs a stack of currently used attributes
    FIB                     m_aFIB;
    PropertyStack           m_aPropertyStacks[NUMBER_OF_CONTEXTS];
    ContextStack            m_aContextStack;
    FontTablePtr            m_pFontTable;
    ListTablePtr            m_pListTable;
    LFOTablePtr             m_pLFOTable;
    StyleSheetTablePtr      m_pStyleSheetTable;
    GraphicImportPtr        m_pGraphicImport;

    PropertyMapPtr                  m_pTopContext;

    ::std::vector<DeletableTabStop> m_aCurrentTabStops;
    sal_uInt32                      m_nCurrentTabStopIndex;
    ::rtl::OUString                 m_sCurrentParaStyleId;
    bool                            m_bInStyleSheetImport;

    bool                            m_bLineNumberingSet;

    void                            GetCurrentLocale(::com::sun::star::lang::Locale& rLocale);
    void                            SetNumberFormat( const ::rtl::OUString& rCommand,
                                        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >& xPropertySet );
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >
                                    FindOrCreateFieldMaster( const sal_Char* pFieldMasterService,
                                                            const ::rtl::OUString& rFieldMasterName )
                                                                throw(::com::sun::star::uno::Exception);
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet >       GetDocumentSettings();

public:
    DomainMapper_Impl(
            DomainMapper& rDMapper,
            uno::Reference < uno::XComponentContext >  xContext,
            uno::Reference< lang::XComponent >  xModel );
    DomainMapper_Impl();
    virtual ~DomainMapper_Impl();

    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameContainer > GetPageStyles();
    ::com::sun::star::uno::Reference< ::com::sun::star::text::XText >               GetBodyText();
    ::com::sun::star::uno::Reference < ::com::sun::star::lang::XMultiServiceFactory > GetTextFactory()
    {
        return m_xTextFactory;
    }

    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextDocument >       GetTextDocument()
    {
        return m_xTextDocument;
    }
    void SetDocumentSettingsProperty( const ::rtl::OUString& rPropName, const uno::Any& rValue );

    void finishParagraph( PropertyMapPtr pPropertyMap );
    void appendTextPortion( const ::rtl::OUString& rString, PropertyMapPtr pPropertyMap );
    void appendTextContent( const ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextContent > );
    ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySet > appendTextSectionAfter(
                    ::com::sun::star::uno::Reference< ::com::sun::star::text::XTextRange >& xBefore );

//    void appendTextSection();

    FIB&    GetFIB() {return m_aFIB;}
    // push the new properties onto the stack and make it the 'current' property map
    void    PushProperties(ContextType eId);
    void    PopProperties(ContextType eId);

    PropertyMapPtr GetTopContext()
            {
                return m_pTopContext;
            }
    PropertyMapPtr GetTopContextOfType(ContextType eId);
    FontTablePtr GetFontTable()
            {
                if(!m_pFontTable)
                    m_pFontTable.reset(new FontTable());
                return m_pFontTable;
            }
    StyleSheetTablePtr GetStyleSheetTable()
            {
                if(!m_pStyleSheetTable)
                    m_pStyleSheetTable.reset(new StyleSheetTable( m_rDMapper ));
                return m_pStyleSheetTable;
            }
    ListTablePtr GetListTable();
    LFOTablePtr GetLFOTable()
            {
                if(!m_pLFOTable)
                    m_pLFOTable.reset( new LFOTable );
                return m_pLFOTable;
            }
    GraphicImportPtr GetGraphicImport(bool bIsShape );
    // this method deletes the current m_pGraphicImport after import
    void    ImportGraphic(doctok::Reference< doctok::Properties>::Pointer_t, bool bIsShape );

    void    InitTabStopFromStyle( const ::com::sun::star::uno::Sequence< ::com::sun::star::style::TabStop >& rInitTabStops );
    void    ModifyCurrentTabStop( doctok::Id nId, sal_Int32 nValue);
    void    IncorporateTabStop (DeletableTabStop &aTabStop);
    ::com::sun::star::uno::Sequence< ::com::sun::star::style::TabStop >     GetCurrentTabStopAndClear();
    void                                NextTabStop() {++m_nCurrentTabStopIndex;}

    void        SetCurrentParaStyleId(sal_Int32 nIntValue) {m_sCurrentParaStyleId = ::rtl::OUString::valueOf(static_cast<sal_Int32>(nIntValue), 16);}
    ::rtl::OUString   GetCurrentParaStyleId() const {return m_sCurrentParaStyleId;}

    ::com::sun::star::uno::Any    GetPropertyFromStyleSheet(PropertyIds eId);
    void        SetStyleSheetImport( bool bSet ) { m_bInStyleSheetImport = bSet;}
    bool        IsStyleSheetImport()const { return m_bInStyleSheetImport;}

    void PushPageHeader(SectionPropertyMap::PageType eType);
    void PushPageFooter(SectionPropertyMap::PageType eType);

    void PopPageHeaderFooter();

    void PushFootOrEndnote( bool bIsFootnote );
    void PopFootOrEndnote();

    //field context starts with a 0x13
    void PushFieldContext();
    //the current field context waits for the completion of the command
    bool IsOpenFieldCommand() const;
    bool IsOpenField() const;
    //collect the pieces of the command
    void AppendFieldCommand(::rtl::OUString& rPartOfCommand);
    //the field command has to be closed (0x14 appeared)
    void CloseFieldCommand();
    //the _current_ fields require a string type result while TOCs accept richt results
    bool IsFieldResultAsString();
    //apply the result text to the related field
    void SetFieldResult( ::rtl::OUString& rResult );
    //the end of field is reached (0x15 appeared) - the command might still be open
    void PopFieldContext();

    //create a new field from the command string
//    void CreateField( ::rtl::OUString& rCommand );
    //set the field result in insert the field
//    void SetFieldMode( bool bSet ) { m_bFieldMode = bSet; }
//    bool IsFieldMode() const { return m_bFieldMode; }
//    void SetFieldResult( ::rtl::OUString& rResult );
//    bool IsFieldAvailable() const;

    TableManager_t & getTableManager() { return m_TableManager; }

    void SetLineNumbering( sal_Int32 nLnnMod, sal_Int32 nLnc, sal_Int32 ndxaLnn );
    bool IsLineNumberingSet() const {return m_bLineNumberingSet;}
    DeletableTabStop                m_aCurrentTabStop;

};
} //namespace dmapper
#endif
