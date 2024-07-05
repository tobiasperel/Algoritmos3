#include <bits/stdc++.h>
using namespace std;

// Definiciones de constantes
const int MAX_ROWS = 31, MAX_COLS = 31, MAX_DIRECTIONS = 4, MAX_CAPACITY = 1123;
const int DELTA_I[MAX_DIRECTIONS] = {-1, 0, 0, 1}, DELTA_J[MAX_DIRECTIONS] = {0, -1, 1, 0};

// Definición de la estructura de la cuadrícula y las capacidades
char area[MAX_ROWS][MAX_COLS];
vector<array<int, 3>> connections[MAX_ROWS][MAX_COLS][2];
int capacity[MAX_ROWS][MAX_COLS][2][MAX_ROWS][MAX_COLS][2], visited[MAX_ROWS][MAX_COLS][2];
array<int, 3> previous[MAX_ROWS][MAX_COLS][2];

// Función para realizar BFS y encontrar el camino aumentante
bool bfs(array<int, 3> source, array<int, 3> sink) {
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLS; ++j) {
            visited[i][j][0] = 0;
            visited[i][j][1] = 0;
        }
    }
    queue<array<int, 7>> queue;
    int src_i = source[0], src_j = source[1], src_orientation = source[2];
    int sink_i = sink[0], sink_j = sink[1], sink_orientation = sink[2];
    queue.push({src_i, src_j, src_orientation, -1, -1, -1, MAX_CAPACITY});
    while (!queue.empty()) {
        array<int, 7> current = queue.front();
        queue.pop();
        int cur_i = current[0], cur_j = current[1], cur_orientation = current[2];
        if (visited[cur_i][cur_j][cur_orientation]) continue;
        visited[cur_i][cur_j][cur_orientation] = 1;
        previous[cur_i][cur_j][cur_orientation] = {current[3], current[4], current[5]};
        if (array<int, 3>{cur_i, cur_j, cur_orientation} == sink) return current[6];
        for (auto next : connections[cur_i][cur_j][cur_orientation]) {
            int next_i = next[0], next_j = next[1], next_orientation = next[2];
            if (capacity[cur_i][cur_j][cur_orientation][next_i][next_j][next_orientation] > 0) {
                queue.push({next_i, next_j, next_orientation, cur_i, cur_j, cur_orientation, 
                            min(current[6], capacity[cur_i][cur_j][cur_orientation][next_i][next_j][next_orientation])});
            }
        }
    }
    return 0;
}

// Función para ejecutar el algoritmo de Ford-Fulkerson y calcular el flujo máximo
int fordFulkerson(array<int, 3> source, array<int, 3> sink) {
    int totalFlow = 0;
    while (int pathFlow = bfs(source, sink)) {
        array<int, 3> current = sink;
        while (current != source) {
            int cur_i = current[0], cur_j = current[1], cur_orientation = current[2];
            int prev_i = previous[cur_i][cur_j][cur_orientation][0];
            int prev_j = previous[cur_i][cur_j][cur_orientation][1];
            int prev_orientation = previous[cur_i][cur_j][cur_orientation][2];
            capacity[prev_i][prev_j][prev_orientation][cur_i][cur_j][cur_orientation] -= pathFlow;
            capacity[cur_i][cur_j][cur_orientation][prev_i][prev_j][prev_orientation] += pathFlow;
            current = {prev_i, prev_j, prev_orientation};
        }
        totalFlow += pathFlow;
    }
    return totalFlow;
}

// Función principal
int main() {
    int rows, cols, maxOccupancy;
    while (cin >> rows >> cols >> maxOccupancy) {
        for (int i = 0; i < rows; ++i) cin >> area[i];
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                connections[i][j][0].clear();
                connections[i][j][1].clear();
            }
        }
        for (int i = 0; i < MAX_ROWS; ++i) {
            for (int j = 0; j < MAX_COLS; ++j) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < MAX_ROWS; ++l) {
                        for (int m = 0; m < MAX_COLS; ++m) {
                            for (int n = 0; n < 2; ++n) {
                                capacity[i][j][k][l][m][n] = 0;
                            }
                        }
                    }
                }
            }
        }
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (area[i][j] == '~') continue;
                for (int k = 0; k < MAX_DIRECTIONS; ++k) {
                    int new_i = i + DELTA_I[k], new_j = j + DELTA_J[k];
                    if (new_i >= 0 && new_i < rows && new_j >= 0 && new_j < cols && area[new_i][new_j] != '~') {
                        connections[i][j][1].push_back({new_i, new_j, 0});
                        capacity[i][j][1][new_i][new_j][0] = MAX_CAPACITY;
                    }
                }
                if (area[i][j] == '*') {
                    connections[rows][cols][0].push_back({i, j, 0});
                    capacity[rows][cols][0][i][j][0] = 1;
                    connections[i][j][0].push_back({i, j, 1});
                    capacity[i][j][0][i][j][1] = 1;
                } else if (area[i][j] == '.') {
                    connections[i][j][0].push_back({i, j, 1});
                    capacity[i][j][0][i][j][1] = 1;
                } else if (area[i][j] == '@') {
                    connections[i][j][0].push_back({i, j, 1});
                    capacity[i][j][0][i][j][1] = MAX_CAPACITY;
                } else if (area[i][j] == '#') {
                    connections[i][j][0].push_back({i, j, 1});
                    capacity[i][j][0][i][j][1] = MAX_CAPACITY;
                    connections[i][j][1].push_back({rows, cols, 1});
                    capacity[i][j][1][rows][cols][1] = maxOccupancy;
                }
            }
        }
        cout << fordFulkerson({rows, cols, 0}, {rows, cols, 1}) << endl;
    }
}
