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
 * 3. 快速排序的空间复杂度为 O(logN) ~ O(N)（尽管快排是原地操作，无需开辟新的内存空间，但递归过程需要占用栈空间）；
 * 4. 快速排序的时间复杂度为 O(NlogN) ~ O(N^2)。
 */
#include <vector>
#include <algorithm>  // for_each
#include <iostream>
using namespace std;

/**
 * 快速排序的优化1：
 * 
 * 当数据趋于有序，或者已经有序了，什么排序算法效率最高？  ==> 插入排序
 * 
 * 因此，随着快排的递归深入，数据将越来越趋于有序，在一定范围内可采用插入排序代替快速排序；
 */
#define USE_INSERT_SORT 0

/**
 * 快速排序的优化2：
 * 
 * 理论上，如果可以选择中间大小的数值作为基准数，那么可以生成完美的二叉平衡树
 * （越平衡，空间复杂度越接近 O(N)，时间复杂度越接近 O(NlogN)）
 * 
 * 实践中，可以采用 “三数取（数值居）中” 法 或 随机数法，尽量找到合适的基准数
 * 
 * 注意：
 * 找到合适的基准数后，需要先将它与左边第一个数换位置，然后再做快排分割操作
 */
#define USE_MEDIAN_OF_THREE 0

/**
 * @brief 快排分割函数
 * 
 * 快速排序的核心操作:
 * 1. 选取（第）一个基准数；
 * 2. 把小于基准数的元素调整到其左边，把大于基准数的调整至其右边。
 * 
 * @param data 待排序数组
 * @param begin 数组的左边界（包含）
 * @param end 数组的右边界（不包含）
 * @return 基准数调整后的位置索引，即分割点
 */
int partition(vector<int>& data, int begin, int end)
{
    // 选择基准数
#if USE_MEDIAN_OF_THREE

#else

    int key = data[begin];

#endif

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

    return l;
}

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

#if USE_INSERT_SORT

    if (end - begin <= 50)
    {
        insertSort(data, begin, end);
        return;
    }
    
#endif
    // 单层递归逻辑：先快排分割，再左右递归（类似二叉树的前序遍历）
    // 先快排分割
    int mid = partition(data, begin, end);
    
    // 再左右递归
    quickSort(data, begin, mid);
    quickSort(data, mid + 1, end);
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