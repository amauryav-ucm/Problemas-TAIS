/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

#define IN_FILE "casos/2.3.in"

// #define NUMC
#define CENT
// #define ILIM

typedef struct caja
{
    int n;
    int t;
} caja;

bool operator<(const caja &a, const caja &b)
{
    return a.t > b.t || (a.t == b.t && a.n > b.n);
}

//@ <answer>

void resolver(int N, int C)
{
    std::priority_queue<caja> q;
    for (int i = 1; i <= N; i++)
    {
        q.emplace(i, 0);
    }
    for (int i = 0; i < C; i++)
    {
        caja x = q.top();
        q.pop();
        int t;
        std::cin >> t;
        x.t += t;
        q.push(x);
    }
    std::cout << q.top().n << "\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, C;
    std::cin >> N >> C;

#ifdef CENT
    if (N == 0 && C == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver(N, C);
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