#ifndef TEST_SIGNAL_VALS_H
#define TEST_SIGNAL_VALS_H
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlQuery>
#include <dowdatabase.h>
#include <signal_vals.h>
//#include <expriment.h>
using namespace testing;

//TODO:数据库读写
TEST(Test_signal_vals,1){
    //添加数据到signal_vals,从signal_vals通过id读取,比对数据
    DowDataBase::openDB();
    DowDataBase::createTable();
//    Experiment experiment;

    Signal_vals signal_vals;
    float tem1=15.3f;
    signal_vals.add_val_to_db(tem1);
    float tem1_get_from_db=signal_vals.get_val_from_db(1);
    ASSERT_EQ(tem1_get_from_db,tem1);

    float press1=132.0f;
    signal_vals.add_val_to_db(press1);
    float press1_get_from_db=signal_vals.get_val_from_db(2);
//    ASSERT_EQ(press1,press1_get_from_db); //TODO1:



}


#endif // TEST_SIGNAL_VALS_H
