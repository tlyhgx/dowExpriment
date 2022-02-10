#include "recordvaltablemodel.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include <qtextcodec.h>

RecordValTableModel::RecordValTableModel(QSqlQueryModel *parent)
    :QSqlQueryModel(parent),m_tableName(""),m_query(new QSqlQuery (QSqlDatabase(QSqlDatabase::database())))
{

    m_roleNames[Qt::UserRole]="create_time";
    m_roleNames[Qt::UserRole+1]="name";
    m_roleNames[Qt::UserRole+2]="value";
//    qDebug()<<QSqlDatabase::database().connectionNames();

    connect(this,&RecordValTableModel::tableNameChanged,
            [&]{
        /*qDebug()<<"tableChanged";*/
        QString queryser;
        if(m_tableName=="signal_vals")
        {

            queryser=QString("select create_time,name,value from %1").arg(m_tableName);

//            qDebug()<< queryser;
        }
        else{
            queryser=QString("select * from %1").arg(m_tableName);
        }

        if(!m_query->exec(queryser))
        {
            qDebug()<<m_query->lastError();
        }else{
            m_rows=0;
            while (m_query->next()) {
                m_rows=m_rows+1;
            }
        }

        this->setQuery(*m_query);

//        int columns=this->columnCount();

        m_tableTitle.clear();
//        for(int i=0;i<columns;i++)
//        {
//            m_tableTitle.append(m_query->record().fieldName(i));
//        }
        QTextCodec *codec = QTextCodec::codecForName("GBK");
        m_tableTitle.append(codec->toUnicode("时间"));
        m_tableTitle.append(codec->toUnicode("内容"));
        m_tableTitle.append(codec->toUnicode("值"));
    });

}

QVariant RecordValTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    //这个函数获取表头内容
    if(role!=Qt::DisplayRole)
        return QVariant();
    if(orientation==Qt::Horizontal)
    {
        return m_tableTitle.at(section);
    }
    else if(orientation==Qt::Vertical){
        return QString::number(section);
    }

    return QVariant();
}

int RecordValTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);



//    return m_query->size();
    return m_rows;
}

int RecordValTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return m_query->record().count();
}

QVariant RecordValTableModel::data(const QModelIndex &index, int role) const
{
    QVariant v;
    //the index returns the requested row and column information
    int row=index.row();
    int column=index.column();

    //boundary check for the row and column
    if(row<0||row>=this->rowCount()||column<0||column>=this->columnCount())
    {
        return v;
    }
    m_query->seek(row);
    return m_query->value(column);

}

QHash<int, QByteArray> RecordValTableModel::roleNames() const
{

    return m_roleNames;
    //    QHash<int,QByteArray>m_roleNames;
    //    //record() returns an empty QSqlRecord
    //    for(int i=0;i<m_query->record().count();i++)
    //    {
    //        m_roleNames.insert(Qt::UserRole+i+1,m_query->record().fieldName(i).toUtf8());
    //    }

    //    return m_roleNames;
}

QString RecordValTableModel::tableName() const
{
    return m_tableName;
}

void RecordValTableModel::setTableName(const QString _tableName)
{
    if(_tableName!=m_tableName){
        m_tableName=_tableName;
        emit tableNameChanged();
    }

}
