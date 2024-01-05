#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

std::vector<char> LCS::fill_dyn_matrix(const std::string &x, const std::string &y) {
    int m = x.length();
    int n = y.length();
    std::vector<std::vector<int>> L(m + 1, std::vector<int>(n + 1));

    // matrix L
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (x[i-1] == y[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = std::max(L[i-1][j], L[i][j-1]);
        }
    }

    //  LCS
    std::vector<char> LCS;
    int x_i = m, y_i = n;
    while (x_i > 0 && y_i > 0) {
        if (x[x_i-1] == y[y_i-1]) {
            LCS.push_back(x[x_i-1]);
            x_i--;
            y_i--;
        } else if (L[x_i-1][y_i] >= L[x_i][y_i-1]) {
            x_i--;
        } else {
            y_i--;
        }
    }

    std::reverse(LCS.begin(), LCS.end());
    return LCS;
}

int main() {
    std::string x = "AGGTAB";
    std::string y = "GXTXAYB";
    std::vector<char> lcs = fill_dyn_matrix(x, y);
    for (char c : lcs) std::cout << c;
    std::cout << std::endl;
    return 0;
}
