#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    business = new Business();
    individual = new Individual();
    connect(business, &Business::back, this, &MainWindow::show);
    connect(individual, &Individual::back, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlDatabase& MainWindow::get_db()
{
    static QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("testdb");
    db.setUserName("root");
    db.setPassword("20643579");
    if(!db.open())
    {
        qDebug() << db.lastError().text();
    }
    return db;
}

void MainWindow::on_pushButton_clicked()
{
    business->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    individual->show();
    this->close();
}

