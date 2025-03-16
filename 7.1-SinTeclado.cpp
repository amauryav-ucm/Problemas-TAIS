/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
#include <deque>
#include <limits>

#define IN_FILE "casos/7.1.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>


template <typename T>   
using Camino = std::deque<T>;
template <typename Valor>
class Dijkstra
{
public:
    Dijkstra(DigrafoValorado<Valor> const &g, int orig) : origen(orig),
                                                          dist(g.V(), INF), ulti(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    Camino<Valor> camino(int v) const
    {
        Camino<Valor> cam;
        // recuperamos el camino retrocediendo
        AristaDirigida<Valor> a;
        for (a = ulti[v]; a.desde() != origen; a = ulti[a.desde()])
            cam.push_front(a);
        cam.push_front(a);
        return cam;
    }

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a)
    {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

int resolver(const DigrafoValorado<int> &g)
{
    Dijkstra alg(g, 0);
    int dest = g.V() - 1;
    if (alg.hayCamino(dest))
        return alg.distancia(dest);
    else
        return -1;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M;
    std::cin >> N;

#ifdef CENT
    if (N == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    DigrafoValorado<int> g(2 * N);
    int v1, v2, c;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> c;
        g.ponArista({2 * i - 2, 2 * i - 1, c});
    }
    std::cin >> M;
    for (int i = 0; i < M; i++)
    {
        std::cin >> v1 >> v2 >> c;
        g.ponArista({2 * v1 - 1, 2 * v2 - 2, c});
    }

    int sol = resolver(g);
    if (sol != -1)
        std::cout << sol << "\n";
    else
        std::cout << "IMPOSIBLE\n";
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