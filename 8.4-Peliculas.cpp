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

#define IN_FILE "casos/8.4.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using min_q = std::priority_queue<ii, vii, std::greater<ii>>;

int resolver(min_q &pelis)
{
    int from = -20, ret = 0;
    while (!pelis.empty())
    {
        while (!pelis.empty() && pelis.top().second - from < 10)
        {
            pelis.pop();
        }if(!pelis.empty()){
        ret++;
        from = pelis.top().first; pelis.pop();}
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, h, m, d;
    std::cin >> N;

#ifdef CENT
    if (N == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    min_q pelis;
    std::cin.ignore();
    std::string line;
    for (int i = 0; i < N; i++)
    {
        getline(std::cin, line);
        sscanf(&line[0], "%d:%d %d", &h, &m, &d);
        int ini = h * 60 + m, fin = ini + d;
        pelis.push({fin, ini});
    }
    int sol = resolver(pelis);
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