#include <iostream>
#include <vector>
#include <string>

// lcs
std::string findLCS(const std::string &a, const std::string &b) {
    int m = a.size(), n = b.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    // coś z LCS
    std::string lcs;
    for (int i = m, j = n; i > 0 && j > 0; ) {
        if (a[i - 1] == b[j - 1]) {
            lcs = a[i - 1] + lcs;
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    return lcs;
}

// wyszukiwanie zmian
void identifyChanges(const std::string &a, const std::string &b, const std::string &lcs) {
    int indexA = 0, indexB = 0, indexLCS = 0;

    while (indexA < a.size() || indexB < b.size()) {
        // kiedy 2 linii skończyli sie
        if (indexA == a.size() && indexB == b.size()) break;

        //  bez zmian lcs
        if (indexA < a.size() && indexB < b.size() && a[indexA] == lcs[indexLCS] && b[indexB] == lcs[indexLCS]) {
            indexA++;
            indexB++;
            indexLCS++;
        } else {
            if (indexA < a.size() && (indexLCS == lcs.size() || a[indexA] != lcs[indexLCS])) {
                std::cout << "Udaleno z 1 stroki: '" << a[indexA] << "' (Position " << indexA + 1 << ")" << std::endl;
                indexA++;
            }
            if (indexB < b.size() && (indexLCS == lcs.size() || b[indexB] != lcs[indexLCS])) {
                std::cout << "Dodano do 2 linii: '" << b[indexB] << "' (Pozycja " << indexB + 1 << ")" << std::endl;
                indexB++;
            }
        }
    }
}

int main() {
    std::string a = "GATTACA";
    std::string b = "GCATGCU";
    std::string lcs = findLCS(a, b);

    std::cout << "LCS: " << lcs << std::endl;
    identifyChanges(a, b, lcs);

    return 0;
}
