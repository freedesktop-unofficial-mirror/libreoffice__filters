/*************************************************************************
 *
 *  $RCSfile: svdoattr.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:28:51 $
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

#ifndef _SVDOATTR_HXX
#define _SVDOATTR_HXX

#ifndef SVX_XFILLIT0_HXX //autogen
#include <bf_svx/xfillit0.hxx>
#endif

#ifndef _SVX_XFLASIT_HXX //autogen
#include <bf_svx/xflasit.hxx>
#endif

#ifndef _SVX_XLINEIT0_HXX //autogen
#include <bf_svx/xlineit0.hxx>
#endif

#ifndef _SVX_XLNASIT_HXX //autogen
#include <bf_svx/xlnasit.hxx>
#endif

#ifndef _SVDOBJ_HXX
#include <bf_svx/svdobj.hxx>
#endif

#ifndef _SVDATTR_HXX
#include <bf_svx/svdattr.hxx>
#endif
class SfxPoolItem; 
class SfxSetItem;
class SfxItemSet;
class SfxItemPool;
namespace binfilter {

//************************************************************
//   Vorausdeklarationen
//************************************************************


class SdrOutliner;

//************************************************************
//   SdrAttrObj
//************************************************************

class SdrAttrObj : public SdrObject
{
    friend class				SdrOutliner;

protected:
    Rectangle					maSnapRect;
    SfxStyleSheet				*mpStyleSheet;
    SfxItemSet					*mpObjectItemSet;

    void ImpDeleteItemSet();
    void ImpForceItemSet();

protected:
    // Strichstaerke ermitteln. Keine Linie -> 0.
    INT32 ImpGetLineWdt() const;

    // Feststellen, wieviel wegen der Linienenden auf's BoundRect draufaddiert werden muss.
    INT32 ImpGetLineEndAdd() const;

    // HitTest auf's Linienende
    // ueber nSin/nCos wird der Winkel vorgegeben
//STRIP001 	FASTBOOL ImpLineEndHitTest(const Point& rEndPt, double nSin, double nCos, FASTBOOL bStart, const Point& rHit, USHORT nTol) const;

    // Schattenabstand ermitteln. FALSE=Kein Schatten.
    FASTBOOL ImpGetShadowDist(sal_Int32& nXDist, sal_Int32& nYDist) const;

    // ggf. Schattenversatz zum BoundRect draufaddieren
    void ImpAddShadowToBoundRect();

    // Line und Fill Attribute fuer Schatten setzen.
    // Return=FALSE: kein Schatten attributiert.
    FASTBOOL ImpSetShadowAttributes( const SfxItemSet& rSet, SfxItemSet& rShadowSet ) const;

    // Zuhoeren, ob sich ein StyleSheet aendert
    virtual void SFX_NOTIFY(SfxBroadcaster& rBC, const TypeId& rBCType, const SfxHint& rHint, const TypeId& rHintType);
    virtual void RemoveStyleSheet();
    virtual void AddStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

    // aus NULL-AttrPointern Pointer auf defaults machen
    virtual void ForceDefaultAttr();
    SdrAttrObj();
    virtual ~SdrAttrObj();

public:
    TYPEINFO();

    // Feststellen, ob bFilledObj && Fuellung!=FillNone
    BOOL HasFill() const;

    // Feststellen, ob Linie!=LineNone
    BOOL HasLine() const;

    virtual const Rectangle& GetSnapRect() const;
    virtual void operator=(const SdrObject& rObj);
    virtual void WriteData(SvStream& rOut) const;
    virtual void ReadData(const SdrObjIOHeader& rHead, SvStream& rIn);
    virtual void SetModel(SdrModel* pNewModel);

    // pre- and postprocessing for objects for saving
    virtual void PreSave();
    virtual void PostSave();

    // ItemSet access
    virtual const SfxItemSet& GetItemSet() const;
    virtual SfxItemSet* CreateNewItemSet(SfxItemPool& rPool);

    // syntactical sugar for ItemSet accesses
    const SfxItemSet& GetUnmergedItemSet() const;

    // t support routines for ItemSet access. NULL pointer means clear item.
    virtual void ItemChange(const sal_uInt16 nWhich, const SfxPoolItem* pNewItem = 0);
    virtual void ItemSetChanged(const SfxItemSet& rSet);

    virtual SfxStyleSheet* GetStyleSheet() const;
    virtual void SetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);
    virtual void NbcSetStyleSheet(SfxStyleSheet* pNewStyleSheet, FASTBOOL bDontRemoveHardAttr);

//STRIP001 	virtual void BurnInStyleSheetAttributes( BOOL bPseudoSheetsOnly=FALSE );

    // ItemPool fuer dieses Objekt wechseln
    virtual void MigrateItemPool(SfxItemPool* pSrcPool, SfxItemPool* pDestPool, SdrModel* pNewModel = NULL );
};

////////////////////////////////////////////////////////////////////////////////////////////////////

}//end of namespace binfilter
#endif //_SVDOATTR_HXX

