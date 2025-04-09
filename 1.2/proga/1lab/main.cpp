#include <iostream>
#include <fstream>
#include <iomanip>
#include <clocale>
using namespace std;

//////////////////////////////////////////////////////////////////////////
///////////////////////Общие функции//////////////////////////////////////

void output_file_name(ofstream &fout) {
	if (fout.is_open()) {
		fout.close();
	}
	cout << "Введите название файла: ";
	bool f = 0;
	char* file_name = new char[256];
	while (cin.getline(file_name, 256)) {
		fout.open(file_name);
		if (!fout.is_open()) {
			if (f == 0) {
				f = 1;
				continue;
			}
			cout << "Не найден такой файл.\n";
			cout << "Введите название файла: ";
		}
		else
			break;
	}
}

void input_file_name(ifstream &fin) {
	if (fin.is_open()) {
		fin.close();
	}
	cout << "Введите название файла: ";
	char* file_name = new char[256];
	bool f = 0;
	while (cin.getline(file_name, 256)) {
		fin.open(file_name);
		if (!fin.is_open()) {
			if (f == 0) {
				f = 1;
				continue;
			}
			cout << "Не найден такой файл.\n";
			cout << "Введите название файла: ";
		}
		else
			break;
	}
}

int input_type() {
	int ch1;
	cout << "Выберете тип ввода данных: 1 - из файла, 2 - в консоли, 3 - случайные числа: ";
	while (cin >> ch1) {
		if (ch1 == 1) {
			break;
		}
		else if (ch1 == 2 || ch1 == 3)
			break;
		else if (ch1 != 1 && ch1 != 2 && ch1 != 3) {
			cout << "Некоректный ввод.\n";
			cout << "Выберете тип ввода данных: 1 - из файла, 2 - в консоли, 3 - случайные числа: ";
		}
	}
	return ch1;
}

int output_type() {
	int ch2;
	cout << "Выберете способ вывода результатов: 1 - в файл, 2 - в консоль: ";
	while (cin >> ch2) {
		if (ch2 == 1) {
			break;
		}
		else if (ch2 == 2)
			break;
		else if (ch2 != 1 && ch2 != 2) {
			cout << "Некоректный ввод.\n";
			cout << "Выберете способ вывода результатов: 1 - в файл, 2 - в консоль: ";
		}
	}
	return ch2;
}

int var_type() {
	int ch3;
	cout << "Выберете вариант программы: 1 - одномерный массив, 2 - массив указателей: ";
	while (cin >> ch3) {
		if (ch3 == 1 || ch3 == 2) {
			break;
		}
		else{
			cout << "Некоректный ввод.\n";
			cout << "Выберете вариант программы: 1 - одномерный массив, 2 - массив указателей: ";
		}
	}
	return ch3;
}

int k_const(int c, ifstream& fin) {
	int k;
	if (c == 1)
		fin >> k;
	else {
		cout << "Введите значение коснтанты (k != 0, |k| <= 20) k = ";
		while (cin >> k) {
			if (k != 0 && abs(k) <= 20)
				break;
			cout << "k != 0, |k| <= 20 !\n";
			cout << "Введите значение коснтанты (k != 0, |k| <= 20) k = ";
		}
	}
	return k;
}

void input_matrix_size(int& size_x, int& size_y, int type, ifstream& fin, char matr_name) {
	int a, b;
	if (type == 1) {
		fin >> a >> b;
		size_x = a, size_y = b;
		return;
	}
	else {
		cout << "Введите размер матрицы (от 1 до 10)" << matr_name << ": ";
		while (cin >> a >> b) {
			if (a >= 1 && a <= 10 && b >= 1 && b <= 10) {
				size_x = a, size_y = b;
				return;
			}
			else {
				cout << "Неправильный размер матрицы!\n";
				cout << "Введите размер матрицы (от 1 до 10)" << matr_name << ": ";
			}
		}
	}
}

bool check_add_sizes(int a_n, int a_m, int b_n, int b_m) {
	if (a_n != b_n || a_m != b_m) {
		cerr << "Несовпадающие размеры матриц.\n";
		return false;
	}
	return true;
}

bool check_mul_sizes(int a_n, int a_m, int b_n, int b_m) {
	if (a_m != b_n) {
		cerr << "Несовпадающие размеры матриц.\n";
		return false;
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
///////////////////////1 ВАРИАНТ (одномерный массив)//////////////////////

void generate_matrices(double* a, int a_n, int a_m, int l, int r) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++) {
			a[i * a_m + j] = rand() % (r - l) + l;
		}
	}
}

bool input_matrix(double* matr, int size_x, int size_y, int type, ifstream &fin, char matr_name) {
	if (type == 1) {
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				fin >> matr[i * size_y + j];
				if (abs(matr[i * size_y + j]) > 20) {
					cout << "Числа в матрице должрны быть |a| <= 20 или пропущены некоторые значения!\n";
					return false;
				}
			}
		}
	}
	else if (type == 2) {
		cout << "Введите значения в матрице " << matr_name << ": \n";
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				cin >> matr[i * size_y + j];
				if (abs(matr[i * size_y + j]) > 20) {
					cout << "Числа в матрице должрны быть |a| <= 20!\n";
					return false;
				}
			}
		}
	}
	else{
		cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
		int l_a, r_a;
		while (cin >> l_a >> r_a) {
			if (abs(l_a) > 20 || abs(r_a) > 20) {
				cout << "Числа не могут быть вне диапозона.\n";
				cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
				continue;
			}
			if (l_a > r_a) {
				cout << "Левая граница не может быть больше правой.\n";
				cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
				continue;
			}
			break;
		}
		generate_matrices(matr, size_x, size_y, l_a, r_a);
	}
	return true;
}

void add_matrices(double* a, int a_n, int a_m, double* b, int b_n, int b_m, double* res) {
	if (a_n != b_n || a_m != b_m) {
		cerr << "Несовпадающие размеры матриц.";
		exit(0);
	}
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++)
			res[i * a_m + j] = a[i * a_m + j] + b[i * b_m + j];
	}
}

void mul_matr(double* a, int a_n, int a_m, double* b, int b_n, int b_m, double* res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < b_m; j++) {
			for (int l = 0; l < b_n; l++) {
				res[i * b_m + j] += a[i * b_n + l] * b[l * b_m + j];
			}
		}
	}
}

void div_matr_by_num(double* a, int a_n, int a_m, int k, double* res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++)
			res[i * a_m + j] = a[i * a_m + j] / k;
	}
}

void transp_matr(double* a, int a_n, int a_m, double* res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++) {
			res[j * a_n + i] = a[i * a_m + j];
		}
	}
}

void print_mat(double* a, int a_n, int a_m, int c, ofstream &fout) {
	if (c == 1) {
		for (int i = 0; i < a_n; i++) {
			fout << setw(2);
			for (int j = 0; j < a_m; j++)
				fout << a[i * a_m + j] << setw(10);
			fout << '\n';
		}
	}
	else {
		for (int i = 0; i < a_n; i++) {
			cout << setw(2);
			for (int j = 0; j < a_m; j++)
				cout << a[i * a_m + j] << setw(10);
			cout << '\n';
		}
	}
}

/////////////////////////////////////////////////////////////////////////
///////////////////////2 ВАРИАНТ (масив указателей)//////////////////////

void generate_matrices(double** a, int a_n, int a_m, int l, int r) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++) {
			a[i][j] = rand() % (r - l) + l;
		}
	}
}

bool input_matrix(double** matr, int size_x, int size_y, int type, ifstream& fin, char matr_name) {
	if (type == 1) {
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				fin >> matr[i][j];
				if (abs(matr[i][j]) > 20) {
					cout << "Числа в матрице должрны быть |a| <= 20 или пропущены некоторые значения!\n";
					return false;
				}
			}
		}
	}
	else if (type == 2) {
		cout << "Введите значения в матрице " << matr_name << ": \n";
		for (int i = 0; i < size_x; i++) {
			for (int j = 0; j < size_y; j++) {
				cin >> matr[i][j];
				if (abs(matr[i][j]) > 20) {
					cout << "Числа в матрице должрны быть |a| <= 20!\n";
					return false;
				}
			}
		}
	}
	else {
		cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
		int l_a, r_a;
		while (cin >> l_a >> r_a) {
			if (abs(l_a) > 20 || abs(r_a) > 20) {
				cout << "Числа не могут быть вне диапозона.\n";
				cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
				continue;
			}
			if (l_a > r_a) {
				cout << "Левая граница не может быть больше правой.\n";
				cout << "Введите диапозон чисел в матрице (от -20 до 20)" << matr_name << ": ";
				continue;
			}
			break;
		}
		generate_matrices(matr, size_x, size_y, l_a, r_a);
	}
	return true;
}

void add_matrices(double** a, int a_n, int a_m, double** b, int b_n, int b_m, double** res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++)
			res[i][j] = a[i][j] + b[i][j];
	}
}

void mul_matr(double** a, int a_n, int a_m, double** b, int b_n, int b_m, double** res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < b_m; j++) {
			for (int l = 0; l < b_n; l++) {
				res[i][j] += a[i][l] * b[l][j];
			}
		}
	}
}

void div_matr_by_num(double** a, int a_n, int a_m, double k, double** res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++)
			res[i][j] = a[i][j] / k;
	}
}

void transp_matr(double** a, int a_n, int a_m, double** res) {
	for (int i = 0; i < a_n; i++) {
		for (int j = 0; j < a_m; j++) {
			res[j][i] = a[i][j];
		}
	}
}

void print_mat(double** a, int a_n, int a_m, int c, ofstream& fout) {
	if (c == 1) {
		for (int i = 0; i < a_n; i++) {
			fout << setw(2);
			for (int j = 0; j < a_m; j++)
				fout << a[i][j] << setw(10);
			fout << '\n';
		}
	}
	else {
		for (int i = 0; i < a_n; i++) {
			cout << setw(2);
			for (int j = 0; j < a_m; j++)
				cout << a[i][j] << setw(10);
			cout << '\n';
		}
	}
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

int main() {
	setlocale(LC_ALL, "Russian");
	ifstream fin;
	ofstream fout;
	while (1) {
		cout << '\n';
		int ch1 = input_type();
		if (ch1 == 1) input_file_name(fin);

		int ch2 = output_type();
		if (ch2 == 1) output_file_name(fout), fout << fixed << setprecision(4);
		else cout << fixed << setprecision(4);

		int ch3 = var_type();

		double k = k_const(ch1, fin);
		if (k == 0 || abs(k) > 20) {
			cout << "k не может быть равен 0 или |k| > 20 !\n";
			continue;
		}

		/////////////////////////////////////////////////////////////////

		int a_n, a_m, b_n, b_m, c_n, c_m;

		input_matrix_size(a_n, a_m, ch1, fin, 'A');
		if (a_n < 1 || a_n > 10 || a_m < 1 || a_m > 10) {
			cout << "Неправильный размер матрицы (от 1 до 10 столбцов и колонок)!\n";
			continue;
		}
		double* a1 = new double[a_n * a_m];
		double** a2 = new double* [a_n];
		if (ch3 == 2) {
			delete[] a1;
			for (int i = 0; i < a_n; i++) {
				a2[i] = new double[a_m];
			}
		}
		else delete[] a2;
		if (ch3 == 1) {
			if (!input_matrix(a1, a_n, a_m, ch1, fin, 'A')) continue;
			else {
				if (ch2 == 1) fout << "Матрица A:\n";
				else cout << "Матрица A:\n";
				print_mat(a1, a_n, a_m, ch2, fout);
			}
		}
		else { if (!input_matrix(a2, a_n, a_m, ch1, fin, 'A')) continue;
			else {
				if (ch2 == 1) fout << "Матрица A:\n";
				else cout << "Матрица A:\n";
				print_mat(a2, a_n, a_m, ch2, fout);
			}
		}

		input_matrix_size(b_n, b_m, ch1, fin, 'B');
		if (b_n < 1 || b_n > 10 || b_m < 1 || b_m > 10) {
			cout << "Неправильный размер матрицы (от 1 до 10 столбцов и колонок)!\n";
			continue;
		}
		double* b1 = new double[b_n * b_m];
		double** b2 = new double* [b_n];
		if (ch3 == 2) {
			delete[] b1;
			for (int i = 0; i < b_n; i++) {
				b2[i] = new double[b_m];
			}
		}
		else delete[] b2;
		if (ch3 == 1) { if (!input_matrix(b1, b_n, b_m, ch1, fin, 'B')) continue;
						else {
							if (ch2 == 1) fout << "Матрица B:\n";
							else cout << "Матрица B:\n";
							print_mat(b1, b_n, b_m, ch2, fout);
						}
		}
		else { if (!input_matrix(b2, b_n, b_m, ch1, fin, 'B')) continue;
				else {
					if (ch2 == 1) fout << "Матрица B:\n";
					else cout << "Матрица B:\n";
					print_mat(b2, b_n, b_m, ch2, fout);
				}
		}

		input_matrix_size(c_n, c_m, ch1, fin, 'C');
		if (c_n < 1 || c_n > 10 || c_m < 1 || c_m > 10) {
			cout << "Неправильный размер матрицы (от 1 до 10 столбцов и колонок)!\n";
			continue;
		}
		double* c1 = new double[c_n * c_m];
		double** c2 = new double* [c_n];
		if (ch3 == 2) {
			delete[] c1;
			for (int i = 0; i < c_n; i++) {
				c2[i] = new double[c_m];
			}
		}
		else delete[] c2;
		if (ch3 == 1) { if (!input_matrix(c1, c_n, c_m, ch1, fin, 'C')) continue; 
						else {
							if (ch2 == 1) fout << "Матрица C:\n";
							else cout << "Матрица C:\n";
							print_mat(c1, c_n, c_m, ch2, fout);
						}
		}
		else { if (!input_matrix(c2, c_n, c_m, ch1, fin, 'C')) continue;
				else {
					if (ch2 == 1) fout << "Матрица C:\n";
					else cout << "Матрица C:\n";
					print_mat(c2, c_n, c_m, ch2, fout);
				}
		}

		//////////////////////////////////////////////////////////////

		if (ch2 == 1) fout << "B / k:\n";
		else cout << "B / k:\n";
		double* d1 = new double[b_n * b_m];
		double** d2 = new double* [b_n];
		if (ch3 == 2) {
			delete[] d1;
			for (int i = 0; i < b_n; i++) {
				d2[i] = new double[b_m];
			}
		}
		else delete[] d2;
		if (ch3 == 1) {
			div_matr_by_num(b1, b_n, b_m, k, d1);
			print_mat(d1, b_n, b_m, ch2, fout);
		}
		else {
			div_matr_by_num(b2, b_n, b_m, k, d2);
			print_mat(d2, b_n, b_m, ch2, fout);
		}
		

		if (ch2 == 1) fout << "A + B / k:\n";
		else cout << "A + B / k:\n";
		if (!check_add_sizes(a_n, a_m, b_n, b_m))
			continue;
		double* e1 = new double[b_n * b_m];
		double** e2 = new double* [b_n];
		if (ch3 == 2) {
			delete[] e1;
			for (int i = 0; i < b_n; i++) {
				e2[i] = new double[b_m];
			}
		}
		else delete[] e2;
		if (ch3 == 1) {
			add_matrices(a1, a_n, a_m, d1, b_n, b_m, e1);
			print_mat(e1, b_n, b_m, ch2, fout);
			delete[] d1;
		}
		else {
			add_matrices(a2, a_n, a_m, d2, b_n, b_m, e2);
			print_mat(e2, b_n, b_m, ch2, fout);
			for (int i = 0; i < b_n; i++)
				delete[] d2[i];
			delete[] d2;
		}

		if (ch2 == 1) fout << "(A + B / k)T\n";
		else cout << "(A + B / k)T\n";
		double* f1 = new double[b_m * b_n];
		double** f2 = new double* [b_m];
		if (ch3 == 2) {
			delete[] f1;
			for (int i = 0; i < b_m; i++) {
				f2[i] = new double[b_n];
			}
		}
		else delete[] f2;
		if (ch3 == 1) {
			transp_matr(e1, a_n, a_m, f1);
			print_mat(f1, b_m, b_n, ch2, fout);
			delete[] e1;
		}
		else {
			transp_matr(e2, a_n, a_m, f2);
			print_mat(f2, b_m, b_n, ch2, fout);
			for (int i = 0; i < b_n; i++)
				delete[] e2[i];
			delete[] e2;
		}

		if (ch2 == 1) fout << "(A + B / k)T * C\n";
		else cout << "(A + B / k)T * C\n";
		if (!check_mul_sizes(b_m, b_n, c_n, c_m))
			continue;
		double* g1 = new double[b_m * c_m];
		double** g2 = new double* [b_m];
		if (ch3 == 2) {
			delete[] g1;
			for (int i = 0; i < b_m; i++) {
				g2[i] = new double[c_m];
				for (int j = 0; j < c_m; j++)
					g2[i][j] = 0;
			}
		}
		else {
			delete[] g2;
			for (int i = 0; i < b_m; i++) {
				for (int j = 0; j < c_m; j++)
					g1[i * c_m + j] = 0;
			}
		}
		if (ch3 == 1) {
			mul_matr(f1, b_m, b_n, c1, c_n, c_m, g1);
			print_mat(g1, b_m, c_m, ch2, fout);
			delete[] f1;
			delete[] g1;
		}
		else {
			mul_matr(f2, b_m, b_n, c2, c_n, c_m, g2);
			print_mat(g2, b_m, c_m, ch2, fout);
			for (int i = 0; i < b_m; i++)
				delete[] f2[i];
			delete[] f2;
			for (int i = 0; i < b_m; i++)
				delete[] g2[i];
			delete[] g2;
		}
		if (ch3 == 1) { delete[] a1; delete[] b1; delete[] c1; }
		else { 
			for (int i = 0; i < a_n; i++)
				delete[] a2[i];
			delete[] a2;
			for (int i = 0; i < b_n; i++)
				delete[] b2[i];
			delete[] b2;
			for (int i = 0; i < c_n; i++)
				delete[] c2[i];
			delete[] c2;
		}
		break;
	}
	fin.close();
	fout.close();
	return 0;
}