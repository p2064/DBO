#ifndef MULTILIST_H
#define MULTILIST_H
#include <QtWidgets>

class MultiList : public QComboBox {
    Q_OBJECT

private:
    QString displayText;
    QStandardItemModel *model;

public:
    MultiList(QWidget *parent = 0);

public slots:
    void addItem(const QString &text);
    void addItems(const QStringList &texts);
    QString getCheckedItems();
    void setCheckedItems(const QStringList &items);
    QMap<int, bool> getCriterias();
    void slotUpdateText();
    void slotUpdate();
    void clearItems();
    int checkedCounter();
};

#endif // MULTILIST_H
