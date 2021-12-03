#include "test_realtimecurve.h"
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "realtimecurvebackend.h"
using namespace testing;

TEST(Test_realTimeCurve,create){
    RealTimeCurveBackend backend;
}
//TODO:原先实时数据读取是通过main界面定时器，
//现要调整为打开程序后实时读取，方便其它界面调用数据
