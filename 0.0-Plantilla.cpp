/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// #define NUMC
// #define CENT
// #define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using vi = std::vector<int>;
using mat = std::vector<vi>;

void resolver()
{
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver();
    return true;
}

//@ </answer>

int main()
{
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


}