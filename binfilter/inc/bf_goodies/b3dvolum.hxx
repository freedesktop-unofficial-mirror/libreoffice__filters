/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: b3dvolum.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 18:22:06 $
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

#ifndef _B3D_VOLUM_HXX
#define _B3D_VOLUM_HXX

#ifndef _SVX_VECTOR3D_HXX
#include "vector3d.hxx"
#endif

#ifndef _INC_FLOAT
#include <float.h>
#endif

#ifndef _STREAM_HXX
#include <tools/stream.hxx>
#endif

/*************************************************************************
|*
|* dreidimensionales Volumen, symmetrisch zu den Koordinatenachsen
|*
\************************************************************************/

namespace binfilter {
class Vol3DPointIterator;

class B3dVolume
{
// friend class binfilter::Vol3DPointIterator; //STRIP008 
 friend class Vol3DPointIterator;
 protected:
    Vector3D aMinVec;
    Vector3D aMaxVec;

 public:
    B3dVolume(const Vector3D& rPos, const Vector3D& r3DSize,
        BOOL bPosIsCenter = TRUE);
    B3dVolume();

    void Reset();
    BOOL IsValid() const;

    B3dVolume& Union(const B3dVolume& rVol2);
    B3dVolume& Union(const Vector3D& rVec);

    const Vector3D& MinVec() const { return aMinVec; }
    Vector3D& MinVec() { return aMinVec; }

    const Vector3D& MaxVec() const { return aMaxVec; }
    Vector3D& MaxVec() { return aMaxVec; }

    double GetWidth()  const { return aMaxVec.X() - aMinVec.X(); }
    double GetHeight() const { return aMaxVec.Y() - aMinVec.Y(); }
    double GetDepth()  const { return aMaxVec.Z() - aMinVec.Z(); }

    friend SvStream& operator>>(SvStream& rIStream, B3dVolume&);
    friend SvStream& operator<<(SvStream& rOStream, const B3dVolume&);
};
}//end of namespace binfilter


#endif			// _B3D_VOLUM_HXX
