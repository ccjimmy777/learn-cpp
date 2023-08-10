/**
 * @file main.cpp
 * @author caichuanjian@foxmail.com
 * @brief 归并排序
 * @version 0.1
 * @date 2023-08-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/**
 * 归并算法的思想：
 * “归” 即递归，在递的过程中缩小问题规模，并在归（返回）的过程中进行数据合并，达到排序的效果！
 * 
 * 需要解决的问题：
 * 1. 何时归：递到什么程度才开始归？即问题规模缩小到什么程度时才可以进行数据合并了？
 * 2. 如何并：怎么做数据合并？
 * 
 * 答：
 * 1. 一直递到一个元素到头（一个元素的序列一定是有序的），然后就可以准备数据合并了；
 * 2. 数据合并需要为新序列额外分配内存空间，然后将两个小段有序序列分别从头开始遍历比较，按序写到新序列中。
 * * 注：也可以直接对原始序列写数据做排序，但需要先拷贝这两个小段有序序列，否则无法比较元素了！
 */

#include <iostream>
#include <vector>
#include <algorithm>  // for_each
using namespace std;

/**
 * @brief 合并两个有序数组：data[begin, mid) 和 data[mid, end)
 * 
 * 归并排序的核心操作：
 * 
 * 将两个小段有序序列分别从头开始遍历比较，按序写到新序列中，
 * 遍历完毕后，新序列也是有序的了。
 * 
 * 注意：
 * 这里的实现是拷贝这两个小段有序数组，而直接原地修改原数组，
 * 因而请特别注意小段数组与原数组的遍历索引的区别！
 * 
 * @param data 原数组（待排序）
 * @param begin 第一个有序数组的左边界在原数组中的索引
 * @param mid 第一个有序数组的右边界（第二个有序数组的左边界）在原数组中的索引
 * @param end 第二个有序数组的右边界在原数组中的索引
 */
void merge(vector<int>& data, int begin, int mid, int end)
{
    vector<int> seg1(data.begin() + begin, data.begin() + mid);
    vector<int> seg2(data.begin() + mid, data.begin() + end);

    int seg1_index = 0, seg2_index = 0;
    int data_index = begin;
    while (seg1_index < seg1.size() && seg2_index < seg2.size())
    {
        if (seg1[seg1_index] < seg2[seg2_index]) {
            data[data_index++] = seg1[seg1_index++];
        } else {
            data[data_index++] = seg2[seg2_index++];
        }
    } 
    while (seg1_index < seg1.size())
    {
        data[data_index++] = seg1[seg1_index++];
    } 
    while (seg2_index < seg2.size())
    {
        data[data_index++] = seg2[seg2_index++];
    } 
}

/**
 * @brief 归并排序（递归接口）
 * 
 * @param data 待排序数组
 * @param begin 数组的左边界（包含）
 * @param end 数组的右边界（不包含）
 */
void mergeSort(vector<int>& data, int begin, int end)
{
    // 递归结束条件
    if (begin >= end - 1) return;

    // 单层递归逻辑：先递后归（在归的过程中合并），类似二叉树的后序遍历
    
    // 先递
    int mid = begin + (end - begin) / 2;  // Do Not "= (begin + end) / 2" to avoid integer overflow
    mergeSort(data, begin, mid);  // [begin, mid)
    mergeSort(data, mid, end);   // [mid, end)
    
    // 再归（并）
    // 把两个小段有序序列 [begin, mid) + [mid, end) 合并为一段有序序列
    merge(data, begin, mid, end);
    
    // 单层递归逻辑完毕，返回上一层递归
}

int main()
{
    vector<int> data {38, 62, 75, 81, 99, 14, 36, 40, 51, 60};

    for_each(data.begin(), data.end(), [](const int& e){ 
        cout << e << " "; 
    });
    cout << "\n"; 

    mergeSort(data, 0, data.size());
    
    for_each(data.begin(), data.end(), [](const int& e){ 
        cout << e << " "; 
    });
    cout << "\n"; 
}