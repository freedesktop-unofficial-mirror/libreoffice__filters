/*************************************************************************
 *
 *  $RCSfile: sxmtaitm.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: mwu $ $Date: 2003-11-06 08:29:11 $
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
#ifndef _SXMTAITM_HXX
#define _SXMTAITM_HXX

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif

#ifndef _SDYNITM_HXX
#include <bf_svx/sdynitm.hxx>
#endif

#ifndef _SDANGITM_HXX
#include <bf_svx/sdangitm.hxx>
#endif
namespace binfilter {

// Den Text automatisch zurechtdrehen (Automatisches UpsideDown).
// TextUpsideDown bleibt trotzdem weiterhin wirksam und dreht
// den Text bei TRUE nochmal.
class SdrMeasureTextAutoAngleItem: public SdrYesNoItem {
public:
    SdrMeasureTextAutoAngleItem(FASTBOOL bOn=TRUE): SdrYesNoItem(SDRATTR_MEASURETEXTAUTOANGLE,bOn) {}
    SdrMeasureTextAutoAngleItem(SvStream& rIn): SdrYesNoItem(SDRATTR_MEASURETEXTAUTOANGLE,rIn) {}
};

// Der bevorzugte Blickwinkel zum lesen des Textes. Wird nur ausgewertet, wenn
// TextAutoAngle=TRUE. Winkel in 1/100deg aus der Zeichnung zum Betrachter.
class SdrMeasureTextAutoAngleViewItem: public SdrAngleItem {
public:
    SdrMeasureTextAutoAngleViewItem(long nVal=31500): SdrAngleItem(SDRATTR_MEASURETEXTAUTOANGLEVIEW,nVal)  {}
    SdrMeasureTextAutoAngleViewItem(SvStream& rIn): SdrAngleItem(SDRATTR_MEASURETEXTAUTOANGLEVIEW,rIn) {}
};

}//end of namespace binfilter
#endif
