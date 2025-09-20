#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <bitset>
using namespace std;

int main() {
    // unsigned char num = 0;
    // int n;
    // unsigned char maska = 1;
    // cin >> n;
    // while (n >= 0 and n <= 7) { // - ввод сортируемых чисел
    //     //cout << bitset<8> (maska << (7 - n)) << endl;
    //     num = num | (maska << (7 - n)); // - изменение n-ого бита в битовом массиве с 0 на 1 путем поразрядного
    //     cin >> n;                       // умножения на маску с предварительно сдвинутым единичным битом на n позиций
    // }
    // for (int i = 7; i >= 0; i--) {
    //     if ((num >> i) & 1u == 1) { // вывод номера бита, если он равен 1, те вывод отсортированного массива
    //         cout << 7 - i << " ";
    //     }
    // }

    // unsigned long long num = 0;
    // int n;
    // unsigned long long maska = 1;
    // cin >> n;
    // while (n >= 0 and n <= 63) {
    //     //cout << bitset<64> (maska << (63 - n)) << endl;
    //     num = num | (maska << (63 - n));
    //     cin >> n;
    // }
    // for (int i = 63; i >= 0; i--) {
    //     if ((num >> i) & 1u == 1) {
    //         cout << 63 - i << " ";
    //     }
    // }

    const int arr_len = 10; // - установка длины массива в числах
    unsigned char arr[arr_len] = {}; // - создание пустого массива
    int n, k;
    unsigned char maska = 1;
    cin >> n;
    while (n >= 0 and n <= arr_len * 8 - 1) { // число меньше чем длина массива умноженная на длину одного элемента в битах
        k = n / 8; // номер байта
        n = n % 8; // номер бита в байте
        arr[k] = arr[k] | (maska << (7 - n)); // изменения нужного бита с нуля на единицу
        //cout << k << "  " << n << "  " << bitset<8> (arr[k]) << endl;
        cin >> n;
    }
    for (int i = 0; i <= arr_len * 8 - 1; i++) {
        k = i / 8;
        n = i % 8;
        if ((arr[k] >> (7 - n)) & 1u == 1) { // сравнение каждого бита с единицей
            //cout << arr_len * 8 - 1 - (k * 8 + n) << " ";
            cout << i << " "; // вывод номера единичного бита
        }
    }
    return 0;
}