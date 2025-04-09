#include <iostream>
#include <clocale>
using namespace std;

struct Vector {
    int size;
    int* cords;

    Vector(): size{0}, cords{nullptr}{}

    Vector(int sz) : size{sz} {
        cords = new int[sz];
    }

    // ~Vector() {
    //     if (cords != nullptr){
    //         delete[] cords;
    //         cords = nullptr;
    //         size = 0;
    //     }
    // }
};

istream& operator >> (istream &is, Vector &vec){
    if (vec.cords != nullptr) {
        delete[] vec.cords;
        vec.size = 0;
    }
    cout << "Введите размер вектора: ";
    is >> vec.size;
    vec.cords = new int[vec.size];
    cout << "\nВведите координаты вектора: ";
    for (int i = 0; i < vec.size; i++)
        is >> vec.cords[i];
    cout << '\n';
    return is;
}

ostream& operator << (ostream &os, const Vector &vec){
    os << "( ";
    for (int i = 0; i < vec.size; i++)
        os << vec.cords[i] << " ";
    os << ")\n";
    return os;
}

Vector add(Vector v1, Vector v2) {
    Vector res(v1.size);
    for (int i = 0; i < v1.size; i++)
        res.cords[i] = v1.cords[i] + v2.cords[i];
    return res;
}

Vector mul(Vector v, int n) {
    Vector res(v.size);
    for (int i = 0; i < v.size; i++)
        res.cords[i] = v.cords[i] * n;
    return res;
}

int scalar_mul(Vector v1, Vector v2) {
    int res = 0;
    for (int i = 0; i < v1.size; i++)
        res += v1.cords[i] * v2.cords[i];
    return res;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Vector a, b, c;
    cin >> a >> b >> c;

    int scal = scalar_mul(b, c);
    cout << "(b * c)\n" << scal << '\n';
    Vector cur1 = mul(a, scal);
    cout << "(b * c) * a\n" << cur1 << '\n';
    Vector cur2 = mul(a, 3);
    cout << "3 * a\n" << cur2 << '\n';
    Vector res = add(cur2, cur1);
    cout << "3 * a + (b * c) * a\n" << res;

    return 0;
}