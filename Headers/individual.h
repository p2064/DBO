#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "multilist.h"
#include "individualresult.h"
#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QIntValidator>


namespace Ui {class Individual;}

class Individual : public QWidget
{
    Q_OBJECT

public:
    explicit Individual(QWidget *parent = nullptr);
    void test();
    ~Individual();

private:
    Ui::Individual *ui;
    MultiList *multiList;
    IndividualResult *resultwindow;

signals:
    void back();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void setValidators();
    void setMultiList();
};

#endif // INDIVIDUAL_H
