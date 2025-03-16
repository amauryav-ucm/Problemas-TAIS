#include <fstream>
#include <iostream>
#include <string>
#include "TreeSet_AVL_1.2.h"

#define IN_FILE "casos/1.2.in"

// #define NUMC
#define CENT
// #define ILIM

void resolver()
{
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int size, aux;
    std::cin >> size;

#ifdef CENT
    if (size == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    Set<int> a;
    for (int i = 0; i < size; i++)
    {
        std::cin >> aux;
        a.insert(aux);
    }
    std::cin >> size;
    for (int i = 0; i < size; i++)
    {
        std::cin >> aux;
        int res = a.kesimo(aux);
        if (res == -1)
            std::cout << "??\n";
        else
            std::cout << res << std::endl;
    }
    std::cout << "---\n";

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