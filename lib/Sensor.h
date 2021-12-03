//
// Created by tangl on 2021-11-23.
//

#ifndef HWWMC_SENSOR_H
#define HWWMC_SENSOR_H

#include<cmath>
#include <string>
using namespace std;

class Sensor {

//    int setUnTreatedVal;
public:
    void setUnTreatedVal(int unTreatedVal);

    void setDecimalDigit(int decimalDigit);

    float getValue();
    string getName() const;
    void setName(const string &value);

    int getOffsetAddress() const;
    void setOffsetAddress(int value);

private:
    int unTreatedVal;
    int decimalDigit;
    string name;
    int offsetAddress;
};
class TemperatureSensor:public Sensor{

};
class LiquidFlowSpeed:public Sensor{

};
class AirFlowSpeed:public Sensor{

};
class AirPressure:public Sensor{

};
class RotationalSpeed:public Sensor{

};

#endif //HWWMC_SENSOR_H
