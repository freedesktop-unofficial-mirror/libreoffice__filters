/*************************************************************************
 *
 *  $RCSfile: zip.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: cl $ $Date: 2002-10-23 19:30:49 $
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
 *  Contributor(s): Christian Lippka (christian.lippka@sun.com)
 *
 *
 ************************************************************************/

#ifndef _SAL_TYPES_H_ 
#include <sal/types.h>
#endif
#ifndef _RTL_STRING_HXX_ 
#include <rtl/string.hxx>
#endif
#ifndef _OSL_FILE_HXX_ 
#include <osl/file.hxx>
#endif

#include <vector>

struct ZipEntry;

class ZipFile
{
public:
    ZipFile( osl::File& rFile );
    ~ZipFile();

    bool addFile( osl::File& rFile, const rtl::OString& rName );
    bool close();

private:
    void writeShort( sal_Int16 s);
    void writeLong( sal_Int32 l );

    void copyAndCRC( ZipEntry *e, osl::File& rFile );
    void writeDummyLocalHeader(ZipEntry *e);
    void writeLocalHeader(ZipEntry *e);
    void writeCentralDir(ZipEntry *e);
    void writeEndCentralDir(sal_Int32 nCdOffset, sal_Int32 nCdSize);

private:
    bool isError() const { return osl::File::E_None != mnRC; }

    osl::File::RC mnRC;
    bool mbOpen;
    osl::File& mrFile;				/* file we're writing to */
    std::vector<ZipEntry*> maEntries;
};
