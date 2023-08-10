/**
 * @file main.cpp
 * @author caichuanjian@foxmail.com
 * @brief 数据查重/去重问题
 * @version 0.1
 * @date 2023-08-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * 涉及数据查重/去重，应当有如下思路：
 * 1. 哈希表：用空间（空间复杂度高）换时间（时间复杂度低），速度快，但要考虑内存限制；
 *    - 分治思想
 * 2. 位图法
 * 3. 布隆过滤器
 * 
 * 特别地，有没有专门针对字符串类型的查重方法？
 * 4. TrieTree字典树（前缀树）
 */

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
    

    return 0;
}