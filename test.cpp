/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// #define NUMC
// #define CENT
// #define ILIM

//@ <answer>
int dp_table[20][1000];
std::vector<int> denom;

void recursiva(int i, int j, std::vector<int> &cantidades)
{
    if (j == 0)
        dp_table[i][j] = 0;
    if (i == 0)
        dp_table[i][j] = 1e9;
    if (denom[i] > j || cantidades[i] == 0)
    {
        recursiva(i - 1, j, cantidades);
    }
    else
    {
        cantidades[i]--;
        recursiva(i, j - denom[i], cantidades);
        cantidades[i]++;
        recursiva(i - 1, j, cantidades);
        dp_table[i][j] = std::min(dp_table[i - 1][j], dp_table[i][j - denom[i]]);
    }
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver();
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