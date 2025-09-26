#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

class Record {
public: int id;
    string pred;
    string uch;

    Record(int id, string pred, string uch) {
        this->id = id;
        this->pred = pred;
        this->uch = uch;
    }

    void printInfo() {
        cout << this->id << " " << this->pred << " " << this->uch << endl;
    }
};


struct RecordIndex {
    int key;        // Ключ (ID записи)
    streampos pos;  // Смещение записи в файле

    // Для сортировки и бинарного поиска
    bool operator<(const RecordIndex& other) const {
        return key < other.key;
    }
};

class BinarySearch {
    string filename;
    vector<RecordIndex> indexTable;
public:
    BinarySearch(string file) {
        filename = file;
    }
    void buildTable() {
        ifstream in(filename, ios_base::binary);

        int size;
        in.read(reinterpret_cast<char*>(&size), sizeof(size));

        for (int i = 0; i < size; i++) {
            streampos currentPos = in.tellg();  // Запоминаем позицию(курсор), tellg - возвращает позицию указателоя чтения

            int id;
            in.read(reinterpret_cast<char*>(&id), sizeof(id));
            size_t pred_length, uch_length;
            in.read(reinterpret_cast<char*>(&pred_length), sizeof(pred_length));
            in.seekg(pred_length, ios::cur);
            in.read(reinterpret_cast<char*>(&uch_length), sizeof(uch_length));
            in.seekg(uch_length, ios::cur);
            indexTable.push_back({id, currentPos});
        }
        sort(indexTable.begin(), indexTable.end());
        in.close();
    }

    streampos binarySearch(int key) {
        int left = 0;
        int right = indexTable.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (indexTable[mid].key == key) {
                return indexTable[mid].pos;  // Возвращаем смещение
            }

            if (indexTable[mid].key < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return streampos(-1);
    }

    Record searchByPos(streampos position) {
        ifstream in(filename, ios_base::binary);
        in.seekg(position);  // Прямой доступ к записи

        int id;
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t pred_length, uch_length;
        in.read(reinterpret_cast<char*>(&pred_length), sizeof(pred_length));
        string pred(pred_length, ' ');
        in.read(&pred[0], pred_length);
        in.read(reinterpret_cast<char*>(&uch_length), sizeof(uch_length));
        string uch(uch_length, ' ');
        in.read(&uch[0], uch_length);

        in.close();
        return Record(id, pred, uch);
    }
};

Record linear_search(int value) {
    ifstream in("binfile.bin", ios_base::binary);

    int size;
    in.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (int i = 0; i < size; i++) {

        int id;
        in.read(reinterpret_cast<char*>(&id), sizeof(id));
        size_t pred_length, uch_length;
        in.read(reinterpret_cast<char*>(&pred_length), sizeof(pred_length));
        string pred(pred_length, ' ');
        in.read(&pred[0], pred_length);
        in.read(reinterpret_cast<char*>(&uch_length), sizeof(uch_length));
        string uch(uch_length, ' ');
        in.read(&uch[0], uch_length);

        if (id == value) {
            Record rec = Record(id, pred, uch);
            return rec;
        }
    }
    in.close();
    Record rec = Record(0, "", "");
    return rec;
}

int main() {
    int const SEARCHING_EL = 8577121;
    auto start = chrono::high_resolution_clock::now();
    //Record rec = linear_search(SEARCHING_EL);
    //rec.printInfo();

    BinarySearch bs = BinarySearch("binfile.bin");
    bs.buildTable();
    Record rec = bs.searchByPos(bs.binarySearch(SEARCHING_EL));
    rec.printInfo();

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "Время выполнения: " << duration.count() << "" << endl; // вывод времени в микросекундах
    return 0;
}