#ifndef TEST_SIGNAL_VALS_H
#define TEST_SIGNAL_VALS_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <dowdatabase.h>
#include <signal_vals.h>
#include <experiment.h>
#include <oper.h>
#include <syspara.h>
#include <QVariant>
using namespace testing;


TEST(Test_signal_vals,1){
    //添加数据到signal_vals,从signal_vals通过id读取,比对数据
    DowDataBase::openDB();
    DowDataBase::createTable();
    Oper oper;
    oper.addOneOper_to_db();
    Experiment experiment;
    experiment.addExpriment_to_db();

    Signal_vals signal_vals;
    float tem1=15.3f;
    signal_vals.add_val_to_db(tem1,"温度1",1);



    float press1=132.0f;
    signal_vals.add_val_to_db(press1,"气体压力",1);
    vector<float> get_from_db=signal_vals.get_val_by_experimentId_from_db(1);
    ASSERT_EQ(get_from_db[0],tem1);
    ASSERT_EQ(get_from_db[1],press1);

    DowDataBase::closeDB();

}


//参数表
TEST(Test_sysPara,1){
    DowDataBase::openDB();
    DowDataBase::createTable();
    //创建初始化数据库信息  假如数据库，参数表单为空，则创建添加一条初始数据


    //只能有一条记录

    SysPara sysPara;
    QSqlQuery query;
    query.exec("select * from sys_para");
    int count=0;
    while (query.next()) {
        ++count;
    }
    ASSERT_EQ(count,1);
    //记录周期默认值是5
    query.exec("select record_cycle_s from sys_para");
    query.next();
    int recordCycle_s=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(recordCycle_s,5);

    //记录周期 更新参数到数据库--从数据库读取--比对
    int recordcycle_s=30;
    sysPara.setRecordCycle_s_to_db(recordcycle_s);
    int ret=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(ret,30);

    //实时曲线显示周期 默认值是1
    query.exec("select realTimeCurve_flashcycle_s from sys_para");
    query.next();
    int realTimeCurve_flashcycle_s=sysPara.getRealTimeCureve_flashcycle_s_from_db();
    ASSERT_EQ(realTimeCurve_flashcycle_s,1);

    //刷新周期 更新参数到数据库--从数据库读取--比对
    realTimeCurve_flashcycle_s=2;
    sysPara.setRealTimeCureve_flashcycle_s_to_db(realTimeCurve_flashcycle_s);
    ret=sysPara.getRealTimeCureve_flashcycle_s_from_db();
    ASSERT_EQ(ret,2);

    //实时曲线显示时长 默认值是900s
    query.exec("select realTimeCurve_time_s from sys_para");
    query.next();
    int realTimeCurve_time_s=sysPara.getRealTimeCurve_time_s_from_db();
    ASSERT_EQ(realTimeCurve_time_s,900);


    //显示时长 更新参数到数据库--从数据库读取--比对
    realTimeCurve_time_s=800;
    sysPara.setRealTimeCurve_time_s_to_db(realTimeCurve_time_s);
    ret=sysPara.getRealTimeCurve_time_s_from_db();
    ASSERT_EQ(ret,800);

    //实时采样周期 默认值是500ms
    query.exec("select askPlc_cycle_ms from sys_para");
    query.next();
    int askPlc_cycle_ms=sysPara.getAskPlc_cycle_ms_from_db();
    ASSERT_EQ(askPlc_cycle_ms,500);

    //采样周期 更新参数到数据库--从数据库读取--比对
    askPlc_cycle_ms=800;
    sysPara.setAskPlc_cycle_ms_to_db(askPlc_cycle_ms);
    ret=sysPara.getAskPlc_cycle_ms_from_db();
    ASSERT_EQ(ret,800);



}

#endif // TEST_SIGNAL_VALS_H
