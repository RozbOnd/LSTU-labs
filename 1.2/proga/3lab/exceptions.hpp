#pragma once
#include <stdexcept>
#include <string>

using namespace std;

struct WrongChoice {
    string message;
    WrongChoice() : message{ "��� ������ ������!" } {}
    string what() const { return message; }
};

struct NotOctalNumber {
    string message;
    NotOctalNumber() : message{ "����� �� �������� ������������!" } {}
    string what() const { return message; }
};

struct TooLargeNumber {
    string message;
    TooLargeNumber() : message{ "������� ������� �����, ���������� ��������� � ������ �������!" } {}
    string what() const { return message; }
};

struct FileError {
    string message;
    FileError() : message{ "�� ���������� ������� ����!" } {}
    string what() const { return message; }
};

struct NotEnoughWords {
    string message;
    NotEnoughWords() : message{ "� ����� ������ 3-� ����!" } {}
    string what() const { return message; }
};

struct NotRightCharacter {
    string message;
    NotRightCharacter() : message{ "� ������ ��������� ������������ ������!" } {}
    string what() const { return message; }
};

struct IndexError {
    string message;
    IndexError() : message{ "����� �� ������� �������!" } {}
    string what() const { return message; }
};