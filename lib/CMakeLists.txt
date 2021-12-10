cmake_minimum_required(VERSION 3.19)

project(lib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core SerialBus SerialPort REQUIRED)
find_package(Qt5Sql)

add_library(lib
  lib.cpp
  lib.h
  mainbackend.cpp
  mainbackend.h




  DowInit.cpp
  DowInit.h
  mymodbus.h
  mymodbus.cpp

  Sensor.h
  Sensor.cpp

  realtimecurvebackend.cpp
  realtimecurvebackend.h

  getplcval.cpp
  getplcval.h
)

target_link_libraries(lib PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialBus Qt${QT_VERSION_MAJOR}::SerialPort  Qt${QT_VERSION_MAJOR}::Sql )


