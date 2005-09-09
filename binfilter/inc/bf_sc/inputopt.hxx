/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: inputopt.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:17:44 $
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

#ifndef SC_INPUTOPT_HXX
#define SC_INPUTOPT_HXX


#ifndef _UTL_CONFIGITEM_HXX_
#include <unotools/configitem.hxx>
#endif

#ifndef _SOLAR_H
#include <tools/solar.h>
#endif

class SvStream;

namespace binfilter {

class ScInputOptions
{
private:
    USHORT		nMoveDir;			// enum ScDirection
    BOOL		bMoveSelection;
    BOOL		bEnterEdit;
    BOOL		bExtendFormat;
    BOOL		bRangeFinder;
    BOOL		bExpandRefs;
    BOOL		bMarkHeader;
    BOOL		bUseTabCol;
    BOOL		bTextWysiwyg;
    BOOL        bReplCellsWarn;

public:
                ScInputOptions();
                ScInputOptions( const ScInputOptions& rCpy );
                ~ScInputOptions();

    void		SetDefaults();

    void        SetMoveDir(USHORT nNew)         { nMoveDir = nNew;       }
    USHORT      GetMoveDir() const              { return nMoveDir;       }
    void        SetMoveSelection(BOOL bSet)     { bMoveSelection = bSet; }
    BOOL        GetMoveSelection() const        { return bMoveSelection; }
    void        SetEnterEdit(BOOL bSet)         { bEnterEdit = bSet;     }
    BOOL        GetEnterEdit() const            { return bEnterEdit;     }
    void        SetExtendFormat(BOOL bSet)      { bExtendFormat = bSet;  }
    BOOL        GetExtendFormat() const         { return bExtendFormat;  }
    void        SetRangeFinder(BOOL bSet)       { bRangeFinder = bSet;   }
    BOOL        GetRangeFinder() const          { return bRangeFinder;   }
    void        SetExpandRefs(BOOL bSet)        { bExpandRefs = bSet;    }
    BOOL        GetExpandRefs() const           { return bExpandRefs;    }
    void        SetMarkHeader(BOOL bSet)        { bMarkHeader = bSet;    }
    BOOL        GetMarkHeader() const           { return bMarkHeader;    }
    void        SetUseTabCol(BOOL bSet)         { bUseTabCol = bSet;     }
    BOOL        GetUseTabCol() const            { return bUseTabCol;     }
    void        SetTextWysiwyg(BOOL bSet)       { bTextWysiwyg = bSet;   }
    BOOL        GetTextWysiwyg() const          { return bTextWysiwyg;   }
    void        SetReplaceCellsWarn(BOOL bSet)  { bReplCellsWarn = bSet; }
    BOOL        GetReplaceCellsWarn() const     { return bReplCellsWarn; }

    const ScInputOptions&	operator=	( const ScInputOptions& rOpt );
/*N*/ 	friend SvStream& 		operator>>	( SvStream& rStream, ScInputOptions& rOpt );
/*N*/ 	friend SvStream&		operator<<	( SvStream& rStream, const ScInputOptions& rOpt );
};


//==================================================================
// CfgItem fuer Eingabe-Optionen
//==================================================================

class ScInputCfg : public ScInputOptions,
    public ::utl::ConfigItem
{
    ::com::sun::star::uno::Sequence<rtl::OUString> GetPropertyNames();

public:
            ScInputCfg();

    void			SetOptions( const ScInputOptions& rNew ){DBG_BF_ASSERT(0, "STRIP");} //STRIP001 	void			SetOptions( const ScInputOptions& rNew );
//STRIP001 	void			OptionsChanged();	// after direct access to SetOptions base class
//STRIP001 
//STRIP001 	virtual void	Notify( const ::com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames );
//STRIP001 	virtual void	Commit();
};


} //namespace binfilter
#endif

