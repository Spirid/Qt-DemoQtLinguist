#include "Linguist.h"
#include <QApplication>
#include<QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Connect translator
    QTranslator translator;
    translator.load("spyder_ru.qm", ".");
    a.installTranslator(&translator);

    //Retrieve the current locale
    QString filespec ("Spyder_");
    QLocale locale = QLocale::system();
    QString locStr = locale.name();


    //Assembly translation file name
    locStr.chop(3);
    filespec+=locStr;
    filespec+=".qm";
    translator.load(filespec , ".");



    Linguist w;

    w.show();

    return a.exec();
}
