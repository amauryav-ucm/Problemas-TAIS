/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

#define IN_FILE "casos/8.3.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
using min_q = std::priority_queue<int, std::vector<int>, std::greater<int>>;

int resolver(min_q &camisas, min_q &jugadores)
{
    int numCamisas = jugadores.size();
    while (!camisas.empty() && !jugadores.empty())
    {
        int dif = camisas.top() - jugadores.top();
        if (dif < 0)
            camisas.pop();
        else if (dif > 1)
            jugadores.pop();
        else
        {
            camisas.pop();
            jugadores.pop();
            numCamisas--;
        }
    }
    return numCamisas;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, M, talla;
    std::cin >> N >> M;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    min_q camisas, jugadores;
    for (int i = 0; i < N; i++)
    {
        std::cin >> talla;
        jugadores.push(talla);
    }
    for (int i = 0; i < M; i++)
    {
        std::cin >> talla;
        camisas.push(talla);
    }

    int sol = resolver(camisas, jugadores);
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