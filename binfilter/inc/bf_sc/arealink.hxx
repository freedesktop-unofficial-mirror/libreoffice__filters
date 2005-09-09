/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: arealink.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 10:57:16 $
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

#ifndef SC_AREALINK_HXX
#define SC_AREALINK_HXX

#ifndef SC_SCGLOB_HXX
#include "global.hxx"
#endif
#ifndef SC_REFRESHTIMER_HXX
#include "refreshtimer.hxx"
#endif

#ifndef _LNKBASE_HXX //autogen
#include <so3/lnkbase.hxx>
#endif
namespace binfilter {

class ScDocShell;
class SfxObjectShell;

class ScAreaLink : public ::so3::SvBaseLink, public ScRefreshTimer
{
private:
    ScDocShell*	pDocShell;		// Container
    String		aFileName;
    String		aFilterName;
    String		aOptions;
    String		aSourceArea;
    ScRange		aDestArea;
    BOOL		bAddUndo;
    BOOL		bInCreate;
    BOOL		bDoInsert;		// wird fuer das erste Update auf FALSE gesetzt

    BOOL		FindExtRange( ScRange& rRange, ScDocument* pSrcDoc, const String& rAreaName );

public:
    TYPEINFO();
    ScAreaLink( SfxObjectShell* pShell, const String& rFile,
                    const String& rFilter, const String& rOpt,
                    const String& rArea, const ScRange& rDest, ULONG nRefresh );
    virtual ~ScAreaLink();

//STRIP001 	virtual void Closed();
    virtual void DataChanged( const String& rMimeType,
                              const ::com::sun::star::uno::Any & rValue );

//STRIP001 	virtual BOOL Edit(Window* pParent);

    BOOL	Refresh( const String& rNewFile, const String& rNewFilter,
                    const String& rNewArea, ULONG nNewRefresh );

    void	SetInCreate(BOOL bSet)					{ bInCreate = bSet; }
    void	SetDoInsert(BOOL bSet)					{ bDoInsert = bSet; }
    void	SetDestArea(const ScRange& rNew);
//STRIP001 	void	SetSource(const String& rDoc, const String& rFlt, const String& rOpt,
//STRIP001 						const String& rArea);

//STRIP001 	BOOL	IsEqual( const String& rFile, const String& rFilter, const String& rOpt,
//STRIP001 						const String& rSource, const ScRange& rDest ) const;

    const String&	GetFile() const			{ return aFileName;		}
    const String&	GetFilter() const		{ return aFilterName;	}
    const String&	GetOptions() const		{ return aOptions;		}
    const String&	GetSource() const		{ return aSourceArea;	}
    const ScRange&	GetDestArea() const		{ return aDestArea;		}

    DECL_LINK( RefreshHdl, ScAreaLink* );

};


} //namespace binfilter
#endif
