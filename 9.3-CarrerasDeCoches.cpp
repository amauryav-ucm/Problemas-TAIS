#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using vi = std::vector<int>;

int main()
{
    int N;
    std::cin >> N;
    vi pilas;
    while (N--)
    {
        int n, v, total = 0;
        std::cin >> n >> v;
        pilas = vi(n);
        for (int &x : pilas)
            std::cin >> x;
        std::sort(pilas.begin(), pilas.end());
        int left = 0, right = pilas.size();
        while (left < right)
        {
            right--;
            while (pilas[right] + pilas[left] < v && left < right)
                left++;
            if (pilas[right] + pilas[left] >= v && left < right)
            {
                total++;
                left++;
            }
        }
        printf("%d\n", total);
    }

    return 0;
}