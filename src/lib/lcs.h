#ifndef LCS_H
#define LCS_H

#include <string>
#include <vector>
class LCS{
public:
    std::vector<char> fill_dyn_matrix(const std::string &x, const std::string &y);
};
#endif
