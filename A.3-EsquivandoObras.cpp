/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

#define IN_FILE "casos/.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define POS(i, j) ((i) >= 0 && (j) >= 0)

using vi = std::vector<int>;
using mati = std::vector<vi>;

int resolver(const mati &m)
{
    mati comb(m.size(), vi(m[0].size(), 0));
    comb[0][0] = m[0][0];
    for (int i = 0; i < m.size(); i++)
        for (int j = 0; j < m[0].size(); j++)
        {
            if (!m[i][j])
                continue;
            if (POS(i - 1, j))
                comb[i][j] += comb[i - 1][j];
            if (POS(i, j - 1))
                comb[i][j] += comb[i][j - 1];
        }
    return comb[m.size()-1][m[0].size()-1];
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M;
    std::cin >> N >> M;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    mati m(N, vi(M));
    char aux;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
        {
            std::cin >> aux;
            m[i][j] = (aux == '.' ? 1 : 0);
        }
    int sol = resolver(m);
    printf("%d\n", sol);
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