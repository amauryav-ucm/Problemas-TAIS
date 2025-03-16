/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <queue>

#define IN_FILE "casos/4.L.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

#define INF std::numeric_limits<int>::max()

using vvi = std::vector<std::vector<int>>;

int resolver(const vvi &g, const std::vector<int> &list)
{
    // Vector de la suma de distacia hasta los 3 puntos
    std::vector<int> comb_dist(g.size(), 0);
    for (int i : list)
    {
        std::vector<int> dist(g.size(), 0);
        std::vector<bool> visited(g.size(), false);
        dist[i] = 0;
        visited[i] = true;
        std::queue<int> q;
        q.push(i);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int w : g[v])
            {
                if (!visited[w])
                {
                    dist[w] = dist[v] + 1;
                    visited[w] = true;
                    q.push(w);
                }
            }
        }
        for (int i = 0; i < g.size(); i++)
        {
            if (dist[i] != INF)
            {
                comb_dist[i] += dist[i];
            }
        }
    }
    int ret = INF;
    for (int i = 1; i < g.size(); i++)
    {
        if (comb_dist[i] < ret)
            ret = comb_dist[i];
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, C, i1, i2;
    // Lista con los 3 puntos de los que se quiere calcular el punto con la menor suma de distancia hasta ellos
    std::vector<int> list(3);
    std::cin >> N >> C >> list[0] >> list[1] >> list[2];

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    // Lista de adyacentes
    vvi g(N + 1);
    for (int i = 0; i < C; i++)
    {
        std::cin >> i1 >> i2;
        g[i1].push_back(i2);
        g[i2].push_back(i1);
    }
    int sol = resolver(g, list);
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