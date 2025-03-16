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

#define IN_FILE "casos/5.4.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
#define INF std::numeric_limits<int>::max()

using vvi = std::vector<std::vector<int>>;

int resolver(const vvi &g, const int K)
{
    std::vector<int> dist(g.size());
    std::vector<bool> visited(g.size(), false);
    std::queue<int> q;
    dist[1] = 0;
    visited[1] = true;
    q.push(1);
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u = 1; u <= K && v + u < g.size(); u++)
        {
            int w = v + u;
            if (!g[w].empty())
            {
                w = g[w].front();
            }
            if (!visited[w])
            {
                visited[w] = true;
                dist[w] = dist[v] + 1;
                q.push(w);
            }
        }
    }
    return dist[g.size() - 1];
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, K, S, E, i1, i2;
    std::cin >> N >> K >> S >> E;

#ifdef CENT
    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    vvi g(N * N + 1);
    for (int i = 0; i < S + E; i++)
    {
        std::cin >> i1 >> i2;
        g[i1].push_back(i2);
    }
    int sol = resolver(g, K);
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