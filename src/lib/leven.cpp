#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Для std::min

int Leven::levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.length(), n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            int deletion = dp[i - 1][j] + 1;
            int insertion = dp[i][j - 1] + 1;
            int substitution = dp[i - 1][j - 1] + cost;

            dp[i][j] = std::min(std::min(deletion, insertion), substitution);
        }
    }

    return dp[m][n];
}


/*
int main() {
    std::string str1 = "kot";
    std::string str2 = "skatr";
    std::cout << "Levenshtein Distance: " << levenshteinDistance(str1, str2) << std::endl;
    return 0;
}*/


double Leven::levenshteinPercentage(const std::string &s1, const std::string &s2) {
    int distance = levenshteinDistance(s1, s2);
    int maxLength = std::max(s1.length(), s2.length());
    
    //nie dzielić na zero
    if (maxLength == 0) return 0.0; 

    return 100.0 * distance / maxLength;
}

int main() {
    std::string str1 = "example";
    std::string str2 = "samples";

    std::cout << "Levenshtein Distance: " << levenshteinDistance(str1, str2) << std::endl;
    std::cout << "Percentage: " << levenshteinPercentage(str1, str2) << "%" << std::endl;

    return 0;
}

