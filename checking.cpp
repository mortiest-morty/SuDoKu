#include "lul.h"

using namespace std;

bool checkMenuCin(int choice) {
    if (choice < 1 || choice > 3) {
        setColor(0, 203);

        cout << "\nОшибка!\n";
        cout << "Введите цифру от 1 до 3: ";
        cin.clear();
        cin.ignore(10000, '\n');

        resetColor();
        setColor(0, 11);

        return false;
    }
    else return true;
}


// проверка ввода цифр в выборе уровня сложности
bool checkLevelCin(int choice) {
    if (choice < 1 || choice > 3) {
        setColor(0, 203);

        cout << "\nОшибка!\n";
        cout << "Введите цифру от 1 до 3: ";
        cin.clear();
        cin.ignore(10000, '\n');

        resetColor();
        setColor(0, 11);

        return false;
    }
    else return true;
}

//проверка ввода при вставке цифр пользователем
int checkPaste() {
    int value;

    while (true) {
        cin >> value;

        if (cin.fail()) {
            setColor(0, 203);
            cout << "Ошибка!\n Введите число от 1 до 9 (или 0/11): ";
            resetColor();
            setColor(0, 11);
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if ((value >= 1 && value <= 9) || value == 0 || value == 11) {
            return value;
        }

        setColor(0, 203);
        cout << "Ошибка!\n Введите от 1 до 9 (или 0/11): ";
        resetColor();
        setColor(0, 11);
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

//проверка смены цифры, столбца или строки пользователем
int checkChange() {
    int value;

    while (true) {
        cin >> value;

        // Проверка на нечисловой ввод
        if (cin.fail()) {
            setColor(0, 203);
            cout << "Ошибка!\n Введите число 1 или 2 (или 0/11): ";
            resetColor();
            setColor(0, 11);
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if ((value >= 1 && value <= 2) || value == 0 || value == 11) {
            return value;
        }

        setColor(0, 203);
        cout << "Ошибка!\n Введите 1 или 2 (или 0/11): ";
        resetColor();
        setColor(0, 11);
        cin.clear();
        cin.ignore(10000, '\n');
    }
}


// проверка возможности постановки цифры для создания игрового поля
bool canPlace(int(&a)[9][9], int n, int m, int num) {
    // Строка
    for (int x = 0; x < 9; x++) {
        if (a[n][x] == num) return false;
    }

    // Столбец
    for (int x = 0; x < 9; x++) {
        if (a[x][m] == num) return false;
    }

    // Квадрат 3x3
    int startRow = n - n % 3;
    int startCol = m - m % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i + startRow][j + startCol] == num) return false;
        }
    }

    return true;
}

//проверка возможности вставки цифры пользователем с выводом ошибок
bool opportunityToPaste(int num, int x, int y, int(&a)[9][9]) {
    int col = 0, row = 0, square = 0, empty = 0;

    x -= 1;
    y -= 1;

    if (a[x][y] != 0) {
        empty++;
    }

    for (int i = 0; i < 9; i++) {
        if (a[i][y] == num) {
            col++;
        }
    }

    for (int j = 0; j < 9; j++) {
        if (a[x][j] == num) {
            row++;
        }
    }

    int startRow = x - x % 3;
    int startCol = y - y % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (a[i + startRow][j + startCol] == num) square++;
        }
    }

    if (col == 0 && row == 0 && square == 0 && empty == 0) {
        a[x][y] = num;
        return true;
    }

    else {
        setColor(0, 204);

        if (empty > 0) cout << "\nЦифра уже есть в данной клетке ('_')";
        if (col == 0 && row > 0 && square == 0) cout << "\nЭта цифра уже есть в данной строке  ('_')";
        if (col == 0 && row > 0 && square > 0)  cout << "\nЭта цифра уже есть в данной строке и квадрате 3x3  ('_')";
        if (col > 0 && row > 0 && square == 0)  cout << "\nЭта цифра уже есть в данной строке и столбце  ('_')";
        if (col > 0 && row > 0 && square > 0)   cout << "\nЭта цифра уже есть в данной строке, столбце и квадрате 3x3  ('_')";
        if (row == 0 && col > 0 && square == 0) cout << "\nЭта цифра уже есть в данном столбце  ('_')";
        if (row == 0 && col > 0 && square > 0)  cout << "\nЭта цифра уже есть в данном столбце и квадрате 3x3  ('_')";
        if (row == 0 && col == 0 && square > 0)  cout << "\nЭта цифра уже есть в данном квадрате 3x3  ('_')";
        cout << endl;

        resetColor();
        setColor(0, 11);

        return false;
    }
}




