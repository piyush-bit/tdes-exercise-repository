#include "dynamic_programming.hpp"
#include <algorithm>
#include <functional>
#include <limits>
#include <string>
#include <vector>

// 1. Longest Common Subsequence & Diff
LCSResult longest_common_subsequence(const std::string& X, const std::string& Y) {
    int m = static_cast<int>(X.length());
    int n = static_cast<int>(Y.length());

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int i = m;
    int j = n;
    std::string lcs_rev = "";
    std::vector<std::string> diff_rev;

    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && X[i - 1] == Y[j - 1]) {
            lcs_rev.push_back(X[i - 1]);
            diff_rev.push_back(std::string(" ") + X[i - 1]);
            i--;
            j--;
        } else if (j > 0 && (i == 0 || dp[i][j - 1] >= dp[i - 1][j])) {
            diff_rev.push_back(std::string("+") + Y[j - 1]);
            j--;
        } else if (i > 0) {
            diff_rev.push_back(std::string("-") + X[i - 1]);
            i--;
        }
    }

    std::reverse(lcs_rev.begin(), lcs_rev.end());
    std::reverse(diff_rev.begin(), diff_rev.end());

    return LCSResult{dp[m][n], lcs_rev, diff_rev};
}

// 2. 0/1 Knapsack Problem
KnapsackResult knapsack_01_dp(int capacity, const std::vector<int>& weights, const std::vector<int>& values) {
    int n = static_cast<int>(weights.size());
    if (n == 0 || capacity <= 0) {
        return KnapsackResult{0, {}};
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (w >= weights[i - 1]) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }

    std::vector<int> selected;
    int w = capacity;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected.push_back(i - 1);
            w -= weights[i - 1];
        }
    }
    std::reverse(selected.begin(), selected.end());

    return KnapsackResult{dp[n][capacity], selected};
}

// 3. Matrix Chain Multiplication
MCMResult matrix_chain_order(const std::vector<int>& dims) {
    int n = static_cast<int>(dims.size()) - 1;
    if (n <= 0) {
        return MCMResult{0, ""};
    }
    if (n == 1) {
        return MCMResult{0, "A1"};
    }

    std::vector<std::vector<int>> m(n + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> s(n + 1, std::vector<int>(n + 1, 0));

    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            m[i][j] = 1e9;
            for (int k = i; k < j; ++k) {
                int q = m[i][k] + m[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (q < m[i][j]) {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }

    std::function<std::string(int, int)> build_parens = [&](int i, int j) -> std::string {
        if (i == j) {
            return "A" + std::to_string(i);
        }
        return "(" + build_parens(i, s[i][j]) + build_parens(s[i][j] + 1, j) + ")";
    };

    return MCMResult{m[1][n], build_parens(1, n)};
}

// 4. Traveling Salesperson Problem (Bitmask DP)
TSPResult tsp_dp(const std::vector<std::vector<int>>& dist) {
    int n = static_cast<int>(dist.size());
    if (n == 0) {
        return TSPResult{0, {}};
    }
    if (n == 1) {
        return TSPResult{0, {0, 0}};
    }

    const int INF = 1e9;
    int num_states = 1 << n;
    std::vector<std::vector<int>> dp(num_states, std::vector<int>(n, INF));
    std::vector<std::vector<int>> parent(num_states, std::vector<int>(n, -1));

    dp[1][0] = 0;

    for (int mask = 1; mask < num_states; ++mask) {
        if (!(mask & 1)) continue;
        for (int u = 0; u < n; ++u) {
            if (!(mask & (1 << u)) || dp[mask][u] == INF) continue;
            for (int v = 0; v < n; ++v) {
                if (mask & (1 << v)) continue;
                int next_mask = mask | (1 << v);
                int new_cost = dp[mask][u] + dist[u][v];
                if (new_cost < dp[next_mask][v]) {
                    dp[next_mask][v] = new_cost;
                    parent[next_mask][v] = u;
                }
            }
        }
    }

    int full_mask = (1 << n) - 1;
    int min_cost = INF;
    int last_city = -1;

    for (int u = 1; u < n; ++u) {
        if (dp[full_mask][u] != INF) {
            int cost = dp[full_mask][u] + dist[u][0];
            if (cost < min_cost) {
                min_cost = cost;
                last_city = u;
            }
        }
    }

    if (last_city == -1) {
        return TSPResult{INF, {}};
    }

    std::vector<int> rev_path;
    int curr_city = last_city;
    int curr_mask = full_mask;

    while (curr_city != 0) {
        rev_path.push_back(curr_city);
        int p = parent[curr_mask][curr_city];
        curr_mask ^= (1 << curr_city);
        curr_city = p;
    }
    rev_path.push_back(0);

    std::reverse(rev_path.begin(), rev_path.end());
    rev_path.push_back(0);

    return TSPResult{min_cost, rev_path};
}
