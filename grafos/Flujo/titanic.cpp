// Inspirado en el algoritmo propuesto por geekForGreks

#include <iostream>
#include <vector>
#include <queue>
#include <array>
using namespace std;

const int MAX_X = 31, MAX_Y = 31, MAX_MOVS = 4, INF = 1200;
const int DI[MAX_MOVS] = {-1, 0, 0, 1}, DJ[MAX_MOVS] = {0, -1, 1, 0};

char grid[MAX_X][MAX_Y];

struct Node {
    int x, y, orientation;
};

struct Edge {
    Node to;
    int capacity;
};

vector<Edge> adj_list[MAX_X][MAX_Y][2];
int adj_matrix[MAX_X][MAX_Y][2][MAX_X][MAX_Y][2];
bool visited[MAX_X][MAX_Y][2];
Node parent[MAX_X][MAX_Y][2];

struct State {
    Node node;
    Node parent;
    int bottleneck;
};

int bfs(Node start, Node target) {
    for (int i = 0; i < MAX_X; ++i)
        for (int j = 0; j < MAX_Y; ++j)
            for (int k = 0; k < 2; ++k)
                visited[i][j][k] = false;

    queue<State> q;
    q.push({start, {-1, -1, -1}, INF});

    while (!q.empty()) {
        State current = q.front();
        q.pop();

        int x = current.node.x, y = current.node.y, orientation = current.node.orientation;
        if (visited[x][y][orientation])
            continue;
        visited[x][y][orientation] = true;

        parent[x][y][orientation] = current.parent;

        if (current.node.x == target.x && current.node.y == target.y && current.node.orientation == target.orientation) {
            return current.bottleneck;
        }

        for (auto &neighbor : adj_list[x][y][orientation]) {
            int nx = neighbor.to.x, ny = neighbor.to.y, norientation = neighbor.to.orientation;
            if (!visited[nx][ny][norientation] && adj_matrix[x][y][orientation][nx][ny][norientation] > 0) {
                q.push({{nx, ny, norientation}, {x, y, orientation}, 
                        min(current.bottleneck, adj_matrix[x][y][orientation][nx][ny][norientation])});
            }
        }
    }
    return 0;
}

int ford_fulkerson(Node start, Node target) {
    int total_flow = 0;

    while (int bottleneck = bfs(start, target)) {
        for (Node u = target; !(u.x == start.x && u.y == start.y && u.orientation == start.orientation); u = parent[u.x][u.y][u.orientation]) {
            Node &p = parent[u.x][u.y][u.orientation];
            adj_matrix[p.x][p.y][p.orientation][u.x][u.y][u.orientation] -= bottleneck;
            adj_matrix[u.x][u.y][u.orientation][p.x][p.y][p.orientation] += bottleneck;
        }
        total_flow += bottleneck;
    }

    return total_flow;
}

int main() {
    int rows, cols, p;
    while (cin >> rows >> cols >> p) {
        for (int i = 0; i < rows; ++i)
            cin >> grid[i];

        for (int i = 0; i <= rows; ++i)
            for (int j = 0; j <= cols; ++j) {
                adj_list[i][j][0].clear();
                adj_list[i][j][1].clear();
            }

        for (int i = 0; i < MAX_X; ++i)
            for (int j = 0; j < MAX_Y; ++j)
                for (int k = 0; k < 2; ++k)
                    for (int l = 0; l < MAX_X; ++l)
                        for (int m = 0; m < MAX_Y; ++m)
                            for (int n = 0; n < 2; ++n)
                                adj_matrix[i][j][k][l][m][n] = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == '~')
                    continue;

                for (int k = 0; k < MAX_MOVS; ++k) {
                    int ni = i + DI[k], nj = j + DJ[k];
                    if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && grid[ni][nj] != '~') {
                        adj_list[i][j][1].push_back({{ni, nj, 0}, INF});
                        adj_list[ni][nj][0].push_back({{i, j, 1}, 0});
                        adj_matrix[i][j][1][ni][nj][0] = INF;
                    }
                }

                if (grid[i][j] == '#') {
                    adj_list[i][j][0].push_back({{i, j, 1}, INF});
                    adj_list[i][j][1].push_back({{i, j, 0}, 0});
                    adj_list[i][j][1].push_back({{rows, cols, 1}, p});
                    adj_list[rows][cols][1].push_back({{i, j, 1}, 0});
                    adj_matrix[i][j][0][i][j][1] = INF;
                    adj_matrix[i][j][1][rows][cols][1] = p;
                }

                if (grid[i][j] == '*') {
                    adj_list[i][j][0].push_back({{i, j, 1}, 1});
                    adj_list[i][j][1].push_back({{i, j, 0}, 0});
                    adj_list[rows][cols][0].push_back({{i, j, 0}, 1});
                    adj_list[i][j][0].push_back({{rows, cols, 0}, 0});
                    adj_matrix[i][j][0][i][j][1] = 1;
                    adj_matrix[rows][cols][0][i][j][0] = 1;
                }

                if (grid[i][j] == '.') {
                    adj_matrix[i][j][0][i][j][1] = 1;
                    adj_list[i][j][0].push_back({{i, j, 1}, 1});
                    adj_list[i][j][1].push_back({{i, j, 0}, 0});
                }

                if (grid[i][j] == '@') {
                    adj_matrix[i][j][0][i][j][1] = INF;
                    adj_list[i][j][0].push_back({{i, j, 1}, INF});
                    adj_list[i][j][1].push_back({{i, j, 0}, 0});
                }
            }
        }
        cout << ford_fulkerson({rows, cols, 0}, {rows, cols, 1}) << endl;
    }
}
