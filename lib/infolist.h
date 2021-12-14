#ifndef INFOLIST_H
#define INFOLIST_H

#include <QAbstractListModel>
#include <QString>



class InfoList
{
public:
    InfoList(const QString & infoTime,const QString & infoContent);
     QString infoTime()const;
    QString infoContent()const;
private:
    QString m_infoTime;
    QString m_infoContent;
};

class InfoListModel:public QAbstractListModel
{
    Q_OBJECT
public:
    enum InfoListRole {
        TimeRole = Qt::UserRole + 1,
        ContentRole
    };
    InfoListModel(QObject *parent=0);
    void addInfoList(const InfoList& infoList);
    // QAbstractItemModel interface
public:


    int rowCount(const QModelIndex &parent= QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QList<InfoList>m_infoList;

    // QAbstractItemModel interface
public:

    QHash<int, QByteArray> roleNames() const override;
};




#endif // INFOLIST_H
