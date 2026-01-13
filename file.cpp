#include "lul.h"

using namespace std;

bool checkFile() {
    string filename = "saving.txt";
    ifstream file(filename);

    if (!file.is_open()) {
        return true;
    }

    file.seekg(0, ios::end);
    streampos fileSize = file.tellg();

    file.close();

    return (fileSize == 0);
}

void saving(int(&a)[9][9]) {
    ofstream file("saving.txt");
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                file << a[i][j] << " ";
            }
            file << endl;
        }
    }
}
