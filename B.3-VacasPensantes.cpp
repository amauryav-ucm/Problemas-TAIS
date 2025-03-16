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
using vi = std::vector<int>;
using mat = std::vector<vi>;

class VacasPensantes
{
public:
    VacasPensantes(int N, const vi &cubos) : dpTable(N, vi(N, 0)), N(N)
    {
        for (int i = 0; i < N; i++)
            dpTable[i][i] = cubos[i];
        for (int i = 0; i < N - 1; i++)
            dpTable[i][i + 1] = std::max(cubos[i], cubos[i + 1]);
        for (int i = N - 1; i >= 0; i--)
            for (int j = i + 2; j < N; j++)
            {
                if (cubos[i + 1] > cubos[j])
                    dpTable[i][j] = dpTable[i + 2][j] + cubos[i];
                else
                    dpTable[i][j] = dpTable[i + 1][j - 1] + cubos[i];
                if (cubos[i] > cubos[j - 1])
                    swpMax(dpTable[i][j], dpTable[i + 1][j - 1] + cubos[j]);
                else
                    swpMax(dpTable[i][j], dpTable[i][j - 2] + cubos[j]);
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
        printf("\n");
    }

    int getResult() { return dpTable[0][N - 1]; }

private:
    mat dpTable;
    int N;
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N;
    std::cin >> N;

#ifdef CENT
    if (!N)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    vi cubos(N);
    for (int &x : cubos)
        std::cin >> x;
    VacasPensantes caso(N, cubos);
    //caso.printDPTable();
    printf("%d\n", caso.getResult());
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