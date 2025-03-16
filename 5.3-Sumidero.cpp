/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define IN_FILE "casos/5.3.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

int resolver(int V, int E)
{
    int ans = -1;
    std::vector<std::vector<int>> g(V);
    std::vector<std::vector<int>> gI(V);
    int i1, i2;
    for (int i = 0; i < E; i++)
    {
        std::cin >> i1 >> i2;
        g[i1].push_back(i2);
        gI[i2].push_back(i1);
    }
    for (int i = 0; i < V; i++)
    {
        if (g[i].size() == 0 && gI[i].size() == V - 1)
            ans = i;
    }
    return ans;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int V, E;
    std::cin >> V >> E;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    int sol = resolver(V, E);
    if (sol == -1)
        std::cout << "NO\n";
    else
        std::cout << "SI " << sol << "\n";
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