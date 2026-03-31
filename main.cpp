#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

const int MAXN = 4000005;

int parent[MAXN];
int rnk[MAXN];

inline int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py) return;

    if (rnk[px] < rnk[py]) {
        parent[px] = py;
    } else if (rnk[px] > rnk[py]) {
        parent[py] = px;
    } else {
        parent[py] = px;
        rnk[px]++;
    }
}

int main() {
    int t = read_int();

    while (t--) {
        int n = read_int();

        unordered_map<int, int> id_map;
        id_map.reserve(2 * n);

        vector<int> i_arr(n), j_arr(n), e_arr(n);
        vector<int> i_idx(n), j_idx(n);

        int cnt = 0;

        // Read all constraints and assign IDs on the fly
        for (int k = 0; k < n; k++) {
            i_arr[k] = read_int();
            j_arr[k] = read_int();
            e_arr[k] = read_int();

            if (id_map.find(i_arr[k]) == id_map.end()) {
                id_map[i_arr[k]] = cnt++;
            }
            if (id_map.find(j_arr[k]) == id_map.end()) {
                id_map[j_arr[k]] = cnt++;
            }

            i_idx[k] = id_map[i_arr[k]];
            j_idx[k] = id_map[j_arr[k]];
        }

        // Initialize Union-Find
        for (int i = 0; i < cnt; i++) {
            parent[i] = i;
            rnk[i] = 0;
        }

        // Process equality constraints
        for (int k = 0; k < n; k++) {
            if (e_arr[k] == 1) {
                unite(i_idx[k], j_idx[k]);
            }
        }

        // Check inequality constraints
        bool satisfied = true;
        for (int k = 0; k < n; k++) {
            if (e_arr[k] == 0) {
                if (find(i_idx[k]) == find(j_idx[k])) {
                    satisfied = false;
                    break;
                }
            }
        }

        printf("%s\n", satisfied ? "YES" : "NO");
    }

    return 0;
}
