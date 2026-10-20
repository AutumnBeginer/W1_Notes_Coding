#include <iostream>  // cin, cout
#include <cstdio>    // printf, scanf（可选，本文件只用 cout）

int main() {
    // ---------- 栈内存 ----------
    int a = 42;              // 栈变量 a
    int b = 73;              // 栈变量 b
    int stack_arr[3] = {1, 2, 3};  // 栈数组

    // ---------- 堆内存 ----------
    int* heap_single = new int(999);      // 单个 int 堆空间
    int* heap_arr = new int[3]{4, 5, 6};  // 堆数组

    // ---------- 指针偏移 ----------
    int* ptr = stack_arr;   // ptr 指向栈数组首元素

    std::cout << "Pause point 1" << std::endl;   // ← 断点

    // 释放堆内存
    delete heap_single;
    delete[] heap_arr;
    heap_single = nullptr;   // C++11 起推荐 nullptr
    heap_arr = nullptr;

    std::cout << "Pause point 2" << std::endl;   // ← 断点
    return 0;
}