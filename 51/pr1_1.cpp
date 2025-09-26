#include <iostream>
#include <bitset>
using namespace std;

int main() {
    // unsigned char x=32; //8-разрядное двоичное число 00100000
    // unsigned char maska = 1; //1=00000001 ? 8-разрядная маска
    // x = x | (maska<<4); //результат x=239
    // cout << bitset<8> (x) << endl;

    // unsigned char x=141;
    // unsigned char maska = 1;
    // cout << bitset<8> (x) << endl; // - вывод 10001101
    // cout << bitset<8> (maska) << endl; // - вывод маски 00000001
    // x = x | (maska<<1); // - поразрядное или
    // cout << bitset<8> (x) << endl;
    // cout << (int)x << endl;

    unsigned int x = 25;
    const int n = sizeof(int)*8; // количество бит в битовом массиве
    unsigned int maska = (1 << n - 1); // смещение единичного бита в маске в начало битового массива
    cout << "Начальный вид маски: " << bitset<n> (maska) << endl;
    cout << "Результат: ";
    for (int i = 1; i <= n; i++) { // переборка каждого бита битового массива числа
        cout << ((x & maska) >> (n - i)); // получение i-ого бита числа и приписывание его к концу записи
        maska = maska >> 1; // сдвиг бита маски на 1 вправо
    }
    cout << endl;
    return 0;
}