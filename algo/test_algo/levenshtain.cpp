#include <iostream>
#include <vector>
#include <algorithm>

int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int len1 = s1.size();
    int len2 = s2.size();
    std::vector<std::vector<int>> d(len1 + 1, std::vector<int>(len2 + 1));

    for (int i = 0; i <= len1; i++) {
        d[i][0] = i;
    }
    for (int j = 0; j <= len2; j++) {
        d[0][j] = j;
    }

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost });
        }
    }

    return d[len1][len2];
}

int main() {
    std::string str1 = "kot";
    std::string str2 = "skatr";
    std::cout << "Levenshtein Distance: " << levenshteinDistance(str1, str2) << std::endl;
    return 0;
}


double levenshteinPercentage(const std::string &s1, const std::string &s2) {
    int distance = levenshteinDistance(s1, s2);
    int maxLength = std::max(s1.length(), s2.length());
    
    //nie dzielić na zero
    if (maxLength == 0) return 0.0; 

    return 100.0 * distance / maxLength;
}

int main1() {
    std::string str1 = "example";
    std::string str2 = "samples";

    std::cout << "Levenshtein Distance: " << levenshteinDistance(str1, str2) << std::endl;
    std::cout << "Percentage: " << levenshteinPercentage(str1, str2) << "%" << std::endl;

    return 0;
}

