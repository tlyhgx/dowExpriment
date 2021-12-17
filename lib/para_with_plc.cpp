#include "getplcval.h"
#include "para_with_plc.h"

Para_with_plc::Para_with_plc(string name, TreatmentMethod treatmentMethod, float givenVal)
{
    this->givenVal=givenVal;
    this->treatmentMethod=treatmentMethod ;
}

vector<int16_t> Para_with_plc::getResVal_DWORD()
{
    vector<int16_t> res;
    if(treatmentMethod==TreatmentMethod::x10)
    {res.push_back(0);

    int16_t word_two_value= givenVal*10;

    res.push_back(word_two_value);}
    else if(treatmentMethod==TreatmentMethod::to_float)
    {
        res=GetPlcVal::parseFloat2Int(givenVal);
    }

    return res;
}
