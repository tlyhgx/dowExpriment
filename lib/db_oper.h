#ifndef DB_OPER_H
#define DB_OPER_H

#include <QObject>
#include <QVariant>
class DB_oper : public QObject
{
    Q_OBJECT
public:
    explicit DB_oper(QObject *parent = nullptr);
    QVariantList getOperNames();
    int getOperIdbyName(QString operName);
    void addOperName(QString operName);
    void delOperName(QString operName);
    void update_oper(QString operName,QString last_name);

signals:

};

#endif // DB_OPER_H
