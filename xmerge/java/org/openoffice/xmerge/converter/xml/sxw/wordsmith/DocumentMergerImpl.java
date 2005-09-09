/************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: DocumentMergerImpl.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 11:20:05 $
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

package org.openoffice.xmerge.converter.xml.sxw.wordsmith;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import org.openoffice.xmerge.DocumentMerger;
import org.openoffice.xmerge.MergeException;
import org.openoffice.xmerge.ConverterCapabilities;
import org.openoffice.xmerge.converter.xml.sxw.SxwDocument;
import org.openoffice.xmerge.merger.DiffAlgorithm;
import org.openoffice.xmerge.merger.Difference;
import org.openoffice.xmerge.merger.NodeMergeAlgorithm;
import org.openoffice.xmerge.merger.Iterator;
import org.openoffice.xmerge.merger.DiffAlgorithm;
import org.openoffice.xmerge.merger.diff.ParaNodeIterator;
import org.openoffice.xmerge.merger.diff.IteratorLCSAlgorithm;
import org.openoffice.xmerge.merger.merge.DocumentMerge;
import org.openoffice.xmerge.merger.merge.CharacterBaseParagraphMerge;
import org.openoffice.xmerge.util.Debug;


/**
 *  Wordsmith implementation of <code>DocumentMerger</code>
 *  for the {@link
 *  org.openoffice.xmerge.converter.xml.sxw.wordsmith.PluginFactoryImpl
 *  PluginFactoryImpl}.</p>
 */
public class DocumentMergerImpl implements DocumentMerger {

    private ConverterCapabilities cc_;
    private org.openoffice.xmerge.Document orig = null;

    public DocumentMergerImpl(org.openoffice.xmerge.Document doc, ConverterCapabilities cc) {
        cc_ = cc;
        this.orig = doc;
    }

    public void merge(org.openoffice.xmerge.Document modifiedDoc) throws MergeException {

        SxwDocument wdoc1 = (SxwDocument) orig;
        SxwDocument wdoc2 = (SxwDocument) modifiedDoc;

        Document doc1 = wdoc1.getContentDOM();
        Document doc2 = wdoc2.getContentDOM();

        Iterator i1 = new ParaNodeIterator(cc_, doc1.getDocumentElement());
        Iterator i2 = new ParaNodeIterator(cc_, doc2.getDocumentElement());

        DiffAlgorithm diffAlgo = new IteratorLCSAlgorithm();

        // find out the paragrah level diffs
        Difference[] diffTable = diffAlgo.computeDiffs(i1, i2);

        if (Debug.isFlagSet(Debug.INFO)) {
            Debug.log(Debug.INFO, "Diff Result: ");

            for (int i = 0; i < diffTable.length; i++) {
                Debug.log(Debug.INFO, diffTable[i].debug());
            }
        }

        // merge the paragraphs
        NodeMergeAlgorithm charMerge = new CharacterBaseParagraphMerge();
        DocumentMerge docMerge = new DocumentMerge(cc_, charMerge);

        Iterator result = null;

        docMerge.applyDifference(i1, i2, diffTable);
    }
}


