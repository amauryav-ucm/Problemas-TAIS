/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#define IN_FILE "casos/2.2.in"

// #define NUMC
#define CENT
// #define ILIM

typedef struct user
{
    int id;
    int period;
    int nexttime;
} user;

bool operator<(const user &a, const user &b)
{
    return b.nexttime < a.nexttime || (b.nexttime == a.nexttime && b.id < a.id);
}

void resolver(std::priority_queue<user> cola, int m)
{
    for(int i = 0;i<m;i++){
        user nextuser = cola.top(); cola.pop();
        std::cout << nextuser.id << "\n";
        nextuser.nexttime+=nextuser.period;
        cola.push(nextuser);
    }
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
    std::priority_queue<user> cola;
    int id, per, m;
    for (int i = 0; i < n; i++)
    {
        std::cin >> id >> per;
        cola.push({id, per, per});
    }
    std::cin >> m;
    resolver(cola, m);
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
