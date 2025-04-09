#include <iostream>
#include <string>
#include <windows.h>
#include <cmath>
#include <fstream>
#include "1task.hpp"
#include "2task.hpp"
#include "3task.hpp"

using namespace std;

int main(){
    SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    try {
        int task;
        cout << "Выберите задание (1, 2, 3): ";
        cin >> task;
        if (task == 1) task1();
        else if (task == 2) task2();
        else if (task == 3) task3();
        else throw WrongChoice();
    }
    catch (const NotOctalNumber& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const TooLargeNumber& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const FileError& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const NotEnoughWords& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const WrongChoice& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const NotRightCharacter& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (const IndexError& ex){
        cerr << ex.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Other exeption" << endl;
        return 1;
    }
    return 0;
}