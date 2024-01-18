// levenshtein.h
#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <string>
#include <vector>
#include <algorithm> // Dla std::min

// Deklaracja funkcji obliczającej odległość Levenshteina
int levenshteinDistance(const std::string &s1, const std::string &s2);

// Deklaracja funkcji obliczającej procentową różnicę pomiędzy ciągami znaków
double levenshteinPercentage(const std::string &s1, const std::string &s2);

#endif // LEVENSHTEIN_H