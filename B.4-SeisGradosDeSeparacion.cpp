/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using vi = std::vector<int>;
using mat = std::vector<vi>;

class Floyd
{
public:
    Floyd(int V, mat adjMat) : dp_table(adjMat), caminoMax(-1)
    {
        for (int k = 0; k < V; k++)
            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++)
                    swpMin(dp_table[i][j], dp_table[i][k] + dp_table[k][j]);
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                swpMax(caminoMax, dp_table[i][j]);
    }

    int get_result() { return caminoMax; }

    void printDPTable()
    {
        for (int i = 0; i < dp_table.size(); i++)
        {
            for (int j = 0; j < dp_table[i].size(); j++)
                printf("%d ", dp_table[i][j]);
            printf("\n");
        }
        printf("\n");
    }

private:
    mat dp_table;
    int caminoMax;
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int V, E;
    std::cin >> V >> E;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    mat adjMat(V, vi(V, 1e9));
    for (int i = 0; i < V; i++)
        adjMat[i][i] = 0;
    std::string v1, v2;
    int currID = 0;
    std::unordered_map<std::string, int> id;
    for (int i = 0; i < E; i++)
    {
        std::cin >> v1 >> v2;
        if (!id.count(v1))
            id.insert({v1, currID++});
        if (!id.count(v2))
            id.insert({v2, currID++});
        adjMat[id[v1]][id[v2]] = adjMat[id[v2]][id[v1]] = 1;
    }
    Floyd caso(V, adjMat);
    //caso.printDPTable();
    int sol = caso.get_result();
    if (sol == 1e9)
        printf("DESCONECTADA\n");
    else
        printf("%d\n", sol);
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