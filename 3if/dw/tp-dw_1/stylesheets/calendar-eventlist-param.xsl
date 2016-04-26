<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" version="1.0" indent="yes"/>
  <xsl:param name="serie"></xsl:param>
  <xsl:template match="/">
  	<xsl:apply-templates  select="//event[title[contains(.,$serie)]] "></xsl:apply-templates>
  </xsl:template>
  <xsl:template match="//event">
    <ul>
      <li>
        <xsl:element name="a">
          <xsl:attribute name="href">
            <xsl:value-of select="url"/>
          </xsl:attribute>
        </xsl:element>
        <div>
          <h4><xsl:value-of select="title"/></h4>
          <div>
            le <xsl:value-of select="concat(substring(dtstart,7,2),'-',substring(dtstart,5,2),'-',substring(dtstart,0,5),' de ',substring(dtstart,10,2),'h',substring(dtstart,12,2),' à ',substring(dtend,10,2),'h',substring(dtend,12,2))"/></div>
          <div>
            <xsl:element name="a">
              <xsl:attribute name="href">
                <xsl:value-of select="url"/>
              </xsl:attribute>
              <xsl:value-of select='summary'/>
            </xsl:element>
          </div>
          <div><xsl:value-of select='description'/></div>
        </div>
      </li>
    </ul>
  </xsl:template>

</xsl:stylesheet>
