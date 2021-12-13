cmake_minimum_required(VERSION 3.19)

project(cs1 LANGUAGES CXX)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick LinguistTools REQUIRED)

add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)
find_package(Qt5SerialPort)
find_package(Qt5SerialBus)
find_package(Qt5Sql)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "F:/C++/lib/googletest-master" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "F:/C++/lib/googletest-master")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

include_directories(../lib)





add_executable(cs1 main.cpp
    # 以下临时注释，后期记得取消
    test_dowInit.cpp

    dow.mdj
    test_sensor.cpp

    test_realTimeCurve.cpp

    test_getplcval.cpp
    todos.cpp

    test_models.cpp

    test_oper.cpp
    test_setParaBackend.cpp



        test_mainBackend.cpp
    #    test_myModbus.cpp
    #    test_database.cpp




    ${GTestFiles}  )
add_test(NAME cs1 COMMAND cs1)

target_link_libraries(cs1 PRIVATE Threads::Threads  )
target_link_libraries(cs1 PRIVATE  Qt${QT_VERSION_MAJOR}::Core 
Qt${QT_VERSION_MAJOR}::SerialPort Qt${QT_VERSION_MAJOR}::SerialBus Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(cs1 PRIVATE lib)


