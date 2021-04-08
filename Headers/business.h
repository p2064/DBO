#ifndef BUSINESS_H
#define BUSINESS_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QBoxLayout>
#include <QSizePolicy>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QListIterator>
#include  "multilist.h"
#include  "businessresult.h"

namespace Ui {class Business;}

class Business : public QWidget
{
    Q_OBJECT

public:
    explicit Business(QWidget *parent = nullptr);
    ~Business();

private:
    Ui::Business *ui;
    MultiList *multiList;
    BusinessResult *res;



signals:
    void back();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();

};

#endif // BUSINESS_H
