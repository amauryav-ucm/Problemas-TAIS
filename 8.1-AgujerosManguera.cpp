/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define IN_FILE "casos/8.1.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

int resolver(const std::vector<int> &huecos, int L)
{
    int ret = 0;
    int hasta = -1;
    for(int x:huecos){
        if(x>hasta){
            hasta = x+L;
            ret++;
        }
    }
    return ret;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, L;
    std::cin >> N >> L;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    std::vector<int> huecos(N);
    for(int &x:huecos ) std::cin >> x;
    int sol = resolver(huecos, L);
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