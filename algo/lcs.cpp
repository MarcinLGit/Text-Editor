#include<iostream>
#include<vector>

// Функция для нахождения LCS
std::string LCS(std::string X, std::string Y) {
    int m = X.size();
    int n = Y.size();
    std::vector<std::vector<int>> c(1 + m, std::vector<int>(1 + n));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
            } else {
                c[i][j] = std::max(c[i][j-1], c[i-1][j]);
            }
        }
    }

    // Восстановление LCS из таблицы c
    std::string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (X[i-1] == Y[j-1]) {
            lcs = X[i-1] + lcs;
            i--;
            j--;
        } else if (c[i-1][j] > c[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

int main() {
    std::string a = " skfvs.kj";
    std::string b = "yoabluaaaannnnnnnnnnnnnn";
    std::string lcs = LCS(a, b);
    std::cout << "Longest Common Subsequence: " << lcs << std::endl;
    return 0;
}
