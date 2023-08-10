
#include <string>
#include <iostream>
#include <algorithm> // reverse
using namespace std;

// 编程题目：请实现以下类的方法，完成大数的加减法
/**
 * 考点：ASCII码 与 相加进位
 * 
 * char转int：char类型的'9'可以通过减'0'快速得到对应的int类型：'9' - '0' = 9 ;
 * int转char：反之，9 + '0' = '0' ;
 * 还有就是要注意进位或借位。
 */

class BigInt
{
private:
    string strBigInt;  // 使用字符串存储大整数
public:
    BigInt(string str) : strBigInt(str) {}
    ~BigInt() = default;

    friend ostream& operator<<(ostream &out, const BigInt& src);
    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
};

// 打印函数
ostream& operator<< (ostream& out, const BigInt& src)
{
    out << src.strBigInt;
    return out;
}

/**
 * @brief 大数加法
 * 
 * 实现思路：从后（个位）往前遍历字符串l,r
 * 同位置的数字相加，同时考虑进位flag的处理逻辑
 * 考虑同时遍历完成、以及某个字符串先遍历完成的情况，
 * 所有遍历完成后，还需要考虑进位！
 * 用string的push_back操作来逐位存储结果，最后需要倒序输出
 * 
 * @param lhs 
 * @param rhs 
 * @return BigInt 
 */
BigInt operator+ (const BigInt& lhs, const BigInt& rhs)
{
    string result;  // 存放结果
    bool flag = false;  // 进位标识

    // 从个位(即倒序)开始相加
    int lhs_index = lhs.strBigInt.size() - 1;
    int rhs_index = rhs.strBigInt.size() - 1;
    for (; lhs_index >= 0 && rhs_index >= 0; --lhs_index, --rhs_index)
    {
        int ret = lhs.strBigInt[lhs_index] - '0' + rhs.strBigInt[rhs_index] - '0';
        // 如果之前有进位
        if (flag)
        {
            ret += 1;
            flag = false;
        }
        // 判断当前是否需要进位
        if (ret >= 10)
        {
            ret = ret % 10;
            flag = true;
        }
        result.push_back(ret + '0');  // 后面还需要倒序输出
    }
    
    // 考虑两操作数长度不一，即 lhs_index 与 rhs_index 并未同步减至 -1
    if (lhs_index >= 0)
    {
        for (; lhs_index >= 0; --lhs_index)
        {
            int ret = lhs.strBigInt[lhs_index] - '0';
            // 如果之前有进位
            if (flag)
            {
                ret += 1;
                flag = false;
            }
            // 判断当前是否需要进位
            if (ret >= 10)
            {
                ret = ret % 10;
                flag = true;
            }
            result.push_back(ret + '0');  // 后面还需要倒序输出
        }
    } 
    else if (rhs_index >= 0)
    {
        for (; rhs_index >= 0; --rhs_index)
        {
            int ret = rhs.strBigInt[rhs_index] - '0';
            // 如果之前有进位
            if (flag)
            {
                ret += 1;
                flag = false;
            }
            // 判断当前是否需要进位
            if (ret >= 10)
            {
                ret = ret % 10;
                flag = true;
            }
            result.push_back(ret + '0');  // 后面还需要倒序输出
        }
    }

    // 最后还需要判断一次进位
    if (flag) {
        result.push_back('1');
    }

    reverse(result.begin(), result.end());
    
    return result;  // 隐式转换 BigInt(result)
}

/**
 * @brief 大数减法
 * 
 * 实现思路：找大的字符串作被减数，小的字符串作减数
 * 
 * @param lhs 
 * @param rhs 
 * @return BigInt 
 */
BigInt operator-(const BigInt& lhs, const BigInt& rhs)
{
    string result;
    bool flag = false;  // 借位项
    bool minor = false;  // 表示最终结果是否需要带负号

    string maxStr = lhs.strBigInt;
    string minStr = rhs.strBigInt;
    if (maxStr.size() < minStr.size())
    {
        swap(maxStr, minStr);
        minor = true;
    }
    else if (maxStr.size() == minStr.size())
    {
        if (maxStr < minStr)
        {
            swap(maxStr, minStr);
            minor = true;
        }
        else if (maxStr == minStr)
        {
            return string("0");
        }
    }

    // 大减小
    // 从个位(即倒序)开始相减
    int max_index = maxStr.size() - 1;
    int min_index = minStr.size() - 1;
    for (; max_index >= 0 && min_index >= 0; --max_index, --min_index)
    {
        int ret = maxStr[max_index] - minStr[min_index];
        // 如果之前有借位
        if (flag)
        {
            ret -= 1;
            flag = false;
        }
        // 判断当前是否需要借位
        if (ret < 0)
        {
            ret = 10 + ret;  // 注意这里还应该是加号而不是减号！
            flag = true;
        }
        result.push_back(ret + '0');  // 后面还需要倒序输出
    }

    for (; max_index >= 0; --max_index)
    {
        int ret = maxStr[max_index] - '0';
        // 如果之前有借位
        if (flag)
        {
            ret -= 1;
            flag = false;
        }
        // 判断当前是否需要借位
        if (ret < 0)
        {
            ret = 10 + ret;  // 注意这里还应该是加号而不是减号！
            flag = true;
        }
        result.push_back(ret + '0');  // 后面还需要倒序输出
    }
    
    // 最后还需要删除高位的0（但须保留最后个位的0）：例如121-120=001，121-121=000
    while (result.size() > 1 && result.back() == '0') {
        result.pop_back();
    }

    if (minor) {
        result.push_back('-');
    }

    reverse(result.begin(), result.end());

    return result;
}

int main() {
    BigInt int1("123456789");
    BigInt int2("123456789123");
    cout << int1 + int2 << "\n";
    cout << int1 - int2 << "\n";
    BigInt int3("123456789999888");
    BigInt int4("123456789999889");
    cout << int3 - int4 << "\n";
    cout << int4 - int3 << "\n";
}