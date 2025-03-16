/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "GrafoValorado.h"
#include <deque>
#include <limits>
#include "IndexPQ.h"

#define IN_FILE "casos/7.2.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

template <typename T>
using Camino = std::deque<T>;
template <typename Valor>
class Dijkstra
{
public:
    Dijkstra(GrafoValorado<Valor> const &g, int orig) : origen(orig),
                                                          dist(g.V(), INF), caminosMin(g.V(), 0), ulti(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        caminosMin[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    int getCaminosMin(int v) const { return caminosMin[v]; };
    Camino<Valor> camino(int v) const
    {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        Arista<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist, caminosMin;
    std::vector<Arista<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(Arista<Valor> a, int v)
    {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            caminosMin[w] = caminosMin[v];
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor())
        {
            caminosMin[w]+=caminosMin[v];
        }
    }
};

int resolver(const GrafoValorado<int> &g)
{
    Dijkstra alg(g,0);
    int dest = g.V()-1;
    return alg.getCaminosMin(dest);
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

    int sol = resolver(g);
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