#include "infolist.h"





InfoList::InfoList(const QString &infoTime, const QString &infoContent)
    :m_infoTime(infoTime),m_infoContent(infoContent)
{

}

 QString InfoList::infoTime() const
{
    return m_infoTime;
}



QString InfoList::infoContent() const
{
    return m_infoContent;
}

InfoListModel::InfoListModel(QObject *parent)
{

}

void InfoListModel::addInfoList(const InfoList &infoList)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_infoList<<infoList;
    endInsertRows();
}

QHash<int, QByteArray> InfoListModel::roleNames() const
{
        QHash<int,QByteArray>roles;
        roles[TimeRole]="infoTime";
        roles[ContentRole]="infoContent";
        return roles;
}




int InfoListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_infoList.count();
}



QVariant InfoListModel::data(const QModelIndex &index, int role) const
{
    if(index.row()<0||index.row()>=m_infoList.count())
    return QVariant();

    const InfoList &infoList=m_infoList[index.row()];
    if(role==TimeRole)
        return infoList.infoTime();
    else if(role==ContentRole)
        return infoList.infoContent();
    return QVariant();

}
