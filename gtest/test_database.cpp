#ifndef TEST_DATABASE_H
#define TEST_DATABASE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariantList>
using namespace testing;

class Test_database:public ::testing::Test{

public:
    QSqlDatabase db;

    //    QSqlQuery query;

    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;

    // Test interface
private:
    void TestBody() override;
};

void Test_database::TestBody()
{
}

void Test_database::SetUp()
{
    if(!db.isOpen())
    {


        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setHostName("localhost");      //设置数据库主机名
        db.setDatabaseName("dow_experiment_data.db");  //设置数据库名称
        db.setUserName("cjkj");         //设置用户名
        db.setPassword("cjkj5215");     //设置密码
        db.open();
    }

    QSqlQuery query;




    query.exec("create table oper("
"id_oper integer primary key,"
"name char(30) default '实验人员',"
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
    bool res_create_table=query.exec("create table signal_vals "
                    "(id_signal_val integer  primary key ,"
                    "value real not null,"
                    "name char(30),"
"create_time timestamp default (datetime('now','localtime')),"
                    "id_experiment integer,"
                    "FOREIGN KEY(id_experiment) REFERENCES experiment(id_experiment))");

    query.exec("create table alarm_para(id_alarm_para integer primary key,"
"record_cycle_s integer default '5')");

    if (res_create_table==false){
        query.exec("drop table oper");
        query.exec("drop table experiment");
        query.exec("drop table signal_vals");
        query.exec("drop table alarm_para");

    }

    query.exec("create table oper("
"id_oper integer primary key,"
"name char(30) default '实验人员',"
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

    query.exec("create table alarm_para(id_alarm_para integer primary key,"
"record_cycle_s integer default '5')");


}

void Test_database::TearDown()
{
    if(db.isOpen()){
        db.close();
    }

}
//打开数据库
TEST_F(Test_database,openDatabase)
{
    ASSERT_EQ(db.open(),true);
}

//插入数据到oper
TEST_F(Test_database,insertData){
        ASSERT_EQ(db.open(),true);
        QSqlQuery query;
        query.exec("insert into oper(name, password)"
                              "VALUES ('huang光旭', 'cjkj5215')");
        query.exec("insert into experiment(name,identifier,remarks,id_oper)"
                              " VALUES ('高分子合成','no_xoe233','这个实验ssoelxx','1')");
        query.exec("insert into signal_vals(value,name,id_experiment)"
                              " VALUES('23.5','temp','1')");
        query.exec("insert into signal_vals(value,name,id_experiment)"
                              " VALUES('122','temp2','1')");
        query.exec("insert into alarm_para(id_alarm_para)"
                              " VALUES('1')");


}

////创建删除数据库表单
//TEST_F(Test_database,createTable1)
//{


//    QSqlQuery query;
//    bool res_create_table=query.exec("create table automobil (id int primary key,attribute varchar)");
//    ASSERT_EQ(res_create_table,false);

//    if (res_create_table==false){
//        query.exec("drop table automobil");

//    }

//    res_create_table=query.exec("create table automobil (id int primary key,attribute varchar)");

//    ASSERT_EQ(res_create_table,true);
//}

//////查询
////TEST_F(Test_database,3)
////{
////    QSqlQuery query;
////    query.exec("select * from automobil");
////    QSqlRecord rec=query.record();
////    ASSERT_EQ(rec.count(),0);
////}

////插入
//TEST_F(Test_database,4)
//{
//    ASSERT_EQ(db.open(),true);
//    QSqlQuery query;

//}

////批量插入
//TEST_F(Test_database,5){
//    QSqlQuery query;
//    query.prepare("insert into automobil(id, attribute)"
//                      "VALUES (:id, :attribute)");
//    //为每一列标题添加绑定值
//    QVariantList id;
//    id<<1<<2<<3<<4<<5<<6<<7
//     <<8<<9<<10<<11<<12<<13<<14;

//    QStringList attribute;
//    attribute<<"初1-1班"<<"初1-2班"<<"初1-3班"<<"初2-1班"
//             <<"初2-2班"<<"初2-3班"<<"初3-1班"<<"初3-2班"<<"初3-3班";


//    foreach (QString attribute, attribute)       //从names表里获取每个名字
//    {
//        query.bindValue(":attribute", attribute);
//        query.bindValue(":id", (rand() % 101));

//        query.exec();               //加入库中
//    }
//}

#endif // TEST_DATABASE_H
