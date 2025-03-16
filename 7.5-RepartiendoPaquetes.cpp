/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <limits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"

#define IN_FILE "casos/7.5.in"

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

int resolver(const DigrafoValorado<int> &g, int O, const std::vector<int> &casas)
{
    int ret = 0;
    DigrafoValorado<int> g_1 = g.inverso();
    Dijkstra<int> dij(g, O), dij_1(g_1, O);
    for (int casa : casas)
    {
        if (dij.hayCamino(casa) && dij_1.hayCamino(casa))
            ret = ret + dij.distancia(casa) + dij_1.distancia(casa);
        else
            return -1;
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    DigrafoValorado<int> g(std::cin, 1);

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    int O, P;
    std::cin >> O >> P;
    O--;
    std::vector<int> casas(P);
    for (int &casa : casas)
    {
        std::cin >> casa;
        casa--;
    }

    int sol = resolver(g, O, casas);
    if (sol == -1)
        std::cout << "Imposible\n";
    else
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