#pragma once
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>
#include <climits>
#include <sstream>
#include <cstring>
#include "exceptions.hpp"

using namespace std;

struct WordsArray {
    string* words_string;
    char** words_cstyle;
    int size;

    WordsArray() : words_string{ nullptr }, words_cstyle{ nullptr }, size{ 0 } {}

    void Add_String_Word(string word) {
        if (words_string == nullptr) {
            words_string = new string[1];
            size = 1;
            words_string[0] = word;
            return;
        }

        string* new_words = new string[size + 1];
        for (int i = 0; i < size; i++) new_words[i] = words_string[i];
        new_words[size] = word;
        size++;
        delete[] words_string;
        words_string = new string[size];
        for (int i = 0; i < size; i++) words_string[i] = new_words[i];
        delete[] new_words;
    }

    void Add_Cstyle_Word(char* word) {
        if (words_cstyle == nullptr) {
            words_cstyle = new char* [1];
            words_cstyle[0] = new char[strlen(word) + 1];
            size = 1;
            strcpy(words_cstyle[0], word);
            return;
        }

        char** new_words = new char* [size + 1];
        for (int i = 0; i < size; i++) {
            new_words[i] = new char[strlen(words_cstyle[i]) + 1];
            strcpy(new_words[i], words_cstyle[i]);
        }
        new_words[size] = new char[strlen(word) + 1];
        strcpy(new_words[size], word);
        size++;
        delete[] words_cstyle;
        words_cstyle = new char* [size];
        for (int i = 0; i < size; i++) {
            words_cstyle[i] = new char[strlen(new_words[i]) + 1];
            strcpy(words_cstyle[i], new_words[i]);
        }
        delete[] new_words;
    }

};

bool check_word(string word) {
    for (int i = 0; i < word.size(); i++) {
        if (('a' <= word[i] && word[i] <= 'z') ||
            ('A' <= word[i] && word[i] <= 'Z') ||
            (word[i] == '-')
            ) continue;
        else throw NotRightCharacter();
    }
    return true;
}

void File_Input(ifstream& fin) {
    string filename;
    cout << "Введите название файла: ";
    cin.ignore();
    getline(cin, filename);
    fin.open(filename);
    if (!fin.is_open()) throw FileError();
}

void task2() {
    int input_type;
    ifstream fin;
    ofstream fout;
    cout << "[1] - ввод с файла, [2] - ввод с клавиатуры: ";
    cin >> input_type;
    if (input_type == 1) File_Input(fin);
    else if (input_type == 2);
    else throw WrongChoice();

    int work_type;
    cout << "[1] - строки std::string, [2] - строки в С-стиле: ";
    cin >> work_type;
    WordsArray words;

    if (work_type == 1) {
        if (input_type == 1) {
            string word;
            while (fin >> word) {
                check_word(word);
                words.Add_String_Word(word);
            }
        }
        else {
            string words_input;
            cin.ignore();
            getline(cin, words_input);
            stringstream words_input_stream(words_input);
            string word;
            while (words_input_stream >> word) {
                check_word(word);
                words.Add_String_Word(word);
            }
        }
    }

    else if (work_type == 2) {
        if (input_type == 1) {
            char text[1001];
            fin.getline(text, 1000);
            char* tokenized = strtok(text, " -");
            while (tokenized != nullptr) {
                check_word(tokenized);
                words.Add_Cstyle_Word(tokenized);
                tokenized = strtok(nullptr, " -");
            }
        }
        else {
            char text[1001];
            cin.ignore();
            cin.getline(text, 1000);
            char* tokenized = strtok(text, " -");
            while (tokenized != nullptr) {
                check_word(tokenized);
                words.Add_Cstyle_Word(tokenized);
                tokenized = strtok(nullptr, " -");
            }
        }

    }
    else throw WrongChoice();

    string output_file_name;
    cout << "Введите название файла для вывода: ";
    cin.ignore();
    getline(cin, output_file_name);
    fout.open(output_file_name);
    if (!fout.is_open()) throw FileError();

    int word_index;
    cout << "Пункт а. Введите номер слова: ";
    fout << "Пункт а. Номер слова: ";
    cin >> word_index;
    fout << word_index << '\n';
    if (word_index < 0 || word_index > words.size) throw IndexError();
    if (work_type == 1){
         cout << "Первая буква слова на позиции " << word_index << ": " << words.words_string[word_index - 1][0] << '\n';
         fout << "Первая буква слова на позиции " << word_index << ": " << words.words_string[word_index - 1][0] << '\n';
    }
    else cout << words.words_cstyle[word_index - 1][0] << '\n', fout << words.words_cstyle[word_index - 1][0] << '\n';
    cout << "Пункт b. Все слова на четных позициях.\n";
    fout << "Пункт b. Все слова на четных позициях.\n";
    for (int i = 0; i < words.size; i += 2) {
        if (work_type == 1) cout << words.words_string[i] << '\n', fout << words.words_string[i] << '\n';
        else cout << words.words_cstyle[i] << '\n', fout << words.words_cstyle[i] << '\n';
    }
    cout << '\n';
    fout << '\n';
    cout << "Пункт c.\n";
    fout << "Пункт c.\n";
    int min_len = INT_MAX;
    for (int i = 0; i < words.size; i++) {
        if (work_type == 1) min_len = min(min_len, (int)words.words_string[i].size());
        else min_len = min(min_len, (int)strlen(words.words_cstyle[i]));
    }
    cout << "Длина самого короткого слова: " << min_len << '\n';
    fout << "Длина самого короткого слова: " << min_len << '\n';
    fout.close();
    return;
}