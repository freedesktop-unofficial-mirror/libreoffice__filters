/*************************************************************************
 *
 *  $RCSfile: hstream.cpp,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: dvo $ $Date: 2003-10-15 14:40:34 $
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
 *  Copyright 2001 by Mizi Research Inc.
 *  Copyright 2003 by Sun Microsystems, Inc.
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
 *  The Initial Developer of the Original Code is: Mizi Research Inc.
 *
 *  Copyright: 2001 by Mizi Research Inc.
 *  Copyright: 2003 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#include <string.h>
#include <stdlib.h>
#include "hstream.h"

HStream::HStream() : size(0), pos(0)
{
    seq = 0;
}


HStream::~HStream()
{
    if( seq )
        free( seq );
}


void HStream::addData( const byte *buf, int aToAdd)
{
    seq = (byte *)realloc( seq, size + aToAdd );
    memcpy( seq + size, buf, aToAdd );
    size += aToAdd;
}


int HStream::readBytes(byte * buf, int aToRead)
{
    if (aToRead >= (size - pos))
        aToRead = size - pos;
    for (int i = 0; i < aToRead; i++)
        buf[i] = seq[pos++];
    return aToRead;
}


int HStream::skipBytes(int aToSkip)
{
    if (aToSkip >= (size - pos))
        aToSkip = size - pos;
    pos += aToSkip;
    return aToSkip;
}


int HStream::available()
{
    return size - pos;
}


void HStream::closeInput()
{
}
