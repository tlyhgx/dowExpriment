#ifndef TEST_SIGNAL_VALS_H
#define TEST_SIGNAL_VALS_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlQuery>
#include <dowdatabase.h>
#include <signal_vals.h>
#include <experiment.h>
#include <oper.h>
using namespace testing;

//TODO:数据库读写
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


#endif // TEST_SIGNAL_VALS_H
