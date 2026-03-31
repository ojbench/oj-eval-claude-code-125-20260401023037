#include <cstdio>
#include <unordered_map>
#include <vector>
using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;

public:
    void make_set(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
        }
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

        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    void clear() {
        parent.clear();
        rank.clear();
    }
};

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        int n;
        scanf("%d", &n);

        UnionFind uf;
        vector<tuple<int, int, int>> constraints;

        // Read all constraints
        for (int k = 0; k < n; k++) {
            int i, j, e;
            scanf("%d %d %d", &i, &j, &e);
            constraints.push_back(make_tuple(i, j, e));
            uf.make_set(i);
            uf.make_set(j);
        }

        // First pass: process all equality constraints
        for (const auto& c : constraints) {
            int i = get<0>(c);
            int j = get<1>(c);
            int e = get<2>(c);
            if (e == 1) {
                uf.unite(i, j);
            }
        }

        // Second pass: check all inequality constraints
        bool satisfied = true;
        for (const auto& c : constraints) {
            int i = get<0>(c);
            int j = get<1>(c);
            int e = get<2>(c);
            if (e == 0) {
                if (uf.same(i, j)) {
                    satisfied = false;
                    break;
                }
            }
        }

        printf("%s\n", satisfied ? "YES" : "NO");
        uf.clear();
    }

    return 0;
}
