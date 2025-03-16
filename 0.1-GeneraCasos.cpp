

/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <fstream>
#include <string>
#include <random>

#define IN_FILE "casos/.in"

#define NUMC
// #define CENT
// #define ILIM

//@ <answer>

bool generaCaso6_1()
{
    // LEER DATOS DE ENTRADA
    int n = rand()%200+1;
    std::cout << n << " " << n << "\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (rand() % 2 == 0)
                std::cout << '#';
            else
                std::cout << "-";
        }
        std::cout << "\n";
    }
    int i = rand() % 1000 + 1;
    std::cout << i << "\n";
    for (int j = 0; j < i; j++)
    {
        int a = rand() % n + 1;
        int b = rand() % n + 1;
        std::cout << a << " " << b << "\n";
    }
    std::cout << "\n";

    return true;
}

void generaCasoB_1(){    
    int T = (rand()%1000)+1;
    int N = (rand()%50)+1;

    printf("%d\n%d\n", T,N);
    for(int i = 0;i<N;i++){
        printf("%d %d\n", rand()%500+1, rand()%1000+1);
    }

}
//@ </answer>

int main()
{
    srand(time(NULL));
    int n = 100;
    for (int i = 0; i < n; i++)
        generaCaso6_1();
}