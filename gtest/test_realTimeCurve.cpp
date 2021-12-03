

#ifndef TEST_REALTIMECURVE_H
#define TEST_REALTIMECURVE_H



#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "realtimecurvebackend.h"
using namespace testing;

TEST(Test_realTimeCurve,create){
    RealTimeCurveBackend backend;
}


#endif // TEST_REALTIMECURVE_H
