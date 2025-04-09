#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
#include <string>
#include <limits>
using namespace std;

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

struct book {
	char name[300];
	int year;
};

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void printTable(const book* books, int count) {
	int c1 = 5, c2 = 19, c3 = 3;
	for (int i = 0; i < count; i++) {
		int j = 0;
		while (books[i].name[j] != '\0') j++;
		c2 = max(c2, j);
	}
	cout << "Номер     " << "Название книги     ";
	for (int i = 0; i < c2 - 19 + 4; i++)cout << " ";
	cout << "Год\n";
	for (int i = 0; i < 10 + c2 + 4 + 4; i++) cout << "-";
	cout << '\n';
	int mx = 0;
	for (int i = 0; i < count; i++) {
		cout << i + 1;
		int l = 0;
		int k = i + 1;
		while (k) k /= 10, l++;
		for (int j = 0; j < 10 - l; j++) cout << " ";
		cout << books[i].name;
		l = 0;
		while (books[i].name[l] != '\0') l++;
		for (int j = 0; j < c2 - l + 4; j++) cout << " ";
		cout << books[i].year << '\n';

		if (books[i].year > mx)
			mx = books[i].year;
	}
	for (int i = 0; i < 10 + c2 + 4 + 4; i++) cout << "-";
	cout << '\n';
	cout << "Макс. год:";
	for (int i = 0; i < 10 + c2 - 10 + 4; i++) cout << " ";
	cout << mx << '\n';
}

void addRecord(book*& books, int& size) {
	book* newBooks = new book[size + 1];

	for (int i = 0; i < size; i++)
		newBooks[i] = books[i];

	cout << "Введите название книги: ";
	cin.clear();
	cin.ignore(1000, '\n');
	cin.getline(newBooks[size].name, 300);
	cout << "Введите год издания: ";
	cin >> newBooks[size].year;
	size++;
	delete[] books;
	books = new book[size];
	for (int i = 0; i < size; i++)
		books[i] = newBooks[i];
	delete[] newBooks;
}

void delRecord(book*& books, int& size) {

	if (size == 0) {
		cerr << "Записей нет, удаление невозможно.\n";
		return;
	}

	book* newBooks = new book[size - 1];

	int ind;
	cout << "Введите номер записи для удаления: ";
	cin >> ind;

	if (ind < 1 || ind > size) {
		cerr << "Неверный номер записи.\n";
		return;
	}
	ind--;
	int cur_i = 0;
	for (int i = 0; i < size; i++)
		if (i != ind) newBooks[cur_i++] = books[i];

	size--;
	delete[] books;
	books = new book[size];
	for (int i = 0; i < size; i++)
		books[i] = newBooks[i];
	delete[] newBooks;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void input_file(ifstream& fin, string& file_name, int type) {
	if (fin.is_open()) {
		fin.close();
	}
	cout << "Введите название файла: ";
	bool f = 0;
	cin.clear();
	cin.ignore(1000, '\n');
	while (getline(cin, file_name)) {
		if (type == 2) fin.open(file_name, ios_base::binary);
		else fin.open(file_name);
		if (!fin.is_open()) {
			if (f == 0) {
				f = 1;
				continue;
			}
			cout << "Не найден такой файл.\n";
			cout << "Введите название файла: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
}

int input_type(ifstream& fin, string& file_name) {
	int ch1;
	cout << "Выберете тип ввода данных: [1] - текстовый файл, [2] - бинарный файл, [3] - в консоли: ";
	while (cin >> ch1) {
		if (ch1 == 1 || ch1 == 2) { input_file(fin, file_name, ch1); break; }
		else if (ch1 == 3) break;
		else {
			cout << "Некоректный ввод.\n";
			cout << "Выберете тип ввода данных: [1] - текстовый файл, [2] - бинарный файл, [3] - в консоли: ";
		}
	}
	return ch1;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

void output_file(ofstream& fout, string& file_name, int type) {
	if (fout.is_open()) {
		fout.close();
	}
	cout << "Введите название файла: ";
	bool f = 0;
	cin.clear();
	cin.ignore(1000, '\n');
	while (getline(cin, file_name)) {
		if (type == 1) fout.open(file_name);
		else fout.open(file_name, ios_base::binary);
		if (!fout.is_open()) {
			if (f == 0) {
				f = 1;
				continue;
			}
			cout << "Не найден такой файл.\n";
			cout << "Введите название файла: ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			break;
	}
}

int output_type(ofstream& fout, string& file_name) {
	int ch2;
	cout << "Выберете способ вывода результатов: [1] - в текстовый файл, [2] - в бинарный файл: ";
	while (cin >> ch2) {
		if (ch2 == 1 || ch2 == 2) { output_file(fout, file_name, ch2); break; }
		else {
			cout << "Некоректный ввод.\n";
			cout << "Выберете способ вывода результатов: [1] - в текстовый файл, [2] - в бинарный файл: ";
		}
	}
	return ch2;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

long long FileSize(ifstream& fin) {
	string file_name;
	cout << "Введите название файла: ";
	cin.clear();
	cin.ignore(1000, '\n');
	while (getline(cin, file_name)) {
		fin.open(file_name, ios_base::binary);
		if (!fin.is_open()) {
			cout << "Не найден такой файл.\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else break;
	}
	long long k;
	fin.seekg(0, ios_base::end);
	k = fin.tellg();
	fin.close();
	return k;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream fin;
	ofstream fout;
	string in_name, out_name;

	book* books = nullptr;
	int size;

	int ch_in = input_type(fin, in_name);
	if (ch_in == 1) {
		fin >> size;
		books = new book[size];
		for (int i = 0; i < size; i++) {
			fin.clear();
			fin.ignore(1000, '\n');
			fin.getline(books[i].name, 300);
			//fin >> books[i].name;
			fin >> books[i].year;
		}
		fin.close();
	}
	if (ch_in == 2) {
		fin.read((char*)&size, sizeof(int));
		books = new book[size];
		for (int i = 0; i < size; i++) fin.read((char*)&books[i], sizeof(book));
		fin.close();
	}
	if (ch_in == 3) {
		cout << "Введите размер массива: ";
		cin >> size;
		books = new book[size];
		for (int i = 0; i < size; i++) {
			cout << "Введите название " << i + 1 << " книги: ";
			cin.clear();
			cin.ignore(1000, '\n');
			cin.getline(books[i].name, 300);
			cout << "Введите год издания книги: ";
			cin >> books[i].year;
			cout << '\n';
		}
	}
	
	while (1) {
		int ch;
		cout << "[1] - добавить запись, [2] - удалить запись, [3] - запись в файл, [4] - вывод значений, [5] - расчет размера файла, [6] - выход: ";
		cin.clear();
		while (cin >> ch) {
			if (ch == 1) addRecord(books, size);
			else if (ch == 2) delRecord(books, size);
			else if (ch == 4) printTable(books, size);
			else if (ch == 3) {
				int ch2 = output_type(fout, out_name);
				if (ch2 == 1) {
					fout << size << '\n';
					for (int i = 0; i < size; i++) fout << books[i].name << '\n' << books[i].year << '\n';
				}
				else {
					fout.write((char*)&size, sizeof(int));
					for (int i = 0; i < size; i++) fout.write((char*)&books[i], sizeof(book));
				}
				fout.close();
			}
			else if (ch == 5) { cout << FileSize(fin) << " байт\n"; cin.clear(); }
			else if (ch == 6) return 0;
			else {
				cout << "Некоректный ввод.\n";
				cout << "[1] - добавить новую запись, [2] - удалить запись, [3] - запись в файл, [4] - вывод значений, [5] - расчет размера файла, [6] - выход: ";
				continue;
			}
			break;
		}
	}

	return 0;
}