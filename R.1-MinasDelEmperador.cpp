#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

struct UFDS
{
    vector<int> p;
    int numSets;
    UFDS(int n) : p(n, 0), numSets(n)
    {
        for (int i = 0; i < n; i++)
            p[i] = i;
    }
    int find(int x)
    {
        return (p[x] == x) ? x : p[x] = find(p[x]);
    }
    void merge(int x, int y)
    {
        int i = find(x), j = find(y);
        if (j == i)
            return;
        p[i] = j;
        --numSets;
    }
};

int V, E;
UFDS uf(0);
priority_queue<pair<int, pair<int, int>>> pq;

int main()
{
    while (std::cin >> V >> E)
    {
        uf = UFDS(V + 1);
        pq = priority_queue<pair<int, pair<int, int>>>();
        int v1, v2, d, mayor = 0;
        for (int i = 0; i < E; i++)
        {
            std::cin >> v1 >> v2 >> d;
            pq.push({-d, {v1, v2}});
        }
        std::cin >> v1 >> v2;
        while (pq.size() && uf.find(v1) != uf.find(v2))
        {
            auto e = pq.top();
            pq.pop();
            uf.merge(e.second.first, e.second.second);
            mayor = -e.first;
        }
        if (uf.find(v1) == uf.find(v2))
            printf("%d\n", mayor);
        else
            printf("IMPOSIBLE\n");
    }
    return 0;
}