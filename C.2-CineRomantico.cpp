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
#include <algorithm>
#include <unordered_set>

// #define NUMC
#define CENT
// #define ILIM

//@ <answer>
#define swpMax(x, y) (x) = (x) > (y) ? (x) : (y)
#define swpMin(x, y) (x) = (x) < (y) ? (x) : (y)
using ii = std::pair<int, int>;
using vii = std::vector<ii>;
using vi = std::vector<int>;
using mat = std::vector<vi>;

class CineRomanticoRec
{
public:
    CineRomanticoRec(const vii &pelis) : pelis(pelis), dp_table(pelis.size(), vi(60 * 24 + 1, -1))
    {
    }

    int get_result() { return recursiva(pelis.size() - 1, 24 * 60); }

    int recursiva(int i, int j)
    {
        if (i == 0 || j == 0)
            return 0;

        if (dp_table[i][j] == -1)
        {
            int duracion = pelis[i].second - pelis[i].first;
            int restriccionTiempo = pelis[i].first - 10;
            dp_table[i][j] = std::max(recursiva(i - 1, j), recursiva(i - 1, restriccionTiempo) + duracion);
        }
        return dp_table[i][j];
    }

private:
    vii pelis;
    mat dp_table;
};

class CineRomantico
{
public:
    CineRomantico(const vii &pelis) : dp_table(pelis.size() + 1, vi(60 * 24 + 1))
    {
        for (int i = 1; i <= pelis.size(); i++)
        {
            int duracion = pelis[i - 1].second - pelis[i - 1].first;
            int restriccionTiempo = std::max(pelis[i - 1].first - 10, 0);
            int termina = pelis[i - 1].second;
            for (int j = 0; j < dp_table[i].size(); j++)
            {
                dp_table[i][j] = dp_table[i - 1][j];
                if (termina <= j)
                    swpMax(dp_table[i][j], dp_table[i - 1][restriccionTiempo] + duracion);
            }
        }
    }

    int get_result() { return dp_table[dp_table.size() - 1][60 * 24]; }

private:
    mat dp_table;
};

class CineRomanticoMod
{

public:
    CineRomanticoMod(const vii &pelis) : ts(), ts_id()
    {
        std::unordered_set<int> times;
        for (ii p : pelis)
        {
            if (!times.count(p.first))
            {
                ts.push_back(p.first);
                times.insert(p.first);
            }
            if (!times.count(p.second + 10))
            {
                ts.push_back(p.second + 10);
                times.insert(p.second + 10);
            }
        }
        std::sort(ts.begin(), ts.end());
        for (int i = 0; i < ts.size(); i++)
            if (!ts_id.count(ts[i]))
                ts_id.insert({ts[i], i});
        dp_table = mat(pelis.size() + 1, vi(ts.size(), 0));
        for (int i = 1; i < dp_table.size(); i++)
        {
            int duration = pelis[i - 1].second - pelis[i - 1].first;
            int time_restriction = ts_id[pelis[i - 1].first];
            int ending = pelis[i - 1].second + 10;
            for (int j = 0; j < dp_table[i].size(); j++)
            {
                dp_table[i][j] = dp_table[i - 1][j];
                if (ending <= ts[j])
                    swpMax(dp_table[i][j], dp_table[i - 1][time_restriction] + duration);
            }
        }
    }

    int get_result() { return dp_table[dp_table.size() - 1][dp_table[0].size() - 1]; }

private:
    mat dp_table;
    vi ts;
    std::unordered_map<int, int> ts_id;
};

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    int N;
    std::cin >> N;

#ifdef CENT
    if (!N)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif
    vii pelis(N);
    int h, m, d;
    for (ii &p : pelis)
    {
        scanf("%d:%d %d", &h, &m, &d);
        p.first = 60 * h + m;
        p.second = p.first + d;
    }
    CineRomantico caso(pelis);
    printf("%d\n", caso.get_result());
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