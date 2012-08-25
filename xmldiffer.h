#ifndef XMLDIFFER_H
#define XMLDIFFER_H

#include <QObject>
#include <QDomDocument>

#include <treemodel.h>


class XMLDiffer : public QObject
{
    Q_OBJECT
public:

    enum XmlDoc {
        XmlDoc1,
        XmlDoc2
    };

    explicit XMLDiffer(QObject *parent = 0);

    TreeModel *treeModel;

    bool openXmlFile( const QString &path, enum XmlDoc xmlDoc );
    QString xmlDoc( enum XmlDoc xmlDoc );
    void setTree( enum XmlDoc numXmlDoc );

    
signals:
    
public slots:

private:
    QDomDocument *m_xmlDoc1;
    QDomDocument *m_xmlDoc2;
    
};

#endif // XMLDIFFER_H
