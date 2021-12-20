#ifndef TST_MAINBACKEND_H
#define TST_MAINBACKEND_H


#include "mainbackend.h"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <dowinit.h>
#include <oper.h>
#include "mymodbus.h"
#include <experiment.h>
#include <dowdatabase.h>
#include <infolist.h>
#include <hwwalarm.h>





using namespace testing;
using namespace std;
#pragma execution_character_set("utf-8")
class TestBackend : public ::testing::Test{
public:

    DowInit *dowInit=new DowInit;
    MyModbus *myModbus=new MyModbus;
    GetPlcVal *getPlcVal=new GetPlcVal(dowInit,myModbus);
    MainBackend *mainBackend;
protected:
    void SetUp() {

        mainBackend=new MainBackend(dowInit,getPlcVal);

    }
    void TearDown() {
        delete mainBackend;
        delete dowInit;
        delete myModbus;
    }
};




//获取传递给界面的值
//TEST_F(TestBackend,5)
//{
//    QVariantList signalVals;

//    signalVals=mainBackend->retSignalVals();

//}



//记录实验人员
TEST_F(TestBackend,7)
{
    DowDataBase::openDB();
    DowDataBase::createTable();
    //模拟从界面设置数据
    QString csName="测试人员1";
    mainBackend->setOperName(csName);
    QString operName=mainBackend->operName();
    ASSERT_EQ(csName,operName);
    //模拟从数据库读取数据

    Oper oper;
    int id=oper.findLastOper_id_by_name_from_db(csName);
    ASSERT_EQ(id,1);



    //模拟从界面设置数据
    csName="测试人员2";
    mainBackend->setOperName(csName);
    operName=mainBackend->operName();
    ASSERT_EQ(csName,operName);
    //模拟从数据库读取数据

    int id_oper=oper.findLastOper_id_by_name_from_db(csName);
    ASSERT_EQ(id_oper,2);
    DowDataBase::closeDB();


}
//记录实验名称
TEST_F(TestBackend,8)
{
    DowDataBase::openDB();
    DowDataBase::createTable();
    QString csName;
    Oper oper;
    csName="测试人员2";
    mainBackend->setOperName(csName);



    //记录实验名称
    //*从界面写入实验名称
    //*写入数据库
    //*从数据库读取比对

    QString csExprimentName="实验1";
    mainBackend->setExprimentName(csExprimentName);
    QString exprimentName=mainBackend->exprimentName();
    ASSERT_EQ(csExprimentName,exprimentName);

    Experiment expriment;
    int expriment_id=expriment.findLastExpriment_id_by_name_from_db(csExprimentName);
    ASSERT_EQ(expriment_id,1);

    csExprimentName="实验2";
    mainBackend->setExprimentName(csExprimentName);
    exprimentName=mainBackend->exprimentName();
    ASSERT_EQ(csExprimentName,exprimentName);

    expriment_id=expriment.findLastExpriment_id_by_name_from_db(csExprimentName);
    ASSERT_EQ(expriment_id,2);

    csExprimentName="实验3";
    mainBackend->setExprimentName(csExprimentName);
    exprimentName=mainBackend->exprimentName();
    ASSERT_EQ(csExprimentName,exprimentName);

    expriment_id=expriment.findLastExpriment_id_by_name_from_db(csExprimentName);
    ASSERT_EQ(expriment_id,3);

    DowDataBase::closeDB();
}

//把signalVals 按指定的周期写入数据库
TEST_F(TestBackend,9){

    //有willRec决定是否记录数据
    //设置willRec为true；数据库数据会增加
//    mainBackend->setWillRec(true);



}


//把InfoListModel 信息显示模块  注入 mainBackend
TEST_F(TestBackend,10){
    InfoListModel infoListModel;
    mainBackend->setInfoListModel(infoListModel);
}

//把报警添加到信息显示及数据库
TEST_F(TestBackend,alarms){
    HwwAlarms hwwAlarms(getPlcVal);
    mainBackend->setAlarmsInfo(hwwAlarms);
}

#endif // TST_MAINBACKEND_H

