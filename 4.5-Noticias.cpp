/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"
#include "GrafoUtils.h"

#define IN_FILE "casos/4.5.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

void resolver()
{
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M, i1, i2, i3;
    std::cin >> N >> M;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    Grafo g(N + 1);
    for (int i = 0; i < M; i++)
    {
        std::cin >> i1;
        if (i1 != 0)
        {
            std::cin >> i2;
            for (int j = 0; j < i1 - 1; j++)
            {
                std::cin >> i3;
                g.ponArista(i2, i3);
                i2 = i3;
            }
        }
    }

    TamanosCompConexa tcc(g);
    for (int i = 1; i <= N; i++)
    {
        std::cout << tcc.tam_comp(i) << " ";
    }
    std::cout << "\n";
    resolver();
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