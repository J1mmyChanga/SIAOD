#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iterator>
#include <string>
#include <random>
using namespace std;

int main() {
    vector<int> vec;
    for (int i = 1000000; i <= 9999999; i++) {
        vec.push_back(i);
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);

    ofstream output_file("./file.txt");
    ostream_iterator<int> output_iterator(output_file, "\n");
    copy(vec.begin(), vec.end(), output_iterator);
    return 0;
}