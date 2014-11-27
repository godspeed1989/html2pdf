#include "pageprinter.h"

#include <QApplication>
#include <QString>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "Option: {u|f} {URL|file_path}" << std::endl;
    if (argc < 3)
    {
        return 0;
    }

    QApplication app(argc, argv);

    PagePrinter *view = new PagePrinter();
    view->settings()->setAttribute(QWebSettings::AutoLoadImages, true);
    view->settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
    view->settings()->setAttribute(QWebSettings::PrintElementBackgrounds, true);

    if (argv[1][0] == 'u')
    {
        view->load(QUrl(argv[2]));
    }
    else if (argv[1][0] == 'f')
    {
        QString fname = argv[2];
        QFile file(fname);
        file.open(QIODevice::Text | QIODevice::ReadOnly);
        if (file.isOpen())
        {
            QString file_content(file.readAll());
            std::cout << argv[2] << ": " << file_content.length() << std::endl;
            view->setHtml(file_content, QUrl("."));
        }
        else
        {
            std::cerr << argv[2] << " open error" << std::endl;
            return 0;
        }
        file.close();
        view->doPrint(true);
    }
    else
    {
        std::cerr << "unkonwn option" << std::endl;
        return 0;
    }

    view->show();
    return app.exec();
}
