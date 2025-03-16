#include <iostream>
#include <vector>
#include <cinttypes>

#define INF 10e9

using ll = uint64_t;
using vi = std::vector<ll>;
using vvi = std::vector<vi>;

int main()
{
    ll N, L, l, c;
    vi comb, minItems, minCost;
    while (std::cin >> N >> L, std::cin)
    {
        comb = vi(L + 1, 0);
        minItems = minCost = vi(L + 1, INF);
        comb[0] = 1;
        minItems[0] = minCost[0] = 0;
        for (int i = 0; i < N; i++)
        {
            std::cin >> l >> c;
            for (int i = L; i >= l; i--)
            {
                comb[i] += comb[i - l];
                minItems[i] = std::min(minItems[i], minItems[i - l] + 1);
                minCost[i] = std::min(minCost[i], minCost[i - l] + c);
            }
        }
        if (comb[L])
            printf("SI %lld %lld %lld\n", comb[L], minItems[L], minCost[L]);
        else
            printf("NO\n");
    }

    return 0;
}