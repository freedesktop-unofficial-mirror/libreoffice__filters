/*************************************************************************
 *
 *  $RCSfile: xpool.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: hjs $ $Date: 2003-10-01 12:23:46 $
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

#ifndef _XPOOL_HXX
#define _XPOOL_HXX

#ifndef _SFXITEMPOOL_HXX //autogen
#include <svtools/itempool.hxx>
#endif
#ifndef _XDEF_HXX
#include <bf_svx/xdef.hxx>
#endif

/*************************************************************************
|*
|* Klassendeklaration
|*
\************************************************************************/

class XOutdevItemPool: public SfxItemPool
{
protected:
    SfxPoolItem**   ppPoolDefaults;
    SfxItemInfo*    pItemInfos;
#if SUPD<355
    USHORT*         pSlotIds;
#endif
/*    USHORT*         pVersion1Map;
    USHORT*         pVersion2Map;
    USHORT*         pVersion3Map;
    USHORT*         pVersion4Map;*/
    USHORT          nStart, nEnd;

private:
    void Ctor(SfxItemPool* pMaster, USHORT nAttrStart, USHORT nAttrEnd);

public:
    // Kontstruktion des Pools als MasterPool
    XOutdevItemPool(USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    FASTBOOL bLoadRefCounts = TRUE);

    // Damit meine SetItems mit dem MasterPool konstruiert werden koennen.
    // Der SdrItemPool wird dabei automatisch als Secondary an den
    // uebergebenen MasterPool bzw. an's Ende einer bestehenden Pool-Kette
    // angehaengt.
    XOutdevItemPool(SfxItemPool* pMaster,
                    USHORT nAttrStart = XATTR_START,
                    USHORT nAttrEnd = XATTR_END,
                    FASTBOOL bLoadRefCounts = TRUE);

    XOutdevItemPool(const XOutdevItemPool& rPool);

    virtual SfxItemPool* Clone() const;

    ~XOutdevItemPool();
};

#endif      // _XPOOL_HXX
