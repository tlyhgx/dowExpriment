#ifndef RECORDVALTABLEMODEL_H
#define RECORDVALTABLEMODEL_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QStringListModel>
class RecordValTableModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QString m_tableName READ tableName WRITE setTableName NOTIFY tableNameChanged)
public:
    RecordValTableModel(QSqlQueryModel *parent = nullptr);




signals:


    // QAbstractItemModel interface
public:
    Q_INVOKABLE QVariant headerData(int section,Qt::Orientation orientation,int role=Qt::DisplayRole)const override;
    Q_INVOKABLE void search(QString keyVal);
    Q_INVOKABLE QVariantList search_expriment_name();
    int rowCount(const QModelIndex & =QModelIndex()) const override;
    int columnCount(const QModelIndex & =QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const override;
    QHash<int, QByteArray>roleNames() const override;

    QString tableName() const;
    void setTableName(const QString _tableName);

signals:
    void tableNameChanged();
private:
    QString m_tableName;
    QVector<QString> m_tableTitle;
    QSqlQuery* m_query;
    int m_rows;
    QHash<int,QByteArray>m_roleNames;


};



#endif // RECORDVALTABLEMODEL_H
