#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "xmldiffer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    XMLDiffer xmlDiffer1;
    XMLDiffer xmlDiffer2;

    if ( xmlDiffer1.openXmlFile( "XMLs/receita-1.xml", XMLDiffer::XmlDoc1 ) ) {
        ui->texml1->setText( xmlDiffer1.xmlDoc( XMLDiffer::XmlDoc1 ) );
    }

    if ( xmlDiffer2.openXmlFile( "XMLs/receita-1.xml", XMLDiffer::XmlDoc2 ) ) {
        ui->texml2->setText( xmlDiffer2.xmlDoc(XMLDiffer::XmlDoc2 ) );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


