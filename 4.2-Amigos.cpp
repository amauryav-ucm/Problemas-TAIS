/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include "Grafo.h"
#include "GrafoUtils.h"

#define IN_FILE "casos/4.2.in"

#define NUMC
// #define CENT
// #define ILIM

//@ <answer>

int resolver(int N, int M)
{
    Grafo g(N);
    int i1, i2;
    for (int i = 0; i < M; i++)
    {
        std::cin >> i1 >> i2;
        g.ponArista(i1 - 1, i2 - 1);
    }
    MaximaCompConexa c(g);
    return c.maximo();
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

    int sol = resolver(N, M);
    std::cout << sol << "\n";
    return true;
}

//@ </answer>
int main()
{

#ifndef DOMJUDGE
    std::ifstream in(IN_FILE);
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#ifndef CMDOUT
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif
#endif

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

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
#ifndef CMDOUT
    std::cout.rdbuf(coutbuf);
#endif
#endif
}