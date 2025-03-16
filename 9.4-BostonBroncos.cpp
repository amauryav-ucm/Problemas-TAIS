#include <iostream>
#include <queue>

template <typename T>
using min_q = std::priority_queue<T, std::vector<T>, std::greater<T>>;
template <typename T>
using max_q = std::priority_queue<T>;

int main()
{
    int N;
    while (std::cin >> N, N)
    {
        int score;
        min_q<int> opps;
        max_q<int> broncos;
        for (int i = 0; i < N; i++)
        {
            std::cin >> score;
            opps.push(score);
        }
        for (int i = 0; i < N; i++)
        {
            std::cin >> score;
            broncos.push(score);
        }
        score = 0;
        while (!broncos.empty() && broncos.top() > opps.top())
        {
            score += broncos.top() - opps.top();
            broncos.pop();
            opps.pop();
        }
        printf("%d\n", score);
    }
}