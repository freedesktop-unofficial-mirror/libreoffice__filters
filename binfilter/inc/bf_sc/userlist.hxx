/*************************************************************************
 *
 *  $RCSfile: userlist.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:25:08 $
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

#ifndef SC_USERLIST_HXX
#define SC_USERLIST_HXX

#ifndef _STREAM_HXX //autogen
#include <tools/stream.hxx>
#endif

#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
namespace binfilter {

//------------------------------------------------------------------------
class ScUserListData : public DataObject
{
friend class ScUserList;
    String	aStr;
    USHORT	nTokenCount;
    String* pSubStrings;
    String* pUpperSub;

    void	InitTokens();

public:
                    ScUserListData(const String& rStr);
                    ScUserListData(const ScUserListData& rData);
//STRIP001 					ScUserListData( SvStream& rStream );
    virtual			~ScUserListData();

    virtual	DataObject*		Clone() const { return new ScUserListData(*this); }
//STRIP001 			BOOL			Store( SvStream& rStream ) const;
    const	String&			GetString() const { return aStr; }
//STRIP001 			void			SetString( const String& rStr);
//STRIP001 			USHORT			GetSubCount() const;
            BOOL			GetSubIndex(const String& rSubStr, USHORT& rIndex) const;
//STRIP001 			String			GetSubStr(USHORT nIndex) const;
//STRIP001 			StringCompare   Compare(const String& rSubStr1, const String& rSubStr2) const;
//STRIP001 			StringCompare   ICompare(const String& rSubStr1, const String& rSubStr2) const;
};

//------------------------------------------------------------------------
class ScUserList : public Collection
{
public:
                    ScUserList( USHORT nLim = 4, USHORT nDel = 4);
                    ScUserList( const ScUserList& rUserList ) : Collection ( rUserList ) {}

    virtual	DataObject*		Clone() const;

            ScUserListData*	GetData( const String& rSubStr ) const;
//STRIP001 			BOOL			Load( SvStream& rStream );
//STRIP001 			BOOL			Store( SvStream& rStream ) const;
            /// If the list in rStr is already inserted
            BOOL            HasEntry( const String& rStr ) const;

    inline	ScUserListData*	operator[]( const USHORT nIndex) const;
    inline	ScUserList&		operator= ( const ScUserList& r );
//STRIP001 			BOOL			operator==( const ScUserList& r ) const;
//STRIP001 	inline  BOOL			operator!=( const ScUserList& r ) const;
};

inline	ScUserList& ScUserList::operator=( const ScUserList& r )
    { return (ScUserList&)Collection::operator=( r ); }

inline ScUserListData* ScUserList::operator[]( const USHORT nIndex) const
    { return (ScUserListData*)At(nIndex); }

//STRIP001 inline BOOL ScUserList::operator!=( const ScUserList& r ) const
//STRIP001 	{ return !operator==( r ); }

} //namespace binfilter
#endif

