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
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using matii = std::vector<vii>;
using vi = std::vector<int>;
using mati = std::vector<vi>;

ii resolver(const mati &m)
{
    int N = m.size(), M = m[0].size();
    ii best;
    matii sum(N, vii(M));
    for (int i = N - 1; i >= 0; i--)
        for (int j = 0; j < M; j++)
        {
            sum[i][j] = {m[i][j], -j};
            if (i == N - 1)
                continue;
            for (int k = std::max(j - 1, 0); k < std::min(j + 2, M); k++)
            {
                ii cand = sum[i + 1][k];
                cand.first += m[i][j];
                sum[i][j] = std::max(sum[i][j], cand);
            }
            if (i == 0)
                best = std::max(best, sum[i][j]);
        }
    return {best.first, -best.second};
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N;
    std::cin >> N;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    mati m(N, vi(N));
    for (vi &row : m)
        for (int &x : row)
            std::cin >> x;
    ii sol = resolver(m);
    printf("%d %d\n", sol.first, ++sol.second);
    return true;
}

//@ </answer>

int main()
{
    printf("200000 %d\n", 200000);

    int i = 0;
    for (int i = 1; i <= 200000; i++)
    {
        if (i > 200000)
            break;
        for (int j = 200000; j >= i; j--)
        {
            if (i > 200000)
                break;
            printf("%d %d %d\n", i, j, 100000);
            i++;
        }
    }
    return 0;
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