#ifndef BACKEND_OPER_MANAGE_H
#define BACKEND_OPER_MANAGE_H

#include <QObject>
#include <QVariant>
#include "db_oper.h"
class Backend_oper_manage : public QObject
{
    Q_OBJECT
    //读取实验人员名称组
    Q_PROPERTY(QVariantList list_operName READ list_operName NOTIFY list_operNameChanged)
    //增加实验人员名称

public:
    explicit Backend_oper_manage(QObject *parent = nullptr);

    QVariantList list_operName();

    Q_INVOKABLE void add_oper(QString operName);

    Q_INVOKABLE void del_oper(QString operName);

    Q_INVOKABLE void update_oper(QString operName,QString last_name);

    void refresh_list_oper_name();

signals:
    void list_operNameChanged();
private:
    DB_oper db_oper;
};

#endif // BACKEND_OPER_MANAGE_H
