#include "getplcval.h"
#include "para_with_plc.h"

Para_with_plc::Para_with_plc(string name, TreatmentMethod treatmentMethod, float givenVal)
{
    this->m_givenVal=givenVal;
    this->treatmentMethod=treatmentMethod ;
}

vector<int16_t> Para_with_plc::getResVal_DWORD()
{
    vector<int16_t> res;
    if(treatmentMethod==TreatmentMethod::x10)
    {
        int16_t word_two_value= m_givenVal*10;
        res.push_back(word_two_value);
        res.push_back(0);}
    else if(treatmentMethod==TreatmentMethod::to_float)
    {
        res=GetPlcVal::parseFloat2Int(m_givenVal);
    }else if(treatmentMethod==TreatmentMethod::none){
        res.push_back(m_givenVal);
        res.push_back(0);
    }


    return res;
}

float Para_with_plc::getGivenVal() const
{
    return m_givenVal;
}

void Para_with_plc::setGivenVal(float givenVal)
{
    m_givenVal = givenVal;
}
