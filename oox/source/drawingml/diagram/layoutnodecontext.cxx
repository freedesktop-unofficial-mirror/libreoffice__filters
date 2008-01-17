/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: layoutnodecontext.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2008-01-17 08:05:58 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2007 by Sun Microsystems, Inc.
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

#include "layoutnodecontext.hxx"

#include "oox/helper/attributelist.hxx"
#include "oox/core/skipcontext.hxx"
#include "oox/drawingml/diagram/diagram.hxx"
#include "oox/drawingml/shapecontext.hxx"
#include "diagramdefinitioncontext.hxx"

using namespace ::oox::core;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;
using ::rtl::OUString;

namespace oox { namespace drawingml {

class IfContext
    : public LayoutNodeContext
{
public:
    IfContext( const FragmentHandlerRef& xHandler,
               const Reference< XFastAttributeList >& xAttribs,
               const LayoutAtomPtr & pNode )
        : LayoutNodeContext( xHandler, xAttribs, pNode )
        {
            ConditionAtomPtr pAtom( boost::dynamic_pointer_cast< ConditionAtom >(pNode) );
            OSL_ENSURE( pAtom, "Must pass a ConditionAtom" );

            pAtom->iterator().loadFromXAttr( xAttribs );
            pAtom->cond().loadFromXAttr( xAttribs );
        }
};



class AlgorithmContext
    : public Context
{
public:
    AlgorithmContext( const FragmentHandlerRef& xHandler,  const Reference< XFastAttributeList >& xAttribs, const LayoutAtomPtr & pNode )
        : Context( xHandler )
        , mnRevision( 0 )
        , mnType( 0 )
        , mpNode( pNode )
        {
            AttributeList aAttribs( xAttribs );
            mnRevision = aAttribs.getInteger( XML_rev, 0 );
            mnType = xAttribs->getOptionalValueToken( XML_type, 0 );
        }

private:
    sal_Int32     mnRevision;
    sal_Int32     mnType;
    LayoutAtomPtr mpNode;
};


class ChooseContext
    : public Context
{
public:
    ChooseContext( const FragmentHandlerRef& xHandler,  const Reference< XFastAttributeList >& xAttribs, const LayoutAtomPtr & pNode )
        : Context( xHandler )
        , mbHasElse( false )
        , mpNode( pNode )
        {
            msName = xAttribs->getOptionalValue( XML_name );
        }

    virtual Reference< XFastContextHandler > SAL_CALL
    createFastChildContext( ::sal_Int32 aElement,
                            const Reference< XFastAttributeList >& xAttribs )
        throw (SAXException, RuntimeException)
        {
            Reference< XFastContextHandler > xRet;

            switch( aElement )
            {
            case XML_if:
            {
                // CT_When
                LayoutAtomPtr pAtom( new ConditionAtom( false ) );
                mpNode->addChild( pAtom );
                xRet.set( new IfContext( getHandler(), xAttribs, pAtom ) );
                break;
            }
            case XML_else:
                // CT_Otherwise
                if( !mbHasElse )
                {
                    LayoutAtomPtr pAtom( new ConditionAtom( true ) );
                    mpNode->addChild( pAtom );
                    xRet.set( new IfContext( getHandler(), xAttribs, pAtom ) );
                    mbHasElse = true;
                }
                else
                {
                    OSL_TRACE( "ignoring second else clause" );
                }
                break;
            default:
                break;
            }

            if( !xRet.is() )
                xRet.set(this);

            return xRet;
        }
private:
    bool     mbHasElse;
    OUString msName;
    LayoutAtomPtr mpNode;
};




class ForEachContext
    : public LayoutNodeContext
{
public:
    ForEachContext( const FragmentHandlerRef& xHandler,  const Reference< XFastAttributeList >& xAttribs, const LayoutAtomPtr & pNode )
        : LayoutNodeContext( xHandler, xAttribs, pNode )
        {
            ForEachAtomPtr pAtom( boost::dynamic_pointer_cast< ForEachAtom >(pNode) );
            OSL_ENSURE( pAtom, "Must pass a ForEachAtom" );
            xAttribs->getOptionalValue( XML_ref );

            pAtom->iterator().loadFromXAttr( xAttribs );
        }
};


// CT_LayoutVariablePropertySet
class LayoutVariablePropertySetContext
    : public Context
{
public:
    LayoutVariablePropertySetContext( const FragmentHandlerRef& xHandler,
                                      LayoutNode::VarMap & aVar )
        : Context( xHandler )
        , mVariables( aVar )
        {
        }

    virtual ~LayoutVariablePropertySetContext()
        {
        }

    virtual Reference< XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 aElement, const Reference< XFastAttributeList >& xAttribs )
        throw (SAXException, RuntimeException)
        {
            Reference< XFastContextHandler > xRet;

            sal_Int32 nIdx =  LayoutNodeContext::tagToVarIdx( aElement & ( ~NMSP_MASK ) );
            if( nIdx != -1 )
            {
                mVariables[ nIdx ] = makeAny( xAttribs->getOptionalValue( XML_val ) );
            }
            if( !xRet.is() )
                xRet.set(this);

            return xRet;
        }
private:
    LayoutNode::VarMap & mVariables;
};


// CT_LayoutNode
LayoutNodeContext::LayoutNodeContext( const FragmentHandlerRef& xHandler, 
                                      const Reference< XFastAttributeList >& xAttribs, 
                                      const LayoutAtomPtr &pNode )
    : Context( xHandler )
    , mpNode( pNode )
{
    OSL_ENSURE( pNode, "Node must NOT be NULL" );
    mpNode->setName( xAttribs->getOptionalValue( XML_name ) );
    // TODO shall we even bother?
    // b or t
//	sal_Int32 nChOrder = xAttributes->getOptionalValueToken( XML_chOrder, XML_b );
//	OUString sMoveWith = xAttributes->getOptionalValue( XML_moveWith );
//	OUString sStyleLbl = xAttributes->getOptionalValue( XML_styleLbl );
}


LayoutNodeContext::~LayoutNodeContext()
{
}

void SAL_CALL LayoutNodeContext::endFastElement( ::sal_Int32 ) 
    throw (SAXException, RuntimeException)
{

}

/** convert the XML tag to a variable index in the array
 * @param aTag the tag, wihout namespace
 * @return the variable index. -1 is an error
 */
sal_Int32 LayoutNodeContext::tagToVarIdx( sal_Int32 aTag )
{
    sal_Int32 nIdx = -1;
    switch( aTag )
    {
    case NMSP_DIAGRAM|XML_animLvl:
        nIdx = LayoutNode::VAR_animLvl;
        break;
    case NMSP_DIAGRAM|XML_animOne:
        nIdx = LayoutNode::VAR_animOne;
        break;
    case NMSP_DIAGRAM|XML_bulletEnabled:
        nIdx = LayoutNode::VAR_bulletEnabled;
        break;
    case NMSP_DIAGRAM|XML_chMax:
        nIdx = LayoutNode::VAR_chMax;
        break;
    case NMSP_DIAGRAM|XML_chPref:
        nIdx = LayoutNode::VAR_chPref;
        break;
    case NMSP_DIAGRAM|XML_dir:
        nIdx = LayoutNode::VAR_dir;
        break;
    case NMSP_DIAGRAM|XML_hierBranch:
        nIdx = LayoutNode::VAR_hierBranch;
        break;
    case NMSP_DIAGRAM|XML_orgChart:
        nIdx = LayoutNode::VAR_orgChart;
        break;
    case NMSP_DIAGRAM|XML_resizeHandles:
        nIdx = LayoutNode::VAR_resizeHandles;
        break;
    default:
        break;
    }
    return nIdx;
}


Reference< XFastContextHandler > SAL_CALL 
LayoutNodeContext::createFastChildContext( ::sal_Int32 aElement, 
                                                  const Reference< XFastAttributeList >& xAttribs ) 
    throw (SAXException, RuntimeException)
{
    Reference< XFastContextHandler > xRet;

    switch( aElement )
    {
    case NMSP_DIAGRAM|XML_layoutNode:
    {
        LayoutNodePtr pNode( new LayoutNode() );
        mpNode->addChild( pNode );
        xRet.set( new LayoutNodeContext( getHandler(), xAttribs, pNode ) );
        break;
    }
    case NMSP_DIAGRAM|XML_shape:
    {
        ShapePtr pShape( new Shape() );
        xRet.set( new ShapeContext( getHandler(), ShapePtr( ( Shape* )NULL ), pShape ) );
        break;
    }
    case NMSP_DIAGRAM|XML_extLst:
        xRet.set( new SkipContext( getHandler() ) );
        break;
    case NMSP_DIAGRAM|XML_alg:
    {
        // CT_Algorithm
        LayoutAtomPtr pAtom( new AlgAtom );
        mpNode->addChild( pAtom );
        xRet.set( new AlgorithmContext( getHandler(), xAttribs, pAtom ) );
        break;
    }
    case NMSP_DIAGRAM|XML_choose:
    {
        // CT_Choose
        LayoutAtomPtr pAtom( new ChooseAtom );
        mpNode->addChild( pAtom );
        xRet.set( new ChooseContext( getHandler(), xAttribs, pAtom ) );
         break;
    }
    case NMSP_DIAGRAM|XML_forEach:
    {
        // CT_ForEach
        LayoutAtomPtr pAtom( new ForEachAtom );
        mpNode->addChild( pAtom );
        xRet.set( new ForEachContext( getHandler(), xAttribs, pAtom ) );
        break;
    }
    case NMSP_DIAGRAM|XML_constrLst:
        // CT_Constraints
        // TODO
        break;
    case NMSP_DIAGRAM|XML_presOf:
    {
        // CT_PresentationOf
        // TODO
        xAttribs->getOptionalValue( XML_axis );
        xAttribs->getOptionalValue( XML_cnt );
        xAttribs->getOptionalValue( XML_hideLastTrans );
        xAttribs->getOptionalValue( XML_ptType );
        xAttribs->getOptionalValue( XML_st );
        xAttribs->getOptionalValue( XML_step );
        break;
    }
    case NMSP_DIAGRAM|XML_ruleLst:
        // CT_Rules
        // TODO
        break;
    case NMSP_DIAGRAM|XML_varLst:
    {
        LayoutNodePtr pNode( boost::dynamic_pointer_cast< LayoutNode >( mpNode ) );
        if( pNode ) 
        {
            xRet.set( new LayoutVariablePropertySetContext( getHandler(), 
                                                            pNode->variables() ) );
        }
        else 
        {
            OSL_TRACE( "OOX: encountered a varLst in a non layoutNode context" );
        }
        break;
    }
    default:
        break;
    }
    if( !xRet.is() )
        xRet.set(this);

    return xRet;
}


} }
