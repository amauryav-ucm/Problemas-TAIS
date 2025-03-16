/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include "Grafo.h"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using vi = std::vector<int>;
using mat = std::vector<vi>;

vi side;
Grafo g(0);

bool dfs(int v, int parent, int s)
{
    side[v] = s;
    for (int w : g.ady(v))
        if (side[w] == s || (w != parent && side[w] == -1 && !dfs(w, v, (s + 1) % 2)))
            return false;
    return true;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    g = Grafo(std::cin, 1);

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    side = vi(g.V(), -1);
    bool ok = true;
    for (int i = 0; i < g.V(); i++)
        if (side[i] == -1 && !dfs(i, -1, 0))
            ok = false;
    printf("%s\n", ok ? "SI" : "NO");

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