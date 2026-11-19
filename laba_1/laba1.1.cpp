#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

int main() {
    SetConsoleOutputCP(1251);

    const int n = 10;
    double* arr = new double[n];

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 1.5;
    }

    cout << fixed << setprecision(1);

    cout << "Содержимое массива:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    cout << "\nАдрес начала массива: " << arr << endl;

    cout << "\nРасстояние элементов от начала массива (в байтах):" << endl;
    for (int i = 0; i < n; i++) {
        long long distance = (long long)&arr[i] - (long long)arr;
        cout << "Элемент arr[" << i << "] находится на расстоянии "
            << distance << " байт от начала." << endl;
    }

    delete[] arr;
    arr = nullptr;

    return 0;
}