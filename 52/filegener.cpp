#include <iostream>
#include <fstream>
#include <random>
#include <sstream>
using namespace std;

void generate_text_file(int size) {
    ofstream out("textFile.txt");

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1000000, 9999999);

    for (int i = 0; i < size; i++) {
        int num = dist(gen);
        out << num << " " << "Предприятие" << to_string(num) << " " << "Учредитель" << to_string(num) << endl;
    }

    out.close();
}

void text_to_bin(int size) {
    int id;
    string line, pred, uch;
    ifstream in("textFile.txt");
    ofstream out("binfile.bin", ios_base::binary);
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));

    while (getline(in, line)) {
        stringstream ss(line);
        ss >> id;
        ss >> pred;
        ss >> uch;
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));

        size_t pred_length = pred.length();
        out.write(reinterpret_cast<const char*>(&pred_length), sizeof(pred_length));
        out.write(pred.c_str(), pred_length);

        size_t uch_length = uch.length();
        out.write(reinterpret_cast<const char*>(&uch_length), sizeof(uch_length));
        out.write(uch.c_str(), uch_length);
    }
    in.close();
    out.close();
}

int main() {
    int static const FILE_SIZE = 10000;
    generate_text_file(FILE_SIZE);
    text_to_bin(FILE_SIZE);
    //read_and_verify_bin();
    return 0;
}