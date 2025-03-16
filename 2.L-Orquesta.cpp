/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define IN_FILE "casos/2.L.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

struct conj
{
    int index;
    int tot;
    int part;
    int max;
};

bool operator<(const conj &a, const conj &b)
{
    return (a.max < b.max)/* || (a.max == b.max && a.part > b.part) || (a.max == b.max && a.part == b.part && a.index > b.index)*/;
}

int resolver(const int p, const int n)
{
    int aux;
    std::priority_queue<conj> q;
    for (int i = 0; i < n; i++)
    {
        std::cin >> aux;
        q.push({i, aux, 1, aux});
    }
    for (int i = 0; i < p - n; i++)
    {
        conj a = q.top();
        q.pop();
        a.part++;
        a.max = a.tot / a.part + (a.tot % a.part != 0);
        q.push(a);
    }
    return q.top().max;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int p, n;
    std::cin >> p >> n;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    int sol = resolver(p, n);

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