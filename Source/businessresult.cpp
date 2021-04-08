#include "businessresult.h"
#include "ui_businessresult.h"
#include "business.h"
#include "mainwindow.h"

BusinessResult::BusinessResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BusinessResult)
{
    ui->setupUi(this);
    this->setFixedSize(900,700);
    this->setWindowTitle("Юридичекое Лицо");

}

BusinessResult::~BusinessResult()
{
    delete ui;
}

void BusinessResult::result()
{

    QMap <QString,QString>  commis;
    commis["0"]="local_transactions";
    commis["1"]="inside_transactions";
    commis["2"]="outgoing_transactions";
    commis["3"]="spb_transactions";

    QMap <QString,QString>::Iterator itt_comm;


    QString finding;
    finding.setNum(this->pair.first);

    QString tmp_commis;
    tmp_commis.setNum(this->pair.second+0.25);


    QString query_str="SELECT * FROM  business WHERE start_price<="+ this->price1 + " AND service_price<=" + this->price2 + " AND "+ *commis.find(finding) +" <= "+ tmp_commis +" ;";

    QSqlQuery query = QSqlQuery(MainWindow::get_db());
    query.exec(query_str);

    QSqlQueryModel *view = new QSqlTableModel;
    QSqlRecord rec = query.record();

    view->setQuery(query);
    view->setHeaderData(0, Qt::Horizontal, tr("Банк"));
    view->setHeaderData(1, Qt::Horizontal, tr("Стоимость подлкючения"));
    view->setHeaderData(2, Qt::Horizontal, tr("Стоимость обслуживания в месяц"));
    view->setHeaderData(3, Qt::Horizontal, tr("Коммиссия между \nсвоими каратами (%)"));
    view->setHeaderData(4, Qt::Horizontal, tr("Коммиссия внутри \nбанка (%)"));
    view->setHeaderData(5, Qt::Horizontal, tr("Коммиссия в другой \nбанк (%)"));
    view->setHeaderData(6, Qt::Horizontal, tr("Коммиссия через \nСПБ (%)"));
    view->setHeaderData(7, Qt::Horizontal, tr("Электронная подпись"));
    view->setHeaderData(8, Qt::Horizontal, tr("Выставление счетов"));
    view->setHeaderData(9, Qt::Horizontal, tr("Онлайн бухгалтерия"));
    view->setHeaderData(10, Qt::Horizontal, tr("Проверка контракгентов"));
    view->setHeaderData(11, Qt::Horizontal, tr("Консультация юристов"));
    view->setHeaderData(12, Qt::Horizontal, tr("Создание сайтов"));
    view->setHeaderData(13, Qt::Horizontal, tr("Рейтинг ИП"));
    view->setHeaderData(14, Qt::Horizontal, tr("Продвижение онлайн"));
    view->setHeaderData(15, Qt::Horizontal, tr("Помощь в сборе документов"));



    QMap <QString,QString>  changes;
    changes["0"]="e_signature";
    changes["1"]="online_bookkeeping";
    changes["2"]="contragents_check";
    changes["3"]="lawyers";
    changes["4"]="site_creation";
    changes["5"]="IP_rating";
    changes["6"]="online_promotion";
    changes["7"]="documents";
    changes["8"]="invoices";

    QStringList *lst=new QStringList();

    for (QString::Iterator str_itt=this->got_indexes.begin();str_itt!=this->got_indexes.end();str_itt++){
        for (QMap<QString,QString>::Iterator map_itt=changes.begin();map_itt!=changes.end();map_itt++)
            if (*str_itt==map_itt.key()) lst->push_back(map_itt.value());
    }

    int counter=0;
    int cnt=0;
    QVector <int> vect;
    while (query.next()){
        for (QStringList::Iterator itt=lst->begin();itt!=lst->end();itt++){
            if (query.value(rec.indexOf(*itt))=="Да")counter++;
        }

        if (counter<((got_indexes.length()/2)+1))vect.push_back(cnt);
        counter=0;
        cnt++;

    }

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setModel(view);
    ui->tableView->setFixedSize(850,350);

    for (int i=0;i<=view->rowCount();i++)ui->tableView->setRowHidden(i,false);
    for (int &number : vect)ui->tableView->hideRow(number);

    ui->tableView->setColumnWidth(1,170);
    ui->tableView->setColumnWidth(2,250);
    ui->tableView->setColumnWidth(3,270);
    ui->tableView->setColumnWidth(4,200);
    ui->tableView->setColumnWidth(5,200);
    ui->tableView->setColumnWidth(6,200);
    ui->tableView->setColumnWidth(7,170);
    ui->tableView->setColumnWidth(8,150);
    ui->tableView->setColumnWidth(9,150);
    ui->tableView->setColumnWidth(10,170);
    ui->tableView->setColumnWidth(11,170);
    ui->tableView->setColumnWidth(12,170);
    ui->tableView->setColumnWidth(14,170);
    ui->tableView->setColumnWidth(15,250);

}

void BusinessResult::on_pushButton_clicked()
{
    emit back();
    this->close();
}

