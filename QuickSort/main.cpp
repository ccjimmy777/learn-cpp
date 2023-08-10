/**
 * @file main.cpp
 * @author Cai Chuanjian
 * @brief 快速排序
 * @version 0.1
 * @date 2023-08-08
 * 
 * @copyright Copyright (c) 2023
 *
 * 快速排序思想：
 * 1. 选取一个基准数；
 * 2. 把小于基准数的元素调整到其左边，把大于基准数的调整至其右边；
 * 3. 分别对左右序列继续执行上述操作，直至无法再分（此时整个序列变为有序）。
 * 
 * 注：
 * 1. 需要用到递归，与二叉树的前序遍历类似：先处理中间节点，再递归左右孩子；
 * 2. 快速排序是不稳定排序；
 * 3. 快速排序的时间复杂度
 * 4. 快速排序的空间复杂度为O(1)（快排是原地操作，无需开辟新的内存空间）。
 */
#include <vector>
#include <algorithm>  // for_each
#include <iostream>
using namespace std;

/**
 * @brief 快速排序（递归接口）
 * 
 * @param data 待排序数组
 * @param begin 数组的左边界（包含）
 * @param end 数组的右边界（不包含）
 */
void quickSort(vector<int>& data, int begin, int end)
{
    // for_each(data.begin(), data.end(), [](const auto a) {cout << a << " "; });
	// cout << "\n";

    // 递归终止条件
    if (begin >= end - 1 || begin < 0 || end > data.size()) return;
    
    // 单层递归逻辑：快排分割函数
    int key = data[begin];  // 选择基准数
    int l = begin;
    int r = end;

    while (l < r)
    {
        // 从end开始找第一个小于基准数的元素，覆盖至begin处
        while (l < r && data[r] >= key)
        {
            --r;
        }
        if (data[r] < key) {
            data[l] = data[r];  // 覆盖的要么是key（已记录），要么是已覆盖至右边的元素
        }

        // 从begin开始找第一个大于等于基准数的元素，覆盖至end处
        while (l < r && data[l] < key)
        {
            ++l;
        }
        if (data[l] >= key) {
            data[r] = data[l];
        }
    }

    // begin == end
    data[l] = key;
    
    // 
    quickSort(data, begin, l);
    quickSort(data, l + 1, end);
}

int main()
{
    vector<int> data {32, 8, 7, 10, 38, 46, 68, 76, 65, 53};
    
    for_each(data.begin(), data.end(), [](const auto a) {cout << a << " "; });
    cout << "\n";

    quickSort(data, 0, data.size());

    for_each(data.begin(), data.end(), [](const auto a) {cout << a << " "; });
	cout << "\n";
}