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
using mat = std::vector<vi>;

struct Objeto
{
    int peso;
    double valor;
};
double mochila_rec(std::vector<Objeto> const &obj, int i, int j,
                   Matriz<double> &mochila)
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

double mochila(std::vector<Objeto> const &objetos, int M, std::vector<bool> &sol)
{
    int n = objetos.size();
    Matriz<double> mochila(n + 1, M + 1, -1);
    double valor = mochila_rec(objetos, n, M, mochila);
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
    int P, N;
    std::cin >> P >> N;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    std::vector<Objeto> list(N);
    std::vector<bool> sol(N);
    for (auto & o : list)
        std::cin >> o.valor >> o.peso;
    double res = mochila(list, P, sol);
    printf("%.0f\n", res);
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