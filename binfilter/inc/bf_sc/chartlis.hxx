/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: chartlis.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:01:03 $
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

#ifndef SC_CHARTLIS_HXX
#define SC_CHARTLIS_HXX


#ifndef _TIMER_HXX //autogen
#include <vcl/timer.hxx>
#endif

#ifndef _SFXLSTNER_HXX //autogen
#include <svtools/lstner.hxx>
#endif
#ifndef SC_COLLECT_HXX
#include "collect.hxx"
#endif
#ifndef SC_RANGELST_HXX
#include "rangelst.hxx"
#endif

//STRIP008 class ScDocument;
//STRIP008 class ScChartUnoData;

#ifndef _COM_SUN_STAR_CHART_XCHARTDATA_HPP_
#include <com/sun/star/chart/XChartData.hpp>
#endif
// auto strip #ifndef _COM_SUN_STAR_CHART_XCHARTDATACHANGEEVENTLISTENER_HPP_
// auto strip #include <com/sun/star/chart/XChartDataChangeEventListener.hpp>
// auto strip #endif
namespace binfilter {
class ScDocument;
class ScChartUnoData;

class ScChartListener : public StrData, public SfxListener
{
private:
    ScRangeListRef	aRangeListRef;
    ScChartUnoData*	pUnoData;
    ScDocument* 	pDoc;
    BOOL			bUsed;	// fuer ScChartListenerCollection::FreeUnused
    BOOL			bDirty;
    BOOL			bSeriesRangesScheduled;

                    // not implemented
    ScChartListener& operator=( const ScChartListener& );

public:
                    ScChartListener( const String& rName, ScDocument* pDoc,
                                    const ScRange& rRange );
                    ScChartListener( const String& rName, ScDocument* pDoc,
                                    const ScRangeListRef& rRangeListRef );
                    ScChartListener( const ScChartListener& );
    virtual			~ScChartListener();
    virtual DataObject*	Clone() const;

    void			SetUno( const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& rListener,
                            const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >& rSource );
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >	GetUnoListener() const;
    ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >						GetUnoSource() const;

    BOOL			IsUno() const	{ return (pUnoData != NULL); }

    virtual void 	Notify( SfxBroadcaster& rBC, const SfxHint& rHint );
    void			StartListeningTo();
    void			EndListeningTo();
    void			ChangeListening( const ScRangeListRef& rRangeListRef,
                                    BOOL bDirty = FALSE );
    void			Update();
    const ScRangeListRef&	GetRangeList() const { return aRangeListRef; }
    void			SetRangeList( const ScRangeListRef& rNew ) { aRangeListRef = rNew; }
    void			SetRangeList( const ScRange& rNew );
    BOOL			IsUsed() const { return bUsed; }
    void			SetUsed( BOOL bFlg ) { bUsed = bFlg; }
    BOOL			IsDirty() const { return bDirty; }
    void			SetDirty( BOOL bFlg ) { bDirty = bFlg; }

    // if chart series ranges are to be updated later on (e.g. DeleteTab, InsertTab)
    void			ScheduleSeriesRanges()		{ bSeriesRangesScheduled = TRUE; }
//STRIP001 	void			UpdateScheduledSeriesRanges();
//STRIP001 	void			UpdateSeriesRangesIntersecting( const ScRange& rRange );
//STRIP001 	void			UpdateSeriesRanges();

//STRIP001 	BOOL			operator==( const ScChartListener& );
//STRIP001 	BOOL			operator!=( const ScChartListener& r )
//STRIP001 						{ return !operator==( r ); }
};

class ScChartListenerCollection : public StrCollection
{
private:
    Timer			aTimer;
    ScDocument*		pDoc;

                    DECL_LINK( TimerHdl, Timer* );

                    // not implemented
    ScChartListenerCollection& operator=( const ScChartListenerCollection& );

public:
                    ScChartListenerCollection( ScDocument* pDoc );
                    ScChartListenerCollection( const ScChartListenerCollection& );
    virtual	DataObject*	Clone() const;

    virtual			~ScChartListenerCollection();

                    // nur nach copy-ctor noetig, wenn neu ins Dok gehaengt
//STRIP001 	void			StartAllListeners();

    void			ChangeListening( const String& rName,
                                    const ScRangeListRef& rRangeListRef,
                                    BOOL bDirty = FALSE );
    // FreeUnused nur wie in ScDocument::UpdateChartListenerCollection verwenden!
    void			FreeUnused();
    void			FreeUno( const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartDataChangeEventListener >& rListener,
                             const ::com::sun::star::uno::Reference< ::com::sun::star::chart::XChartData >& rSource );
    void			StartTimer();
    void			UpdateDirtyCharts();
    void			SetDirty();
//STRIP001 	void			SetDiffDirty( const ScChartListenerCollection&,
//STRIP001 						BOOL bSetChartRangeLists = FALSE );

//STRIP001 	void			SetRangeDirty( const ScRange& rRange );		// z.B. Zeilen/Spalten

    void			UpdateScheduledSeriesRanges();
    void			UpdateSeriesRangesContainingTab( USHORT nTab );

//STRIP001 	BOOL			operator==( const ScChartListenerCollection& );
};


} //namespace binfilter
#endif

