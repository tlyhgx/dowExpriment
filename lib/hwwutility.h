#ifndef HWWUTILITY_H
#define HWWUTILITY_H

#include<vector>
using namespace std;
class HwwUtility
{
public:
    HwwUtility();
    ///输入两个不同的数，通过异或得到不同数的所在位置组
    /// \brief xor_get_diff
    /// \param one
    /// \param two
    /// \return
    ///
    static vector<int> xor_get_diff(int one,int two);
    ///输入一个int值转换为vector<int> 只包含0，1
    /// \brief int_vector_int_0_1
    /// \param givenVal
    /// \return
    ///
    static vector<int> int_vector_int_0_1(int givenVal);
};

#endif // HWWUTILITY_H
