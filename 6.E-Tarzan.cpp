/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

#define IN_FILE "casos/6.E.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

int resolver(GrafoValorado<int> &g, ConjuntosDisjuntos &uf)
{
    int ret = 0;
    PriorityQueue<Arista<int>> pq(g.aristas());
    Arista<int> a;
    while (!pq.empty() && uf.num_cjtos() > 1)
    {
        a = pq.top();
        pq.pop();
        int v = a.uno();
        int w = a.otro(v);
        uf.unir(v, w);
        ret = a.valor();
    }
    if (uf.num_cjtos() == 1)
        return ret;
    else
        return -1;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    GrafoValorado<int> g(std::cin, 1);

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    ConjuntosDisjuntos uf(g.V());

    int sol = resolver(g, uf);
    if (sol != -1)
        std::cout << sol << "\n";
    else
        std::cout << "Imposible\n";
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