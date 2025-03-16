/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#define IN_FILE "casos/8.2.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
using min_q = std::priority_queue<int, std::vector<int>, std::greater<int>>;

int resolver(min_q &qCity, min_q &qTeam)
{
    int ret = 0;
    while (!qCity.empty() && !qTeam.empty())
    {
        while (!qTeam.empty() && qCity.top() > qTeam.top())
        {
            qTeam.pop();
        }
        if (!qTeam.empty())
        {
            qCity.pop();
            qTeam.pop();
            ret++;
        }
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N;
    std::cin >> N;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    min_q qCity, qTeam;
    int i1;
    for (int i = 0; i < N; i++)
    {
        std::cin >> i1;
        qCity.push(i1);
    }
    for (int i = 0; i < N; i++)
    {
        std::cin >> i1;
        qTeam.push(i1);
    }

    int sol = resolver(qCity, qTeam);
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