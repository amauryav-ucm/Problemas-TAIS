#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

#define IN_FILE "casos/2.1.in"

// #define NUMC
#define CENT
// #define ILIM

using ll = long long int;

void resolver(std::priority_queue<ll, std::vector<ll>, std::greater<ll>> &cola, ll &total)
{
    if (cola.size() == 1)
        return;
    else
    {
        ll sum = cola.top();
        cola.pop();
        sum += cola.top();
        cola.pop();
        cola.push(sum);
        total += sum;
        resolver(cola, total);
    }
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int n;
    std::cin >> n;

#ifdef CENT
    if (n == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    std::priority_queue<ll, std::vector<ll>, std::greater<ll>> cola;
    ll aux;
    for (int i = 0; i < n; i++)
    {
        std::cin >> aux;
        cola.push(aux);
    }
    ll total = 0;
    resolver(cola, total);
    std::cout << total << std::endl;
    return true;
}
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
