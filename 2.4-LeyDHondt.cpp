/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <vector>

#define IN_FILE "casos/2.4.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>

struct cand
{
    int vot;
    double coeff;
    int ord;
};

bool operator<(const cand &a, const cand &b)
{
    return (a.coeff < b.coeff) ||
           (a.coeff == b.coeff && a.vot < b.vot) ||
           (a.coeff == b.coeff && a.vot == b.vot && a.ord > b.ord);
}

std::vector<int> resolver(int N, int C)
{
    std::vector<int> ch(C, 0);
    std::priority_queue<cand> c;
    int aux;
    for (int i = 0; i < C; i++)
    {
        std::cin >> aux;
        c.push({aux, (double)aux, i});
    }
    for (int i = 0; i < N; i++)
    {
        cand a = c.top();
        c.pop();
        ch[a.ord]++;
        a.coeff = (double)a.vot / (1.0 + (double)ch[a.ord]);
        c.push(a);
    }
    return ch;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int C, N;
    std::cin >> C >> N;

#ifdef CENT
    if (C == 0 && N == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    std::vector<int> ans = resolver(N, C);

    for (int x : ans)
        std::cout << x << " ";
    std::cout << "\n";

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