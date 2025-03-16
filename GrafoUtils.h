#include <vector>
#include <queue>
#include "Grafo.h"
#include "Digrafo.h"

class CompConexa
{
public:
    CompConexa(Grafo const &g, int v) : visit(g.V(), false), tam(0)
    {
        tam = dfs(g, v);
    }
    // tamaño máximo de una componente conexa
    int get_tam() const
    {
        return tam;
    }

private:
    std::vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int tam;

    // tamaño de la componente mayor
    int dfs(Grafo const &g, int v)
    {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v))
        {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

class MaximaCompConexa
{
public:
    MaximaCompConexa(Grafo const &g) : visit(g.V(), false), maxim(0), cant(0)
    {
        for (int v = 0; v < g.V(); ++v)
        {
            if (!visit[v])
            { // se recorre una nueva componente conexa
                cant++;
                int tam = dfs(g, v);
                maxim = std::max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const
    {
        return maxim;
    }
    int cantidad() const { return cant; }

private:
    std::vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    int maxim;
    int cant;
    // tamaño de la componente mayor
    int dfs(Grafo const &g, int v)
    {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v))
        {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

class TamanosCompConexa
{
public:
    TamanosCompConexa(Grafo const &g) : visit(g.V(), false), maxim(0), cant(0), comp(g.V()), tams(g.V())
    {
        for (int v = 0; v < g.V(); ++v)
        {
            if (!visit[v])
            { // se recorre una nueva componente conexa
                int tam = dfs(g, v, cant);
                tams[cant++] = tam;
                maxim = std::max(maxim, tam);
            }
        }
    }
    // tamaño máximo de una componente conexa
    int maximo() const
    {
        return maxim;
    }
    int cantidad() const { return cant; }

    int tam_comp(int v)
    {
        return tams[comp[v]];
    }

private:
    std::vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    std::vector<int> comp;
    std::vector<int> tams;
    int maxim;
    int cant;
    // tamaño de la componente mayor
    int dfs(Grafo const &g, int v, int id)
    {
        visit[v] = true;
        comp[v] = id;
        int tam = 1;
        for (int w : g.ady(v))
        {
            if (!visit[w])
                tam += dfs(g, w, id);
        }
        return tam;
    }
};

class CaminoMasCorto
{
public:
    CaminoMasCorto(Grafo const &g, int s) : visit(g.V(), false),
                                            ant(g.V()), dist(g.V()), s(s)
    {
        bfs(g);
    }
    // ¿hay camino del origen a v?
    bool hayCamino(int v) const
    {
        return visit[v];
    }

    // número de aristas entre s y v
    int distancia(int v) const
    {
        return dist[v];
    }
    // devuelve el camino más corto desde el origen a v (si existe)
    std::deque<int> camino(int v) const
    {
        if (!hayCamino(v))
            throw std::domain_error("No existe camino");
        std::deque<int> cam;
        for (int x = v; x != s; x = ant[x])
            cam.push_front(x);
        cam.push_front(s);
        return cam;
    }

private:
    std::vector<bool> visit; // visit[v] = ¿hay camino de s a v?
    std::vector<int> ant;    // ant[v]  = último vértice antes de llegar a v
    std::vector<int> dist;   // dist[v] = aristas en el camino s-v más corto
    int s;
    void bfs(Grafo const &g)
    {
        std::queue<int> q;
        dist[s] = 0;
        visit[s] = true;
        q.push(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            for (int w : g.ady(v))
            {
                if (!visit[w])
                {
                    ant[w] = v;
                    dist[w] = dist[v] + 1;
                    visit[w] = true;
                    q.push(w);
                }
            }
        }
    }
};