/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "GrafoValorado.h"
#include "PriorityQueue.h"
#include "ConjuntosDisjuntos.h"

#define IN_FILE "casos/6.3.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

int resolver(const GrafoValorado<int> &g)
{
    int ret = 0;
    PriorityQueue<Arista<int>> pq(g.aristas());
    ConjuntosDisjuntos uf(g.V());
    while (!pq.empty() && uf.num_cjtos() > 1)
    {
        Arista<int> e = pq.top();
        pq.pop();
        int v = e.uno();
        int w = e.otro(v);
        if (!uf.unidos(v, w))
        {
            ret += e.valor();
            uf.unir(v, w);
        }
    }
    return (uf.num_cjtos() == 1 ? ret : -1);
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    GrafoValorado<int> g(std::cin, 1);

#ifdef CENT
    if (condicion)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    int sol = resolver(g);

    if (sol != -1)
        std::cout << sol << "\n";
    else
        std::cout << "No hay puentes suficientes\n";

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