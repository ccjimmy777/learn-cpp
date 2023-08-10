#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stdlib.h>  // srand
#include <time.h>  // time

using namespace std;

int main()
{
    // 模拟问题，vector中放原始数据
    vector<int> vec;
    srand(time(NULL));
    for (int i = 0; i < 10000; i++)
    {
        vec.push_back(rand() % 10000);
    }
    
    // Q1: 找出第一个出现重复的数字
    unordered_set<int> s1;
    for (int key : vec)
    {
        // 先查找
        auto it = s1.find(key);
        
        if (it == s1.end())  // 如果没有找到
        {
            s1.insert(key);
        } 
        else  // 如果找到
        {
            cout << "find duplicate key: " << key << "\n";
            break;
            // return key;
        }
    }
    
    // Q1.1：找出所有重复出现的数字
    // 去除Q1代码中的 break; 即可

    // Q2: 统计重复出现的数字及重复次数
    unordered_map<int, int> m1;  // <key, 出现次数>
    for (int key : vec)
    {
        m1[key]++;
    }
    
    for (auto pair : m1)
    {
        if (pair.second > 1) {
            cout << "find duplicate key: " << pair.first
                 << " counts: " << pair.second << "\n";
        }
    }

    // Q2.1: 统计没有重复出现过的第一个字符
    string str = "uxzigvzkjcbv1ux";
    unordered_map<char, int> m2;  // <key, 出现次数>
    for (char key : str)
    {
        m2[key]++;
    }
    // unordered_map是无序的，因此这么输出的结果不能保证是第一个出现的
    for (auto pair : m2)
    {
        if (pair.second == 1) {
            cout << "find 1st non-duplicate key: " << pair.first << "\n";
            break;
        }
    }
    // 应该是这样
    for (char key : str)
    {
        if (m2[key] == 1) {
            cout << "find 1st non-duplicate key: " << key << "\n";
            break;
        }
    }
    
    // Q3: 有两个文件分别是a和b，里面存放了很多ip地址（url地址、email地址），请找出两个文件中重复的ip并输出
    /**
     * 析：哈希表。
     * 先把a文件中所有的ip存放到一个哈希表中，然后依次遍历文件b中的ip，每遍历一个ip，就查询哈希表（查询复杂度
     * 仅为 O(1)）有无记录，搜到了就是有重复的ip，输出即可。
     * 
     */

    return 0;
}