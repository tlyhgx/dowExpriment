#ifndef TEST_OPER_H
#define TEST_OPER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QSqlQuery>
#include <oper.h>
#include <QDebug>

using namespace testing;




//测试添加oper到数据库
//*创建oper
//*通过名字找到id
//*通过id找到名字，并比对
TEST(Test_oper,1){
    Oper oper;

    bool res=oper.addOneOper_to_db("用户1","654321","管理员");
    ASSERT_EQ(res,true);
    int oper_id=oper.findLastOper_id_by_name_from_db("用户1");
    qDebug()<<oper_id<<112233;
    QString operName=oper.find_name_by_id_from_db(oper_id);
    ASSERT_EQ(operName,"用户1");

    res=oper.addOneOper_to_db("用户2","654541","操作员");
    ASSERT_EQ(res,true);
    oper_id=oper.findLastOper_id_by_name_from_db("用户2");
    operName=oper.find_name_by_id_from_db(oper_id);
    ASSERT_EQ(operName,"用户2");
//    res=oper.addOneOper_to_db("用户2","111111","操作员");
}
#endif

