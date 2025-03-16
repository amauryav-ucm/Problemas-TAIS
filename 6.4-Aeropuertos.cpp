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

#define IN_FILE "casos/6.4.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

std::pair<int, int> resolver(const GrafoValorado<int> &g, int A)
{
    int cost = 0;
    PriorityQueue<Arista<int>> pq(g.aristas());
    ConjuntosDisjuntos uf(g.V());
    while (!pq.empty() && pq.top().valor() < A && uf.num_cjtos() > 1)
    {
        Arista<int> e = pq.top();
        pq.pop();
        int v = e.uno();
        int w = e.otro(v);
        if (!uf.unidos(v, w))
        {
            uf.unir(v, w);
            cost += e.valor();
        }
    }
    return {cost + A * uf.num_cjtos(), uf.num_cjtos()};
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M, A;
    std::cin >> N >> M >> A;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    GrafoValorado<int> g(N);
    int v1, v2, c;
    for (int i = 0; i < M; i++)
    {
        std::cin >> v1 >> v2 >> c;
        g.ponArista({v1 - 1, v2 - 1, c});
    }
    auto [cost, nA] = resolver(g, A);
    std::cout << cost << " " << nA << "\n";
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