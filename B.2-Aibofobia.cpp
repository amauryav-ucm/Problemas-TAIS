/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <unordered_map>
#include <string>
#include <list>
#include <vector>

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define MAX_LEN 1000

using vi = std::vector<int>;
using mat = std::vector<vi>;

class Aibofobia
{
public:
    Aibofobia(std::string word) : word(word), n(word.size()), dpTable(word.size(), vi(word.size(), 0))
    {
        for (int i = n - 1; i >= 0; i--)
            for (int j = i + 1; j < n; j++)
            {
                if (word[i] == word[j])
                    dpTable[i][j] = dpTable[i + 1][j - 1];
                else
                    dpTable[i][j] = std::min(dpTable[i + 1][j], dpTable[i][j - 1]) + 1;
            }
    }
    void printDPTable()
    {
        for (int i = 0; i < dpTable.size(); i++)
        {
            for (int j = 0; j < dpTable[i].size(); j++)
                printf("%d ", dpTable[i][j]);
            printf("\n");
        }
    }

    int getResult() { return dpTable[0][n - 1]; }

    std::string reconstruir()
    {
        std::string palindrome(n + dpTable[0][n - 1], ' ');
        int left = 0, right = palindrome.size() - 1;
        int i = 0, j = n - 1;
        int best = std::min(dpTable[i + 1][j - 1], std::min(dpTable[i + 1][j], dpTable[i][j - 1]));
        while (left <= right)
        {
            if (word[i] == word[j])
            {
                palindrome[left++] = word[i++];
                palindrome[right--] = word[j--];
            }
            else if (dpTable[i][j] == dpTable[i][j - 1] + 1)
            {
                palindrome[left++] = word[j];
                palindrome[right--] = word[j--];
            }
            else
            {
                palindrome[left++] = word[i];
                palindrome[right--] = word[i++];
            }
        }
        return palindrome;
    }

private:
    int n;
    std::string word;
    mat dpTable;
};
bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    std::string s;
    std::cin >> s;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    Aibofobia caso(s);
    // caso.printDPTable();
    // printf("\n");
    // printf("%d\n", caso.getResult());
    printf("%d %s\n", caso.getResult(), caso.reconstruir().c_str());
    //  printf("\n");

    return true;
}

//@ </answer>

int main()
{
#ifdef NUMC
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++)
        resuelveCaso();

#endif

#ifndef NUMC
    while (resuelveCaso())
        ;
#endif
}