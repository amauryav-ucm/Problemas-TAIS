/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ConjuntosDisjuntos.h"

#define IN_FILE "casos/6.1.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

class Petrolero
{
public:
    Petrolero(int f, int c) : maxConj(0), F(f), C(c), grid(F, std::vector<bool>(C, false)), cd(F * C)
    {
    }

    void setBlack(int f, int c)
    {
        grid[f][c] = true;
        join(f, c);
        maxConj = std::max(maxConj, cd.cardinal(toNode(f, c)));
    }

    int getMaxConj()
    {
        return maxConj;
    }

private:
    int maxConj;
    int F;
    int C;
    std::vector<std::vector<bool>> grid;
    ConjuntosDisjuntos cd;

    int toNode(int f, int c)
    {
        return f * C + c;
    }

    void join(int f, int c)
    {
        if (grid[f][c] == 0)
            return;
        for (int x = -1; x <= 1; x++)
            for (int y = -1; y <= 1; y++)
                if (0 <= f + y && f + y < F && 0 <= c + x && c + x < C && grid[f + y][c + x] == true)
                    cd.unir(toNode(f, c), toNode(f + y, c + x));
    }
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int F, C, N, f, c;
    std::cin >> F >> C;
    std::cin.ignore();

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    Petrolero p(F, C);
    std::string line;
    for (int i = 0; i < F; i++)
    {
        std::getline(std::cin, line);
        for (int j = 0; j < C; j++)
        {
            if (line.at(j) == '#')
                p.setBlack(i, j);
        }
    }

    std::cin >> N;
    std::cout << p.getMaxConj();
    for (int i = 0; i < N; i++)
    {
        std::cin >> f >> c;
        p.setBlack(f - 1, c - 1);
        std::cout << " " << p.getMaxConj();
    }
    std::cout << "\n";

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