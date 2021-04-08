#include "multilist.h"
#include "businessresult.h"

MultiList::MultiList(QWidget *parent): QComboBox(parent)
{
    setEditable(true);
    displayText = "";
    model = new QStandardItemModel;
    slotUpdateText();
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotUpdate()));
}

void MultiList::addItem(const QString &text)
{
    int row = model->rowCount();
    QStandardItem* item = new QStandardItem();
    item->setText(text);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    item->setBackground(QColor::fromRgb(255, 255, 255));
    model->setItem(row, 0, item);
    this->setModel(model);
}

void MultiList::addItems(const QStringList &texts)
{
    for (int i = 0; i < texts.count(); i++)
    {
        addItem(texts.at(i));
    }
}

QString MultiList::getCheckedItems()
{
    QString checkedItemsIndexes="";
    QString tmp;

    for (int i = 0; i < model->rowCount(); i++) {
        if (model->item(i, 0)->checkState() == Qt::Checked) {
            tmp.setNum(i);
            checkedItemsIndexes += tmp;
        }
    }
    return checkedItemsIndexes;
}



void MultiList::setCheckedItems(const QStringList &items) {
    for (int i = 0; i < items.count(); i++)
    {
        int index = findText(items.at(i));
        if (index != -1)
        {
            model->item(index)->setData(Qt::Checked, Qt::CheckStateRole);
        }
    }
    slotUpdate();
}

void MultiList::slotUpdateText()
{
    lineEdit()->setText(displayText);
}

void MultiList::slotUpdate()
{
    displayText = "";

    for (int i = 0; i < model->rowCount(); i++)
    {
        if (model->item(i, 0)->checkState() == Qt::Checked)
        {
            displayText = displayText + model->item(i, 0)->text() + "; ";
        }
    }
    QTimer::singleShot(0, this, SLOT(slotUpdateText()));
}

void MultiList::clearItems()
{
    for (int i = 0; i < model->rowCount(); i++)
    {
        if (model->item(i, 0)->checkState() == Qt::Checked)
        {
            model->item(i, 0)->setData(Qt::Unchecked, Qt::CheckStateRole);
        }
    }
}

QMap<int, bool> MultiList::getCriterias()
{
    QMap<int, bool> criterias = {};
    for (int i = 0; i < model->rowCount(); i++)
    {
        if (model->item(i, 0)->checkState() == Qt::Checked)
            criterias[i+11] = true;
        else
            criterias[i+11] = false;
    }
    return criterias;
}

int MultiList::checkedCounter()
{
    int checkedCounter = 0;
    for (int i = 0; i < model->rowCount(); i++)
        if (model->item(i, 0)->checkState() == Qt::Checked)
            checkedCounter++;
    return checkedCounter;
}


