#include <iostream>
#include <clocale>
#include <string>
#include <stdexcept>
using namespace std;

struct NegativeDepositException {
    string message;
    NegativeDepositException() : message{ "Нельзя пополнить счёт на отрицательную сумму!" } {}
    string what() const { return message; }
};

struct InsufficientFundsException {
    string message;
    InsufficientFundsException() : message{ "Недостаточно средств на счету!" } {}
    string what() const { return message; }
};

struct BankAccount {
    int money;
    BankAccount() : money{ 0 } {}
    BankAccount(int mn) : money{ mn } {}

    void deposit(int mn) {
        if (mn < 0) throw NegativeDepositException();
        money += mn;
        cout << "Деньги добавлены!\n" << "Текущий счёт: " << money << '\n';
    }

    void withdraw(int mn) {
        if (mn > money) throw InsufficientFundsException();
        money -= mn;
        cout << "Деньги выведены!\n" << "Текущий счёт: " << money << '\n';
    }
};

struct BankSystem {
    BankAccount* accs;
    int size;

    BankSystem() : size{ 0 }, accs{ nullptr } {}

    void addAcc() {
        BankAccount* newBank = new BankAccount[size + 1];
        for (int i = 0; i < size; i++) newBank[i] = accs[i];
        newBank[size] = BankAccount();
        size += 1;
        delete[] accs;
        accs = newBank;
        cout << "Добавлен новый аккаунт (id = " << size << ")\n";
    }

    void iterAcc() {
        int ind;
        cout << "Введите id аккаунта: ";
        cin >> ind;

        if (ind < 1 || ind > size) throw out_of_range("Вы вышли за пределы массива аккаунтов!");

        cout << "Действия с аккаунтом (1 - пополнить счёт, 2 - вывести средства, 3 - закончить работу с аккаунтом): ";
        int ch;
        while (cin >> ch) {
            if (ch == 1) {
                int mn;
                cout << "Введите количество денег: ";
                cin >> mn;
                accs[ind].deposit(mn);
                break;
            }
            else if (ch == 2) {
                int mn;
                cout << "Введите количество денег: ";
                cin >> mn;
                accs[ind].withdraw(mn);
                break;
            }
            else if (ch == 3) {
                return;
            }
            else {
                cout << "Нет такого варианта!\n";
                cout << "Действия с аккаунтом (1 - пополнить счёт, 2 - вывести средства, 3 - закончить работу с аккаунтом): ";
            }
        }
    }

    ~BankSystem() {
        if (accs != nullptr) {
            delete[] accs;
            accs = nullptr;
            size = 0;
        }
    }

    BankSystem(const BankSystem& other) {
        size = other.size;
        accs = new BankAccount[size];
        for (int i = 0; i < size; i++)
            accs[i] = other.accs[i];
    }

    BankSystem& operator=(const BankSystem& other) {
        if (this != &other) {
            if (accs != nullptr) delete[] accs;
            size = other.size;
            accs = new BankAccount[size];
            for (int i = 0; i < size; i++)
                accs[i] = other.accs[i];
        }
        return *this;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    BankSystem bank;

    while (true){
        try {
            int ch_m;
            cout << "(1 - добавить аккаунт в систему, 2 - действия с аккаунтом, 3 - выход): ";
            while (cin >> ch_m) {
                if (ch_m == 1) {
                    bank.addAcc();
                    break;
                }
                else if (ch_m == 2) {
                    bank.iterAcc();
                    break;
                }
                else if (ch_m == 3) {
                    return 0;
                }
                else {
                    cout << "Нет такого варианта!\n";
                    cout << "(1 - добавить аккаунт в систему, 2 - действия с аккаунтом, 3 - выход): ";
                }
            }

        }
        catch (const NegativeDepositException& ex) {
            cerr << ex.what() << endl;
            return 1;
        }
        catch (const InsufficientFundsException& ex) {
            cerr << ex.what() << endl;
            return 1;
        }
        catch (const out_of_range& ex) {
            cerr << ex.what() << endl;
            return 1;
        }
        catch (...) {
            cerr << "Other exeption" << endl;
            return 1;
        }
    }
    return 0;
}
