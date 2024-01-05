#include <iostream>
#include <vector>
#include <algorithm> // для std::max


void printAlignment(const std::string &a, const std::string &b, const std::vector<std::vector<int>> &path) {
    int i = a.size();
    int j = b.size();
    std::string alignA = "", alignB = "";

    while (i > 0 && j > 0) {
        if (path[i][j] == path[i-1][j-1] + ((a[i-1] == b[j-1]) ? 0 : -1)) {
            alignA = a[i-1] + alignA;
            alignB = b[j-1] + alignB;
            i--;
            j--;
        } else if (path[i][j] == path[i-1][j] - 1) {
            alignA = a[i-1] + alignA;
            alignB = "-" + alignB;
            i--;
        } else {
            alignA = "-" + alignA;
            alignB = b[j-1] + alignB;
            j--;
        }
    }

    while (i > 0) {
        alignA = a[i-1] + alignA;
        alignB = "-" + alignB;
        i--;
    }

    while (j > 0) {
        alignA = "-" + alignA;
        alignB = b[j-1] + alignB;
        j--;
    }

    std::cout << alignA << "\n" << alignB << "\n";
}

void needlemanWunsch(const std::string &a, const std::string &b) {
    int penalty = -1; // sztrafy
    int m = a.size();
    int n = b.size();
    std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));

  
    for(int i = 0; i <= m; i++) dp[i][0] = i * penalty;
    for(int j = 0; j <= n; j++) dp[0][j] = j * penalty;

    // matrix
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            int match = dp[i-1][j-1] + (a[i-1] == b[j-1] ? 0 : penalty);
            int deleteA = dp[i-1][j] + penalty;
            int deleteB = dp[i][j-1] + penalty;
            dp[i][j] = std::max({match, deleteA, deleteB});
        }
    }

    
    printAlignment(a, b, dp);
}

int main() {
    std::string a = "GATTACA";
    std::string b = "GCATGCU";
    needlemanWunsch(a, b);
    return 0;
}
