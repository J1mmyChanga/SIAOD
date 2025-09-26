#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;

int main() {
    auto start = chrono::high_resolution_clock::now(); // - ��砫� ����� �६���

    const long long arr_len = (10000000 + 63) / 64; // ������ ����� ���ᨢ� long long
    unsigned long long arr[arr_len] = {};
    size_t arr_size = arr_len * sizeof(long long); // ����砥� ࠧ��� ���ᨢ�� � �����

    int k, n;
    unsigned long long maska = 1;

    ifstream file("file.txt"); // �⠥� 䠩�

    while (file >> n) { // ���뢠�� �᫠ �� 䠩�� ���� ��� �� ���������
        k = n / 64; // ����砥� ����� �᫠ long long � ��⮢�� ���ᨢ�
        n = n % 64; // ����砥� ����� ��� � �᫥ long long
        arr[k] = arr[k] | (maska << (63 - n)); // ��ࠧ�來�� ����樥� ��᪨ � �����楩 � n-�� ��� � k-��� �᫠ long long
        //cout << k << "  " << n << "  " << bitset<8> (arr[k]) << endl; // �����塞 n-� ��� �� �������
    }
    for (int i = 0; i <= arr_len * 64 - 1; i++) {
        k = i / 64;
        n = i % 64;
        if ((arr[k] >> (63 - n)) & 1u == 1) { // �뢮� ����� ���, �᫨ �� ࠢ�� 1
            //cout << i << " ";
        }
    }
    file.close();

    auto stop = chrono::high_resolution_clock::now(); // ��⠭���� ���稪� �६���
    // Calculate duration
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start); //���᫥��� ���-�� ��襤襣� �६���
    cout << "�६� �믮������: " << duration.count() << " �����ᥪ㭤" << endl; // �뢮� �६��� � �����ᥪ㭤��
    cout << "������⮢: " << arr_len << endl;
    cout << "������ �����: " << sizeof(long long) << " ���⮢" << endl;
    cout << "��ꥬ � �����: " << arr_size << " ���⮢" << endl;
    cout << "��ꥬ � ���������: " << arr_size / 1024.0 << " ��" << endl;
    cout << "��ꥬ � ���������: " << arr_size / 1024.0 / 1024.0 << " ��" << endl; // �뢮� ��� ��⮢��� ���ᨢ� � ��
    return 0;
}