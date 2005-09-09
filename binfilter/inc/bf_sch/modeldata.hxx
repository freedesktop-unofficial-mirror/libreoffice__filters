/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: modeldata.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:48:24 $
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
#ifndef _SCH_MODELDATA_HXX
#define _SCH_MODELDATA_HXX

#include "chtmodel.hxx"
namespace binfilter {

/** This class contains all members of the ChartModel, that can be stored for
    later for a complete undo.  Some members were omitted, that cannot be copied
    or must not be applied later.

    The original ChartModel from which is copied must stay alive until ApplyTo()
    is called, because the SfxItemSets use its pool.
 */
class SchModelData
{
public:
    SchModelData( const ChartModel & );

    /// sets the stored ChartModel members at the given ChartModel
    void ApplyTo( ChartModel & );

private:
    ChartBarDescriptor  aBarY1;
    ChartBarDescriptor  aBarY2;

    DescrList           aXDescrList;
    DescrList           aYDescrList;
    DescrList           aZDescrList;

//     BOOL                bClearDepth;
//     BOOL                bNewOrLoadCompleted;
//     SfxObjectShell*     pDocShell;
//     BOOL                bAttrAutoStorage;

//     SchMemChart*        pChartDataBuffered;     // save data in buffer while editing chart #61907#

//     OutputDevice*       pChartRefOutDev;
    long                nChartStatus;

//     Window*             pAutoPilot;             // #46895#

//     SdrObjList*         pSdrObjList;
//     Matrix4D            aSceneMatrix;
//     BOOL                bResizePie;
//     long                nPieRadius;

//     SvNumberFormatter*  pOwnNumFormatter;
//     SvNumberFormatter*  pNumFormatter;      // points either to pOwnNumFormatter or calc's number formatter

    ::com::sun::star::uno::Reference< ::com::sun::star::util::XRefreshable > mxChartAddIn;

    long                nBarPercentWidth;       // #50116#
    long                nNumLinesInColChart;
    long                m_nDefaultColorSet;     // #50037#

//     SchDataLogBook*     pLogBook;
    Rectangle           aChartRect;
    Size                aInitialSize;

//     SchItemPool*        pChItemPool;
//     ChartScene*         pScene;

//     Vector3D*           aLightVec;

    ::std::auto_ptr< SchMemChart > m_apChartData;

    double              fMinData;
    double              fMaxData;
    double              fAmbientIntensity;
    Color               aAmbientColor;
    double              fSpotIntensity;
    Color               aSpotColor;
    SvxChartStyle       eChartStyle;
    SvxChartStyle       eOldChartStyle;
//     int                 eChartLinePoints[ LINE_POINT_COUNT ];

//     List*               pDefaultColors;

    BOOL                bTextScalable;
    BOOL                bIsCopied;
    BOOL                bLegendVisible;
    BOOL                bShowAverage;
    SvxChartKindError   eErrorKind;
    SvxChartIndicate    eIndicate;
    SvxChartRegress     eRegression;
    double              fIndicatePercent;
    double              fIndicateBigError;
    double              fIndicatePlus;
    double              fIndicateMinus;
    int                 nSplineDepth;
    int                 nGranularity;

    /** This member is a temporary storage. I don't understand the comment, so
        I can't translate it into english, so I leave it in german, maybe an important hint someday:

        FG: Reiner Zwischenspeicher, wird in chtmod3d.cxx gesetzt und im selben
        File in Position3DAxisTitles im selben File abgefragt, weil die
        ChartScene::FitInSnapRect das nicht als Parameter bekommen kann, da
        diese von der Polyscene gerufen wird.  */
    BOOL                bSwitch3DColRow;

    long                nMarkLen;
    long                nPieHeight;
    long*               pPieSegOfs;
    short               nPieSegCount;
    short               nXAngle;
    short               nYAngle;
    short               nZAngle;

    BOOL                bCanRebuild;

    BOOL                bShowMainTitle;
    BOOL                bShowSubTitle;
    BOOL                bShowXAxisTitle;
    BOOL                bShowYAxisTitle;
    BOOL                bShowZAxisTitle;

    String              aMainTitle;
    String              aSubTitle;
    String              aXAxisTitle;
    String              aYAxisTitle;
    String              aZAxisTitle;

    BOOL                bShowXGridMain;
    BOOL                bShowXGridHelp;
    BOOL                bShowYGridMain;
    BOOL                bShowYGridHelp;
    BOOL                bShowZGridMain;
    BOOL                bShowZGridHelp;

    BOOL                bShowDataDescr; // show description for all series (esp. important for auto pilot)

    ::std::auto_ptr< SfxItemSet > m_apTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apMainTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apSubTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apXAxisTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apYAxisTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apZAxisTitleAttr;
    ::std::auto_ptr< SfxItemSet > m_apAxisAttr;

//     ChartAxis*          pChartXAxis;
//     ChartAxis*          pChartYAxis;
//     ChartAxis*          pChartZAxis;
//     ChartAxis*          pChartAAxis;    // secondary x axis
//     ChartAxis*          pChartBAxis;    // secondary y axis

    ::std::auto_ptr< SfxItemSet > m_apGridAttr;
    ::std::auto_ptr< SfxItemSet > m_apXGridMainAttr;
    ::std::auto_ptr< SfxItemSet > m_apYGridMainAttr;
    ::std::auto_ptr< SfxItemSet > m_apZGridMainAttr;
    ::std::auto_ptr< SfxItemSet > m_apXGridHelpAttr;
    ::std::auto_ptr< SfxItemSet > m_apYGridHelpAttr;
    ::std::auto_ptr< SfxItemSet > m_apZGridHelpAttr;
    ::std::auto_ptr< SfxItemSet > m_apDiagramAreaAttr;
    ::std::auto_ptr< SfxItemSet > m_apDiagramWallAttr;
    ::std::auto_ptr< SfxItemSet > m_apDiagramFloorAttr;
    ::std::auto_ptr< SfxItemSet > m_apLegendAttr;
    ::std::auto_ptr< SfxItemSet > m_apDummyAttr;

    ::std::auto_ptr< SfxItemSet > m_apStockLineAttr;
    ::std::auto_ptr< SfxItemSet > m_apStockLossAttr;
    ::std::auto_ptr< SfxItemSet > m_apStockPlusAttr;

//     SfxItemSet*         pTmpXItems;
//     SfxItemSet*         pTmpYItems;
//     SfxItemSet*         pTmpZItems;

    ::std::auto_ptr< SfxItemSet > m_apChartAttr;

    ItemSetList         aDataRowAttrList;
    ItemSetList         aDataPointAttrList;
    ItemSetList         aSwitchDataPointAttrList;
    ItemSetList         aRegressAttrList;
    ItemSetList         aAverageAttrList;
    ItemSetList         aErrorAttrList;

    // this is for 'old 3d storage' (whatever that is ;-)
//     ItemSetList         aTmpDataRowAttrList;
//     ItemSetList         aTmpDataPointAttrList;
//     ItemSetList         aTmpSwitchDataPointAttrList;


    SvxChartDataDescr   eDataDescr;
    BOOL                bShowSym;
    BOOL                bSwitchData;

    BOOL                bNoBuildChart;          // BuildChart does nothing if this is true
    BOOL                bShouldBuildChart;      // This is set when BuildChart was called and bNoBuildChart was TRUE
    BOOL                bReadError;
    BOOL                mbIsInitialized;

//     SdrOutliner*        pOutliner;

    /// short: textbreak enabled
    BOOL                bFormatXAxisTextInMultipleLinesIfNecessary;
    BOOL                bFormatYAxisTextInMultipleLinesIfNecessary;
    BOOL                bFormatZAxisTextInMultipleLinesIfNecessary;
    BOOL                bFormatLegendTextInMultipleLinesIfNecessary;

    /// maximum number of lines for textbreak
    int                 nXAxisTextMaximumNumberOfLines;
    int                 nYAxisTextMaximumNumberOfLines;
    int                 nZAxisTextMaximumNumberOfLines;

    long                nWidthOfFirstXAxisText;
    long                nWidthOfLastXAxisText;

    // positions of chart objects
    Point               aTitleTopCenter;
    Point               aSubTitleTopCenter;
    Rectangle           aDiagramRectangle;
    Rectangle           aLastDiagramRectangle;  // ?
    Point               aLegendTopLeft;

    Point               aTitleXAxisPosition;
    Point               aTitleYAxisPosition;
    Point               aTitleZAxisPosition;

    ChartAdjust         eAdjustXAxesTitle;
    ChartAdjust         eAdjustYAxesTitle;
    ChartAdjust         eAdjustZAxesTitle;

    // FG: Falls dieser gesetzt ist so wird bei einem Resize (eigentlich bei jedem Buildchart)
    //     die relative Position der Gruppenobjekte zur Seite beachtet.
    //     Je nach Objekt bleibt die linke obere Ecke oder das Zentrum an der gleichen Stelle.

    /** On resize objects remember their position relatively to the page if
        this member is TRUE.  For some objects the upper left corner is
        preserved for others the center position */
    BOOL                bUseRelativePositionsForChartGroups;

    /// on manual move of chart objects the calculation of space left has to be changed
    BOOL                bAdjustMarginsForLegend;
    BOOL                bAdjustMarginsForMainTitle;
    BOOL                bAdjustMarginsForSubTitle;
    BOOL                bAdjustMarginsForXAxisTitle;
    BOOL                bAdjustMarginsForYAxisTitle;
    BOOL                bAdjustMarginsForZAxisTitle;

    /// keep track if objects have manually been repositioned
    BOOL                bDiagramHasBeenMovedOrResized;
    BOOL                bMainTitleHasBeenMoved;
    BOOL                bSubTitleHasBeenMoved;
    BOOL                bLegendHasBeenMoved;
    BOOL                bXAxisTitleHasBeenMoved;
    BOOL                bYAxisTitleHasBeenMoved;
    BOOL                bZAxisTitleHasBeenMoved;

    Size                aInitialSizefor3d;

    /** test object for calculating the height of two rows
        @see GetHeightOfnRows */
//     SdrRectObj*         pTestTextObj;

    INT32               nXLastNumFmt;
    INT32               nYLastNumFmt;
    INT32               nBLastNumFmt;

    /// document languages
    LanguageType        eLanguage;
    LanguageType        eLanguageCJK;
    LanguageType        eLanguageCTL;

    ProjectionType      eProjection;

    /// for late loading of graphics
//     mutable SotStorage*          mpDocStor;
//     mutable SotStorageRef        mxPictureStorage;
//     mutable SotStorageStreamRef  mxDocStream;
};

// _SCH_MODELDATA_HXX
} //namespace binfilter
#endif
