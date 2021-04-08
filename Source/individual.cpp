#include "individual.h"
#include "ui_individual.h"
#include "ui_individualresult.h"

Individual::Individual(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Individual)
{
    resultwindow = new IndividualResult();
    connect(resultwindow, &IndividualResult::back, this, &Individual::show);

    this->ui->setupUi(this);
    this->setWindowTitle("Физическое Лицо");
    this->setFixedSize(900,700);
    this->setValidators();
    this->setMultiList();
}

Individual::~Individual()
{
    delete ui;
}

void Individual::on_pushButton_clicked()
{
    this->close();
    emit back();
}

void Individual::on_pushButton_2_clicked()
{
    QString str1 = ui->lineEdit_2->text();
    QString str2 = ui->lineEdit_3->text();
    str1.replace(",",".");
    str2.replace(",",".");

    QPair<int, float> comission_1 (ui->comboBox_2->currentIndex()+1, str1.toFloat());
    QPair<int, float> comission_2 (ui->comboBox_2->currentIndex()+5, str2.toFloat());

    QPair<int, bool> alert_1 (9, ui->checkBox->isChecked());
    QPair<int, bool> alert_2 (10, ui->checkBox_2->isChecked());
    int alert_value = ui->lineEdit_4->text().toInt();

    QMap<int, bool> criterias = multiList->getCriterias();
    int checkedCounter = multiList->checkedCounter();

    resultwindow->setValues(comission_1, comission_2, alert_1, alert_2, alert_value, criterias, checkedCounter);
    resultwindow->getTable();
    this->close();
}

void Individual::on_pushButton_3_clicked()
{
    ui->lineEdit_2->setText("2,0");
    ui->lineEdit_3->setText("2,0");
    ui->lineEdit_4->setText("59");
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->comboBox_2->setCurrentIndex(0);
    ui->comboBox_3->setCurrentIndex(0);
    multiList->clearItems();
}

void Individual::setValidators()
{
    QDoubleValidator *dValidator = new QDoubleValidator(0, 99, 2, this);
    dValidator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEdit_2->setValidator(dValidator);
    ui->lineEdit_2->setText("2,0");
    ui->lineEdit_2->setMaxLength(5);
    ui->lineEdit_3->setValidator(dValidator);
    ui->lineEdit_3->setText("2,0");
    ui->lineEdit_3->setMaxLength(5);

    QIntValidator * iValidator = new QIntValidator(0, 999);
    ui->lineEdit_4->setValidator(iValidator);
    ui->lineEdit_4->setText("59");
    ui->lineEdit_4->setMaxLength(3);
}

void Individual::setMultiList()
{
    multiList = new MultiList();
    multiList->addItems(QStringList() << "Инвестиции и трейдинг" << "Мультивалютный счет" <<
                        "Оплата по QR" << "Бесплатная поддержка 24/7" <<
                        "Получение справок"<< "Автопереводы"
                        <<"Выписки ПФР" << "Перевод зарубеж");
    QFont font("Calibri", 11);
    multiList->setFont(font);
    multiList->setStyleSheet("color: #000000");
    multiList->setMaximumWidth(370);

    QLabel *label_1 = new QLabel("Дополнительные услуги:");
    label_1->setFont(font);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addSpacing(70);
    hLayout->addWidget(label_1);
    hLayout->addWidget(multiList, 1);
    hLayout->addSpacing(90);

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->addSpacing(90);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);
}
