/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define IN_FILE "casos/5.L.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

using vvi = std::vector<std::vector<int>>;

template <typename T>
void print_sep(T *f, std::string sep, int n, bool ending)
{
    for (int i = 0; i < n - 1; i++)
        std::cout << f() << sep;
    std::cout << f();
    if (ending)
        std::cout << sep;
}

typedef enum
{
    NO_VISTO,
    TOCADO,
    HUNDIDO
} v_state;

bool dfs(const vvi &adj, int u, bool &hay_ciclo, std::vector<v_state> &estado)
{
    estado[u] = TOCADO;
    for (int i = 0; i < adj[u].size(); ++i)
    {
        int v = adj[u][i];
        if (estado[v] == TOCADO)
            hay_ciclo = true;
        else if ((estado[v] == NO_VISTO) && dfs(adj, v, hay_ciclo, estado))
            hay_ciclo = true;
    }
    estado[u] = HUNDIDO;
    return false;
}

std::string resolver(const vvi &adj)
{
    std::vector<v_state> estado(adj.size(), NO_VISTO);
    bool hay_ciclo = false;
    dfs(adj, 1, hay_ciclo, estado);
    std::string ans;
    if (!hay_ciclo)
        ans = "SIEMPRE";
    else if (estado[estado.size() - 1] == NO_VISTO)
        ans = "NUNCA";
    else
        ans = "A VECES";
    return ans;
}

bool resuelveCaso()
{
    // leer los datos de la entrada
    int L, i1;
    std::cin >> L;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    vvi adj(L + 2);
    char inst;
    bool hay_ciclo = false;
    for (int i = 1; i <= L; i++)
    {
        std::cin >> inst;
        switch (inst)
        {
        case 'A':
            adj[i].push_back(i + 1);
            break;
        case 'J':
            std::cin >> i1;
            adj[i].push_back(i1);
            break;
        case 'C':
            std::cin >> i1;
            adj[i].push_back(i1);
            adj[i].push_back(i + 1);
            break;
        default:
            break;
        }
    }

    std::cout << resolver(adj) << "\n";

    // escribir sol
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