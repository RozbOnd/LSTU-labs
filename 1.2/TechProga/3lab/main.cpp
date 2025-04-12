#include <iostream>
#include "list.hpp"

using namespace std;

int main(){
    BlockList list;
    int choice;
    cout << "[1] - Добавить запись в начало списка; [2] - Добавить запись в конец списка; [3] - Вставить запись на заданную позицию; ";
    cout << "[4] - Удалить запись на заданной позиции; [5] - Изменить запись на заданной позиции; [6] - Очистить массив; [7] - Поиск по индексу; ";
    cout << "[8] - Вывод содержимое массива; [9] - Вывод служеюных данных; [10] - Поиск по индексу; [0] - Выход.\n";
    while (cin >> choice){
        if (choice == 1) {
            Element el;
            el.input();
            el.print();
            list.push_front(el);
        }
        else if (choice == 2) {
            Element el;
            el.input();
            list.push_back(el);
        }
        else if (choice == 3){
            Element el;
            el.input();
            int index;
            cout << "Введите индекс (с 1): ";
            cin >> index;
            if (index < 1 || index > list.Size){
                cerr << "Выход за пределы списка!\n";
                continue;
            }
            list.InsertAt(el, index);
        }
        else if (choice == 4){}
        else if (choice == 5){
            Element el;
            el.input();
            int index;
            cout << "Введите индекс (с 1): ";
            cin >> index;
            if (index < 1 || index > list.Size){
                cerr << "Выход за пределы списка!\n";
                continue;
            }
            list.UpdateAt(el, index);
        }
        else if (choice == 6) list.Clear();
        else if (choice == 7){}
        else if (choice == 8) list.PrintData();
        else if (choice == 9) list.PrintExtraInfo();
        else if (choice == 10) {
            int index;
            cout << "Введите индекс (с 1): ";
            cin >> index;
            if (index < 1 || index > list.Size){
                cerr << "Выход за пределы списка!\n";
                continue;
            }
            list.GetByIndex(index);
        }
        else if (choice == 0) break;
        else cout << "Нет такой опции!\n \n";
        cout << "[1] - Добавить запись в начало списка; [2] - Добавить запись в конец списка; [3] - Вставить запись на заданную позицию; ";
        cout << "[4] - Удалить запись на заданной позиции; [5] - Изменить запись на заданной позиции; [6] - Очистить массив; [7] - Поиск по индексу; ";
        cout << "[8] - Вывод содержимое массива; [9] - Вывод служеюных данных; [10] - Поиск по индексу; [0] - Выход.\n";
    }
    return 0;
}