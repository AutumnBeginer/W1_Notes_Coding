#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;//输入几个数
    int* arr = new int[n];//指针指向新建数组
    for (int i = 0; i < n; i++) {//依次输入n个数组元素
        cin >> arr[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    cout << sum << endl;//求和
    delete[] arr;//释放空间
    return 0;
}