#include "individualresult.h"
#include "ui_individualresult.h"
#include "mainwindow.h"

IndividualResult::IndividualResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndividualResult)
{
    ui->setupUi(this);
    this->setWindowTitle("Физическое Лицо");
    this->setFixedSize(900,700);
    ui->label->setText("К сожалению ни один банк не подошел по заданным критериям,\nпопробуйте вернуться назад и изменить их.");
    ui->label->setAlignment(Qt::AlignCenter);
    this->setQuary();
}

IndividualResult::~IndividualResult()
{
    delete ui;
    quary.clear();
}

// Setting table column names and size
void IndividualResult::setHeaders()
{
    QStringList texts = QStringList() << "Банк" << "Перевод между\nсвоими счетами (%)" << "Перевод клиенту\nэтого же банка (%)"
        << "Перевод клиенту\nдругого банка (%)" << "Перевод\nчерез СБП (%)" << "Пополнение с карты\n стороннего банка (%)"
        << "Оплата\nмобильной связи (%)" << "Пополнение\nэлектронного кошелька (%)" << "Оплата\nналогов (%)"
        << "Уведомления\nпо СМС (₽)" << "Уведомления\nв приложении (₽)" << "Инвестиции\nи трейдинг"
        << "Мультивалютный\nсчет" << "Оплата\nпо QR" << "Бесплатная\nподдержка 24/7" << "Получение\nсправок"
        << "Автопереводы" << "Выписки\n для ПФР" << "Перевод\nзарубеж";
    for (int i = 0; i < texts.count(); i++)
        model->setHeaderData(i, Qt::Horizontal, texts.at(i), Qt::DisplayRole);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setVisible(false);
}

void IndividualResult::getTable()
{
    quary.first();
    for (int j = 0; j < quary.size(); j++)
    {
        bool flag = false;
        int counter = 0;
        QSqlRecord rec = quary.record();
        if (rec.value(comission_1.first) == "-" || rec.value(comission_1.first).toFloat() > comission_1.second) flag = true;
        if (rec.value(comission_2.first) == "-" || rec.value(comission_2.first).toFloat() > comission_2.second) flag = true;
        if (alert_1.second && rec.value(alert_1.first).toInt() > alert_value) flag = true;
        if (alert_2.second && rec.value(alert_2.first).toInt() > alert_value) flag = true;
        for(QMap<int, bool>::iterator i = criterias.begin(); i != criterias.end(); i++)
            if (rec.value(i.key()).toString() == "+" && i.value())
                counter++;
        if (counter < (checkedCounter / 2 + 1) && checkedCounter) flag = true;
        ui->tableView->setRowHidden(j, false);
        if (flag) ui->tableView->setRowHidden(j, true);
        quary.next();
    }
    setTable();
    this->show();
}

void IndividualResult::on_pushButton_clicked()
{
    this->close();
    emit back();
}

void IndividualResult::setValues(QPair<int, float> comission_1, QPair<int, float> comission_2, QPair<int, bool> alert_1,
                                 QPair<int, bool> alert_2, int alert_value, QMap<int, bool> criterias, int checkedCounter)
{
    this->comission_1 = comission_1;
    this->comission_2 = comission_2;
    this->alert_1 = alert_1;
    this->alert_2 = alert_2;
    this->alert_value = alert_value;
    this->criterias = criterias;
    this->checkedCounter = checkedCounter;
}

void IndividualResult::setQuary()
{
    model =new QSqlQueryModel();
    quary = QSqlQuery(MainWindow::get_db());
    if (!quary.exec("SELECT * FROM individual"))
    {
        qDebug() << quary.lastError().databaseText();
        qDebug() << quary.lastError().driverText();
        return;
    }
    quary.exec("SELECT * FROM individual");
    model->setQuery(quary);
    setHeaders();
    ui->tableView->setModel(model);
}

void IndividualResult::setTable()
{
    int hiddenRowCounter = 0;
    for(int j = 0; j < quary.size(); j++)
        if (!ui->tableView->isRowHidden(j))
            hiddenRowCounter++;

    if (!hiddenRowCounter)
    {
        ui->label_2->hide();
        ui->tableView->hide();
        ui->label->show();
    }
    else
    {
        ui->label->hide();
        ui->label_2->show();
        ui->tableView->show();
    }
}





