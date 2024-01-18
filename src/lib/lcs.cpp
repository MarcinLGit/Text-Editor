#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 



std::vector<char> fill_dyn_matrix( std::string &x,  std::string &y) {
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

    // LCS
    std::vector<char> lcs;
    int x_i = m, y_i = n;
    while (x_i > 0 && y_i > 0) {
        if (x[x_i-1] == y[y_i-1]) {
            lcs.push_back(x[x_i-1]);
            x_i--;
            y_i--;
        } else if (L[x_i-1][y_i] > L[x_i][y_i-1]) {
            x_i--;
        } else {
            y_i--;
        }
    }

    std::reverse(lcs.begin(), lcs.end());
    return lcs;
}


double lcsPercentage(const std::string &s1, const std::string &s2) {
    
    std::string s1_copy = s1;
    std::string s2_copy = s2;

    std::vector<char> lcs = fill_dyn_matrix(s1_copy, s2_copy);

    int lcsLength = lcs.size();
    int maxLength = std::max(s1.length(), s2.length());

    if (maxLength == 0) return 0.0; 

    return 100.0 * lcsLength / maxLength;
}


