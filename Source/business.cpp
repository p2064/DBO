#include "business.h"
#include "ui_business.h"

Business::Business(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Business)
{
    ui->setupUi(this);
    this->setFixedSize(900,700);
    this->setWindowTitle("Юридичекое Лицо");

    res=new BusinessResult();
    connect(res,&BusinessResult::back,this,&Business::show);


    QValidator *validator = new QIntValidator(0, 999999999, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit_3->setValidator(validator);


    QStringList list;
    multiList = new MultiList();
    QFont font("Calibri", 11);
    multiList->addItems(list <<"Электронная подпись"<<"Онлайн бухгалтерия"<<"Проверка контрагентов"<<"Консультация юристов"<<"Возможность оформления сайта"
                        <<"Рейтинг ЮЛ"<<"Продвижение бизнеса онлайн"<<"Конструктор документов"<<"Cервис выставления счетов");

    multiList->setStyleSheet("color: #000000");
    multiList->setMaximumWidth(370);

    QLabel *label_1 = new QLabel("Дополнительные услуги:");
    label_1->setFont(font);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addSpacing(91);
    hLayout->addWidget(label_1);
    hLayout->addWidget(multiList, 1);
    hLayout->addSpacing(90);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addSpacing(10);
    vLayout->addLayout(hLayout);
    this->setLayout(vLayout);
}

Business::~Business()
{
    delete ui;
}

void Business::on_pushButton_clicked()
{
    this->close();
    emit back();
}

void Business::on_pushButton_3_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->comboBox_2->setCurrentIndex(0);
    multiList->clearItems();
}

void Business::on_pushButton_2_clicked()
{
    ui->lineEdit_2->text().replace(",",".");
    res->pair.first=ui->comboBox_2->currentIndex();
    res->pair.second=ui->lineEdit_2->text().toFloat();
    multiList->getCheckedItems()=="" ? res->got_indexes="0" :  res->got_indexes=multiList->getCheckedItems(); //FIX
    if (ui->lineEdit->text().length()==0) ui->lineEdit->setText("88888"); //FIX
    if (ui->lineEdit_2->text().length()==0) ui->lineEdit_2->setText("8"); //FIX
    if (ui->lineEdit_3->text().length()==0) ui->lineEdit_3->setText("88888"); //FIX
    res->price1=ui->lineEdit->text();
    res->price2=ui->lineEdit_3->text();
    res->result();
    res->show();
    this->on_pushButton_3_clicked();
    this->close();
}
