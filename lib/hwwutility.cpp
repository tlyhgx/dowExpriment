#include "hwwutility.h"

HwwUtility::HwwUtility()
{


}

vector<int> HwwUtility::xor_get_diff(int one, int two)
{
    vector<int> xors;
    int xor_val=one^two;

    xors=int_vector_int_0_1(xor_val);


    return xors;
}

vector<int> HwwUtility::int_vector_int_0_1(int givenVal)
{
    vector<int> xors;



    for(int i=0;i<sizeof(int)*8;i++)
    {
        xors.push_back((givenVal>>i)&1);
    }

    return xors;
}
