
#include <iostream>
#include <limits>

#include "markov.hpp"
#include "turing.hpp"

using namespace std;

int main() {
    int choice;

    while (true) {
        cout << "\n===== МЕНЮ =====\n";
        cout << "1. Машина Маркова\n";
        cout << "2. Машина Тьюринга\n";
        cout << "0. Выход\n";
        cout << "Выберите алгоритм: ";

        if (!(cin >> choice)) {
            if (cin.eof())
                break;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите число!\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            runMarkov();
        }
        else if (choice == 2) {
            runTuring();
        }
        else if (choice == 0) {
            cout << "Выход из программы.\n";
            break;
        }
        else {
            cout << "Неверный выбор!\n";
        }
    }

    return 0;
}
