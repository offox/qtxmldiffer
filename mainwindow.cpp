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

#include <QDebug>
#include <QFile>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "xmldiffer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_xmlFile( 0 )
{
    ui->setupUi(this);

    ui->treeWidget->setColumnCount( 3 );

    QStringList colunmsTitle;
    colunmsTitle << "Tag" << "Value" << "Attributes";

    ui->treeWidget->setHeaderLabels(colunmsTitle);


//    XMLDiffer xmlDiffer1;
//    XMLDiffer xmlDiffer2;

//    if ( xmlDiffer1.openXmlFile( "XMLs/receita-1.xml", XMLDiffer::XmlDoc1 ) ) {
//        ui->texml1->setText( xmlDiffer1.xmlDoc( XMLDiffer::XmlDoc1 ) );
//    }

//    if ( xmlDiffer2.openXmlFile( "XMLs/receita-1.xml", XMLDiffer::XmlDoc2 ) ) {
//        ui->texml2->setText( xmlDiffer2.xmlDoc(XMLDiffer::XmlDoc2 ) );
//    }

    connect(ui->actionOpenXmls, SIGNAL(triggered()), SLOT(openXmlFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void
MainWindow::openXmlFile()
{
     QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home/offox/project",
                                                    tr("Xml (*.xml)"));

     if ( m_xmlFile )
     {
         delete m_xmlFile;
         m_xmlFile = 0;
     }

     m_xmlFile = new QDomDocument("xml");

     QString *error = new QString();

     QFile file(fileName);
     if (!file.open(QIODevice::ReadOnly)) {
         qDebug() << "file.open() error!";
         return;
     }
     if (!m_xmlFile->setContent(&file, error)) {
         qDebug() << "setContent() error: " << error;
         file.close();
         return;
     }
     file.close();

     parserXmlFile();
}

void
MainWindow::parserXmlFile()
{
    //Get the root element
    QDomElement xmlFileElem = m_xmlFile->documentElement();

    // You could check the root tag name here if it matters
    QString rootTag = xmlFileElem.tagName();

    QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(rootTag));

    ui->treeWidget->insertTopLevelItem(0 , item);

    QDomNodeList nodeList = xmlFileElem.childNodes();

    parserNodeList( nodeList, item );

}

void
MainWindow::parserNodeList( QDomNodeList & nodeList, QTreeWidgetItem *parentItem )
{
    if ( nodeList.count() < 2 )
    {
        return;
    }

    QString elTag;
    QString elValue;
    QDomNamedNodeMap elAttributes;
    QDomNodeList childNodeList;
    QTreeWidgetItem *item;

    //Check each node one by one.
    for(int i = 0; i < nodeList.count(); i++)
    {
        // get the current one as QDomElement
        QDomElement el = nodeList.at(i).toElement();
        elTag = el.tagName();
        elValue = el.text();
        elAttributes = el.attributes();

        QString attributes;

        for (int j = 0; j < elAttributes.count(); j++ )
        {
           attributes += elAttributes.item( j ).nodeName();
           attributes += ": \"";
           attributes += elAttributes.item( j ).nodeValue();
           if ( j != elAttributes.count() - 1  )
                attributes += "\"\n";
        }

        QStringList temp;
        temp << elTag << elValue << attributes;

        item = new QTreeWidgetItem((QTreeWidget*)0, temp );

        parentItem->addChild( item );

        childNodeList = el.childNodes();

        parserNodeList( childNodeList, item );
    }

    return;
}

void
MainWindow::parserNode( QDomNode & node, QTreeWidgetItem *parentItem )
{

}
