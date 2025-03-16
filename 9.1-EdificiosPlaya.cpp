/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>

#define IN_FILE "casos/9.1.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using min_q = std::priority_queue<ii, vii, std::greater<ii>>;

int resolver(min_q &edificios)
{
    int from = -1, ret = 0;
    while (!edificios.empty())
    {
        while (!edificios.empty() && edificios.top().second<from)
        {
            edificios.pop();
        }if(!edificios.empty()){
        ret++;
        from = edificios.top().first; edificios.pop();}
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, W, E;
    std::cin >> N;

#ifdef CENT
    if (N == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    min_q edificios;
    for (int i = 0; i < N; i++)
    {
        std::cin >> W >> E;
        edificios.push({E, W});
    }
    int sol = resolver(edificios);
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