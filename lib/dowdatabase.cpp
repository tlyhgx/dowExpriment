#include "dowdatabase.h"

#include <QSqlQuery>
#pragma execution_character_set("utf-8")
DowDataBase::DowDataBase(QObject *parent) : QObject(parent)
{

}

bool DowDataBase::openDB()
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("qt_sql_default_connection")){
        db=QSqlDatabase::database("qt_sql_default_connection");
        db.open();
    }else{
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");      //设置数据库主机名
        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
        db.setUserName("cjkj");         //设置用户名
        db.setPassword("cjkj5215");     //设置密码
        db.open();
    }
//    if(!db.isOpen())
//    {
//        db=QSqlDatabase::addDatabase("QSQLITE");
//        db.setHostName("localhost");      //设置数据库主机名
//        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
//        db.setUserName("cjkj");         //设置用户名
//        db.setPassword("cjkj5215");     //设置密码
//        db.open();
//    }
    if(!db.isOpen()){

        return false;
    }else{
        return true;
    }

}

void DowDataBase::closeDB()
{

    QString name;
    name=QSqlDatabase::database().connectionName();
    QSqlDatabase::removeDatabase(name);


}

bool DowDataBase::createTable()
{
    QSqlQuery query;
    QString sql;
    bool res;
    sql=QString("select * from sqlite_master where name='%1'").arg("oper");

    res=query.exec(sql);
    if(res==true){
        query.exec("drop table oper");
        query.exec("drop table experiment");
        query.exec("drop table signal_vals");
        query.exec("drop table sys_para");
    }

        query.exec("create table oper("
    "id_oper integer primary key,"
    "name char(30) unique default '实验人员',"
    "password char(30) default '123456' ,"
    "permission char(30) default '操作员',"
    "add_time timestamp default (datetime('now','localtime')))");
        query.exec("create table experiment("
    "id_experiment integer primary key,"
    "name char(50) default '实验xxxx',"
    "identifier char(50) default 'identifier_abc',"
    "remarks char(100) default '备注',"
    "create_time timestamp default (datetime('now','localtime')),"
    "id_oper integer,"
    "FOREIGN KEY(id_oper) REFERENCES oper(id_oper))");
        query.exec("create table signal_vals "
                        "(id_signal_val integer  primary key ,"
                        "value real not null,"
                        "name char(30),"
    "create_time timestamp default (datetime('now','localtime')),"
                        "id_experiment integer,"
                        "FOREIGN KEY(id_experiment) REFERENCES experiment(id_experiment))");

        query.exec("create table sys_para(id_sys_para integer primary key,"
    "record_cycle_s integer default '5')");
        query.exec("create table process_info(id_process_info integer primary key,"
    "info_content char(30),info_time,timestamp default (datetime('now','localtime')),"
" id_experiment integer)");


    res=query.exec(sql);

    return res;

}


