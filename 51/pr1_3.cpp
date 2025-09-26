#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now(); // - начало отсчета времени

    const long long arr_len = (10000000 + 63) / 64; // задаем длину массива long long
    unsigned long long arr[arr_len] = {};
    size_t arr_size = arr_len * sizeof(long long); // получаем размер массивай в байтах

    int k, n;
    unsigned long long maska = 1;

    ifstream file("file.txt"); // читаем файл

    while (file >> n) { // считываем числа из файла пока они не закончатся
        k = n / 64; // получаем номер числа long long в битовом массиве
        n = n % 64; // получаем номер бита в числе long long
        arr[k] = arr[k] | (maska << (63 - n)); // поразрядной дизъюнкцией маски с единицей в n-ом бите и k-ого числа long long
        //cout << k << "  " << n << "  " << bitset<8> (arr[k]) << endl; // изменяем n-ый бит на единицу
    }
    for (int i = 0; i <= arr_len * 64 - 1; i++) {
        k = i / 64;
        n = i % 64;
        if ((arr[k] >> (63 - n)) & 1u == 1) { // вывод номера бита, если он равен 1
            //cout << i << " ";
        }
    }
    file.close();

    auto stop = chrono::high_resolution_clock::now(); // остановка счетчика времени
    // Calculate duration
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); //вычисление кол-ва прошедшего времени
    cout << "Время выполнения: " << duration.count() << " миллисекунд" << endl; // вывод времени в миллисекундах
    cout << "Элементов: " << arr_len << endl;
    cout << "Размер элемента: " << sizeof(long long) << " байтов" << endl;
    cout << "Объем в байтах: " << arr_size << " байтов" << endl;
    cout << "Объем в килобайтах: " << arr_size / 1024.0 << " Кб" << endl;
    cout << "Объем в мегабайтах: " << arr_size / 1024.0 / 1024.0 << " Мб" << endl; // вывод веса битового массива в мб
    return 0;
}