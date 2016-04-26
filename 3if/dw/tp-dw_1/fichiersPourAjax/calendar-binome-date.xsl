<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:output method="html" version="1.0" indent="yes"/>
  <xsl:template match="/">
    <ul>
         <li>
 Numéro de binôme : 
        <xsl:value-of select="//NoBinome"/>
      </li>
              <li>
Date : 
        <xsl:value-of select="//date"/>
      </li>
    </ul>
  </xsl:template>

</xsl:stylesheet>







































