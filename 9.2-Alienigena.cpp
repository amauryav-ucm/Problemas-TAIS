/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#define IN_FILE "casos/9.2.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using min_q = std::priority_queue<ii, vii, std::greater<ii>>;

int resolver(min_q &trabajos, int C, int F)
{
    int ret = 0;
    int cubiertoHasta = C;
    int mejorCobertura = C;
    while (!trabajos.empty() && cubiertoHasta < F)
    {
        while (!trabajos.empty() && trabajos.top().first <= cubiertoHasta)
        {
            mejorCobertura = std::max(mejorCobertura, trabajos.top().second);
            trabajos.pop();
        }
        if (mejorCobertura > cubiertoHasta)
        {
            ret++;
            cubiertoHasta = mejorCobertura;
        }
        else
            return -1;
    }
    return cubiertoHasta >= F ? ret : -1;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int C, F, N;
    std::cin >> C >> F >> N;

#ifdef CENT
    if (!C && !F && !N)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    min_q trabajos;
    int c, f;
    for (int i = 0; i < N; i++)
    {
        std::cin >> c >> f;
        trabajos.push({c, f});
    }

    int sol = resolver(trabajos, C, F);
    if (sol != -1)
        std::cout << sol << "\n";
    else
        std::cout << "Imposible\n";
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