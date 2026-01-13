#include "lul.h"

using namespace std;

int main() {
    setColor(0, 11);

    setlocale(LC_ALL, "rus");

    int n = 9, m = 9;
    int a[9][9] = {};
    string begin = "(^-^) ====== S U D O K U ====== (^-^)";
    string continue_file, filename;

    printScreensaver();

    cout << endl;

    printMenu(a, begin);

    return 0;
}
