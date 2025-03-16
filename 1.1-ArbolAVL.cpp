#include <fstream>
#include <iostream>
#include <string>
#include "BinTree.h"

#define IN_FILE "casos/1.1.in"

#define CMDOUT

// #define NUMC
// #define CENT
#define ILIM

template <typename T>
struct sol
{
    bool avl;
    T min;
    T max;
    int height;
};

template <typename T>
sol<T> resolver(const BinTree<T> tree)
{
    sol<T> ans;
    if (tree.empty())
    {
        ans.avl = true;
        ans.height = 0;
        return ans;
    }
    sol<T> left = resolver(tree.left());
    sol<T> right = resolver(tree.right());
    if (!left.avl ||
        !right.avl ||
        (left.height > 0 && tree.root() <= left.max) ||
        (right.height > 0 && tree.root() >= right.min) ||
        (abs(left.height - right.height) > 1))
    {
        ans.avl = false;
        return ans;
    }
    else
    {
        ans.avl = true;
        ans.height = std::max(left.height, right.height) + 1;
        ans.min = (left.height > 0) ? left.min : tree.root();
        ans.max = (right.height > 0) ? right.max : tree.root();
    }
    return ans;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    char c;
    std::cin >> c;

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    if (c == 'P')
    {
        sol<std::string> ans = resolver<std::string>(read_tree<std::string>(std::cin));
        std::cout << (ans.avl ? "SI" : "NO") << std::endl;
    }
    else
    {
        sol<int> ans = resolver<int>(read_tree<int>(std::cin));
        std::cout << (ans.avl ? "SI" : "NO") << std::endl;
    }
    return true;
}

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
