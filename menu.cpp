#include "lul.h"

using namespace std;


int pasteNumber(int(&a)[9][9], string begin) {
    int num = 0, x = 0, y = 0, change = 0;

    cout << "\n====== Вставка цифр ======\n";

    cout << "\nВведите номер строки: ";
    x = checkPaste();
    if (x == 0) return 0;
    if (x == 11) return 11;

    cout << "\nВведите номер столбца: ";
    y = checkPaste();
    if (y == 0) return 0;
    if (y == 11) return 11;

    cout << "\nВведите саму цифру: ";
    num = checkPaste();
    if (num == 0) return 0;
    if (num == 11) return 11;

    while (opportunityToPaste(num, x, y, a) == false) {
        cout << "\nВы хотите поменять:\n\n    1 - цифру\n    2 - строку или столбец\n\nВведите выбранную цифру: ";
        change = checkChange();
        if (change == 0) return 0;
        if (change == 11) return 11;

        if (change == 1) {
            cout << "\nВведите саму цифру: ";
            num = checkPaste();
            if (num == 0) return 0;
            if (num == 11) return 11;
        }
        else {
            cout << "\nВведите номер строки: ";
            x = checkPaste();
            if (x == 0) return 0;
            if (x == 11) return 11;

            cout << "\nВведите номер столбца: ";
            y = checkPaste();
            if (y == 0) return 0;
            if (y == 11) return 11;
        }

    }
    system("cls");
    printField(a, begin);
    return 1;
}


bool printMenu(int(&a)[9][9], string begin) {
    int choice;

    cout << endl;
    cout << " /\\_/\\                                      /\\_/\\ " << endl;
    cout << "( o.o ) ============== Меню ============== ( o.o )\n";
    cout << "\n    1 - начать новую игру\n    2 - продолжить игру\n    3 - выйти из игры" << "\n";
    cout << "\n" << "Выберите действие: ";
    cin >> choice;
    //проверка ввода
    while(!checkMenuCin(choice)) cin >> choice;

    switch (choice) {
    case 1:
        newGame(a, begin);
        printMenu(a, begin);
        break;
    case 2:
        continueGame(a, begin);
        printMenu(a, begin);
        break;
    case 3:
        system("cls");
        cout << endl;
        cout << endl << setw(80) << "/\\_/\\                            /\\_/\\ \n";
        cout << setw(80) << "( o.o ) ====== конец игры ====== ( o.o )\n" << endl;
        saving(a);
        return false;
        break;
    }

    return true;
}


void newGame(int(&a)[9][9], string begin) {
    int complexity;
    cout << "\nКакой уровень сложности вы хотите ?\n\n  1 - лёгкий\n  2 - средний\n  3 - сложный\n\n";
    cout << "Введите цифру от 1 до 3: ";
    cin >> complexity;
    while (!checkLevelCin(complexity)) cin >> complexity;

    system("cls");

    playingField(a, 9, 9, complexity);
    printField(a, begin);
    saving(a);

    gameLoop(a, begin);
}


void continueGame(int(&a)[9][9], string begin) {
    system("cls");
    cout << "\n" << setw(78) << "====== Продолжение игры ======\n\n" << endl;
    if (!loadGame(a)) {
        cout << endl << setw(80) << "(^-^) У вас нет сохранений. Начните новую игру (^-^)\n\n";
        return;
    }
    if (!isFieldOk(a)) {
        cout << endl;
        cout << setw(90) << "(' - ') ====== Поле заполнено неверно ====== (' - ')\n\n";
        return ;
    }
    if (!checkMatrix(a)) {
        cout << "\n" << setw(90) << "(^-^) ====== Ваше последнее судоку решено ====== (^-^)" << "\n\n";
        return;
    }
    else {
        printField(a, begin);
        gameLoop(a, begin);
    }

}



bool loadGame(int(&a)[9][9]) {
    if (checkFile()) return false;

    ifstream file("saving.txt");
    if (!file.is_open()) return false;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            file >> a[i][j];
        }
    }
    file.close();

    return true;
}


void gameLoop(int(&a)[9][9], string begin) {
    int result;

    while (checkMatrix(a)) {
        result = pasteNumber(a, begin);
        saving(a);

        if (result == 0) break;

        if (result == 11) {
            solveSudoku(a);
            printField(a, begin);
            saving(a);
            cout << "\n" << setw(82) << "(^-^) ====== Судоку решено ====== (^-^)" << "\n";
            break;
        }
    }

    if (!checkMatrix(a)) {
        cout << "\n" << setw(92) << "(^-^) ====== Поздравляю. Вы решили судоку! ====== (^-^)\n";
    }
}

