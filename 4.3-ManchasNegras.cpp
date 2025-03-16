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

#define IN_FILE "casos/4.3.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

std::pair<int, int> resolver(int F, int C)
{
    std::vector<bool> negro(F * C, false);
    Grafo g(F * C);
    int blancos = F * C;
    char c;
    for (int i = 0; i < F * C; i++)
    {
        std::cin >> c;
        if (c == '#')
        {
            negro[i] = true;
            blancos--;
        }
        if (i >= C - 1 && negro[i] && negro[i - C])
            g.ponArista(i, i - C);
        if (i % C != 0 && negro[i] && negro[i - 1] && i > 0)
            g.ponArista(i, i - 1);
    }
    MaximaCompConexa cc(g);
    return {cc.cantidad() - blancos, cc.cantidad() == blancos ? 0 : cc.maximo()};
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int F, C;
    std::cin >> F >> C;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    std::pair<int, int> sol = resolver(F, C);
    std::cout << sol.first << " " << sol.second << "\n";
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