#ifndef BUSINESSRESULT_H
#define BUSINESSRESULT_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QtSql>
#include <QString>
#include <QAbstractItemModel>
#include <QTableView>
#include <QSqlTableModel>
#include <QPair>



namespace Ui {
class BusinessResult;
}

class BusinessResult : public QWidget
{
    Q_OBJECT

public:
    explicit BusinessResult(QWidget *parent = nullptr);
    QString price1;
    QString price2;
    QString got_indexes;

    QPair <int,float> pair;

    void result();
    ~BusinessResult();

private:
    Ui::BusinessResult *ui;



private slots:

    void on_pushButton_clicked();

signals:
    void back();




};

#endif // BUSINESSRESULT_H
