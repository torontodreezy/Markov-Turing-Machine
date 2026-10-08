
#pragma once

#include <iostream>
#include <string>
#include <vector>

inline void runMarkov() {
    using namespace std;

    vector<string> left, right;
    vector<bool> finish;

    string rule;

    cout << "Введите правила Маркова (end для завершения):\n";

    while (getline(cin, rule)) {
        if (rule == "end")
            break;

        size_t pos = rule.find("->.");
        bool isFinish = (pos != string::npos);

        if (!isFinish)
            pos = rule.find("->");

        if (pos == string::npos) {
            cout << "Неверный формат правила!\n";
            continue;
        }

        string l = rule.substr(0, pos);
        string r = rule.substr(pos + (isFinish ? 3 : 2));

        while (!l.empty() && l.back() == ' ')
            l.pop_back();

        while (!r.empty() && r.front() == ' ')
            r.erase(0, 1);

        left.push_back(l);
        right.push_back(r);
        finish.push_back(isFinish);
    }

    string s;
    cout << "Введите исходную строку: ";
    getline(cin, s);

    int steps = 0;
    const int LIMIT = 10000;

    cout << "\nНачальная строка: " << s << "\n";

    while (steps < LIMIT) {
        bool changed = false;

        for (int i = 0; i < (int)left.size(); i++) {
            size_t pos = s.find(left[i]);

            if (pos != string::npos) {
                s.replace(pos, left[i].size(), right[i]);
                steps++;

                cout << "Шаг " << steps << ": " << s << "\n";

                changed = true;

                if (finish[i]) {
                    cout << "\nЗавершающее правило!\n";
                    cout << "Результат: " << s << "\n";
                    return;
                }

                break;
            }
        }

        if (!changed)
            break;
    }

    if (steps == LIMIT)
        cout << "\nДостигнут лимит шагов!\n";

    cout << "\nРезультат: " << s << "\n";
}
