#ifndef DOWDATABASE_H
#define DOWDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#pragma execution_character_set("utf-8")
class DowDataBase : public QObject
{
    Q_OBJECT
public:
    explicit DowDataBase(QObject *parent = nullptr);
    static bool openDB();
//    static void closeDB();
    static bool createTable();
signals:

//    private:
//    static QSqlDatabase db;  //TODO:99 �Ƿ����ת��Ϊ��̬����

};

#endif // DOWDATABASE_H
