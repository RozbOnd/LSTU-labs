#pragma once
#include "Sorting.h"

void interval_search_a(element* els, int size, char* start, char* end) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(els[mid].a, start);

        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    int start_index = left;

    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(els[mid].a, end);

        if (cmp > 0) right = mid - 1;
        else left = mid + 1;
    }
    int end_index = right;

    if (start_index <= end_index) {
        cout << "Записи в интервале [" << start << "; " << end << "]:" << '\n';
        for (int i = start_index; i <= end_index; i++) els[i].print();
    }
    else cout << "Записи в интервале [" << start << "; " << end << "] не найдены." << '\n';
}

void interval_search_b(element* els, int size, char* start, char* end) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(els[mid].b, start);

        if (cmp < 0) left = mid + 1;
        else right = mid - 1;
    }
    int start_index = left;

    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(els[mid].b, end);

        if (cmp > 0) right = mid - 1;
        else left = mid + 1;
    }
    int end_index = right;

    if (start_index <= end_index) {
        cout << "Записи в интервале [" << start << "; " << end << "]:" << '\n';
        for (int i = start_index; i <= end_index; i++) els[i].print();
    }
    else cout << "Записи в интервале [" << start << "; " << end << "] не найдены." << '\n';
}

void interval_search_c(element* els, int size, int start, int end) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (start > els[mid].c) left = mid + 1;
        else right = mid - 1;
    }
    int start_index = left;

    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (end < els[mid].c) right = mid - 1;
        else left = mid + 1;
    }
    int end_index = right;

    if (start_index <= end_index) {
        cout << "Записи в интервале [" << start << "; " << end << "]:" << '\n';
        for (int i = start_index; i <= end_index; i++) els[i].print();
    }
    else cout << "Записи в интервале [" << start << "; " << end << "] не найдены." << '\n';
}

void interval_search_d(element* els, int size, float start, float end) {
    int left = 0;
    int right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (start > els[mid].d) left = mid + 1;
        else right = mid - 1;
    }
    int start_index = left;

    left = 0;
    right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (end < els[mid].d) right = mid - 1;
        else left = mid + 1;
    }
    int end_index = right;

    if (start_index <= end_index) {
        cout << "Записи в интервале [" << start << "; " << end << "]:" << '\n';
        for (int i = start_index; i <= end_index; i++) els[i].print();
    }
    else cout << "Записи в интервале [" << start << "; " << end << "] не найдены." << '\n';
}