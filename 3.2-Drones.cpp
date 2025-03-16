/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "IndexPQ.h"

#define IN_FILE "casos/3.2.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
struct u
{
    int id;
    char c;
    int newV;
};

void resolver(int N, int A, int B)
{
    std::vector<u> undo(N);
    IndexPQ<int, std::greater<int>> qA(A);
    IndexPQ<int, std::greater<int>> qB(B);
    int a1, a2, t, u;
    for (int i = 0; i < A; i++)
    {
        std::cin >> a1;
        qA.push(i, a1);
    }
    for (int i = 0; i < B; i++)
    {
        std::cin >> a1;
        qB.push(i, a1);
    }
    while (!qA.empty() && !qB.empty())
    {
        t = 0;
        u = 0;
        for (int i = 0; i < N; i++)
        {
            if (qA.empty() || qB.empty())
                break;
            auto xA = qA.top();
            auto xB = qB.top();
            t += std::min(xA.prioridad, xB.prioridad);
            if (xA.prioridad == xB.prioridad)
            {
                qA.pop();
                qB.pop();
                undo[i] = {0, 'X', 0};
            }
            else if (xA.prioridad < xB.prioridad)
            {
                qA.pop();
                qB.update(xB.elem, 0);
                undo[i] = {xB.elem, 'B', xB.prioridad - xA.prioridad};
            }
            else if (xA.prioridad > xB.prioridad)
            {
                qB.pop();
                qA.update(xA.elem, 0);
                undo[i] = {xA.elem, 'A', xA.prioridad - xB.prioridad};
            }
            u++;
        }

        std::cout << t << " ";
        for (int i = 0; i < u; i++)
        {
            switch (undo[i].c)
            {
            case 'A':
                qA.update(undo[i].id, undo[i].newV);
                break;
            case 'B':
                qB.update(undo[i].id, undo[i].newV);
            default:
                break;
            }
        }
    }
    std::cout << "\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N, A, B;
    std::cin >> N >> A >> B;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver(N, A, B);
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