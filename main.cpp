#include <cstdio>
#include <algorithm>
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

        vector<int> vals;
        vals.reserve(2 * n);

        vector<int> i_arr(n), j_arr(n), e_arr(n);
        vector<int> i_idx(n), j_idx(n);

        // Read all constraints
        for (int k = 0; k < n; k++) {
            i_arr[k] = read_int();
            j_arr[k] = read_int();
            e_arr[k] = read_int();
            vals.push_back(i_arr[k]);
            vals.push_back(j_arr[k]);
        }

        // Coordinate compression
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();

        // Initialize Union-Find
        for (int i = 0; i < m; i++) {
            parent[i] = i;
            rnk[i] = 0;
        }

        // Pre-compute indices
        for (int k = 0; k < n; k++) {
            i_idx[k] = lower_bound(vals.begin(), vals.end(), i_arr[k]) - vals.begin();
            j_idx[k] = lower_bound(vals.begin(), vals.end(), j_arr[k]) - vals.begin();
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
