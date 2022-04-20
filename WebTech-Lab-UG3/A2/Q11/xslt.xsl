<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">

    <html>
        <head>
            <title>XML to HTML DATA</title>
        </head>

        <body>
            <h1>XML to HTML using XSLT</h1>
            <xsl:for-each select="question-paper/question">
                <h2>
                    <xsl:value-of select="@no"/>)
                    <xsl:value-of select="text"/> 
                </h2>
                <p>A) <xsl:value-of select="optionA"/></p>
                <p>B) <xsl:value-of select="optionB"/></p>
                <p>C) <xsl:value-of select="optionC"/></p>
                <p>D) <xsl:value-of select="optionD"/></p>
                <p>The Answer is <xsl:value-of select="answer/@value"/></p>
            </xsl:for-each>
        </body>
    </html>

</xsl:template>

</xsl:stylesheet>