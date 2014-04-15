<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
 xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
 xmlns:xlink="http://www.w3.org/1999/xlink"
    xmlns:foxml="info:fedora/fedora-system:def/foxml#"
     xmlns:eml="eml://ecoinformatics.org/eml-2.1.0"
    exclude-result-prefixes="eml">

   <xsl:template match="foxml:datastream[@ID='EML']/foxml:datastreamVersion[last()]" name="index_EML">
        <xsl:param name="content"/>
        <xsl:param name="prefix">EML_</xsl:param>
        <xsl:param name="suffix">_ms</xsl:param>
        <xsl:for-each select="$content//eml:taxonomicClassification">
            <xsl:variable name="RANKNAME" select="./eml:taxonRankName" />
            <xsl:variable name="RANKVALUE" select="./eml:taxonRankValue" />

            <xsl:if test="$RANKVALUE!= ''">
                <field>
                    <xsl:attribute name="name">
                        <xsl:value-of select="concat($prefix, $RANKNAME, $suffix)"/>
                    </xsl:attribute>
                    <xsl:value-of select="$RANKVALUE"/>
                </field>
           </xsl:if>

        </xsl:for-each>

        <xsl:variable name="NORTH" select="$content//eml:northBoundingCoordinate"/>
        <xsl:variable name="WEST" select="$content//eml:westBoundingCoordinate" />
        
        <xsl:if test="$NORTH!= '' and $WEST!= ''">
            <field>
                <xsl:attribute name="name">
                    <xsl:value-of select="concat($prefix, 'coordinates', $suffix)"/>
                </xsl:attribute>
                <xsl:value-of select="concat($NORTH, ', ', $WEST)"/>
            </field>
        </xsl:if>

	<xsl:variable name="SITENAME" select="$content//eml:geographicDescription"/>
	<xsl:if test="$SITENAME!= ''">
	   <field>
	        <xsl:attribute name="name">
		    <xsl:value-of select="concat($prefix, 'sitename', $suffix)"/>
		</xsl:attribute>
		<xsl:value-of select="$SITENAME"/>
	   </field>
	</xsl:if>

	<xsl:variable name="DEPTH" select="$content//eml:altitudeMinimum"/>
	<xsl:variable name="UNITS" select="$content//eml:altitudeUnits"/>
	<xsl:if test="$DEPTH!= '' and $UNITS!= ''">
	    <field>
		<xsl:attribute name="name">
		    <xsl:value-of select="concat($prefix, 'depth', $suffix)"/>
		</xsl:attribute>
	        <xsl:value-of select="concat($DEPTH, ' ', $UNITS)"/>
	    </field>
	</xsl:if>

	<xsl:variable name="DATE" select="$content//eml:calendarDate"/>
	<xsl:if test="$DATE!= ''">
	    <field>
	    	<xsl:attribute name="name">
		    <xsl:value-of select="concat($prefix, 'date', $suffix)"/>
		</xsl:attribute>
		<xsl:value-of select="$DATE"/>
	    </field>
	</xsl:if>
    </xsl:template>
</xsl:stylesheet>
