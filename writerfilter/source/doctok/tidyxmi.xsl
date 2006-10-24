<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:UML = 'org.omg.xmi.namespace.UML' xml:space="default">
<xsl:output indent="yes"/>
<xsl:template match="/">
<XMI xmi.version="1.2">
  <XMI.header>
    <XMI.documentation/>
  </XMI.header>
  <XMI.content>
    <UML:Model xmlns:UML="org.omg.xmi.namespace.UML" name="WW8Document" >
      <UML:Namespace.ownedElement>
        <xsl:apply-templates select=".//UML:Model/UML:Namespace.ownedElement"/>
      </UML:Namespace.ownedElement>
    </UML:Model>
  </XMI.content>
</XMI>

</xsl:template>

<xsl:template match="UML:Namespace.ownedElement">
  <xsl:comment>Stereotypes </xsl:comment>
  <xsl:copy-of select="UML:Stereotype"/>
  <xsl:comment>Stereotypes</xsl:comment>
  <xsl:comment>Datatypes </xsl:comment>
  <xsl:copy-of select="UML:DataType"/>
  <xsl:comment>Datatypes</xsl:comment>
  <xsl:comment>Tag definitions </xsl:comment>
  <xsl:copy-of select="UML:TagDefinition"/>
  <xsl:comment>Tag definitions </xsl:comment>
  <xsl:comment>Classes without stereotype</xsl:comment>
  <xsl:apply-templates select="UML:Class[count(./UML:ModelElement.stereotype) = 0]"/>  
  <xsl:comment>Classes without stereotype</xsl:comment>
  <xsl:comment>Resources</xsl:comment>
  <xsl:copy-of select="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='resource']"/>
  <xsl:comment>Resources</xsl:comment>
  <xsl:comment>WW8 resources</xsl:comment>
  <xsl:apply-templates select="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='ww8resource' and count(UML:ModelElement.stereotype/UML:Stereotype[@xmi.idref='ww8sprm']) = 0]"/>
  <xsl:comment>WW8 resources</xsl:comment>
  <xsl:comment>SPRMS</xsl:comment>
  <xsl:apply-templates select="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='ww8sprm']"/>
  <xsl:comment>SPRMS</xsl:comment>
  <xsl:comment>DFFS</xsl:comment>
  <xsl:apply-templates select="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='dffrecord']"/>
  <xsl:comment>DFFS</xsl:comment>
  <xsl:comment>DFFOPT</xsl:comment>
  <xsl:apply-templates select="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='dffopt']"/>
  <xsl:comment>DFFOPT</xsl:comment>
</xsl:template>

<xsl:template match="UML:Class[count(UML:ModelElement.stereotype) = 0]">
  <xsl:variable name="theid"><xsl:value-of select="@xmi.id"/></xsl:variable>
  <xsl:comment>Class <xsl:value-of select="@xmi.id"/></xsl:comment>
  <xsl:copy-of select="."/>
  <xsl:copy-of select="//UML:Generalization[UML:Generalization.child/UML:Class/@xmi.idref=$theid]"/>
  <xsl:comment>Class <xsl:value-of select="@xmi.id"/></xsl:comment>
</xsl:template>

<xsl:template match="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='ww8resource' and count(UML:ModelElement.stereotype/UML:Stereotype[@xmi.idref='ww8sprm']) = 0]">
  <xsl:variable name="theid"><xsl:value-of select="@xmi.id"/></xsl:variable>
  <xsl:comment>Class <xsl:value-of select="@xmi.id"/></xsl:comment>
  <xsl:copy-of select="."/>
  <xsl:copy-of select="//UML:Generalization[UML:Generalization.child/UML:Class/@xmi.idref=$theid]"/>
  <xsl:comment>Class <xsl:value-of select="@xmi.id"/></xsl:comment>
</xsl:template>

<xsl:template match="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='ww8sprm']">
  <xsl:variable name="theid"><xsl:value-of select="@xmi.id"/></xsl:variable>
  <xsl:comment>SPRM <xsl:value-of select="@xmi.id"/></xsl:comment>
  <xsl:copy-of select="."/>
  <xsl:copy-of select="//UML:Generalization[UML:Generalization.child/UML:Class/@xmi.idref=$theid]"/>
  <xsl:comment>SPRM <xsl:value-of select="@xmi.id"/></xsl:comment>
</xsl:template>

<xsl:template match="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='dffrecord']">
  <xsl:variable name="theid"><xsl:value-of select="@xmi.id"/></xsl:variable>
  <xsl:comment>DFF <xsl:value-of select="@xmi.id"/></xsl:comment>
  <xsl:copy-of select="."/>
  <xsl:copy-of select="//UML:Generalization[UML:Generalization.child/UML:Class/@xmi.idref=$theid]"/>
  <xsl:comment>DFF <xsl:value-of select="@xmi.id"/></xsl:comment>
</xsl:template>

<xsl:template match="UML:Class[UML:ModelElement.stereotype/UML:Stereotype/@xmi.idref='dffopt']">
  <xsl:variable name="theid"><xsl:value-of select="@xmi.id"/></xsl:variable>
  <xsl:comment>DFFOPT <xsl:value-of select="@xmi.id"/></xsl:comment>
  <xsl:copy-of select="."/>
  <xsl:copy-of select="//UML:Generalization[UML:Generalization.child/UML:Class/@xmi.idref=$theid]"/>
  <xsl:comment>DFFOPT <xsl:value-of select="@xmi.id"/></xsl:comment>
</xsl:template>

</xsl:stylesheet>