#ifndef BACKEND_OPER_MANAGE_H
#define BACKEND_OPER_MANAGE_H

#include <QObject>
#include <QVariant>
#include "db_oper.h"
class Backend_oper_manage : public QObject
{
    Q_OBJECT
    //��ȡʵ����Ա������
    Q_PROPERTY(QVariantList list_operName READ list_operName NOTIFY list_operNameChanged)
    //����ʵ����Ա����
    Q_INVOKABLE void add_oper(QString operName);
public:
    explicit Backend_oper_manage(QObject *parent = nullptr);

    QVariantList list_operName();



signals:
    void list_operNameChanged();
private:
    DB_oper db_oper;
};

#endif // BACKEND_OPER_MANAGE_H
