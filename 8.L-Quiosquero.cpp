#include <stdio.h>
#include <cstdint>
#include <unordered_set>
#include <iostream>
#include <cassert>

int main()
{
    uint64_t n, s;
    //int tests = 10000, top = 10000000;
    while (std::cin >> n >> s, std::cin/* , tests-- */)
    {
        /* n = rand() % top + 1;
        s = rand() % top + 1;
        uint64_t sum = 0;
        uint64_t i = 1;
        uint64_t count = 0;
        for (; count < n; i++)
        {
            if (i > s / 2 && i < s)
                continue;
            count++;
            sum += i;
        }
        printf("%lld\n", sum); */

        uint64_t sol = n * (n + 1) / 2;
        uint64_t s_2 = s / 2;
        if (n > s_2)
            sol += (std::min(s - 1, n) - s_2) * (std::max(n + 1, s) - s_2 - 1);
        //assert(sol == sum);
        printf("%lld\n", sol);
    }
    return 0;
}