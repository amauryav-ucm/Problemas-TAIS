/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include "KeyedPQ.h"

#define IN_FILE "casos/3.3.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

struct tr
{
    int i;
    int m;
};

bool operator<(const tr &a, const tr &b)
{
    if (a.i == -1)
        return true;
    return a.m > b.m || (a.m == b.m && a.i > b.i);
}

void resolver(int N)
{
    KeyedPQ<std::string, tr> q;
    std::string s1;
    std::vector<std::pair<std::string, tr>> v(3);
    int i1;
    for (int i = 0; i < N; i++)
    {
        std::cin >> s1;
        if (s1 == "C")
        {
            std::cin >> s1 >> i1;
            if (q.count(s1) == 0)
                q.push(s1, {i, i1});
            else
            {
                q.update(s1, {i, q.priority(s1).m + i1});
            }
        }
        else if (s1 == "E")
        {
            std::cin >> s1 >> i1;
            int newV = q.priority(s1).m - i1;
            q.update(s1, {q.priority(s1).i, newV});
        }
        else if (s1 == "TC")
        {
            q.mostrartop3();
        }
        else
            throw std::domain_error("ERROR");
    }
    std::cout << "---\n";
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

    resolver(N);
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