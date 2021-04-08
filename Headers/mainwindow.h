#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "business.h"
#include "individual.h"
#include <QSqlDatabase>
#include <QSqlError>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Ui::MainWindow *ui;
    Business *business;
    Individual *individual;

public:
    static QSqlDatabase& get_db();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};
#endif // MAINWINDOW_H

