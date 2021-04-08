#ifndef INDIVIDUALRESULT_H
#define INDIVIDUALRESULT_H

#include <QWidget>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QBoxLayout>
#include <QLabel>
#include <QDebug>

namespace Ui {
class IndividualResult;
}

class IndividualResult : public QWidget
{
    Q_OBJECT
    Ui::IndividualResult *ui;
    QSqlQueryModel *model;
    QSqlQuery quary;
    QPair<int, float> comission_1;
    QPair<int, float> comission_2;
    QPair<int, bool> alert_1;
    QPair<int, bool> alert_2;
    int alert_value;
    QMap<int, bool> criterias;
    int checkedCounter;

public:
    explicit IndividualResult(QWidget *parent = nullptr);
    ~IndividualResult();
    void getTable();
    void setValues(QPair<int, float> comission_1, QPair<int, float> comission_2,  QPair<int, bool> alert_1,
                   QPair<int, bool> alert_2, int alert_value, QMap<int, bool> criterias, int checkedCounter);

private slots:
    void setHeaders();
    void on_pushButton_clicked();
    void setQuary();
    void setTable();

signals:
    void back();
};

#endif // INDIVIDUALRESULT_H
