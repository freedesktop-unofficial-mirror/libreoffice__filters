/*************************************************************************
 *
 *  $RCSfile: unoprov.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:25 $
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

#ifndef SVX_UNOPROV_HXX
#define SVX_UNOPROV_HXX

#ifndef _COM_SUN_STAR_LANG_XSERVICEINFO_HPP_
#include <com/sun/star/lang/XServiceInfo.hpp>
#endif

#ifndef _SVDPOOL_HXX //autogen
#include <bf_svx/svdpool.hxx>
#endif
#ifndef _SFX_ITEMPROP_HXX //autogen
#include <svtools/itemprop.hxx>
#endif
#ifndef _LIST_HXX
#include <tools/list.hxx>
#endif
namespace binfilter {

/***********************************************************************
* class UHashMap                                                       *
***********************************************************************/

struct UHashMapEntry
{
    ::rtl::OUString aIdentifier;
    UINT32 nId;

    UHashMapEntry(const sal_Char * value, sal_Int32 length, UINT32 _nId) : aIdentifier(value,length,RTL_TEXTENCODING_ASCII_US), nId(_nId) { }
};

DECLARE_LIST( UHashMapEntryList, UHashMapEntry* )//STRIP008 DECLARE_LIST( UHashMapEntryList, UHashMapEntry* );

#define HASHARRAYSIZE	0x10
#define UHASHMAP_NOTFOUND (~0)

class UHashMap
{
private:
    UHashMapEntryList m_aHashList[HASHARRAYSIZE];

public:
    UHashMap( UHashMapEntry* pMap );
    ~UHashMap() {};

    UINT32 getId( const ::rtl::OUString& rCompareString );
};

/***********************************************************************
* Soriterer                                                            *
***********************************************************************/

#define	SVXMAP_SHAPE				0
#define	SVXMAP_CONNECTOR			1
#define	SVXMAP_DIMENSIONING			2
#define	SVXMAP_CIRCLE				3
#define	SVXMAP_POLYPOLYGON			4
#define	SVXMAP_POLYPOLYGONBEZIER	5
#define	SVXMAP_GRAPHICOBJECT		6
#define	SVXMAP_3DSCENEOBJECT		7
#define	SVXMAP_3DCUBEOBJEKT			8
#define	SVXMAP_3DSPHEREOBJECT		9
#define	SVXMAP_3DLATHEOBJECT		10
#define	SVXMAP_3DEXTRUDEOBJECT		11
#define	SVXMAP_3DPOLYGONOBJECT		12
#define	SVXMAP_ALL					13
#define SVXMAP_GROUP				14
#define SVXMAP_CAPTION				15
#define SVXMAP_OLE2					16
#define SVXMAP_PLUGIN				17
#define SVXMAP_FRAME				18
#define SVXMAP_APPLET				19
#define SVXMAP_CONTROL				20
#define SVXMAP_TEXT					21
#define	SVXMAP_END					22	// last+1 !

/***********************************************************************
* SvxUnoPropertyMapProvider											   *
***********************************************************************/
class SvxUnoPropertyMapProvider
{
    SfxItemPropertyMap* aMapArr[SVXMAP_END];
    void Sort(USHORT nId);
public:
    SvxUnoPropertyMapProvider();
    SfxItemPropertyMap* GetMap(UINT16 nPropertyId);
};

/***********************************************************************
* Globals                                                              *
***********************************************************************/

const sal_Int16 OBJ_OLE2_APPLET	= 100;
const sal_Int16 OBJ_OLE2_PLUGIN = 101;

extern SvxUnoPropertyMapProvider aSvxMapProvider;
extern UHashMapEntry pSdrShapeIdentifierMap[];
extern UHashMap aSdrShapeIdentifierMap;

#define SFX_METRIC_ITEM				(0x40)
#define E3D_INVENTOR_FLAG			(0x80000000)
}//end of namespace binfilter
#include <bf_svx/unoipset.hxx>
namespace binfilter {

/***********************************************************************
* class SvxServiceInfoHelper                                           *
***********************************************************************/

/** this class provides a basic helper for classes suporting the XServiceInfo Interface.
 *
 *  you can overload the <code>getSupprotedServiceNames</code> to implement a XServiceInfo.
 *  you can use the static helper methods to combine your services with that of parent
 *  or aggregatet classes.
 */
class SvxServiceInfoHelper : public ::com::sun::star::lang::XServiceInfo
{
public:
    // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName() throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);

    // helper
    static ::com::sun::star::uno::Sequence< ::rtl::OUString > concatSequences( const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rSeq1, const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rSeq2 ) throw();
    static void addToSequence( ::com::sun::star::uno::Sequence< ::rtl::OUString >& rSeq,UINT16 nServices, /* sal_Char* */... ) throw();
    static sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName, const ::com::sun::star::uno::Sequence< ::rtl::OUString >& SupportedServices ) throw();
};

/***********************************************************************
* class SvxPropertySetInfoPool                                         *
***********************************************************************/

const sal_Int32 SVXUNO_SERVICEID_COM_SUN_STAR_DRAWING_DEFAULTS = 0;
const sal_Int32 SVXUNO_SERVICEID_COM_SUN_STAR_DRAWING_DEFAULTS_WRITER = 1;
const sal_Int32 SVXUNO_SERVICEID_LASTID = 1;
}//end of namespace binfilter
namespace comphelper { class PropertySetInfo; }
namespace binfilter {
class SvxPropertySetInfoPool
{
public:
    static comphelper::PropertySetInfo* getOrCreate( sal_Int32 nServiceId ) throw();

private:
    static comphelper::PropertySetInfo* mpInfos[SVXUNO_SERVICEID_LASTID+1];
};

}//end of namespace binfilter
#endif

