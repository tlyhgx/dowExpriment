#include "tst_cs1.h"
#include "tst_mainBackend.h"
#include "test_myModbus.h"
#include <gtest/gtest.h>
#include "test_dowInit.h"
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();


}


