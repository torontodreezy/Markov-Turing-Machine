
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <algorithm>

inline void runTuring() {
    using namespace std;

    struct Rule {
        char write;
        char move;
        string nextState;
    };

    map<pair<string, char>, Rule> rules;

    string line;

    cout << "Введите правила машины Тьюринга:\n";
    cout << "Формат: q0 1 0 R q1\n";
    cout << "Для завершения введите end\n\n";

    while (getline(cin, line)) {
        if (line == "end")
            break;

        string state, nextState;
        string readSymbol, writeSymbol, direction;
        string extra;

        istringstream iss(line);

        if (!(iss >> state >> readSymbol >> writeSymbol
                  >> direction >> nextState) ||
            (iss >> extra) ||
            readSymbol.size() != 1 ||
            writeSymbol.size() != 1 ||
            direction.size() != 1) {
            cout << "Неверный формат правила!\n";
            continue;
        }

        char move = direction[0];

        if (move != 'L' && move != 'R' && move != 'S') {
            cout << "Неверное направление!\n";
            continue;
        }

        rules[{state, readSymbol[0]}] = {
            writeSymbol[0], move, nextState
        };
    }

    string tape;
    cout << "\nВведите начальную ленту: ";
    getline(cin, tape);

    if (tape.empty())
        tape = "_";

    string state;
    cout << "Введите начальное состояние: ";
    getline(cin, state);

    map<int, char> cells;

    for (int i = 0; i < (int)tape.size(); i++) {
        if (tape[i] != '_')
            cells[i] = tape[i];
    }

    int head = 0;
    int steps = 0;
    const int LIMIT = 10000;

    while (steps < LIMIT) {
        int left = head - 2;
        int right = head + 2;

        if (!cells.empty()) {
            left = min(left, cells.begin()->first);
            right = max(right, cells.rbegin()->first);
        }

        cout << "\nШаг " << steps
             << " | Состояние: " << state << "\n";

        for (int i = left; i <= right; i++) {
            auto it = cells.find(i);
            cout << (it != cells.end() ? it->second : '_');
        }

        cout << "\n";

        for (int i = left; i < head; i++)
            cout << ' ';

        cout << "^\n";

        if (state == "HALT") {
            cout << "\nМашина завершила работу!\n";
            break;
        }

        char current = '_';

        auto cell = cells.find(head);

        if (cell != cells.end())
            current = cell->second;

        auto it = rules.find({state, current});

        if (it == rules.end()) {
            cout << "\nНет подходящего правила.\n";
            break;
        }

        Rule r = it->second;

        if (r.write == '_')
            cells.erase(head);
        else
            cells[head] = r.write;

        if (r.move == 'R')
            head++;
        else if (r.move == 'L')
            head--;

        state = r.nextState;
        steps++;
    }

    if (steps == LIMIT)
        cout << "\nДостигнут лимит шагов!\n";

    cout << "\nИтоговая лента: ";

    if (cells.empty()) {
        cout << "_";
    } else {
        int left = min(head, cells.begin()->first);
        int right = max(head, cells.rbegin()->first);

        for (int i = left; i <= right; i++) {
            auto it = cells.find(i);
            cout << (it != cells.end() ? it->second : '_');
        }
    }

    cout << "\nКоличество шагов: " << steps << "\n";
}
