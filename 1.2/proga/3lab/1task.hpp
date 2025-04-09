#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include "exceptions.hpp"

using namespace std;

bool isOct(string s) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] < '0' || s[i] > '7') return false;
    return true;
}

string octToQuin(string oct) {
    long long dec = 0;
    int power = 0;
    for (int i = oct.size() - 1; i >= 0; i--)
        dec += (oct[i] - '0') * pow(8, power), power++;

    string quin;
    while (dec)
        quin = to_string(dec % 5) + quin, dec /= 5;
    return quin;
}

void task1() {
    string str;
    cout << "Введите восьмеричное число: ";
    cin >> str;
    if (!isOct(str)) throw NotOctalNumber();
    string quin = octToQuin(str);
    if (quin.size() == 0) throw TooLargeNumber();
    cout << "Пятеричный эквивалент: " << quin << '\n';
}