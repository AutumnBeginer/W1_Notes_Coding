#include <vector>
#include <iostream>
using namespace std;

vector<int> bubbleSort(vector<int> vec) {
    // 如果数组中只有一个元素或者为空，直接返回
    if (vec.size() <= 1) {
        return vec;
    }

    // 初始化交换次数，如果已经排序过，可以跳过
    int n = vec.size();
    int swaps = 0;

    for (int i = 0; i < n - 1; ++i) {
        // 第i个元素与后面所有未排序的元素比较
        for (int j = 0; j < n - i - 1; ++j) {
            // 如果当前元素大于下一个元素，交换它们
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
                swaps++;
            }
        }
    }

    if (swaps == 0) {
        // 已经排序过，直接返回
        return vec;
    }

    return vec;
}

int main() {
    vector<int> arr = {5, 2, 9, 1, 3};
    vector<int> sortedArr = bubbleSort(arr);
    
    cout << "排序后的数组: ";
    for (int num : sortedArr) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}