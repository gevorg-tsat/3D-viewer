#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    // QLocale::setDefault(QLocale("C"));
    QLocale::setDefault(QLocale::c());
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
