#ifndef HWWUTILITY_H
#define HWWUTILITY_H

#include<vector>
using namespace std;
class HwwUtility
{
public:
    HwwUtility();
    ///����������ͬ������ͨ�����õ���ͬ��������λ����
    /// \brief xor_get_diff
    /// \param one
    /// \param two
    /// \return
    ///
    static vector<int> xor_get_diff(int one,int two);
    ///����һ��intֵת��Ϊvector<int> ֻ����0��1
    /// \brief int_vector_int_0_1
    /// \param givenVal
    /// \return
    ///
    static vector<int> int_vector_int_0_1(int givenVal);
};

#endif // HWWUTILITY_H
