#include "pageprinter.h"

#include <QFile>
#include <QPrinter>
#include <QPrinterInfo>

#include <iostream>

PagePrinter::PagePrinter(QWidget *parent) : QWebView(parent)
{
    QObject::connect(this, SIGNAL(loadFinished(bool)), this, SLOT(doPrint(bool)));
}

void PagePrinter::doPrint(bool ok)
{
    if (!ok)
    {
        std::cerr << "Page may not completely loaded" << std::endl;
    }

    // start a printer
    QPrinter *printer = new QPrinter(QPrinterInfo::defaultPrinter(), QPrinter::ScreenResolution);
    printer->setFontEmbeddingEnabled(true);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setFullPage(true);
    printer->setOutputFileName(QString("out.pdf"));

    // print out
    this->print(printer);

    std::cout << "Print to out.pdf" << std::endl;
    delete printer;
}
