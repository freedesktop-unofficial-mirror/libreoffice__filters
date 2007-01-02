/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: svx_unoviwou.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2007-01-02 17:37:23 $
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



#include "unoviwou.hxx"
#include "outliner.hxx"
#include "svdotext.hxx"
namespace binfilter {


SvxDrawOutlinerViewForwarder::SvxDrawOutlinerViewForwarder( OutlinerView& rOutl, const Point& rShapePosTopLeft ) :
    mrOutlinerView ( rOutl ), maTextShapeTopLeft( rShapePosTopLeft )
{
}

SvxDrawOutlinerViewForwarder::~SvxDrawOutlinerViewForwarder()
{
}

Point SvxDrawOutlinerViewForwarder::GetTextOffset() const
{
    // #101029# calc text offset from shape anchor
    Rectangle aOutputRect( mrOutlinerView.GetOutputArea() );
    
    return aOutputRect.TopLeft() - maTextShapeTopLeft;
}

BOOL SvxDrawOutlinerViewForwarder::IsValid() const
{
    return sal_True;
}

Rectangle SvxDrawOutlinerViewForwarder::GetVisArea() const
{
    OutputDevice* pOutDev = mrOutlinerView.GetWindow();

    if( pOutDev )
    {
        Rectangle aVisArea = mrOutlinerView.GetVisArea();

        // #101029#
        Point aTextOffset( GetTextOffset() );
        aVisArea.Move( aTextOffset.X(), aTextOffset.Y() );

        // figure out map mode from edit engine
        Outliner* pOutliner = mrOutlinerView.GetOutliner();

        if( pOutliner )
        {
            MapMode aMapMode(pOutDev->GetMapMode());
            aVisArea = OutputDevice::LogicToLogic( aVisArea, 
                                                   pOutliner->GetRefMapMode(), 
                                                   aMapMode.GetMapUnit() );
            aMapMode.SetOrigin(Point());
            return pOutDev->LogicToPixel( aVisArea, aMapMode );
        }
    }

    return Rectangle();
}

Point SvxDrawOutlinerViewForwarder::LogicToPixel( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrOutlinerView.GetWindow();

    if( pOutDev )
    {
        Point aPoint1( rPoint );
        Point aTextOffset( GetTextOffset() );

        // #101029#
        aPoint1.X() += aTextOffset.X();
        aPoint1.Y() += aTextOffset.Y();

        MapMode aMapMode(pOutDev->GetMapMode());
        Point aPoint2( OutputDevice::LogicToLogic( aPoint1, rMapMode, 
                                                   aMapMode.GetMapUnit() ) );
        aMapMode.SetOrigin(Point());
        return pOutDev->LogicToPixel( aPoint2, aMapMode );
    }

    return Point();
}

Point SvxDrawOutlinerViewForwarder::PixelToLogic( const Point& rPoint, const MapMode& rMapMode ) const
{
    OutputDevice* pOutDev = mrOutlinerView.GetWindow();

    if( pOutDev )
    {
        MapMode aMapMode(pOutDev->GetMapMode());
        aMapMode.SetOrigin(Point());
        Point aPoint1( pOutDev->PixelToLogic( rPoint, aMapMode ) );
        Point aPoint2( OutputDevice::LogicToLogic( aPoint1, 
                                                   aMapMode.GetMapUnit(), 
                                                   rMapMode ) );
        // #101029#
        Point aTextOffset( GetTextOffset() );

        aPoint2.X() -= aTextOffset.X();
        aPoint2.Y() -= aTextOffset.Y();

        return aPoint2;
    }

    return Point();
}

sal_Bool SvxDrawOutlinerViewForwarder::GetSelection( ESelection& rSelection ) const
{
    rSelection = mrOutlinerView.GetSelection();
    return sal_True;
}

sal_Bool SvxDrawOutlinerViewForwarder::SetSelection( const ESelection& rSelection )
{
    mrOutlinerView.SetSelection( rSelection );
    return sal_True;
}

sal_Bool SvxDrawOutlinerViewForwarder::Copy()
{
    mrOutlinerView.Copy();
    return sal_True;
}

sal_Bool SvxDrawOutlinerViewForwarder::Cut()
{
    mrOutlinerView.Cut();
    return sal_True;
}

sal_Bool SvxDrawOutlinerViewForwarder::Paste()
{
    mrOutlinerView.Paste();
    return sal_True;
}

}
