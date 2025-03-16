/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "Grafo.h"
#include "GrafoUtils.h"

#define IN_FILE "casos/4.6.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

void resolver(const Grafo &g)
{
    int i1, i2, i3;
    std::cin >> i1;
    for (int i = 0; i < i1; i++)
    {
        int count = 0;
        std::cin >> i2 >> i3;
        CaminoMasCorto cmc(g, i2);
        for (int i = 1; i < g.V(); i++)
        {
            if (cmc.distancia(i) > i3||(cmc.distancia(i)==0&&i!=i2))
                count++;
        }
        std::cout << count << "\n";
    }
    std::cout << "---\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, C, i1, i2;
    std::cin >> N >> C;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    Grafo g(N + 1);
    for (int i = 0; i < C; i++)
    {
        std::cin >> i1 >> i2;
        g.ponArista(i1, i2);
    }
    resolver(g);
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