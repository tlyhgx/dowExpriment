#ifndef PARA_WITH_PLC_H
#define PARA_WITH_PLC_H

#include <string>
#include <vector>
using namespace std;

enum class TreatmentMethod
{
    x10,
    to_float,
    none
};

class Para_with_plc
{
public:
//    enum TreatmentMethod{
//        x10,
//        to_float
//    };
    Para_with_plc(string name, TreatmentMethod treatmentMethod, float givenVal);
    //返回代表双字的数组
    vector<int16_t>  getResVal_DWORD();

private:
    float givenVal;
    TreatmentMethod treatmentMethod;
};

#endif // PARA_WITH_PLC_H
