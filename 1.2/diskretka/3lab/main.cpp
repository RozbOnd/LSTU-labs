#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <climits>
#include <windows.h>

using namespace std;

const int INF = INT_MAX;

int main() {
    srand(time(0));
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    vector<vector<int>> graph(6, vector<int>(6, INF));

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////
    graph[0][1] = rand() % 15 + 1;
    graph[1][0] = graph[0][1];

    graph[0][2] = rand() % 15 + 1;
    graph[2][0] = graph[0][2];
    
    graph[2][1] = rand() % 15 + 1;
    graph[1][2] = graph[2][1];

    graph[2][3] = rand() % 15 + 1;
    graph[3][2] = graph[2][3];
    
    graph[2][4] = rand() % 15 + 1;
    graph[4][2] = graph[2][4];

    graph[3][4] = rand() % 15 + 1;
    graph[4][3] = graph[3][4];

    graph[3][5] = rand() % 15 + 1;
    graph[5][3] = graph[3][5];

    graph[4][5] = rand() % 15 + 1;
    graph[5][4] = graph[4][5];

    graph[5][1] = rand() % 15 + 1;
    graph[1][5] = graph[5][1];

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////

    cout << "Ребро 1-2: " << graph[0][1] << '\n';
    cout << "Ребро 1-3: " << graph[0][2] << '\n';
    cout << "Ребро 2-3: " << graph[1][2] << '\n';
    cout << "Ребро 2-6: " << graph[1][5] << '\n';
    cout << "Ребро 3-4: " << graph[2][3] << '\n';
    cout << "Ребро 3-5: " << graph[2][4] << '\n';
    cout << "Ребро 4-5: " << graph[3][4] << '\n';
    cout << "Ребро 4-6: " << graph[3][5] << '\n';
    cout << "Ребро 5-6: " << graph[4][5] << '\n';

    //////////////////////////////////////////////////
    //////////////////////////////////////////////////

    vector<int> vertices(6);
    for (int i = 0; i < 6; i++) vertices[i] = i;

    int min_cost = INF;
    vector<int> best_path;

    do {
        bool valid = true;
        int current_cost = 0;

        for (int i = 0; i < 5; i++) {
            int u = vertices[i];
            int v = vertices[i + 1];
            if (graph[u][v] == INF) {
                valid = false;
                break;
            }
            current_cost += graph[u][v];
        }

        if (valid && current_cost < min_cost) {
            min_cost = current_cost;
            best_path = vertices;
        }

    } while (next_permutation(vertices.begin(), vertices.end()));

    cout << "Длина кратчайшего пути: " << min_cost << endl;
    cout << "Путь: ";
    for (int i = 0; i < 5; i++){
        cout << best_path[i] << " - ";
    }
    cout << best_path[5];

    return 0;
}