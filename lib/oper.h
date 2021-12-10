#ifndef OPER_H
#define OPER_H

#include <QObject>
#include <QSqlDatabase>

class Oper : public QObject
{
    Q_OBJECT
public:
    explicit Oper(QObject *parent = nullptr);
    //添加一个用户到数据库
    bool addOneOper_to_db(QString name="cs01", QString password="123456", QString permission="操作员");
    int findLastOper_id_by_name_from_db(QString name);

    QString find_name_by_id_from_db(int id);
signals:
private:
    QSqlDatabase db;

};

#endif // OPER_H
