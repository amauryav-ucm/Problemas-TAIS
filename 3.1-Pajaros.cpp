/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

#define IN_FILE "casos/3.1.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>

void resolver(int A, int N)
{
    int a1, a2, d = 1;
    std::priority_queue<int> l;
    std::priority_queue<int, std::vector<int>, std::greater<int>> r;
    r.push(A);
    for (int i = 0; i < N; i++)
    {
        std::cin >> a1 >> a2;
        if (a1 < r.top())
        {
            l.push(a1);
            d--;
        }
        else
        {
            r.push(a1);
            d++;
        }
        if (a2 < r.top())
        {
            l.push(a2);
            d--;
        }
        else
        {
            r.push(a2);
            d++;
        }
        switch (d)
        {
        case -1:
            a1 = l.top();
            l.pop();
            r.push(a1);
            break;
        case 3:
            a1 = r.top();
            r.pop();
            l.push(a1);
            break;
        default:
            break;
        }
        d = 1;
        std::cout << r.top() << " ";
    }
    std::cout << "\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int A, N;
    std::cin >> A >> N;

#ifdef CENT
    if (A == 0 && N == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver(A, N);
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