#ifndef PAGEPRINTER_H
#define PAGEPRINTER_H

#include <QWebView>

class PagePrinter : public QWebView
{
    Q_OBJECT

public:
    PagePrinter(QWidget *parent = 0);

public slots:
    void doPrint(bool ok);
};

#endif
