/*
 * Copyright (c) 2012, Offox - Oswaldo F. Filho
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 * This product includes software developed by the Offox - Oswaldo F. Filho.
 * 4. Neither the name of the <organization> nor the
 * names of its contributors may be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Offox - Oswaldo F. Filho ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Offox - Oswaldo F. Filho BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QFile>

//#include <treemodel.h>
#include "xmldiffer.h"

XMLDiffer::XMLDiffer(QObject *parent) :
    QObject(parent),
    m_xmlDoc1( 0 ),
    m_xmlDoc2( 0 )
{
}

bool
XMLDiffer::openXmlFile( const QString &path, enum XmlDoc xmlDoc )
{
    if ( xmlDoc == XMLDiffer::XmlDoc1 ) {
        if ( !m_xmlDoc1 )
            m_xmlDoc1 = new QDomDocument("xml");
    } else {
        if ( !m_xmlDoc2 )
            m_xmlDoc2 = new QDomDocument("xml");
    }

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        /* TODO - Logar o erro. */
        return false;
    if ( (xmlDoc == XMLDiffer::XmlDoc1  ? !m_xmlDoc1->setContent(&file) : !m_xmlDoc2->setContent(&file) ) ) {
        /* TODO - Logar o erro. */
        file.close();
        return false;
    }
    file.close();

    return true;
}

QString
XMLDiffer::xmlDoc ( enum XmlDoc xmlDoc )
{
    return xmlDoc == XMLDiffer::XmlDoc1 ?  m_xmlDoc1->toString() :  m_xmlDoc2->toString();
}

void
XMLDiffer::setTree( enum XmlDoc numXmlDoc )
{
    QDomDocument *xmlDoc = numXmlDoc == XMLDiffer::XmlDoc1 ? m_xmlDoc1 : m_xmlDoc2;

    QDomNode root = xmlDoc->documentElement();

    //if ( root.childNodes() )

}

