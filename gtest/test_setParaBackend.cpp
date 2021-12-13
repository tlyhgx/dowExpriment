#ifndef TST_PARABACKEND_H
#define TST_PARABACKEND_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <setparabackend.h>
#include <syspara.h>


class Test_setParaBackend:public ::testing::Test{
public:
    SetParaBackend setParaBackend;

    // Test interface
protected:
    void SetUp() override;
    void TearDown() override;
};

void Test_setParaBackend::SetUp()
{
}

void Test_setParaBackend::TearDown()
{
}


//��ӽ������úͶ�ȡ ���ݼ�¼���ڵ�
TEST_F(Test_setParaBackend,1){
    //����--����д--recordCycle_s
    int recordCycle_s=5;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    int ret=setParaBackend.recordRecycle_s();
    ASSERT_EQ(recordCycle_s,ret);
}

//���ݼ�¼����д�����ݿ�
TEST_F(Test_setParaBackend,2){
    //�������ú����ݸı䣬����д�����ݿ⶯��
    int recordCycle_s=20;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    //�����ݿ��ȡ��ȶ�
    SysPara sysPara;
    int ret=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(ret,recordCycle_s);

    recordCycle_s=15;
    setParaBackend.setRecordRecycle_s(recordCycle_s);
    ret=sysPara.getRecordRecycle_s_from_db();
    ASSERT_EQ(ret,recordCycle_s);
}


//TODO:���ݼ�¼���ڣ�����Ϊ�գ������3000s,Ĭ�ϸ�Ϊ5S


#endif

