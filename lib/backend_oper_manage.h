#ifndef BACKEND_OPER_MANAGE_H
#define BACKEND_OPER_MANAGE_H

#include <QObject>
#include <QVariant>
class Backend_oper_manage : public QObject
{
    Q_OBJECT
    //读取实验人员名称组
    Q_PROPERTY(QVariantList list_operName READ list_operName )
    //增加或改变实验人员名称
public:
    explicit Backend_oper_manage(QObject *parent = nullptr);

    QVariantList list_operName();



signals:

};

#endif // BACKEND_OPER_MANAGE_H
