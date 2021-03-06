﻿cmake_minimum_required(VERSION 3.19)

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
#  dowinfolist.cpp
#  dowinfolist.h
  mainbackend.cpp
  mainbackend.h

  recordvaltablemodel.h
  recordvaltablemodel.cpp


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

  signal_vals.cpp
  signal_vals.h

  oper.cpp
  oper.h

  experiment.cpp
  experiment.h

  dowdatabase.cpp
  dowdatabase.h

  setparabackend.cpp
  setparabackend.h

  syspara.cpp
  syspara.h

  infolist.cpp
  infolist.h

  para_with_plc.cpp
  para_with_plc.h

  hwwalarm.cpp
  hwwalarm.h

  hwwutility.cpp
  hwwutility.h

  outputstate.cpp
  outputstate.h

  backend_adjust_analog_set.cpp
  backend_adjust_analog_set.h

  db_adjust_analog.cpp
  db_adjust_analog.h

  backend_history_chart.cpp
  backend_history_chart.h

  db_oper.cpp
  db_oper.h

  db_experiment.cpp
  db_experiment.h

  db_signal_vals.cpp
  db_signal_vals.h

  backend_oper_manage.h
  backend_oper_manage.cpp
)

target_link_libraries(lib PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::SerialBus Qt${QT_VERSION_MAJOR}::SerialPort  Qt${QT_VERSION_MAJOR}::Sql )


