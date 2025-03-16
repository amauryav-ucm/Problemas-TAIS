/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include "IndexPQ.h"

#define IN_FILE "casos/3.L.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
struct res
{
    int canal;
    int aud;
};

bool operator<(const res &a, const res &b)
{
    return a.aud > b.aud || (a.aud == b.aud && a.canal < b.canal);
}

void resolver(int D, int C, int N)
{
    std::vector<int> t(C + 1);
    IndexPQ<int, std::greater<int>> q(C + 1);
    IndexPQ<res> qt(C + 1);

    int a1, a2, t1 = 0, t2 = 0;
    for (int i = 1; i <= C; i++)
    {
        std::cin >> a1;
        q.push(i, a1);
    }
    for (int i = 1; i <= C; i++)
    {
        qt.push(i, {i, 0});
    }
    for (int i = 0; i < N; i++)
    {
        std::cin >> t2;
        int tid = q.top().elem;
        qt.update(tid, {tid, qt.priority(tid).aud + t2 - t1});
        std::cin >> a1;
        while (a1 != -1)
        {
            std::cin >> a2;
            q.update(a1, a2);
            std::cin >> a1;
        }
        t1 = t2;
    }
    t2 = D;
    int tid = q.top().elem;
    qt.update(tid, {tid, qt.priority(tid).aud + t2 - t1});
    while (!qt.empty() && qt.top().prioridad.aud != 0)
    {
        std::cout << qt.top().elem << " " << qt.top().prioridad.aud << "\n";
        qt.pop();
    }
    std::cout << "---\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int D, C, N;
    std::cin >> D >> C >> N;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver(D, C, N);
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