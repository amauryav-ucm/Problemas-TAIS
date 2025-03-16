/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <limits>
#include "GrafoValorado.h"
#include "IndexPQ.h"

#define IN_FILE "casos/7.L.in"

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
    Dijkstra(GrafoValorado<Valor> const &g, std::vector<int> orig, int D) : origen(orig), result(0),
                                                                     dist(g.V(), D+1), caminosMin(g.V(), 0), ulti(g.V()), pq(g.V())
    {
        for (int x : origen)
        {
            dist[x] = 0;
            caminosMin[x] = 1;
            pq.push(x, 0);
        }
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            result++;
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }
    bool hayCamino(int v) const { return dist[v] != INF; }
    Valor distancia(int v) const { return dist[v]; }
    int getCaminosMin(int v) const { return caminosMin[v]; };
    int getResult() {return result;}

private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int result;
    std::vector<int> origen;
    std::vector<Valor> dist, caminosMin;
    std::vector<Arista<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(Arista<Valor> a, int v)
    {
        int w = a.otro(v);
        if (dist[w] > dist[v] + a.valor()&&dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            caminosMin[w] = caminosMin[v];
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor())
        {
            caminosMin[w] += caminosMin[v];
        }
    }
};

int resolver(const GrafoValorado<int> &g, std::vector<int> borr, int D)
{
    Dijkstra dij(g, borr, D);
    return dij.getResult();
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int D, B;
    std::cin >> D;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    GrafoValorado<int> g(std::cin, 1);
    std::cin >> B;
    std::vector<int> borr(B);
    for(int&x:borr) {std::cin >> x; x--;}

    int sol = resolver(g, borr, D);
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