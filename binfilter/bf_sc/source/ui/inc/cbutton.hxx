/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cbutton.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 19:34:25 $
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

//------------------------------------------------------------------

#ifndef SC_CBUTTON_HXX
#define SC_CBUTTON_HXX

#ifndef _GEN_HXX //autogen
#include <tools/gen.hxx>
#endif

// auto strip #ifndef _COLOR_HXX //autogen
// auto strip #include <tools/color.hxx>
// auto strip #endif

class Window;
namespace binfilter {


//==================================================================

class ScDDComboBoxButton
{
public:
            ScDDComboBoxButton( Window* pOutputDevice );
            ~ScDDComboBoxButton();

//STRIP001 	void	Draw( const Point&	rAt,
//STRIP001 				  const Size&	rSize,
//STRIP001                   BOOL          bState,
//STRIP001 				  BOOL			bBtnIn = FALSE );

//STRIP001 void	Draw( const Point&	rAt,
//STRIP001                  BOOL          bState,
//STRIP001 			  BOOL			bBtnIn = FALSE )
//STRIP001                { Draw( rAt, aBtnSize, bState, bBtnIn ); }

//STRIP001    void    Draw( BOOL          bState,
//STRIP001                  BOOL          bBtnIn = FALSE )
//STRIP001                { Draw( aBtnPos, aBtnSize, bState, bBtnIn ); }

    void	SetOptSizePixel();

    void	SetPosPixel( const Point& rNewPos )  { aBtnPos = rNewPos; }
    Point	GetPosPixel() const				 	 { return aBtnPos; }

    void	SetSizePixel( const Size& rNewSize ) { aBtnSize = rNewSize; }
    Size	GetSizePixel() const				 { return aBtnSize; }

private:
//STRIP001 	void	ImpDrawArrow( const Rectangle&	rRect,
//STRIP001                           BOOL              bState );

protected:
    Window*	pOut;
    Point	aBtnPos;
    Size	aBtnSize;
};


} //namespace binfilter
#endif // SC_CBUTTON_HXX


