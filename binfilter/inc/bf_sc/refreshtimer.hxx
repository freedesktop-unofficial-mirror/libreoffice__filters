/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: refreshtimer.hxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: rt $ $Date: 2006-10-28 02:40:52 $
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

#ifndef SC_REFRESHTIMER_HXX
#define SC_REFRESHTIMER_HXX

#ifndef _SV_TIMER_HXX
#include <vcl/timer.hxx>
#endif
#ifndef _VOS_MUTEX_HXX
#include <vos/mutex.hxx>
#endif
namespace binfilter {

#define SC_REFRESHTIMER_CONTROL_LIST 0
#if SC_REFRESHTIMER_CONTROL_LIST
class ScRefreshTimer;
DECLARE_LIST( ScRefreshTimerList, ScRefreshTimer* )
#endif

class ScRefreshTimerControl
{
private:
            ::vos::OMutex		aMutex;
            USHORT				nBlockRefresh;

public:
#if SC_REFRESHTIMER_CONTROL_LIST
            ScRefreshTimerList	aList;
#endif

                                ScRefreshTimerControl() : nBlockRefresh(0) {}

            void				SetAllowRefresh( BOOL b )
                                    {
                                        if ( b && nBlockRefresh )
                                            --nBlockRefresh;
                                        else if ( !b && nBlockRefresh < (USHORT)(~0) )
                                            ++nBlockRefresh;
                                    }
            BOOL				IsRefreshAllowed() const	{ return !nBlockRefresh; }
            ::vos::OMutex&		GetMutex()					{ return aMutex; }
};


class ScRefreshTimerProtector
{
private:
    ScRefreshTimerControl * const *	ppControl;
public:
                                ScRefreshTimerProtector( ScRefreshTimerControl * const *	 pp );
                                ~ScRefreshTimerProtector()
                                    {
                                        if ( ppControl && *ppControl )
                                            (*ppControl)->SetAllowRefresh( TRUE );
                                    }
};


class ScRefreshTimer : public AutoTimer
{
private:
    ScRefreshTimerControl * const *	ppControl;

            void				AppendToControl()
                                    {
#if SC_REFRESHTIMER_CONTROL_LIST
                                        if ( ppControl && *ppControl )
                                            (*ppControl)->aList.Insert( this, LIST_APPEND );
#endif
                                    }
            void				RemoveFromControl()
                                    {
#if SC_REFRESHTIMER_CONTROL_LIST
                                        if ( ppControl && *ppControl )
                                            (*ppControl)->aList.Remove( this );
#endif
                                    }

            void				Start()
                                    {
                                        if ( GetTimeout() )
                                            AutoTimer::Start();
                                    }

public:
                                ScRefreshTimer() : ppControl(0)
                                    { SetTimeout( 0 ); }
                                ScRefreshTimer( ULONG nSeconds ) : ppControl(0)
                                    {
                                        SetTimeout( nSeconds * 1000 );
                                        Start();
                                    }
                                ScRefreshTimer( const ScRefreshTimer& r )
                                    : AutoTimer( r ), ppControl(0)
                                    {}
    virtual						~ScRefreshTimer();

            ScRefreshTimer&		operator=( const ScRefreshTimer& r )
                                    {
                                        SetRefreshControl(0);
                                        AutoTimer::operator=( r );
                                        return *this;
                                    }

            BOOL				operator==( const ScRefreshTimer& r ) const
                                    { return GetTimeout() == r.GetTimeout(); }

            BOOL				operator!=( const ScRefreshTimer& r ) const
                                    { return !ScRefreshTimer::operator==( r ); }

            void				StartRefreshTimer()
                                    { Start(); }

            void				SetRefreshControl( ScRefreshTimerControl * const * pp )
                                    {
                                        RemoveFromControl();
                                        ppControl = pp;
                                        AppendToControl();
                                    }

            void				SetRefreshHandler( const Link& rLink )
                                    { SetTimeoutHdl( rLink ); }

            ULONG				GetRefreshDelay() const
                                    { return GetTimeout() / 1000; }

            void				StopRefreshTimer()
                                    { Stop(); }

    virtual	void				SetRefreshDelay( ULONG nSeconds );
};


} //namespace binfilter
#endif // SC_REFRESHTIMER_HXX

