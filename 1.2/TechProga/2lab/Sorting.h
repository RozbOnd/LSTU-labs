#pragma once
#include <cstring>
#include <iostream>
using namespace std;

struct element {
    char a[20];
    char* b = new char[40];
    int c;
    float d;

    void print() {
        cout << "Key: " << a << ", char*: " << b << ", int: " << c << ", float: " << d << '\n';
    }
};

element* copy_arr(element* b, int n) {
    element* a = new element[n];
    for (int i = 0; i < n; i++) a[i] = b[i];
    return a;
}

bool comp_a(const element& a, const element& b) {
    return strcmp(a.a, b.a) < 0;
}

bool comp_b(const element& a, const element& b) {
    return strcmp(a.b, b.b) < 0;
}

bool comp_c(const element& a, const element& b) {
    return a.c < b.c;
}

bool comp_d(const element& a, const element& b) {
    return a.d < b.d;
}

void sort_Shell(element* els, int n, bool(*comp)(const element&, const element&)) {
    for (int step = n / 2; step > 0; step /= 2) {
        for (int i = step; i < n; i++) {
            element cur = els[i];
            int j;
            for (j = i; j >= step && comp(cur, els[j - step]); j -= step)
                els[j] = els[j - step];
            els[j] = cur;
        }
    }
}
