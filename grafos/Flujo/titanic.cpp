#include <bits/stdc++.h>

using namespace std;

const int MAX_X = 31, MAX_Y = 31, MAX_MOVS = 4, INF = 1123;
const int DI[MAX_MOVS] = {-1, 0, 0, 1}, DJ[MAX_MOVS] = {0, -1, 1, 0};

char grid[MAX_X][MAX_Y];

vector<tuple<int, int, int>> adj_list[MAX_X][MAX_Y][2];
int adj_matrix[MAX_X][MAX_Y][2][MAX_X][MAX_Y][2];
bool visited[MAX_X][MAX_Y][2];
tuple<int, int, int> parent[MAX_X][MAX_Y][2];

struct State {
    int x, y, orientation, px, py, porientation, bottleneck;
};

int bfs(tuple<int, int, int> start, tuple<int, int, int> target) {
    // Reset visited array without using memset
    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            for (int k = 0; k < 2; ++k) {
                visited[i][j][k] = false;
            }
        }
    }

    queue<State> q;
    int start_x = get<0>(start), start_y = get<1>(start), start_orientation = get<2>(start);
    q.push({start_x, start_y, start_orientation, -1, -1, -1, INF});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int curr_x = current.x, curr_y = current.y, curr_orientation = current.orientation;
        if (visited[curr_x][curr_y][curr_orientation]) continue;
        visited[curr_x][curr_y][curr_orientation] = true;

        parent[curr_x][curr_y][curr_orientation] = {current.px, current.py, current.porientation};

        if (curr_x == get<0>(target) && curr_y == get<1>(target) && curr_orientation == get<2>(target)) {
            return current.bottleneck;
        }

        for (auto neighbor : adj_list[curr_x][curr_y][curr_orientation]) {
            int next_x = get<0>(neighbor), next_y = get<1>(neighbor), next_orientation = get<2>(neighbor);
            if (adj_matrix[curr_x][curr_y][curr_orientation][next_x][next_y][next_orientation] > 0) {
                q.push({next_x, next_y, next_orientation, curr_x, curr_y, curr_orientation,
                        min(current.bottleneck, adj_matrix[curr_x][curr_y][curr_orientation][next_x][next_y][next_orientation])});
            }
        }
    }
    return 0;
}

int ford_fulkerson(tuple<int, int, int> start, tuple<int, int, int> target) {
    int max_flow = 0;
    while (int bottleneck = bfs(start, target)) {
        int x = get<0>(target), y = get<1>(target), orientation = get<2>(target);
        while (!(x == get<0>(start) && y == get<1>(start) && orientation == get<2>(start))) {
            int px = get<0>(parent[x][y][orientation]);
            int py = get<1>(parent[x][y][orientation]);
            int porientation = get<2>(parent[x][y][orientation]);
            adj_matrix[px][py][porientation][x][y][orientation] -= bottleneck;
            adj_matrix[x][y][orientation][px][py][porientation] += bottleneck;
            x = px;
            y = py;
            orientation = porientation;
        }
        max_flow += bottleneck;
    }
    return max_flow;
}

int main() {
    int rows, cols, p;
    while (cin >> rows >> cols >> p) {
        for (int i = 0; i < rows; ++i) {
            cin >> grid[i];
        }

        for (int i = 0; i <= rows; ++i) {
            for (int j = 0; j <= cols; ++j) {
                adj_list[i][j][0].clear();
                adj_list[i][j][1].clear();
            }
        }

        // Reset adj_matrix without using memset
        for (int i = 0; i < MAX_X; ++i) {
            for (int j = 0; j < MAX_Y; ++j) {
                for (int k = 0; k < 2; ++k) {
                    for (int l = 0; l < MAX_X; ++l) {
                        for (int m = 0; m < MAX_Y; ++m) {
                            for (int n = 0; n < 2; ++n) {
                                adj_matrix[i][j][k][l][m][n] = 0;
                            }
                        }
                    }
                }
            }
        }

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '~') continue;

                for (int k = 0; k < MAX_MOVS; ++k) {
                    int ni = i + DI[k], nj = j + DJ[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj] != '~') {
                        adj_list[i][j][1].emplace_back(ni, nj, 0);
                        adj_list[ni][nj][0].emplace_back(i, j, 1);
                        adj_matrix[i][j][1][ni][nj][0] = INF;
                    }
                }

                if (grid[i][j] == '#') {
                    adj_list[i][j][0].emplace_back(i, j, 1);
                    adj_list[i][j][1].emplace_back(i, j, 0);
                    adj_matrix[i][j][0][i][j][1] = INF;
                    adj_list[i][j][1].emplace_back(rows, cols, 1);
                    adj_list[rows][cols][1].emplace_back(i, j, 1);
                    adj_matrix[i][j][1][rows][cols][1] = p;
                }

                if (grid[i][j] == '*') {
                    adj_list[i][j][0].emplace_back(i, j, 1);
                    adj_list[i][j][1].emplace_back(i, j, 0);
                    adj_matrix[i][j][0][i][j][1] = 1;
                    adj_list[rows][cols][0].emplace_back(i, j, 0);
                    adj_list[i][j][0].emplace_back(rows, cols, 0);
                    adj_matrix[rows][cols][0][i][j][0] = 1;
                }

                if (grid[i][j] == '.') {
                    adj_list[i][j][0].emplace_back(i, j, 1);
                    adj_list[i][j][1].emplace_back(i, j, 0);
                    adj_matrix[i][j][0][i][j][1] = 1;
                }

                if (grid[i][j] == '@') {
                    adj_list[i][j][0].emplace_back(i, j, 1);
                    adj_list[i][j][1].emplace_back(i, j, 0);
                    adj_matrix[i][j][0][i][j][1] = INF;
                }
            }
        }
        cout << ford_fulkerson({rows, cols, 0}, {rows, cols, 1}) << endl;
    }
}
