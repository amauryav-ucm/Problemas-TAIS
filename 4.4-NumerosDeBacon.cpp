/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#define IN_FILE "casos/4.4.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define KB "KevinBacon"
using umus = std::unordered_map<std::string, std::unordered_set<std::string>>;
using is = std::pair<int, std::string>;

void resolver(const umus &g, int N)
{
    std::unordered_map<std::string, int> dist;
    std::unordered_map<std::string, bool> visited;
    std::queue<std::string> q;
    std::string s1;
    dist[KB] = 0;
    visited[KB] = true;
    if (g.count(KB))
        q.push(KB);

    while (!q.empty())
    {
        std::string v = q.front();
        q.pop();
        for (std::string w : g.at(v))
            if (!visited[w])
            {
                dist[w] = dist[v] + 1;
                visited[w] = true;
                q.push(w);
            }
    }
    for (int i = 0; i < N; i++)
    {
        std::cin >> s1;
        std::cout << s1 + " ";
        if (dist.count(s1))
        {
            std::cout << dist.at(s1) / 2 << "\n";
        }
        else
        {
            std::cout << "INF\n";
        }
    }
    std::cout << "---\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int P, N;
    std::cin >> P;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    umus g;
    std::string s1, s2;
    int i1;
    for (int i = 0; i < P; i++)
    {
        std::cin >> s1 >> i1;
        for (int i = 0; i < i1; i++)
        {
            std::cin >> s2;
            g[s1].insert(s2);
            g[s2].insert(s1);
        }
    }

    std::cin >> N;

    resolver(g, N);
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