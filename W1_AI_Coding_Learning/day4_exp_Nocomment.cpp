#include <cstdio> // 包含标准输入输出库
using namespace std; // 使用标准命名空间
int main() {
    int n; // 声配一个整数变量n，用于存储输入的整数个数
    scanf("%d", &n); // 从标准输入读取一个整数，存储在变量n中
    int a[100]; // 壮配一个整数数组a，用于存储输入的整数
    for (int i = 0; i < n; i++) { // 遍历输入的整数个数
        scanf("%d", &a[i]); // 从标准输入读取一个整数，存储在数组a的第i个位置
    }
    // 下面计算平均值并输出
    int sum = 0; // 初始化一个整数变量sum，用于存储输入整数的和
    for (int i = 0; i < n; i++) { // 遍历输入的整数个数
        sum += a[i]; // 将数组a的第i个位置的整数累加到sum中
    }
    double avg = (double)sum / n; // 计算平均值
    printf("%.2f\n", avg); // 输出平均值，保留两位小数
    return 0; // 返回0表示程序结束
}

// 该程序的功能是从标准输入读取一组整数，计算它们的平均值并输出。

