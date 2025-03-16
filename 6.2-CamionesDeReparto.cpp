/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GrafoValorado.h"

#define IN_FILE "casos/6.2.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

void dfs(GrafoValorado<int> const &G, int v, int umbral, std::vector<bool> &visit)
{
    visit[v] = true;
    for (auto a : G.ady(v))
    {
        if (a.valor() >= umbral)
        {
            int w = a.otro(v);
            if (!visit[w])
                dfs(G, w, umbral, visit);
        }
    }
}

bool resolver(const GrafoValorado<int> &g, int i, int f, int width)
{
    std::vector<bool> visit(g.V(), false);
    dfs(g, i, width, visit);
    return visit[f];
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int V, E, K, v1, v2, eV;
    std::cin >> V >> E;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    GrafoValorado<int> g(V + 1);
    for (int i = 0; i < E; i++)
    {
        std::cin >> v1 >> v2 >> eV;
        g.ponArista(Arista(v1, v2, eV));
    }
    std::cin >> K;
    for (int i = 0; i < K; i++)
    {
        std::cin >> v1 >> v2 >> eV;
        bool sol = resolver(g, v1, v2, eV);
        std::cout << (sol ? "SI" : "NO") << "\n";
    }

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