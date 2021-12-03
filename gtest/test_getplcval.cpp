
#ifndef TEST_GETPLCVAL_H
#define TEST_GETPLCVAL_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "getplcval.h"
using namespace testing;

TEST(Test_getPLCval,1)
{
    DowInit dowInit;
    MyModbus myModbus;
    GetPlcVal getPlcVal(&dowInit,&myModbus);
    getPlcVal.askSignalVals();
}

#endif // TEST_GETPLCVAL_H
