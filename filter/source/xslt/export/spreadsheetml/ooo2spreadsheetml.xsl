<?xml version="1.0" encoding="UTF-8"?>
<!--

    OpenOffice.org - a multi-platform office productivity suite
 
    $RCSfile: ooo2spreadsheetml.xsl,v $
 
    $Revision: 1.4 $
 
    last change: $Author: rt $ $Date: 2005-09-08 22:03:54 $
 
    The Contents of this file are made available subject to
    the terms of GNU Lesser General Public License Version 2.1.
 
 
      GNU Lesser General Public License Version 2.1
      =============================================
      Copyright 2005 by Sun Microsystems, Inc.
      901 San Antonio Road, Palo Alto, CA 94303, USA
 
      This library is free software; you can redistribute it and/or
      modify it under the terms of the GNU Lesser General Public
      License version 2.1, as published by the Free Software Foundation.
 
      This library is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
      Lesser General Public License for more details.
 
      You should have received a copy of the GNU Lesser General Public
      License along with this library; if not, write to the Free Software
      Foundation, Inc., 59 Temple Place, Suite 330, Boston,
      MA  02111-1307  USA
 
-->
<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:chart="urn:oasis:names:tc:opendocument:xmlns:chart:1.0"
	xmlns:config="urn:oasis:names:tc:opendocument:xmlns:config:1.0"
	xmlns:dc="http://purl.org/dc/elements/1.1/"
	xmlns:dom="http://www.w3.org/2001/xml-events"
	xmlns:dr3d="urn:oasis:names:tc:opendocument:xmlns:dr3d:1.0"
	xmlns:draw="urn:oasis:names:tc:opendocument:xmlns:drawing:1.0"
	xmlns:fo="urn:oasis:names:tc:opendocument:xmlns:xsl-fo-compatible:1.0"
	xmlns:form="urn:oasis:names:tc:opendocument:xmlns:form:1.0"
	xmlns:math="http://www.w3.org/1998/Math/MathML"
	xmlns:meta="urn:oasis:names:tc:opendocument:xmlns:meta:1.0"
	xmlns:number="urn:oasis:names:tc:opendocument:xmlns:datastyle:1.0"
	xmlns:office="urn:oasis:names:tc:opendocument:xmlns:office:1.0"
	xmlns:ooo="http://openoffice.org/2004/office"
	xmlns:oooc="http://openoffice.org/2004/calc"
	xmlns:ooow="http://openoffice.org/2004/writer"
	xmlns:script="urn:oasis:names:tc:opendocument:xmlns:script:1.0"
	xmlns:style="urn:oasis:names:tc:opendocument:xmlns:style:1.0"
	xmlns:svg="urn:oasis:names:tc:opendocument:xmlns:svg-compatible:1.0"
	xmlns:table="urn:oasis:names:tc:opendocument:xmlns:table:1.0"
	xmlns:text="urn:oasis:names:tc:opendocument:xmlns:text:1.0"
	xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns="urn:schemas-microsoft-com:office:spreadsheet" xmlns:c="urn:schemas-microsoft-com:office:component:spreadsheet" xmlns:html="http://www.w3.org/TR/REC-html40" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet" xmlns:x2="http://schemas.microsoft.com/office/excel/2003/xml" xmlns:x="urn:schemas-microsoft-com:office:excel" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	exclude-result-prefixes="chart config dc dom dr3d draw fo form math meta number office ooo oooc ooow script style svg table text xlink">


	<!--+++++ INCLUDED XSL MODULES +++++-->

	<!-- helper collection, to convert measures (e.g. inch to pixel using DPI (dots per inch) parameter)-->
	<xsl:import  href="../../common/measure_conversion.xsl" />

	<!-- excel table handling -->
	<xsl:include  href="table.xsl" />

	<!-- mapping rules of office style properties to Excel style properties -->
	<xsl:include href="style_mapping.xsl" />

	<!-- creating the Excel styles element  -->
	<xsl:include href="styles.xsl" />

	<!-- mapping formalar Expressions  -->
	<xsl:include href="formular.xsl" />

	<xsl:output method               = "xml"
				indent               = "no"
				encoding             = "UTF-8"
				omit-xml-declaration = "no" />

	<xsl:strip-space elements="ss:Data html:Data" />


	<!-- common table handling -->
	<xsl:variable name="namespace" select="'urn:schemas-microsoft-com:office:spreadsheet'" />

	<!--+++++ PARAMETER SECTION +++++-->

	<!-- OPTIONAL: (MANDATORY: for all input document with relative external links): parameter is a (relative) URL to the target directory.
		 Relative links from the office document (e.g. to external graphics) will get this parameter as a prefix -->
	<xsl:param name="targetBaseURL" select="'./'" />

	<!-- OPTIONAL: (MANDATORY: for input document with relative internal links)
		 To access contents of a office file (content like the meta.xml, styles.xml file or  graphics) a URL could be choosen.
	 This could be even a JAR URL. The sourceBase of the content URL "jar:file:/C:/temp/Test.sxw!/content.xml" would be
	 "jar:file:/C:/temp/Test.sxw!/" for example.
		 When working with OpenOffice API a Package-URL encoded over HTTP can be used to access the jared contents of the the jared document. -->
	<xsl:param name="sourceBaseURL" select="'./'" />

	<!-- OPTIONAL: (MANDATORY: for session management by URL rewriting)
		 Useful for WebApplications: if a HTTP session is not cookie based, URL rewriting is beeing used (the session is appended to the URL).
		 This URL session is used for example when links to graphics are created by XSLT. Otherwise the user havt to log again in for every graphic he liks to see. -->
	<xsl:param name="optionalURLSuffix" />

	<!-- OPTIONAL: URL to office meta file (flat xml use the URL to the input file) -->
	<xsl:param name="metaFileURL" />

	<!-- OPTIONAL: URL to office meta file (flat xml use the URL to the input file) -->
	<xsl:param name="stylesFileURL" />

	<!-- OPTIONAL: in case of using a different processor than a JAVA XSLT, you can unable the Java functionality
		 (e.g. encoding chapter names for the content-table as href and anchors ) -->
	<xsl:param name="java"        select="true()" />
	<xsl:param name="javaEnabled" select="boolean($java)" />

	<!-- OPTIONAL: for activating the debug mode set the variable here to 'true()' or give any value from outside -->
	<xsl:param name="debug"                    select="false()" />
	<xsl:param name="debugEnabled"             select="boolean($debug)" />


	<!-- *************************** -->
	<!-- *** Built up Excel file *** -->
	<!-- *************************** -->
	<xsl:template match="/">
		<xsl:processing-instruction  name="mso-application">progid="Excel.Sheet"</xsl:processing-instruction>
		<!-- Note: for debugging purpose include schema location
		<Workbook xsi:schemaLocation="urn:schemas-microsoft-com:office:spreadsheet <YOUR_SCHEMA_URL>/excelss.xsd"> -->
		<Workbook>
			<!-- adding some default settings -->
			<OfficeDocumentSettings xmlns="urn:schemas-microsoft-com:office:office">
				<DownloadComponents/>
			</OfficeDocumentSettings>
			<ExcelWorkbook xmlns="urn:schemas-microsoft-com:office:excel">
				<WindowHeight>9000</WindowHeight>
				<WindowWidth>13860</WindowWidth>
				<WindowTopX>240</WindowTopX>
				<WindowTopY>75</WindowTopY>
				<ProtectStructure>False</ProtectStructure>
				<ProtectWindows>False</ProtectWindows>
			</ExcelWorkbook>
			<!-- Note: the following handling will exchange the default, later
				<x:ExcelWorkbook>
					<xsl:apply-templates select="table:calculation-settings" />
				</x:ExcelWorkbook>
			-->
			<xsl:element name="Styles">
				<!-- our application default will not be used for export to Excel
				<xsl:apply-templates select="/*/office:styles/style:default-style" mode="styles" />-->
				<xsl:apply-templates select="/*/office:styles/style:style" mode="styles" />
				<xsl:apply-templates select="/*/office:automatic-styles/style:style" mode="styles" >
					<xsl:with-param name="isAutomatic" select="true()" />
				</xsl:apply-templates>
			</xsl:element>
			<xsl:apply-templates select="/*/office:body" />
		</Workbook>
	</xsl:template>

	<xsl:template match="office:body">
		<!-- office:body table:table children are spreadsheets -->
		<xsl:apply-templates />
	</xsl:template>

	<xsl:template match="office:spreadsheet">
		<xsl:apply-templates />
	</xsl:template>

	<!-- Disable default element matching
	<xsl:template match="*" />
	-->

	<!-- office:body table:table children are spreadsheets -->
	<xsl:template match="office:spreadsheet/table:table">
		<xsl:element name="Worksheet">
			<xsl:attribute name="ss:Name">
				<xsl:value-of select="@table:name" />
			</xsl:attribute>
			<xsl:call-template name="table:table" />
		</xsl:element>
	</xsl:template>

	<xsl:template match="table:decls" mode="ExcelWorkbook">
		<xsl:apply-templates mode="ExcelWorkbook" />
	</xsl:template>

	<xsl:template match="table:calculation-settings"  mode="ExcelWorkbook">
		<xsl:if test="table:precision-as-shown">
			<x:PrecisionAsDisplayed/>
		</xsl:if>
		<xsl:if test="table:null-date/@office:date-value='1904-01-01'">
			<x:Date1904/>
		</xsl:if>
		<xsl:apply-templates select="table:iteration" />
	</xsl:template>

	<xsl:template match="table:iteration" mode="ExcelWorkbook">
		<xsl:element name="x:ExcelWorkbook">
			<xsl:if test="@table:status = 'enable'">
				<x:Iteration/>
			</xsl:if>
			<xsl:if test="@table:steps">
				<xsl:element name="x:MaxIterations">
					<xsl:value-of select="@table:steps" />
				</xsl:element>
			</xsl:if>
			<xsl:if test="@table:maximum-difference">
				<xsl:element name="x:MaxChange">
					<xsl:value-of select="@table:maximum-difference" />
				</xsl:element>
			</xsl:if>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>
