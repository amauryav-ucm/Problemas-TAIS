/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using vi = std::vector<int>;
using mat = std::vector<vi>;

class LCS
{
public:
    LCS(const vi &list1, const vi &list2) : len1(list1.size()), len2(list2.size()),
                                            dp_table(len1 + 1, vi(len2 + 1, 0)),
                                            list1(list1), list2(list2)
    {
        for (int i = 1; i <= len1; i++)
            for (int j = 1; j <= len2; j++)
            {
                if (list1[i - 1] == list2[j - 1])
                    dp_table[i][j] = dp_table[i - 1][j - 1] + 1;
                else if (dp_table[i - 1][j] > dp_table[i][j - 1])
                    dp_table[i][j] = dp_table[i - 1][j];
                else
                    dp_table[i][j] = dp_table[i][j - 1];
            }
    }

    vi get_result()
    {
        vi ret(dp_table[len1][len2]);
        int i = len1, j = len2;
        int it = ret.size();
        while (it > 0)
        {
            if (list1[i - 1] == list2[j - 1])
            {
                ret[--it] = list1[i - 1];
                i--;
                j--;
            }
            else if (dp_table[i][j] == dp_table[i - 1][j])
                i--;
            else
                j--;
        }
        return ret;
    }

    void
    printDPTable()
    {
        for (int i = 0; i < dp_table.size(); i++)
        {
            for (int j = 0; j < dp_table[i].size(); j++)
                printf("%d ", dp_table[i][j]);
            printf("\n");
        }
    }

private:
    int len1, len2;
    mat dp_table;
    vi list1, list2;
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    std::string line1, line2;
    getline(std::cin, line1);
    getline(std::cin, line2);

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    std::unordered_map<std::string, int> id;
    std::unordered_map<int, std::string> name;
    int currID = 0;
    vi list1, list2;
    std::stringstream stream1(line1), stream2(line2);
    std::string word;
    while (stream1 >> word)
    {
        if (!id.count(word))
        {
            id.insert({word, currID});
            name.insert({currID++, word});
        }
        list1.push_back(id.at(word));
    }
    while (stream2 >> word)
    {
        if (!id.count(word))
        {
            id.insert({word, currID});
            name.insert({currID++, word});
        }
        list2.push_back(id.at(word));
    }

    LCS caso(list1, list2);
    //caso.printDPTable();
    for (int x : caso.get_result())
        printf("%s ", name.at(x).c_str());
    printf("\n");
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