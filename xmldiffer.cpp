#include <QFile>

#include <treemodel.h>

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

