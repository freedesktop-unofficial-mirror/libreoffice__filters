/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

package complex.unoxml;

import helper.StreamSimulator;

import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.lang.XServiceInfo;
import com.sun.star.lang.IllegalArgumentException;
import com.sun.star.lang.WrappedTargetException;
import com.sun.star.lang.WrappedTargetRuntimeException;
import com.sun.star.beans.XPropertySet;
import com.sun.star.beans.Pair;
import com.sun.star.beans.StringPair;
import com.sun.star.container.XEnumeration;
import com.sun.star.container.ElementExistException;
import com.sun.star.container.NoSuchElementException;
import com.sun.star.io.XInputStream;
import com.sun.star.io.XOutputStream;
import com.sun.star.text.XTextRange;
import com.sun.star.text.XText;
import com.sun.star.rdf.*;
import lib.TestParameters;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import org.openoffice.test.OfficeConnection;
import static org.junit.Assert.*;

/**
 * Test case for service com.sun.star.rdf.Repository
 * Currently, this service is implemented in
 * unoxml/source/rdf/librdf_repository.cxx
 * 
 * @author mst
 */
public class RDFRepositoryTest
{
    XComponentContext xContext;
    String tempDir;

    XDocumentRepository xRep;
    XURI foo;
    XURI bar;
    XURI baz;
    XURI uint;
    XURI rdfslabel;
    XURI manifest;
    XURI uuid;
    XURI base;
    XBlankNode blank;
    XLiteral lit;
    XLiteral litlang;
    XLiteral littype;
    String rdfs = "http://www.w3.org/2000/01/rdf-schema#";

    /**
     * The test parameters
     */
    private static TestParameters param = null;

//    public String[] getTestMethodNames ()
//    {
//        return new String[] { "check", "checkSPARQL", "checkRDFa" };
//    }

    @Before public void before()
    {
        try {
            XMultiServiceFactory xMSF = getMSF();
            param = new TestParameters();
            param.put("ServiceFactory", xMSF);

            assertNotNull("could not create MultiServiceFactory.", xMSF);
            XPropertySet xPropertySet = UnoRuntime.queryInterface(XPropertySet.class, xMSF);
            Object defaultCtx = xPropertySet.getPropertyValue("DefaultContext");
            xContext = UnoRuntime.queryInterface(XComponentContext.class, defaultCtx);
            assertNotNull("could not get component context.", xContext);

            tempDir = util.utils.getOfficeTemp/*Dir*/(xMSF);
            System.out.println("tempdir: " + tempDir);

            foo = URI.create(xContext, "uri:foo");
            assertNotNull("foo", foo);
            bar = URI.create(xContext, "uri:bar");
            assertNotNull("bar", bar);
            baz = URI.create(xContext, "uri:baz");
            assertNotNull("baz", baz);
            uint = URI.create(xContext, "uri:int");
            assertNotNull("uint", uint);
            blank = BlankNode.create(xContext, "_:uno");
            assertNotNull("blank", blank);
            lit = Literal.create(xContext, "i am the literal");
            assertNotNull("lit", lit);
            litlang = Literal.createWithLanguage(xContext,
                "i am the literal", "en");
            assertNotNull("litlang", litlang);
            littype = Literal.createWithType(xContext, "42", uint);
            assertNotNull("littype", littype);

            rdfslabel = URI.create(xContext, rdfs + "label");
            assertNotNull("rdfslabel", rdfslabel);
            manifest = URI.create(xContext, "manifest:manifest"); //FIXME
            assertNotNull("manifest", manifest);
            uuid = URI.create(xContext,
                "urn:uuid:224ab023-77b8-4396-a75a-8cecd85b81e3");
            assertNotNull("uuid", uuid);
            base = URI.create(xContext, "base-uri:"); //FIXME
            assertNotNull("base", base);
        } catch (Exception e) {
            report(e);
        }
        //FIXME: ?
//            xRep = Repository.create(xContext);
        System.out.println("Creating service Repository...");
        xRep = UnoRuntime.queryInterface(XDocumentRepository.class, Repository.create(xContext));
        assertNotNull("null", xRep);
        System.out.println("...done");
    }

    @After public void after()
    {
        xRep = null;
    }

    @Test public void check()
    {
        try {
            System.out.println("Checking that new repository is really empty...");
            assertTrue("empty: graphs", 0 == xRep.getGraphNames().length);

            XEnumeration stmts;
            stmts = xRep.getStatements(null, null, null);
            assertTrue("empty: stmts", !stmts.hasMoreElements());

            System.out.println("...done");

            System.out.println("Checking graph creation...");

            XNamedGraph xFooGraph = xRep.createGraph(foo);
            assertNotNull("foo graph", xFooGraph);

            try {
                xRep.createGraph(foo);
                assertFalse("creating duplicate graph was allowed", false);
            } catch (ElementExistException e) {
                // ignore
            }

            try {
                xRep.createGraph(null);
                assertFalse("invalid graph name was allowed", false);
            } catch (IllegalArgumentException e) {
                // ignore
            }

            XURI[] names = xRep.getGraphNames();
            assertTrue("no foo graph in getGraphNames",
                1 == names.length && eq(names[0], foo));
            assertNotNull("no foo graph", xRep.getGraph(foo));

            stmts = xFooGraph.getStatements(null, null, null);
            assertTrue("stmts in foo graph", !stmts.hasMoreElements());

            XOutputStream xFooOut =
                new StreamSimulator(tempDir + "empty.rdf", false, param);
            xRep.exportGraph(FileFormat.RDF_XML, xFooOut, foo, base);
            xFooOut.closeOutput();

            XInputStream xFooIn =
                new StreamSimulator(tempDir + "empty.rdf", true, param);
            xRep.importGraph(FileFormat.RDF_XML, xFooIn, bar, base);
            assertNotNull("no bar graph", xRep.getGraph(bar));

            System.out.println("...done");

            System.out.println("Checking graph manipulation...");

            XEnumeration xFooEnum;

            Statement xFoo_FooBarBaz = new Statement(foo, bar, baz, foo);
            xFooGraph.addStatement(foo, bar, baz);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,baz)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz }));

            Statement xFoo_FooBarBlank = new Statement(foo, bar, blank, foo);
            xFooGraph.addStatement(foo, bar, blank);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,blank)",
                eq(xFooEnum,
                    new Statement[] { xFoo_FooBarBaz, xFoo_FooBarBlank }));
            xFooEnum = xRep.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,blank) (global)",
                eq(xFooEnum,
                    new Statement[] { xFoo_FooBarBaz, xFoo_FooBarBlank }));

            Statement xFoo_BazBarLit = new Statement(baz, bar, lit, foo);
            xFooGraph.addStatement(baz, bar, lit);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(baz,bar,lit)",
                eq(xFooEnum, new Statement[] {
                    xFoo_FooBarBaz, xFoo_FooBarBlank, xFoo_BazBarLit }));
            xFooEnum = xFooGraph.getStatements(baz, bar, null);
            assertTrue("addStatement(baz,bar,lit) (baz,bar)",
                eq(xFooEnum, new Statement[] { xFoo_BazBarLit }));

            Statement xFoo_BazBarLitlang =
                new Statement(baz, bar, litlang, foo);
            xFooGraph.addStatement(baz, bar, litlang);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(baz,bar,litlang)",
                eq(xFooEnum, new Statement[] {
                    xFoo_FooBarBaz, xFoo_FooBarBlank, xFoo_BazBarLit,
                    xFoo_BazBarLitlang }));
            xFooEnum = xFooGraph.getStatements(null, null, baz);
            assertTrue("addStatement(baz,bar,litlang) (baz)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz }));

            Statement xFoo_BazBarLittype =
                new Statement(baz, bar, littype, foo);
            xFooGraph.addStatement(baz, bar, littype);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(baz,bar,littype)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz, xFoo_FooBarBlank,
                    xFoo_BazBarLit, xFoo_BazBarLitlang, xFoo_BazBarLittype }));

            xFooGraph.removeStatements(baz, bar, litlang);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("removeStatement(baz,bar,litlang)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz, xFoo_FooBarBlank,
                    xFoo_BazBarLit, xFoo_BazBarLittype }));

            xFooGraph.removeStatements(foo, bar, null);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("removeStatement(foo,bar,null)",
                eq(xFooEnum, new Statement[] {
                    xFoo_BazBarLit, xFoo_BazBarLittype }));

            xFooGraph.addStatement(foo, bar, baz);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,baz) (re-add)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz,
                    xFoo_BazBarLit, xFoo_BazBarLittype }));

            xFooGraph.addStatement(foo, bar, baz);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,baz) (duplicate)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz,
                    xFoo_BazBarLit, xFoo_BazBarLittype }));

            xFooGraph.addStatement(xFooGraph, bar, baz);
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("addStatement(foo,bar,baz) (triplicate, as graph)",
                eq(xFooEnum, new Statement[] { xFoo_FooBarBaz,
                     xFoo_BazBarLit, xFoo_BazBarLittype }));

            System.out.println("...done");

            System.out.println("Checking graph import/export...");

            xFooOut = new StreamSimulator(tempDir + "foo.rdf", false, param);
            xRep.exportGraph(FileFormat.RDF_XML, xFooOut, foo, base);
            xFooOut.closeOutput();

            xFooIn = new StreamSimulator(tempDir + "foo.rdf", true, param);
            try {
                xRep.importGraph(FileFormat.RDF_XML, xFooIn, bar, base);
                assertFalse("importing existing graph did not fail", false);
            } catch (ElementExistException e) {
                // ignore
            }

            xFooIn = new StreamSimulator(tempDir + "foo.rdf", true, param);
            xRep.importGraph(FileFormat.RDF_XML, xFooIn, baz, base);
            XNamedGraph xBazGraph =  xRep.getGraph(baz);
            assertNotNull("no baz graph", xBazGraph);

            Statement xBaz_FooBarBaz = new Statement(foo, bar, baz, baz);
            Statement xBaz_BazBarLit = new Statement(baz, bar, lit, baz);
            Statement xBaz_BazBarLittype =
                new Statement(baz, bar, littype, baz);
            XEnumeration xBazEnum = xBazGraph.getStatements(null, null, null);
            assertTrue("importing exported graph",
                eq(xBazEnum, new Statement[] {
                     xBaz_FooBarBaz, xBaz_BazBarLit, xBaz_BazBarLittype }));

            System.out.println("...done");

            System.out.println("Checking graph deletion...");

            xFooGraph.clear();
            xFooEnum = xFooGraph.getStatements(null, null, null);
            assertTrue("clear", eq(xFooEnum, new Statement[] { }));

            xRep.destroyGraph(baz);
            assertNull("baz graph zombie", xRep.getGraph(baz));

            try {
                xBazGraph.clear();
                assertFalse("deleted graph not invalid (clear)", false);
            } catch (NoSuchElementException e) {
                // ignore
            }

            try {
                xBazGraph.addStatement(foo, foo, foo);
                assertFalse("deleted graph not invalid (add)", false);
            } catch (NoSuchElementException e) {
                // ignore
            }

            try {
                xBazGraph.removeStatements(null, null, null);
                assertFalse("deleted graph not invalid (remove)", false);
            } catch (NoSuchElementException e) {
                // ignore
            }

            try {
                xBazGraph.getStatements(null, null, null);
                assertFalse("deleted graph not invalid (get)", false);
            } catch (NoSuchElementException e) {
                // ignore
            }

            System.out.println("...done");

        } catch (Exception e) {
            report(e);
        }
    }

    @Test
    public void checkSPARQL()
    {
        try {

            System.out.println("Checking SPARQL queries...");

            XInputStream xIn = new StreamSimulator(TestDocument.getUrl("example.rdf"), true, param);
                // util.utils.getFullTestDocName("example.rdf"), true, param);
            xRep.importGraph(FileFormat.RDF_XML, xIn, manifest, base);

            String query;
            query = "SELECT ?p WHERE { ?p rdf:type pkg:Package . }";
            XQuerySelectResult result = xRep.querySelect(mkNss() + query);
            assertTrue("query: package-id\n" + query,
                eq(result, new String[] { "p" },
                    new XNode[][] { { uuid } }));

            query = "SELECT ?part ?path FROM <" + manifest +
               "> WHERE { ?pkg rdf:type pkg:Package . ?pkg pkg:hasPart ?part ."
               + " ?part pkg:path ?path . ?part rdf:type odf:ContentFile. }";
            result = xRep.querySelect(mkNss() + query);
            assertTrue("query: contentfile",
                eq(result, new String[] { "part", "path" },
                    new XNode[][] { { BlankNode.create(xContext, "whatever"),
                            Literal.create(xContext, "content.xml") } }));

            query = "SELECT ?pkg ?path FROM <" + toS(manifest) +  "> WHERE { "
                + "?pkg rdf:type pkg:Package . ?pkg pkg:hasPart ?part . "
                + "?part pkg:path ?path . ?part rdf:type odf:ContentFile. }";
            result = xRep.querySelect(mkNss() + query);
            assertTrue("query: contentfile\n" + query,
                eq(result, new String[] { "pkg", "path" },
                    new XNode[][] { { uuid ,
                            Literal.create(xContext, "content.xml") } }));

            query = "SELECT ?part ?path FROM <" + toS(manifest) + "> WHERE { "
                + "?pkg rdf:type pkg:Package . ?pkg pkg:hasPart ?part . "
                + "?part pkg:path ?path . ?part rdf:type odf:StylesFile. }";
            result = xRep.querySelect(mkNss() + query);
            assertTrue("query: stylesfile\n" + query,
                eq(result, new String[] { "part", "path" },
                    new XNode[][] { }));

            query = "SELECT ?part ?path FROM <" + toS(manifest) + "> WHERE { "
                + "?pkg rdf:type pkg:Package . ?pkg pkg:hasPart ?part . "
                + "?part pkg:path ?path . ?part rdf:type odf:MetadataFile. }";
            result = xRep.querySelect(mkNss() + query);
            assertTrue("query: metadatafile\n" + query,
                eq(result, new String[] { "part", "path" },
                    new XNode[][] { {
                        URI.create(xContext, "http://hospital-employee/doctor"),
                        Literal.create(xContext,
                            "meta/hospital/doctor.rdf") } }));

//FIXME redland BUG
            String uri = "uri:example-element-2";
            query = "SELECT ?path ?idref FROM <" + toS(manifest) +  "> WHERE { "
//                + "<" + toS(uuid) + "> rdf:type pkg:Package ; "
//                                 + " pkg:hasPart ?part . "
                + "<" + toS(uuid) + "> pkg:hasPart ?part . "
                + "?part pkg:path ?path ; "
                     + " rdf:type ?type ; "
                     + " pkg:hasPart <" + uri + "> . "
//                + "<" + uri + "> rdf:type odf:Element ; "
                + "<" + uri + "> "
                      + " pkg:idref ?idref . "
                + " FILTER (?type = odf:ContentFile || ?type = odf:StylesFile)"
                + " }";
//System.out.println(query);
            result = xRep.querySelect(mkNss() + query);
            assertTrue("query: example-element-2\n" + query,
                eq(result, new String[] { "path", "idref" },
                    new XNode[][] { {
                        Literal.create(xContext, "content.xml"),
                        Literal.create(xContext, "ID_B") } }));

            // CONSTRUCT result triples have no graph!
            Statement x_PkgFooLit = new Statement(uuid, foo, lit, null);
            query = "CONSTRUCT { ?pkg <" + toS(foo) + "> \"" +
                lit.getStringValue() + "\" } FROM <" + toS(manifest) +
                "> WHERE { ?pkg rdf:type pkg:Package . } ";
            XEnumeration xResultEnum = xRep.queryConstruct(mkNss() + query);
            assertTrue("query: construct\n" + query,
                eq(xResultEnum, new Statement[] { x_PkgFooLit }));

            query = "ASK { ?pkg rdf:type pkg:Package . }";
            boolean bResult = xRep.queryAsk(mkNss() + query);
            assertTrue("query: ask\n" + query, bResult);

            System.out.println("...done");

        } catch (Exception e) {
            report(e);
        }
    }

    @Test public void checkRDFa()
    {
        try {
            System.out.println("Checking RDFa gunk...");

            String content = "behold, for i am the content.";
            XTextRange xTR = new TestRange(content);
            XMetadatable xM = (XMetadatable) xTR;

            Pair<Statement[], Boolean> result =
                xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: not empty (initial)",
                0 == result.First.length);

            try {
                xRep.setStatementRDFa(foo, new XURI[] {}, xM, "", null);
                assertFalse("RDFa: set: no predicate", false);
            } catch (IllegalArgumentException e) {
                // ignore
            }

            try {
                xRep.setStatementRDFa(foo, new XURI[] {bar}, null, "", null);
                assertFalse("RDFa: set: null", false);
            } catch (IllegalArgumentException e) {
                // ignore
            }

            XLiteral trlit = Literal.create(xContext, content);
            Statement x_FooBarTRLit = new Statement(foo, bar, trlit, null);
            xRep.setStatementRDFa(foo, new XURI[] { bar }, xM, "", null);

            result = xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: without content",
                !result.Second && (1 == result.First.length)
                && eq(result.First[0], x_FooBarTRLit));

            //FIXME: do this?
            xTR.setString(lit.getStringValue());
/*
            Statement xFooBarLit = new Statement(foo, bar, lit, null);
            result = xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: change",
                eq((Statement)result.First, xFooBarLit) && null == result.Second);
*/

            Statement x_FooBarLittype = new Statement(foo, bar, littype, null);
            xRep.setStatementRDFa(foo, new XURI[] { bar }, xM, "42", uint);

            result = xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: with content",
                result.Second &&
                (1 == result.First.length) &&
                eq(result.First[0], x_FooBarLittype));

            //FIXME: do this?
            xTR.setString(content);
/*
            Statement xFooLabelTRLit = new Statement(foo, rdfslabel, trlit, null);
            result = xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: change (label)",
                eq((Statement)result.First, xFooBarLittype) &&
                eq((Statement)result.Second, xFooLabelTRLit));
*/

            xRep.removeStatementRDFa((XMetadatable)xTR);

            result = xRep.getStatementRDFa((XMetadatable)xTR);
            assertTrue("RDFa: get: not empty (removed)",
                0 == result.First.length);

            xRep.setStatementRDFa(foo, new XURI[] { foo, bar, baz }, xM,
                "", null);

            Statement x_FooFooTRLit = new Statement(foo, foo, trlit, null);
            Statement x_FooBazTRLit = new Statement(foo, baz, trlit, null);
            result = xRep.getStatementRDFa((XMetadatable) xTR);
            assertTrue("RDFa: get: without content (multiple predicates, reinsert)",
                !result.Second &&
                eq(result.First, new Statement[] {
                     x_FooFooTRLit, x_FooBarTRLit, x_FooBazTRLit }));

            xRep.removeStatementRDFa((XMetadatable)xTR);

            result = xRep.getStatementRDFa((XMetadatable) xTR);
            assertTrue("RDFa: get: not empty (re-removed)",
                0 == result.First.length);

            System.out.println("...done");

        } catch (Exception e) {
            report(e);
        }
    }

// utilities -------------------------------------------------------------

    public void report2(Exception e)
    {
        if (e instanceof WrappedTargetException)
        {
            System.out.println("Cause:");
            Exception cause = (Exception)
                (((WrappedTargetException)e).TargetException);
            System.out.println(cause.toString());
            report2(cause);
        } else if (e instanceof WrappedTargetRuntimeException) {
            System.out.println("Cause:");
            Exception cause = (Exception)
                (((WrappedTargetRuntimeException)e).TargetException);
            System.out.println(cause.toString());
            report2(cause);
        }
    }

    public void report(Exception e) {
        System.out.println("Exception occurred:");
        e.printStackTrace();
        report2(e);
        fail();
    }

    public static String toS(XNode n) {
        if (null == n)
        {
            return "< null >";
        }
        return n.getStringValue();
    }

    static boolean isBlank(XNode i_node)
    {
        XBlankNode blank = UnoRuntime.queryInterface(XBlankNode.class, i_node);
        return blank != null;
    }

/*
    static class Statement implements XStatement
    {
        XResource m_Subject;
        XResource m_Predicate;
        XNode m_Object;
        XURI m_Graph;

        Statement(XResource i_Subject, XResource i_Predicate, XNode i_Object,
            XURI i_Graph)
        {
            m_Subject = i_Subject;
            m_Predicate = i_Predicate;
            m_Object = i_Object;
            m_Graph = i_Graph;
        }

        public XResource getSubject() { return m_Subject; }
        public XResource getPredicate() { return m_Predicate; }
        public XNode getObject() { return m_Object; }
        public XURI getGraph() { return m_Graph; }
    }
*/

    static Statement[] toSeq(XEnumeration i_Enum) throws Exception
    {
        java.util.Collection c = new java.util.Vector();
        while (i_Enum.hasMoreElements()) {
            Statement s = (Statement) i_Enum.nextElement();
//System.out.println("toSeq: " + s.getSubject().getStringValue() + " " + s.getPredicate().getStringValue() + " " + s.getObject().getStringValue() + ".");
            c.add(s);
        }
//        return (Statement[]) c.toArray();
        // java sucks
        Object[] arr = c.toArray();
        Statement[] ret = new Statement[arr.length];
        for (int i = 0; i < arr.length; ++i) {
            ret[i] = (Statement) arr[i];
        }
        return ret;
    }

    static XNode[][] toSeqs(XEnumeration i_Enum) throws Exception
    {
        java.util.Collection c = new java.util.Vector();
        while (i_Enum.hasMoreElements()) {
            XNode[] s = (XNode[]) i_Enum.nextElement();
            c.add(s);
        }
//        return (XNode[][]) c.toArray();
        Object[] arr = c.toArray();
        XNode[][] ret = new XNode[arr.length][];
        for (int i = 0; i < arr.length; ++i) {
            ret[i] = (XNode[]) arr[i];
        }
        return ret;
    }

    static class BindingComp implements java.util.Comparator
    {
        public int compare(Object i_Left, Object i_Right)
        {
            XNode[] left = (XNode[]) i_Left;
            XNode[] right = (XNode[]) i_Right;
            if (left.length != right.length)
            {
                throw new RuntimeException();
            }
            for (int i = 0; i < left.length; ++i) {
                int eq = (left[i].getStringValue().compareTo(
                            right[i].getStringValue()));
                if (eq != 0) return eq;
            }
            return 0;
        }
    }

    static class StmtComp implements java.util.Comparator
    {
        public int compare(Object i_Left, Object i_Right)
        {
            int eq;
            Statement left = (Statement) i_Left;
            Statement right = (Statement) i_Right;
            if ((eq = cmp(left.Graph,     right.Graph    )) != 0)
            {
                return eq;
            }
            if ((eq = cmp(left.Subject,   right.Subject  )) != 0)
            {
                return eq;
            }
            if ((eq = cmp(left.Predicate, right.Predicate)) != 0)
            {
                return eq;
            }
            if ((eq = cmp(left.Object,    right.Object   )) != 0)
            {
                return eq;
            }
            return 0;
        }

        public int cmp(XNode i_Left, XNode i_Right)
        {
            if (isBlank(i_Left)) {
                return isBlank(i_Right) ? 0 : 1;
            } else {
                if (isBlank(i_Right)) {
                    return -1;
                } else {
                    return toS(i_Left).compareTo(toS(i_Right));
                }
            }
        }
    }

    static boolean eq(Statement i_Left, Statement i_Right)
    {
        XURI lG = i_Left.Graph;
        XURI rG = i_Right.Graph;
        if (!eq(lG, rG)) {
            System.out.println("Graphs differ: " + toS(lG) + " != " + toS(rG));
            return false;
        }
        if (!eq(i_Left.Subject, i_Right.Subject)) {
            System.out.println("Subjects differ: " +
                i_Left.Subject.getStringValue() + " != " +
                i_Right.Subject.getStringValue());
            return false;
        }
        if (!eq(i_Left.Predicate, i_Right.Predicate)) {
            System.out.println("Predicates differ: " +
                i_Left.Predicate.getStringValue() + " != " +
                i_Right.Predicate.getStringValue());
            return false;
        }
        if (!eq(i_Left.Object, i_Right.Object)) {
            System.out.println("Objects differ: " +
                i_Left.Object.getStringValue() + " != " +
                i_Right.Object.getStringValue());
            return false;
        }
        return true;
    }

    static boolean eq(Statement[] i_Result, Statement[] i_Expected)
    {
        if (i_Result.length != i_Expected.length) {
            System.out.println("eq: different lengths: " + i_Result.length + " " +
                i_Expected.length);
            return false;
        }
        Statement[] expected = (Statement[])
            java.util.Arrays.asList(i_Expected).toArray();
        java.util.Arrays.sort(i_Result, new StmtComp());
        java.util.Arrays.sort(expected, new StmtComp());
        for (int i = 0; i < expected.length; ++i) {
            if (!eq(i_Result[i], expected[i]))
            {
                return false;
            }
        }
        return true;
    }

    static boolean eq(XEnumeration i_Enum, Statement[] i_Expected)
        throws Exception
    {
        Statement[] current = toSeq(i_Enum);
        return eq(current, i_Expected);
    }

    static boolean eq(XNode i_Left, XNode i_Right)
    {
        if (i_Left == null) {
            return (i_Right == null);
        } else {
            return (i_Right != null) &&
                (i_Left.getStringValue().equals(i_Right.getStringValue())
                // FIXME: hack: blank nodes considered equal
                || (isBlank(i_Left) && isBlank(i_Right)));
        }
    }

    static boolean eq(XQuerySelectResult i_Result,
            String[] i_Vars, XNode[][] i_Bindings) throws Exception
    {
        String[] vars = (String[]) i_Result.getBindingNames();
        XEnumeration iter = (XEnumeration) i_Result;
        XNode[][] bindings = toSeqs(iter);
        if (vars.length != i_Vars.length) {
            System.out.println("var lengths differ");
            return false;
        }
        if (bindings.length != i_Bindings.length) {
            System.out.println("binding lengths differ: " + i_Bindings.length +
                " vs " + bindings.length );
            return false;
        }
        java.util.Arrays.sort(bindings, new BindingComp());
        java.util.Arrays.sort(i_Bindings, new BindingComp());
        for (int i = 0; i < i_Bindings.length; ++i) {
            if (i_Bindings[i].length != i_Vars.length) {
                System.out.println("TEST ERROR!");
                throw new Exception();
            }
            if (bindings[i].length != i_Vars.length) {
                System.out.println("binding length and var length differ");
                return false;
            }
            for (int j = 0; j < i_Vars.length; ++j) {
                if (!eq(bindings[i][j], i_Bindings[i][j])) {
                    System.out.println("bindings differ: " +
                        toS(bindings[i][j]) + " != " + toS(i_Bindings[i][j]));
                    return false;
                }
            }
        }
        for (int i = 0; i < i_Vars.length; ++i) {
            if (!vars[i].equals(i_Vars[i])) {
                System.out.println("variable names differ: " +
                    vars[i] + " != " + i_Vars[i]);
                return false;
            }
        }
        return true;
    }

    static String mkNamespace(String i_prefix, String i_namespace)
    {
        return "PREFIX " + i_prefix + ": <" + i_namespace + ">\n";
    }

    static String mkNss()
    {
        String namespaces = mkNamespace("rdf",
            "http://www.w3.org/1999/02/22-rdf-syntax-ns#");
        namespaces += mkNamespace("pkg",
            "http://docs.oasis-open.org/opendocument/meta/package/common#");
        namespaces += mkNamespace("odf",
            "http://docs.oasis-open.org/opendocument/meta/package/odf#");
        return namespaces;
    }

    class TestRange implements XTextRange, XMetadatable, XServiceInfo
    {
        String m_Stream;
        String m_XmlId;
        String m_Text;
        TestRange(String i_Str) { m_Text = i_Str; }

        public String getStringValue() { return ""; }
        public String getNamespace() { return ""; }
        public String getLocalName() { return ""; }

        public StringPair getMetadataReference()
            { return new StringPair(m_Stream, m_XmlId); }
        public void setMetadataReference(StringPair i_Ref)
            throws IllegalArgumentException
            { m_Stream = i_Ref.First; m_XmlId = i_Ref.Second; }
        public void ensureMetadataReference()
            { m_Stream = "content.xml"; m_XmlId = "42"; }

        public String getImplementationName() { return null; }
        public String[] getSupportedServiceNames() { return null; }
        public boolean supportsService(String i_Svc)
            { return i_Svc.equals("com.sun.star.text.Paragraph"); }

        public XText getText() { return null; }
        public XTextRange getStart() { return null; }
        public XTextRange getEnd() { return null; }
        public String getString() { return m_Text; }
        public void setString(String i_Str) { m_Text = i_Str; }
    }

        private XMultiServiceFactory getMSF()
    {
        final XMultiServiceFactory xMSF1 = UnoRuntime.queryInterface(XMultiServiceFactory.class, connection.getComponentContext().getServiceManager());
        return xMSF1;
    }

    // setup and close connections
    @BeforeClass public static void setUpConnection() throws Exception {
        System.out.println("setUpConnection()");
        connection.setUp();
    }

    @AfterClass public static void tearDownConnection()
        throws InterruptedException, com.sun.star.uno.Exception
    {
        System.out.println("tearDownConnection()");
        connection.tearDown();
    }

    private static final OfficeConnection connection = new OfficeConnection();
}

