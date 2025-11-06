// 实验三：使用信号量实现三个线程的互斥输出（替代实验二的线程并发但无保护）
#include <windows.h>
#include <iostream>
using namespace std;

// 创建一个信号量，初值为1，最大值为1 --> 互斥信号量
HANDLE hSemaphore;

// 线程函数：打印A
DWORD WINAPI Print_A(LPVOID lpParam) {
    WaitForSingleObject(hSemaphore, INFINITE); // 进入临界区
    printf("A\n"); // 临界区代码
    ReleaseSemaphore(hSemaphore, 1, NULL);     // 离开临界区
    return 0;
}

// 线程函数：打印B
DWORD WINAPI Print_B(LPVOID lpParam) {
    WaitForSingleObject(hSemaphore, INFINITE);
    printf("B\n");
    ReleaseSemaphore(hSemaphore, 1, NULL);
    return 0;
}

// 线程函数：打印C
DWORD WINAPI Print_C(LPVOID lpParam) {
    WaitForSingleObject(hSemaphore, INFINITE);
    printf("C\n");
    ReleaseSemaphore(hSemaphore, 1, NULL);
    return 0;
}

int main() {
    // 初始化信号量，初始为1，最大为1
    hSemaphore = CreateSemaphore(NULL, 1, 1, NULL);
    if (hSemaphore == NULL) {
        cout << "创建信号量失败！" << endl;
        return 1;
    }

    HANDLE hThreads[3];

    // 创建三个线程
    hThreads[0] = CreateThread(NULL, 0, Print_A, NULL, 0, NULL);
    hThreads[1] = CreateThread(NULL, 0, Print_B, NULL, 0, NULL);
    hThreads[2] = CreateThread(NULL, 0, Print_C, NULL, 0, NULL);

    if (hThreads[0] == NULL || hThreads[1] == NULL || hThreads[2] == NULL) {
        cout << "创建线程失败！" << endl;
        return 1;
    }

    // 等待所有线程完成
    WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);

    // 关闭句柄
    for (int i = 0; i < 3; i++) {
        CloseHandle(hThreads[i]);
    }
    CloseHandle(hSemaphore);

    cout << "主线程结束。" << endl;
    system("pause");
    return 0;
}