#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>

using namespace std;

struct State {
    int room;
    vector<bool> lights;
    int steps;
    vector<string> actions;
};

string state_to_string(const State& state) {
    string state_str = to_string(state.room) + ":";
    for (bool light : state.lights) state_str += (light ? "1" : "0");
    return state_str;
}

bool is_valid_state(const State& state, int r) {
    // Verificar que no se entre a una habitación oscura
    if (!state.lights[state.room]) return false;
    // Verificar que solo la luz del dormitorio esté encendida al llegar
    if (state.room == r) {
        for (int i = 1; i < r; ++i) {
            if (state.lights[i]) return false;
        }
        return true; // Asegurar que la luz del dormitorio está encendida
    }
    return true;
}

int main() {
    int test_case = 1;
    while (true) {
        int r, d, s;
        cin >> r >> d >> s;
        if (r == 0 && d == 0 && s == 0) break;

        vector<vector<int>> adj(r + 1);
        vector<vector<int>> switches(r + 1);

        for (int i = 0; i < d; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 0; i < s; ++i) {
            int k, l;
            cin >> k >> l;
            switches[k].push_back(l);
        }

        queue<State> q;
        unordered_set<string> visited;

        vector<bool> initial_lights(r + 1, false);
        initial_lights[1] = true;
        q.push({1, initial_lights, 0, {}});

        bool solved = false;
        State final_state;

        while (!q.empty() && !solved) {
            State current = q.front();
            q.pop();

            string state_str = state_to_string(current);
            if (visited.count(state_str)) continue;
            visited.insert(state_str);

            if (current.room == r && is_valid_state(current, r)) {
                solved = true;
                final_state = current;
                break;
            }

            for (int next_room : adj[current.room]) {
                if (current.lights[next_room]) {
                    State next_state = current;
                    next_state.room = next_room;
                    next_state.steps++;
                    next_state.actions.push_back("Move to room " + to_string(next_room) + ".");
                    q.push(next_state);
                }
            }

            for (int light : switches[current.room]) {
                State next_state = current;
                next_state.lights[light] = !next_state.lights[light];
                next_state.steps++;
                string action = next_state.lights[light] ? "Switch on" : "Switch off";
                next_state.actions.push_back(action + " light in room " + to_string(light) + ".");
                q.push(next_state);
            }
        }

        cout << "Villa #" << test_case << endl;
        if (solved) {
            cout << "The problem can be solved in " << final_state.steps << " steps:" << endl;
            for (const string& action : final_state.actions) {
                cout << "- " << action << endl;
            }
        } else {
            cout << "The problem cannot be solved." << endl;
        }
        cout << endl;

        test_case++;
    }

    return 0;
}
