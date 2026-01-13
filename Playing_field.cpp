#include "lul.h"

using namespace std;


void fillDiagonal(int(&a)[9][9]) {
    vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    for (int box = 0; box < 3; box++) {
        random_shuffle(nums.begin(), nums.end());
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                a[box * 3 + i][box * 3 + j] = nums[index++];
            }
        }
    }
}


bool fillEmpty(int(&a)[9][9], int  n = 0, int m = 0) {
    if (n == 8 && m == 9) return true;
    if (m == 9) {
        n++;
        m = 0;
    }

    if (a[n][m] != 0) {
        return fillEmpty(a, n, m + 1);
    }

    vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_shuffle(nums.begin(), nums.end());

    for (int num : nums) {
        if (canPlace(a, n, m, num)) {
            a[n][m] = num;
            if (fillEmpty(a, n, m + 1)) return true;
            a[n][m] = 0;
        }
    }
    return false;
}


void playingField(int(&a)[9][9], int n, int m, int difficulty) {

    srand(time(0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i][j] = 0;
        }
    }

    fillDiagonal(a);

    fillEmpty(a);

    // количество клеток, которые нужно удалить
    int cellsToRemove;
    switch (difficulty) {
    case 1: cellsToRemove = 43; break;  // Легкий
    case 2: cellsToRemove = 45; break;  // Средний
    case 3: cellsToRemove = 51; break;  // Сложный
    default: cellsToRemove = 45;
    }

    int removed = 0;
    while (removed < cellsToRemove) {
        int row = rand() % 9;
        int col = rand() % 9;

        if (a[row][col] != 0) {
            a[row][col] = 0;
            removed++;
        }
    }
}

void solveSudoku(int(&a)[9][9]) {
    bool fixed[9][9] = { false };
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] != 0) {
                fixed[i][j] = true;
            }
        }
    }

    int row = 0, col = 0;
    bool backtrack = false;

    while (row < 9) {
        if (fixed[row][col]) {
            if (backtrack) {
                do {
                    if (col == 0) {
                        col = 8;
                        row--;
                    }
                    else {
                        col--;
                    }
                    if (row < 0) return;
                } while (fixed[row][col]); 
                backtrack = true;
                continue;
            }
            else {
                col++;
                if (col == 9) {
                    col = 0;
                    row++;
                }
                continue;
            }
        }

        if (backtrack) {
            backtrack = false;
            int startNum = a[row][col] + 1;
            bool found = false;

            for (int num = startNum; num <= 9; num++) {
                if (canPlace(a, row, col, num)) {
                    a[row][col] = num;
                    found = true;
                    break;
                }
            }

            if (!found) {
                a[row][col] = 0; 

                do {
                    if (col == 0) {
                        col = 8;
                        row--;
                    }
                    else {
                        col--;
                    }
                    if (row < 0) return;
                } while (fixed[row][col]); 

                backtrack = true;
                continue;
            }
        }
        else if (a[row][col] == 0) {
            bool found = false;
            for (int num = 1; num <= 9; num++) {
                if (canPlace(a, row, col, num)) {
                    a[row][col] = num;
                    found = true;
                    break;
                }
            }

            if (!found) {
                a[row][col] = 0;

                do {
                    if (col == 0) {
                        col = 8;
                        row--;
                    }
                    else {
                        col--;
                    }
                    if (row < 0) return;
                } while (fixed[row][col]);

                backtrack = true;
                continue;
            }
        }

        col++;
        if (col == 9) {
            col = 0;
            row++;
        }
    }
}



void printField(int(&a)[9][9], string begin) {
    const int yellow = 11;
    const int purple = 132;
    const int black = 0;

    cout << endl << setw(81) << begin << endl;
    setColor(0, 8);
    cout << "* Меню - 0 (введите в любом месте)" << endl;
    cout << "* итеративный решатель судоку - введите 11";
    resetColor();
    setColor(0, yellow);
    cout << setw(38) << " -----------------------------------" << endl;

    for (int i = 0; i < 9; i++) {
        int bigRow = i / 3;

        if (i % 3 == 0 && i != 0) {
            setColor(0, yellow);
            cout << setw(81) << "|-----------------------------------|" << endl;
            cout << setw(45) << "|";
        }
        else {
            setColor(0, yellow);
            cout << setw(45) << "|";
        }

        for (int j = 0; j < 9; j++) {
            int bigCol = j / 3;
            int squareNum = bigRow * 3 + bigCol;

            // Определяем фон: розовый для четных квадратов, черный для нечетных
            int bgColor = (squareNum % 2 == 0) ? purple : black;

            setColor(bgColor, yellow);

            if (a[i][j] == 0) {
                cout << " _ ";
            }
            else {
                cout << " " << a[i][j] << " ";
            }

            setColor(0, yellow);
            if (j < 8) {
                cout << "|";
            }
        }

        setColor(0, yellow);
        cout << "|" << endl;
    }

    setColor(0, yellow);
    cout << setw(80) << " -----------------------------------" << endl;
    resetColor();
    setColor(0, 11);
}


bool checkMatrix(int(&a)[9][9]) {
    int cnt = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] == 0) {
                cnt++;
            }
        }
    }

    if (cnt > 0) {
        return true;
    }
    else {
        return false;
    }
}

// Проверка всего поля на корректность
bool isFieldOk(int(&a)[9][9]) {
    int tempField[9][9];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tempField[i][j] = a[i][j];
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (tempField[i][j] != 0) {
                int temp = tempField[i][j];
                tempField[i][j] = 0;

                if (!canPlace(tempField, i, j, temp)) {
                    return false;
                }

                tempField[i][j] = temp;
            }
        }
    }
    return true;
}

