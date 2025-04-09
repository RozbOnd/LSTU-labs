#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include "exceptions.hpp"

using namespace std;

string clear_str(string s){
    int i = 0;
    string res = "";
    while (i < s.size() &&
        (('a' <= s[i] && s[i] <= 'z') ||
        ('A' <= s[i] && s[i] <= 'Z') ||
        ('а' <= s[i] && s[i] <= 'я') ||
        ('А' <= s[i] && s[i] <= 'Я') ||
        (s[i] == '-')))
            res.push_back(s[i]), i++;
    return res;
}

void task3(){
    string filename;
    cout << "Введите название файла: ";
    cin.ignore();
    getline(cin, filename);
    ifstream fin(filename);
    if (!fin.is_open()) throw FileError();
    string s1, s2, s3;
    string s;

    while (fin >> s){
        s = clear_str(s);
        if (s.size() > s1.size()) s3 = s2, s2 = s1, s1 = s;
        else if (s.size() > s2.size()) s3 = s2, s2 = s;
        else if (s.size() > s3.size()) s3 = s;
    }
    fin.close();
    if (s3.empty()) throw NotEnoughWords();
    cout << "Три самых длинных слова в порядке возрастания их длин:\n";
    cout << s3 << '\n' << s2 << '\n' << s1 << '\n';
}