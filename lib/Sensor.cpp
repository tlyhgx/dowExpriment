//
// Created by tangl on 2021-11-23.
//

#include "Sensor.h"




Sensor::Sensor(string name, int decimalDigit, int offsetAddress)
    :decimalDigit(decimalDigit),name(name),offsetAddress(offsetAddress)
{

}

/// 把modbus的整型值直接赋值
/// \param unTreatedVal  未处理的值（后面要加小数位后才能使用，因为PLC只能发整型数）
void Sensor::setUnTreatedVal(int unTreatedVal) {
    this->unTreatedVal=unTreatedVal;
}
/// 设置小数位数
/// \param decimalDigit  小数位数
void Sensor::setDecimalDigit(int decimalDigit) {
    this->decimalDigit=decimalDigit;
}
/// 获取处理后的值
/// \return
float Sensor::getValue() {
    return unTreatedVal*pow(0.1,decimalDigit);
}

string Sensor::getName() const
{
    return name;
}

void Sensor::setName(const string &value)
{
    name = value;
}

int Sensor::getOffsetAddress() const
{
    return offsetAddress;
}

void Sensor::setOffsetAddress(int value)
{
    offsetAddress = value;
}
