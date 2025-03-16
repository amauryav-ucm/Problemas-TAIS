/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <limits>
#include "Digrafo.h"

#define IN_FILE "casos/5.1.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

#define MAX 10000
#define INF std::numeric_limits<int>::max()

int adyacente(int v, int i)
{
    switch (i)
    {
    case 0:
        return (v + 1) % MAX;
    case 1:
        return (v * 2) % MAX;
    case 2:
        return v / 3;
    }
    return -1;
}

int resolver(int origen, int destino)
{
    if (origen == destino)
        return 0;
    std::vector<int> distancia(MAX, INF);
    distancia[origen] = 0;
    std::queue<int> cola;
    cola.push(origen);
    while (!cola.empty())
    {
        int v = cola.front();
        cola.pop();
        for (int i = 0; i < 3; ++i)
        {
            int w = adyacente(v, i);
            if (distancia[w] == INF)
            {
                distancia[w] = distancia[v] + 1;
                if (w == destino)
                    return distancia[w];
                else
                    cola.push(w);
            }
        }
    }
    return -1;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int i, f;
    std::cin >> i >> f;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    int sol = resolver(i,f);
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