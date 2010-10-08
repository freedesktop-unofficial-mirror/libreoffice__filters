/*************************************************************************
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
 *  The Initial Developer of the Original Code is: IBM Corporation
 *
 *  Copyright: 2008 by IBM Corporation
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
/*************************************************************************
 * @file
 *  For LWP filter architecture prototype
 ************************************************************************/
/*************************************************************************
 * Change History
 Jan 2005			Created
 ************************************************************************/

#ifndef LWPOBJFACTORY_HXX_
#define LWPOBJFACTORY_HXX_

#include "lwpheader.hxx"
#include "lwpobjid.hxx"
#include "lwpobj.hxx"
#include "lwpobjhdr.hxx"
#include "lwpidxmgr.hxx"
#if 0
#ifdef WIN32
#include <so3/svstor.hxx>
#include <so3/outplace.hxx>
#include <so3/ipobj.hxx>
#include <so3/factory.hxx>
#include <svx/svdoole2.hxx>
#include <svx/svdpage.hxx>
#include <sfx2/objsh.hxx>
#include <sot/storinfo.hxx>
#endif //WIN32
#endif
/**
 * @brief	object factory used for lwp object creation and maintenance
*/
class LwpObjectFactory
{
public:
    LwpObjectFactory(LwpSvStream* pSvStream);
public:
//	static LwpObjectFactory* Instance(LwpSvStream* pSvStream=NULL);
    ~LwpObjectFactory();

//For object Factory and object manager
private:
//	static LwpObjectFactory *m_pMgr;
    sal_uInt32 m_nNumObjs;
    LwpSvStream* m_pSvStream;
    struct hashFunc
    {
            size_t operator()( const LwpObjectID& rName ) const
            {
                return rName.HashCode();
            }
    };
    struct eqFunc
    {
            bool operator()( const LwpObjectID& rKey1, const LwpObjectID& rKey2 ) const
            {
                return(rKey1==rKey2);
            }
    };
    typedef std::hash_map<LwpObjectID, LwpObject *, hashFunc, eqFunc> LwpObjMap;
    LwpObjMap m_ObjList;
    LwpIndexManager m_IndexMgr;
    void ClearObjectMap();

protected:
    LwpObject* FindObject(const LwpObjectID &objID);
public:
    LwpObject* CreateObject(sal_uInt32 type, LwpObjectHeader &objHdr);
    LwpObject* QueryObject(const LwpObjectID &objID);
    void ReleaseObject(const LwpObjectID &objID);
    void ReadIndex(LwpSvStream* pStrm);
    LwpIndexManager* GetIndexManager(){return &m_IndexMgr;}
#if 0
// for OLE objects in current wordpro file
#ifdef WIN32
private:
    SvStorageRef m_objStor;
    SvStorageInfoList m_infoList;
public:
    void SetOleObjInfo(SvStorageRef & objStor);
    void GetOleObjInfo(SvStorageRef & objStor, SvStorageInfoList ** ppInfoList);
#endif
#endif
};

#endif
