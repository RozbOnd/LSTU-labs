#pragma once
#include <stdexcept>
#include <string>

using namespace std;

struct WrongChoice {
    string message;
    WrongChoice() : message{ "Нет такого выбора!" } {}
    string what() const { return message; }
};

struct NotOctalNumber {
    string message;
    NotOctalNumber() : message{ "Число не является восьмиричным!" } {}
    string what() const { return message; }
};

struct TooLargeNumber {
    string message;
    TooLargeNumber() : message{ "Слишком длинное число, невозможно перевести в другую систему!" } {}
    string what() const { return message; }
};

struct FileError {
    string message;
    FileError() : message{ "Не получилось открыть файл!" } {}
    string what() const { return message; }
};

struct NotEnoughWords {
    string message;
    NotEnoughWords() : message{ "В файле меньше 3-х слов!" } {}
    string what() const { return message; }
};

struct NotRightCharacter {
    string message;
    NotRightCharacter() : message{ "В тексте находится недопустимым символ!" } {}
    string what() const { return message; }
};

struct IndexError {
    string message;
    IndexError() : message{ "Выход за пределы массива!" } {}
    string what() const { return message; }
};