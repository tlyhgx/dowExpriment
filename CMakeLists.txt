cmake_minimum_required(VERSION 3.19)

project(DowExperimentDataMonitor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(app_WINRC Appicon.rc)
set_property(SOURCE Appicon.rc APPEND PROPERTY
    OBJECT_DEPENDS ${PROJECT_SOURCE_DIR}/cjkj.ico)
# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick LinguistTools  REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick  LinguistTools REQUIRED)
find_package(Qt5SerialPort)
find_package(Qt5SerialBus)
find_package(Qt5Charts)
find_package(Qt5Qml)
find_package(Qt5Sql)

add_subdirectory(lib)
include_directories(lib)
#add_subdirectory(gtest)




#set(TS_FILES DowExperimentDataMonitor_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc

        sortfilterproxymodel.cpp
        sortfilterproxymodel.h
        easytablemodel.h
        easytablemodel.cpp
        todos.cpp



#        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DowExperimentDataMonitor
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(DowExperimentDataMonitor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(DowExperimentDataMonitor
          ${PROJECT_SOURCES}  ${app_WINRC}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_compile_definitions(DowExperimentDataMonitor
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(DowExperimentDataMonitor
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick
  Qt${QT_VERSION_MAJOR}::SerialPort Qt${QT_VERSION_MAJOR}::SerialBus
  Qt${QT_VERSION_MAJOR}::Charts Qt${QT_VERSION_MAJOR}::Qml Qt${QT_VERSION_MAJOR}::Sql)

target_link_libraries(DowExperimentDataMonitor  PRIVATE lib)
