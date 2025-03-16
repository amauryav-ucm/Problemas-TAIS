/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include "GrafoValorado.h"
#include <limits>
#include "IndexPQ.h"

#define IN_FILE "casos/7.3.in"

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
                                                        dist(g.V(), INF), anterior(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        anterior[origen] = -1;
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
    Camino<Valor> camino(int v) const
    {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        for (int x = v; x!=-1; x = anterior[x])
            cam.push_front(x);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<int> anterior;
    IndexPQ<Valor> pq;
    void relajar(Arista<Valor> a, int v)
    {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            anterior[w] = v;
            pq.update(w, dist[w]);
        }
    }
};

void resolver(const GrafoValorado<int> &g)
{
    int K, i1, i2;
    std::cin >> K;
    for (int i = 0; i < K; i++)
    {
        std::cin >> i1 >> i2;
        Dijkstra alg(g, i1 - 1);
        if (alg.hayCamino(i2 - 1))
        {
            std::cout << alg.distancia(i2 - 1) << ": ";
            std::deque<int> c = alg.camino(i2 - 1);
            c.pop_back();
            for (int x : c)
                std::cout << x + 1 << " -> ";
            std::cout << i2 << "\n";
        }
        else
            std::cout << "NO LLEGA\n";
    }
    std::cout << "---\n";
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