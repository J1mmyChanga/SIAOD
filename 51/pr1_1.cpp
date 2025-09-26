#include <iostream>
#include <bitset>
using namespace std;

int main() {
    // unsigned char x=32; //8-ࠧ�來�� ����筮� �᫮ 00100000
    // unsigned char maska = 1; //1=00000001 ? 8-ࠧ�來�� ��᪠
    // x = x | (maska<<4); //१���� x=239
    // cout << bitset<8> (x) << endl;

    // unsigned char x=141;
    // unsigned char maska = 1;
    // cout << bitset<8> (x) << endl; // - �뢮� 10001101
    // cout << bitset<8> (maska) << endl; // - �뢮� ��᪨ 00000001
    // x = x | (maska<<1); // - ��ࠧ�來�� ���
    // cout << bitset<8> (x) << endl;
    // cout << (int)x << endl;

    unsigned int x = 25;
    const int n = sizeof(int)*8; // ������⢮ ��� � ��⮢�� ���ᨢ�
    unsigned int maska = (1 << n - 1); // ᬥ饭�� �����筮�� ��� � ��᪥ � ��砫� ��⮢��� ���ᨢ�
    cout << "��砫�� ��� ��᪨: " << bitset<n> (maska) << endl;
    cout << "�������: ";
    for (int i = 1; i <= n; i++) { // ��ॡ�ઠ ������� ��� ��⮢��� ���ᨢ� �᫠
        cout << ((x & maska) >> (n - i)); // ����祭�� i-��� ��� �᫠ � �ਯ��뢠��� ��� � ����� �����
        maska = maska >> 1; // ᤢ�� ��� ��᪨ �� 1 ��ࠢ�
    }
    cout << endl;
    return 0;
}