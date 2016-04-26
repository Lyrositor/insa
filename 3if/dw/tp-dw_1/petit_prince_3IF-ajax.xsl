<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html" />
  <xsl:param name="language" />
  
  <xsl:template match="/">
    <div style="background-color:white;">
      <xsl:apply-templates select="//infos" />
      <xsl:apply-templates select="//corps" />
    </div>
  </xsl:template>
  
  <xsl:template match="infos/titre">
    <h1 style="text-align:center; color:blue;">
      <xsl:apply-templates />
    </h1>
  </xsl:template>
  
  <xsl:template match="infos/auteur">
    <h2 style="text-align:center; font-style:italic;">
      <xsl:apply-templates />
    </h2>
  </xsl:template>
  
  <xsl:template match="infos">
    <table cellspacing="50" align="center">
      <tbody>
        <tr>
          <td>
            <xsl:apply-templates select="couverture" />
          </td>
          <td>
            <xsl:apply-templates select="titre" />
            <xsl:apply-templates select="auteur" />
            <blockquote style="color:darkgreen;">
              But du TP du <xsl:value-of select="date" />: <xsl:value-of select="but" /><br />
              Auteurs:
              <xsl:variable name="multiBinomes" select="count(//mise_en_forme_par/auteur[not(@NoBinome=preceding::auteur/@NoBinome)])" />
              <xsl:for-each select="mise_en_forme_par/auteur">
                <xsl:value-of select="text()" />
                <xsl:if test="$multiBinomes &gt; 1"> (<xsl:value-of select="@NoBinome" />)</xsl:if>
                <xsl:if test="position() != last()"> et </xsl:if>
              </xsl:for-each>
              <xsl:if test="$multiBinomes = 1"> (<xsl:value-of select="mise_en_forme_par/auteur[1]/@NoBinome" />)</xsl:if>
              <br />
              Email du responsable:
              <xsl:value-of select="email" />
              <br />
            </blockquote>
          </td>
        </tr>
      </tbody>
    </table>
    <hr />
  </xsl:template>
  
  <xsl:template match="infos/couverture">
    <div align="center">
      <img>
        <xsl:attribute name="src">
          <xsl:value-of select="@chemin" />
        </xsl:attribute>
      </img>
    </div>
  </xsl:template>
  
  <xsl:template match="image">
    <div align="center">
      <img>
        <xsl:attribute name="src">
          <xsl:value-of select="@chemin" />
        </xsl:attribute>
      </img>
    </div>
  </xsl:template>
  
  <xsl:template match="paragr">
    <p>
      <xsl:if test="$language != 'hu'">
        <xsl:apply-templates select="phrase[@langue='fr']" />
      </xsl:if>
      <br />
      <xsl:if test="$language != 'fr'">
        <xsl:apply-templates select="phrase[@langue='hu']" />
      </xsl:if>
    </p>
  </xsl:template>
  
  <xsl:template match="corps">
    <h3>Début du texte:</h3>
    <xsl:apply-templates />
    <h3>Fin du texte.</h3>
    <hr />
  </xsl:template>
  
  <xsl:template match="phrase[@langue='fr']">
    <xsl:choose>
      <xsl:when test="contains(text(), 'mouton')">
        <span style="font-size: 24; font-weight: bold;">
          <xsl:value-of select="text()" />
        </span>
        <img src="images/moutonDessin.png" />
      </xsl:when>
      <xsl:otherwise>
        <xsl:value-of select="text()" />
      </xsl:otherwise>
    </xsl:choose>
    <xsl:text> </xsl:text>
  </xsl:template>
  
  <xsl:template match="phrase[@langue='hu']">
    <span style="color:brown; font-style:italic;">
      <xsl:apply-templates />
    </span>
    <xsl:text> </xsl:text>
  </xsl:template>
  
  <xsl:template match="paragr[@type='dialogue']">
    <table width="90%" align="center">
      <tbody>
        <tr>
          <xsl:if test="$language !='hu'">
            <td width="45%">
              <table width="100%" cellpadding="10" border="1">
                <tbody>
                  <xsl:for-each select="phrase[@langue='fr']">
                    <tr>
                      <td width="50">
                        <img src="images/{@locuteur}.png" />
                      </td>
                      <td>
                        <xsl:apply-templates select="." />
                      </td>
                    </tr>
                  </xsl:for-each>
                </tbody>
              </table>
            </td>
          </xsl:if>
          <xsl:if test="$language = ''">
            <td></td>
          </xsl:if>
          <xsl:if test="$language != 'fr'">
            <td width="45%">
              <table width="100%" cellpadding="10" border="1">
                <tbody>
                  <xsl:for-each select="phrase[@langue='hu']">
                    <tr>
                      <td width="50">
                        <img src="images/{@locuteur}.png" />
                      </td>
                      <td>
                        <xsl:apply-templates select="." />
                      </td>
                    </tr>
                  </xsl:for-each>
                </tbody>
              </table>
            </td>
          </xsl:if>
        </tr>
      </tbody>
    </table>
  </xsl:template>
</xsl:stylesheet>
