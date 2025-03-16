/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <limits>
#include <queue>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

#define IN_FILE "casos/7.4.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
using ii = std::pair<int, int>;
using ib = std::pair<int, bool>;
using vii = std::vector<ii>;
using vib = std::vector<ib>;

struct Coste
{
    int distancia;
    int numAristas;

    bool operator<(const Coste &other) const
    {
        return distancia < other.distancia || (distancia == other.distancia && numAristas < other.numAristas);
    }

    Coste operator+(const Coste &other) const
    {
        return {distancia + other.distancia, numAristas + other.numAristas};
    }
};


template <typename T>   
using Camino = std::deque<T>;
template <typename Valor>
class Dijkstra
{
public:
    Dijkstra(DigrafoValorado<Valor> const &g, int orig) : origen(orig),
                                                          dist(g.V(), {INF,0}), ulti(g.V()), pq(g.V())
    {
        dist[origen] = {0,0};
        pq.push(origen, {0,0});
        while (!pq.empty())
        {
            int v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    bool hayCamino(int v) const { return dist[v].distancia != INF; }
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
    const int INF = std::numeric_limits<int>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<AristaDirigida<Valor>> ulti;
    IndexPQ<Valor> pq;
    void relajar(AristaDirigida<Valor> a)
    {
        int v = a.desde(), w = a.hasta();
        if (!(dist[w] < dist[v] + a.valor()))
        {
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

int bfs(const DigrafoValorado<Coste>&g, int o, int d){
    std::vector<int> dist(g.V(),-1);
    std::queue<int> q;
    q.push(o);
    dist[o]=0;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(auto a : g.ady(v)){
            int u = a.hasta();
            if(dist[u]==-1){
                dist[u]=dist[v]+1;
                if(u == d) return dist[u];
                q.push(u);
            }
        }
    }
    return -1;
}

vib resolver(const DigrafoValorado<Coste> &g, const vii &queries)
{
    vib ret(queries.size());

    for (int i = 0; i < queries.size(); i++)
    {
        int numAr = bfs(g,queries[i].first, queries[i].second);
        if(numAr!=-1){
            Dijkstra dij(g, queries[i].first);
             Coste a = dij.distancia(queries[i].second);
            ret[i] = {a.distancia,numAr==a.numAristas};
        }
        else{
            ret[i] = {-1, true};
        }
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, C;
    std::cin >> N >> C;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    DigrafoValorado<Coste> g(N);
    int v1, v2, d;
    for (int i = 0; i < C; i++)
    {
        std::cin >> v1 >> v2 >> d;
        v1--;
        v2--;
        g.ponArista(AristaDirigida<Coste>(v1, v2, {d, 1}));
        g.ponArista(AristaDirigida<Coste>(v2, v1, {d, 1}));
    }
    int K;
    std::cin >> K;
    vii queries(K);
    for (int i = 0;i<K;i++){
        std::cin >> v1 >> v2;
        v1--;
        v2--;
        queries[i]= {v1,v2};
        }
    vib sol = resolver(g, queries);
    for (auto [dist, res] : sol)
        if (dist != -1)
            std::cout << dist << " " << (res ? "SI" : "NO") << "\n";
        else
            std::cout << "SIN CAMINO\n";
    std::cout << "---\n";
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