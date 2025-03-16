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
#define CENT
// #define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using vi = std::vector<int>;
using mat = std::vector<vi>;

class Carpintero
{
public:
    Carpintero(int L, const vi &cuts) : L(L), N(cuts.size()), dp_table(N + 1, vi(N + 1, 1e9)), sStart(N + 1), sEnd(N + 1)
    {
        sStart[0] = 0;
        sEnd[N] = L;
        for (int i = 0; i < N; i++)
        {
            sStart[i + 1] = cuts[i];
            sEnd[i] = cuts[i];
        }
        for (int i = 0; i <= N; i++)
            dp_table[i][i] = 0;
        for (int i = N; i >= 0; i--)
            for (int j = i + 1; j <= N; j++)
            {
                for (int k = i; k < j; k++)
                    swpMin(dp_table[i][j], dp_table[i][k] + dp_table[k + 1][j]);
                dp_table[i][j] += 2 * (sEnd[j] - sStart[i]);
            }
    }

    int get_result() { return dp_table[0][N]; }

private:
    int L, N;
    vi sStart, sEnd;
    mat dp_table;
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int L, N;
    std::cin >> L >> N;

#ifdef CENT
    if (!L && !N)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    vi cuts(N);
    for (int &x : cuts)
        std::cin >> x;
    Carpintero caso(L, cuts);
    printf("%d\n", caso.get_result());
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