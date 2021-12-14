#ifndef DOWINFOLIST_H
#define DOWINFOLIST_H

#include <QAbstractListModel>

class DowInfoList:public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DowInfoList(QObject *parent=nullptr);
    enum {
        DescriptionRole=Qt::UserRole,
    };
    // QAbstractItemModel interface
public:
    Q_INVOKABLE bool testInsertRows(int position,int rows);
    Q_INVOKABLE bool testRemoveRows(int position,int rows);

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QStringList stringList;
};

QModelIndex DowInfoList::index(int row, int column, const QModelIndex &parent) const
{
}

QModelIndex DowInfoList::parent(const QModelIndex &child) const
{
}

int DowInfoList::rowCount(const QModelIndex &parent) const
{
}

int DowInfoList::columnCount(const QModelIndex &parent) const
{
}

QVariant DowInfoList::data(const QModelIndex &index, int role) const
{
}

bool DowInfoList::setData(const QModelIndex &index, const QVariant &value, int role)
{
}

bool DowInfoList::insertRows(int row, int count, const QModelIndex &parent)
{
}

bool DowInfoList::removeRows(int row, int count, const QModelIndex &parent)
{
}

Qt::ItemFlags DowInfoList::flags(const QModelIndex &index) const
{
}

QHash<int, QByteArray> DowInfoList::roleNames() const
{
}

#endif // DOWINFOLIST_H
