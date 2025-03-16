#include <cstdio>
#include <iostream>
#include <vector>

#define INF 10e8

using vi = std::vector<int>;
using vvi = std::vector<vi>;

int main()
{
    int V, S;
    while (std::cin >> V >> S, std::cin)
    {
        vi valores(S);
        vi minDardos(V + 1, INF);
        minDardos[0] = 0;
        vvi comb(V + 1, vi());
        for (int &v : valores)
            std::cin >> v;
        for (int i = valores[0]; i <= V; i++)
            for (int j = S; j > 0; j--)
            {
                int v = valores[j - 1];
                if (i - v >= 0 && minDardos[i] > minDardos[i - v] + 1)
                {
                    minDardos[i] = minDardos[i - v] + 1;
                    comb[i] = comb[i - v];
                    comb[i].push_back(v);
                }
            }
        if (minDardos[V] < INF)
        {
            printf("%d:", minDardos[V]);
            vi &sol = comb[V];
            for (int i = sol.size(); i > 0; i--)
                printf(" %d", sol[i - 1]);
        }
        else
            printf("Imposible");
        printf("\n");
    }
}
