#include "lul.h"

using namespace std;


void printScreensaver() {
    char str[] = "(^-^) ====== S  U  D  O  K  U ====== (^-^)";
    cout << endl << setw(45);
    setColor(0, 159);
    for (int i = 0; i < strlen(str); i++) {
        Sleep(300);
        cout << str[i];
    }
    resetColor();
    setColor(0, 11);
    cout << endl;
}


void setColor(int bg, int fg) {
    // фон
    cout << "\033[48;5;" << bg << "m";
    // текст  
    cout << "\033[38;5;" << fg << "m";
}


void resetColor() {
    cout << "\033[0m";
}

