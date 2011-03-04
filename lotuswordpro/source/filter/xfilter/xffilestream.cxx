/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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
 * Interface for the all content object,ie. text,paragraph,picture,and so on.
 ************************************************************************/
#include	"xffilestream.hxx"
#include	"xffileattrlist.hxx"
#include	"ixfattrlist.hxx"

void	WriteStartTag(std::ofstream& ofs, const char *pStr, int len);
void	WriteEndTag(std::ofstream& ofs, const char *pStr, int len);
void	WriteString(std::ofstream& ofs, const char *pStr, int len);
void	WriteXmlString(std::ofstream& ofs, const char *pStr, int len);
void	WriteOUString(std::ofstream& ofs, const rtl::OUString& oustr);

XFFileStream::XFFileStream(std::string strFileName):m_aFile(strFileName.c_str())
{
    m_pAttrList = new XFFileAttrList();
}

XFFileStream::~XFFileStream()
{
    if( m_pAttrList )
        delete m_pAttrList;
}

void		XFFileStream::StartDocument()
{
    std::string	strXmlDecl = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    WriteString(m_aFile, strXmlDecl.c_str(),strXmlDecl.length());
}

void		XFFileStream::EndDocument()
{
    m_aFile.close();
}


void		XFFileStream::StartElement(const rtl::OUString& oustr)
{
    WriteString(m_aFile, "\n<",2);
    WriteOUString(m_aFile, oustr);

    //write attributes:
    std::vector<std::pair<rtl::OUString,rtl::OUString> >::iterator	it;
    for( it = m_pAttrList->m_aAttrList.begin(); it != m_pAttrList->m_aAttrList.end(); ++it )
    {
        std::pair<rtl::OUString,rtl::OUString>	pair = *it;
        rtl::OUString	name = pair.first;
        rtl::OUString	value = pair.second;

        WriteString(m_aFile," ",1);
        WriteOUString(m_aFile, name);
        WriteString(m_aFile, "=\"",2);
        WriteOUString(m_aFile, value);
        WriteString(m_aFile, "\"",1);

    }

    WriteString(m_aFile, ">",1);
    m_pAttrList->Clear();
}

void		XFFileStream::EndElement(const rtl::OUString& oustr)
{
    rtl::OString	ostr;

    ostr = rtl::OUStringToOString(oustr,RTL_TEXTENCODING_UTF8);
    WriteEndTag(m_aFile, ostr.getStr(), ostr.getLength());
}

void		XFFileStream::Characters(const rtl::OUString& oustr)
{
    WriteOUString(m_aFile, oustr);
}

IXFAttrList*	XFFileStream::GetAttrList()
{
    return m_pAttrList;
}

//------------------------------------------------------------------------------

void	WriteStartTag(std::ofstream& ofs, const char *pStr, int len)
{
    ofs.write("\n<",2);
    ofs.write(pStr,len);
}

void	WriteEndTag(std::ofstream& ofs, const char *pStr, int len)
{
    ofs.write("</",2);
    ofs.write(pStr,len);
    ofs.write(">\n",2);
}

void	WriteString(std::ofstream& ofs, const char *pStr, int len)
{
    ofs.write(pStr,len);
}

/**
 * @descr:	Replace some reserved characters of xml character into xml entity.Please refer to w3c xml spec.
 */
void	WriteXmlString(std::ofstream& ofs, const char *pStr, int len)
{
    std::string	 str;

    for( int i=0; i<len; i++ )
    {
        switch(pStr[i])
        {
        case '&':
            str += "&amp;";
            break;
        case '<':
            str += "&lt;";
            break;
        case '>':
            str += "&gt;";
            break;
        case '\'':
            str += "&apos;";
            break;
        case '\"':
            str += "&quot;";
            break;
        case 13:
            str += "&#x0d;";
            break;
        case 10:
            str += "&#x0a;";
            break;
        case 9:
            str += "&#x09;";
            break;
        default:
            str += pStr[i];
        }
    }
    ofs.write(str.c_str(),str.length());
}

void	WriteOUString(std::ofstream& ofs, const rtl::OUString& oustr)
{
    rtl::OString	ostr;

    ostr = rtl::OUStringToOString(oustr,RTL_TEXTENCODING_UTF8);

    WriteXmlString(ofs, ostr.getStr(),ostr.getLength());
}
/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
