/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include "Matriz.h"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using sol = std::pair<ii, vii>;

struct Objeto
{
    int peso;
    int valor;
};

int mochila_rec(std::vector<Objeto> const &obj, int i, int j,
                   Matriz<int> &mochila)
{
    if (mochila[i][j] != -1) // subproblema ya resuelto
        return mochila[i][j];
    if (i == 0 || j == 0)
        mochila[i][j] = 0;
    else if (obj[i - 1].peso > j)
        mochila[i][j] = mochila_rec(obj, i - 1, j, mochila);
    else
        mochila[i][j] = std::max(mochila_rec(obj, i - 1, j, mochila),
                                 mochila_rec(obj, i - 1, j - obj[i - 1].peso, mochila) + obj[i - 1].valor);
    return mochila[i][j];
}

int mochila(std::vector<Objeto> const &objetos, int M, std::vector<bool> &sol)
{
    int n = objetos.size();
    Matriz<int> mochila(n + 1, M + 1, -1);
    int valor = mochila_rec(objetos, n, M, mochila);
    // calculo de los objetos
    int i = n, j = M;
    sol = std::vector<bool>(n, false);
    while (i > 0 && j > 0)
    {
        if (mochila[i][j] != mochila[i - 1][j])
        {
            sol[i - 1] = true;
            j = j - objetos[i - 1].peso;
        }
        --i;
    }
    return valor;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int T, N;
    std::cin >> T >> N;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    std::vector<Objeto> tesoros(N);
    std::vector<bool> sol(N);
    for (auto &t : tesoros)
        std::cin >> t.peso >> t.valor;

    int d = mochila(tesoros, T / 3, sol);
    int t = 0;
    for (bool used : sol)
        t += used;
    printf("%d\n%d\n", d, t);
    for (int i = 0; i < N; i++)
    {
        if (sol[i])
            printf("%d %d\n", tesoros[i].peso, tesoros[i].valor);
    }
    printf("---\n");
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