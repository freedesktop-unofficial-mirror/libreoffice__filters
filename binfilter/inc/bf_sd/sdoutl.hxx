/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: sdoutl.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 12:04:08 $
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

#ifndef _SD_SPOUTLINER_HXX
#define _SD_SPOUTLINER_HXX

#ifndef _SVDOUTL_HXX
#include <bf_svx/svdoutl.hxx>
#endif
#ifndef _PRESENTATION_HXX
#include "pres.hxx"
#endif
#ifndef _SD_OUTLINER_ITERATOR_HXX
#include "SdOutlinerIterator.hxx"
#endif
class SfxStyleSheetPool;
class SdrObjListIter;
namespace binfilter {

class SdViewShell;
class SdDrawViewShell;
class SdWindow;
class SdView;
class SdPage;
class SdrObject;
class SdrTextObj;
class SdDrawDocument;



/** The main purpose of this class is searching and replacing as well as
    spelling of impress documents.  The main part of both tasks lies in
    iterating over the pages and view modes of a document and apply the
    respective function to all objects containing text on those pages.

    <p>Relevant objects: There are two sets of objects to search/spell
    check.  One is the set of all selected objects.  The other consists of
    all objects on all pages in draw-, notes-, and handout view as well as
    slide- and background view (draw pages and master pages).</p>

    <p>Iteration: Search/replace and spelling functions operate on shapes
    containing text.  To cover all relevant objects an order has to be
    defined on the objects.  For the set of all selected objects this order
    is simply the order in which they can be retrieved from the selection
    object.<br>
    When there is no selection the order is nested.  The three modes of the
    draw view are on the outer level: draw mode, notes mode, handout mode.
    The inner level switches between draw pages and master pages.  This
    leads to the following order:
    <ol>
    <li>draw pages of draw mode</li>
    <li>master pages of draw mode</li>
    <li>draw pages of notes mode</li>
    <li>master pages of notes mode</li>
    <li>draw pages of handout mode</li>
    <li>master pages of handout mode</li>
    </ol>
    Iteration starts at the top of the current page.  When reaching the end
    of the document, i.e. the last master page of the handout mode, it jumps
    to the first draw page of draw mode.  In backward searches this order is
    reversed.  When doing a <em>replace all</em> then the whole document is
    searched for matches starting at the first page of the draw/slide view
    (or last page of handout/background view even though search
    direction).</p>

    <p>The start position is restored after finishing spell checking or
    replacing all matches in a document.</p>

    <p>Some related pieces of information:
    The search dialog (<type>SvxSearchDialog</type>) can be controlled in
    more than one way:
    <ul><li>A set of option flags returned by the slot call 
    SID_SEARCH_OPTIONS handled by the
    <member>SdDrawDocument::GetState()</member> method.</li>
    <li>The contents of the search item of type
    <type>SvxSearchItem</type>.</li>
    <li>The <member>HasSelection()</member> view shell method that returns
    whether or not a selection exists.  However, it is called from the
    search dialog with an argument so that only text selections are
    queried.  This is only sufficient for searching the outline view.
    </p>
*/
class SdOutliner : public SdrOutliner
{
public:
//STRIP001     friend class ::binfilter::sd::outliner::OutlinerContainer;

    /** Create a new sd outliner object.
        @param pDoc
            The draw document from which to take the content.
        @param nMode
            The valid values <const>OUTLINERMODE_DONTKNOW</const>,
            <const>OUTLINERMODE_TEXTOBJECT</const>,
            <const>OUTLINERMODE_TITLEOBJECT</const>,
            <const>OUTLINERMODE_OUTLINEOBJECT</const>, and
            <const>OUTLINERMODE_OUTLINEVIEW</const> are defined in
            bf_svx/outliner.hxx.
    */
    SdOutliner( SdDrawDocument* pDoc, USHORT nMode );
    virtual ~SdOutliner();

    /** Despite the name this method is called prior to spell cheking *and*
        searching and replacing.  The position of current view
        mode/page/object/caret position is remembered and, depending on the
        search mode, may be restored after finishing searching/spell
        checking.
    */
//STRIP001 	void PrepareSpelling (void);
 
    /** Initiate a spell check.
    */
//STRIP001 	void StartSpelling (void);

    /** Initiate a find and/or replace on the next relevant text object.
        @return
            Returns </TRUE> when the search/replace is finished (as
            indicated by user input to the search dialog).  A </FALSE> value
            indicates that another call to this method is required.
    */
//STRIP001 	BOOL StartSearchAndReplace (const SvxSearchItem* pSearchItem);

    /** Initiate the spell check of the next relevant text object.
        @return
            Returns <TRUE/> to indicate that another call to this method is
            required.  When all text objects have been processed then
            <FALSE/> is returned.
    */
//STRIP001 	virtual BOOL SpellNextDocument (void);

    /** Release all resources that have been created during the find&replace
        or spell check.
    */
//STRIP001 	void EndSpelling (void);
//STRIP001 	DECL_LINK( SpellError, void * );

private:
    /// Specifies whether to search and replace or to spell check.
    enum {SEARCH, SPELL} meMode;

    /// The view which displays the searched objects.
    SdView* mpView;
    /// The view shell containing the view.
    SdViewShell* mpViewShell;
    /// This window contains the view.
    SdWindow* mpWindow;
    /// The document on whose objects and pages this class operates.
    SdDrawDocument* mpDrawDocument;

    /** Flag that specifies whether we own the outline view pointed to by
        <member>mpOutlineView</member> and thus have to
        delete it in <member>EndSpelling()</member>.
    */
    bool mbOwnOutlineView;

    /** The outline view used for searching and spelling.  If searching or
        spell checking an outline view this data member points to that
        view.  For all other views a new outline view is created used only
        for searching or spell checking.  The
        <member>mbOwnOutlineView</member> distinguishes between both cases.
    */
    OutlinerView* mpOutlineView;

    /// Specifies whether the search string has been found so far.
    BOOL mbStringFound;

    /** This flag indicates whether there may exist a match of the search
        string before/after the current position in the document.  It can be
        set to </FALSE> only when starting from the beginning/end of the
        document.  When reaching the end/beginning with it still be set to
        </FALSE> then there exists no match and the search can be terminated.
    */
    bool mbMatchMayExist;

    /// The number of pages in the current view.
    USHORT mnPageCount;
    
    /// Number of objects on the current page / in the current selection.
    INT32 mnObjectCount;

    /** A <TRUE/> value indicates that the end of the find&replace or spell
        check has been reached.
    */
    BOOL mbEndOfSearch;

    /** Set to <TRUE/> when an object has been prepared successfully for
        searching/spell checking.  This flag directs the internal iteration
        which stops when set to </TRUE>.
    */
    BOOL mbFoundObject;

    /** When set to <TRUE/> this flag indicates that an error has occured
        that should terminate the iteration over the objects to search/spell
        check.
    */
    BOOL mbError;

    /** This flag indicates whether to search forward or backwards.
    */
    bool mbDirectionIsForward;

    /** This flag indicates that only the selected objects are to be
        searched.
    */
    bool mbRestrictSearchToSelection;

    /** When the search is restricted to the current selection then this
        list contains pointers to all the selection's objects.  This copy is
        necessary because during the search process the mark list is
        modified.
    */
    ::std::vector<SdrObject*> maMarkListCopy;

    /**  This flag inidcates that only the current view is to be used for
         searching and spelling.  Automatically switching to other view does
         not take place when this flag is set.
    */
    bool mbProcessCurrentViewOnly;

    /** Current object that may be a text object.  The object pointer to
        corresponds to <member>mnObjIndex</member>.  While iterating over the
        objects on a page <member>mpObj</member> will point to every object
        while <member>mpTextObj</member> will be set only to valid text
        objects.
    */
    SdrObject* mpObj;

    /// Candidate for being searched/spell checked.
    SdrTextObj* mpTextObj;

    /// Paragraph object of <member>mpTextObj</member>.
    OutlinerParaObject* mpParaObj;

    /// The view mode that was active when starting to search/spell check.
    PageKind meStartViewMode;

    /// The master page mode that was active when starting to search/spell check.
    EditMode meStartEditMode;

    /// The current page index on starting to search/spell check.
    USHORT mnStartPageIndex;

    /// The object in edit mode when searching /spell checking was started
    /// (if any).
    SdrObject* mpStartEditedObject;

    /// The position of the caret when searching /spell checking was started.
    ESelection maStartSelection;

    /** The original edit mode directly after switching to a different view
        mode.  Used for restoring the edit mode when leaving that view mode
        again. 
    */
    EditMode meOriginalEditMode;

    /** The search item contains various attributes that define the type of
        search.  It is set every time the
        <member>SearchAndReplaceAll</member> method is called.
    */
    const SvxSearchItem* mpSearchItem;

    /// The actual object iterator.
    ::binfilter::sd::outliner::Iterator maObjectIterator;
    /// The current position of the object iterator.
    ::binfilter::sd::outliner::IteratorPosition maCurrentPosition;
    /// The position when the search started.  Corresponds largely to the
    /// m?Start* members.
    ::binfilter::sd::outliner::Iterator maSearchStartPosition;

    /** This flag remebers a selection change between a call to the
        selection change listener callback and the next
        <member>DetectChange()</member> method call. 
    */
    bool mbSelectionHasChanged;

    /** This flag indicates whether a selection change event is expected due
        to a programatical change of the selection.
    */
    bool mbExpectingSelectionChangeEvent;

    /** Initialize the object iterator.  Call this method after being
        invoked from the search or spellcheck dialog.  It creates a new
        iterator pointing at the current object when this has not been done
        before.  It reverses the direction of iteration if the given flag
        differs from the current direction.
        @param bDirectionIsForward
            This flag specifies in which direction to iterator over the
            objects.  If it differs from the current direction the iterator
            is reversed.
    */
    void Initialize (bool bDirectionIsForward);

    /** Do search and replace for whole document.
    */
    BOOL SearchAndReplaceAll (void);
    
    /** Do search and replace for next match.
        @return
            The return value specifies whether the search ended (</TRUE>) or
            another call to this method is required (</FALSE>).
    */
    BOOL SearchAndReplaceOnce (void);

    /** Detect changes of the document or view and react accordingly.  Such
        changes may occur because different calls to
        <member>SearchAndReplace()</member> there usually is user
        interaction.  This is at least the press of the search or replace
        button but may include any other action some of which affect the
        search.
    */
    void DetectChange (void);

    /** Detect whether the selection has changed.
        @return
            Return <TRUE/> when the selection has been changed since the
            last call to this method.
    */
    bool DetectSelectionChange (void);

    /** Remember the current edited object/caret position/page/view mode
        when starting to search/spell check so that it can be restored on
        termination.
    */
    void RememberStartPosition (void);

    /** Restore the position stored in the last call of
        <member>RememberStartPositiony</member>.
    */
    void RestoreStartPosition (void);

    /** Provide next object to search or spell check as text object in edit
        mode on the current page.  This skips all objects that do not
        match or are no text object.
    */
    void ProvideNextTextObject (void);

    /** Handle the situation that the iterator has reached the last object.
        This may result in setting the <member>mbEndOfSearch</member> flag
        back to </FALSE>.  This method may show either the end-of-search
        dialog or the wrap-arround dialog.
    */
    void EndOfSearch (void);

    /** Prepare to commence searching/spell checking on the specified page.
        This also creates a proper page iterator.
        @param nPageIndex
            Index of the page to prepare for searching.  The default value
            of -1 is a flag for using the first/last page of the current
            edit mode/view mode depending on the search direction.
    */
    void InitPage (USHORT nPageIndex = (USHORT)-1);
        
    /** Show a dialog that tells the user that the search has ended either
        because there are no more matches after finding at least one or that
        no match has been found at all.
    */
    void ShowEndOfSearchDialog (void);

    /** Show a dialog that asks the user whether to wrap arround to the
        beginning/end of the document and continue with the search/spell
        check.
    */
    bool ShowWrapArroundDialog (void);

    /** Check whether the object pointed to by the iterator is a valid text
        object.
        @param aPosition
            The object for which to test whether it is a valid text object.
    */
    bool IsValidTextObject (const ::binfilter::sd::outliner::IteratorPosition& rPosition);

    /** Put text of current text object into outliner so that the text can
        be searched/spell checked.
    */
    void PutTextIntoOutliner (void);

    /** Prepare to do spell checking on the current text object.  This
        includes putting it into edit mode.  Under certain conditions this
        method sets <member>mbEndOfSearch</member> to <TRUE/>.
    */
    void PrepareSpellCheck (void);

    /** Prepare to search and replace on the current text object.  This
        includes putting it into edit mode.
    */
    void PrepareSearchAndReplace (void);

    /** Switch to a new view mode.  Try to restore the original edit mode
        before doing so.
        @param ePageKind
            Specifies the new view mode.
    */
    void SetViewMode (PageKind ePageKind);

    /** Switch to the page or master page specified by the
        <member>mnPage</member> index.  Master page mode is specified by
        <member>meEditMode</member>. 
        @param eEditMode
            The new edit mode.
        @param nPageIndex
            The new page index.
    */
    void SetPage (EditMode eEditMode, USHORT nPageIndex);

    /** Switch on edit mode for the currently selected text object.
    */
    void EnterEditMode (void);

    /** Return the position at which a new search is started with respect to
        the search direction as specified by the argument.
        @return
            The position mentioned above in form of a selection with start
            equals end.
    */
//STRIP001     ESelection GetSearchStartPosition (void);

    /** Detect whether there exists a previous match.  Note that only the
        absence of such a match can be detected reliably.  An existing match
        is assumed when the search started not at the beginning/end of the
        presentation.  This does not have to be true.  The user can have set
        the cursor at the middle of the text without a prior search.
        @return
            Returns </True> when there is no previous match and </False>
            when there may be one.
    */
//STRIP001     bool HasNoPreviousMatch (void);

    /** Handle a failed search (with or without replace) for the outline
        mode.  Show message boxes when the search failed completely,
        i.e. there is no match in the whole presentation, or when no further
        match exists.
        @return
            The returned value indicates whether another (wrapped arround)
            search shall take place.  If that is so, then it is the caller's
            responsibility to set the cursor position accordingly.
    */
//STRIP001     bool HandleFailedSearch (void);

    /** Return a parent window for a dialog.  The returned window depends on
        the search mode.
    */
    Window* GetParentForDialog (void);

    /** Take a position as returned by an object iterator and switch to the
        view and page on which the object specified by this position is
        located.
        @param rPosition
            This position points to a <type>SdrObject</type> object and
            contains the view and page where it is located.
        @return
            Return a pointer to the <type>SdrObject</type>.
    */
    SdrObject* SetObject (const ::binfilter::sd::outliner::IteratorPosition& rPosition);

    /** Use this method when the view shell in which to search has changed.
        It handles i.e. registering at the associated view as selection
        change listener.
    */
    void SetViewShell (SdViewShell* pViewShell);

    /** Activate or deactivate the search in the current selection.  Call
        this method whenever the selection has changed.  This method creates
        a copy of the current selection and reassings the object iterator to
        the current() iterator.
    */
    void HandleChangedSelection (void);
};



} //namespace binfilter
#endif		// _SD_OUTLINER_HXX

