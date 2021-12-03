//
// Created by tangl on 2021-11-23.
//

#ifndef HWWMC_SENSOR_H
#define HWWMC_SENSOR_H

#include<cmath>
#include <string>
using namespace std;

class Sensor {
    ///构造传感器
    /// \brief Sensor
    /// \param name 名称
    /// \param decimalDigit 小数位
    /// \param offsetAddress 偏移量（对应基准地址）
    ///
public:
    Sensor(string name="传感器名称1", int decimalDigit=0, int offsetAddress=0);
//    int setUnTreatedVal;
public:
    void setUnTreatedVal(int unTreatedVal);

    void setDecimalDigit(int decimalDigit);

    float getValue();
    string getName() const;
    void setName(const string &value);

    int getOffsetAddress() const;
    void setOffsetAddress(int value);

    int getDecimalDigit() const;

private:
    int unTreatedVal;
    int decimalDigit;
    string name;
    int offsetAddress;
};
//class TemperatureSensor:public Sensor{

//};
//class LiquidFlowSpeed:public Sensor{

//};
//class AirFlowSpeed:public Sensor{

//};
//class AirPressure:public Sensor{

//};
//class RotationalSpeed:public Sensor{

//};

#endif //HWWMC_SENSOR_H
