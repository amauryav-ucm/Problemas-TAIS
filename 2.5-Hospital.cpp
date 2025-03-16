/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

#define IN_FILE "casos/2.5.in"

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
struct pat
{
    std::string name;
    int grav;
    int ind;
};

bool operator<(const pat &a, const pat &b)
{
    return a.grav < b.grav || (a.grav == b.grav && a.ind > b.ind);
}

void resolver(int n)
{
    std::priority_queue<pat> q;
    char event;
    std::string auxn;
    int auxg;
    for (int i = 0; i < n; i++)
    {
        std::cin >> event;
        switch (event)
        {
        case 'I':
            std::cin >> auxn >> auxg;
            q.push({auxn, auxg, i});
            break;
        case 'A':
            pat a = q.top();
            q.pop();
            std::cout << a.name << "\n";
            break;
        }
    }
    std::cout << "---\n";
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int n;
    std::cin >> n;

#ifdef CENT
    if (n == 0)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    resolver(n);
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