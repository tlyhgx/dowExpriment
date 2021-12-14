
#ifndef TEST_INFOLISTMODEL_H
#define TEST_INFOLISTMODEL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <QString>
#include <infolist.h>

//infoList 属性  时间  事件
TEST(Test_infoList,1)
{
    QString infoTime="2021-09-09 11:11:11";
    QString infoContent="温度1过高！";
    InfoList infoList(infoTime,infoContent);
    ASSERT_EQ (infoTime,infoList.infoTime()) ;
    ASSERT_EQ(infoList.infoContent(),infoContent);
}

//infoListModel
TEST(Test_infoListModel,1){
    InfoListModel infoListModel;
    infoListModel.addInfoList(InfoList("2021-09-09 12:12:12","开始记录！"));
    ASSERT_EQ(infoListModel.rowCount(),1);
    infoListModel.addInfoList(InfoList("2021-09-09 12:18:12","停止记录！"));
    ASSERT_EQ(infoListModel.rowCount(),2);


}
#endif
