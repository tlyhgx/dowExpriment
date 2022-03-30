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

signals:

};

#endif // DB_OPER_H
