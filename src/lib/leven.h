#ifndef LEVEN_H
#define LEVEN_H

#include <string>
class Leven{
public:
    int levenshteinDistance(const std::string &s1, const std::string &s2);
    double levenshteinPercentage(const std::string &s1, const std::string &s2);
};
#endif // LEVENSHTEIN_H
