/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Grafo.h"
#include "GrafoUtils.h"

#define IN_FILE "casos/4.1.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

bool resolver(int V, int E)
{
    int i1, i2;
    if (E != V - 1)
    {
        for (int i = 0; i < E; i++)
        {
            std::cin >> i1 >> i2;
        }
        return false;
    }
    Grafo g(V);
    for (int i = 0; i < E; i++)
    {
        std::cin >> i1 >> i2;
        g.ponArista(i1, i2);
    }
    CompConexa c(g, 0);
    return V == c.get_tam();
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int V, E;
    std::cin >> V >> E;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    bool a = resolver(V, E);
    std::cout << (a ? "SI\n" : "NO\n");
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