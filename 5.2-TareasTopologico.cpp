/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#define IN_FILE "casos/5.2.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using vb = std::vector<bool>;

int dfs(const vvi &dg, int v, vb &visited, vb &stacked, std::deque<int> &list)
{
    if (stacked[v])
        return -1;
    if (visited[v])
        return 0;
    visited[v] = true;
    stacked[v] = true;
    for (int x : dg[v])
    {
        if (dfs(dg, x, visited, stacked, list) == -1)
            return -1;
    }
    list.push_back(v);
    stacked[v] = false;
    return 0;
}

std::deque<int> resolver(const vvi &dg, int N)
{
    vb visited(N + 1, false);
    vb stacked(N + 1, false);
    std::deque<int> list;
    for (int i = 1; i <= N; i++)
    {
        if (!visited[i])
            if (dfs(dg, i, visited, stacked, list) == -1)
                return std::deque<int>();
    }
    return list;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M, i1, i2;
    std::cin >> N >> M;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    vvi adjList = vvi(N + 1);
    for (int i = 0; i < M; i++)
    {
        std::cin >> i1 >> i2;
        adjList[i1].push_back(i2);
    }

    std::deque<int> sol = resolver(adjList, N);
    if (sol.empty())
    {
        std::cout << "Imposible\n";
        return true;
    }
    while (!sol.empty())
    {
        std::cout << sol.back() << " ";
        sol.pop_back();
    }
    std::cout << "\n";
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