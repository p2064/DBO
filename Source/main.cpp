#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());
    MainWindow w;
    w.setFixedSize(800,400);
    w.setWindowTitle("Дистанционное Банковское Обслуживание");
    w.show();
    return a.exec();

}
