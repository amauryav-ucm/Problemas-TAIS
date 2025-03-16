/* @ <authors>
 * TAIS109 Amaury Antonio Valle Lopez
 * @ </authors>
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include "GrafoValorado.h"
#include "IndexPQ.h"

#define IN_FILE "casos/.in"

// #define NUMC
// #define CENT
#define ILIM

//@ <answer>

/*
Explicacion:
Calculamos los caminos minimos desde el norte y desde el sur, luego calculamos la diferencia para cada ciudad
entre la distancia al norte y al sur, por lo que este numero indica para cada ciudad, que tanto favorece una
planta u otra, un coste positivo alto indica que favorece la planta sur, y negativo que favorece la planta norte
luego lo ordenamos y asignamos los (N-2)/2 mayores a la planta sur y los otros a la planta norte.
Esta es la mejor solucion ya que una solucion distlla implica llercambiar una ciudad de la planta norte a la
sur y otra viceversa, esto significa que el nuevo coste sera el anterior mas la diferencia del vector de la que hemos
pasado a la norte, menos la diferencia del vector de la que hemos pasado a la sur, es decir
costeAnterior + diferencias[i]-diferencias[j]
donde pasamos i a la planta norte y j a la planta sur, como pusimos los de la derecha en la planta sur, eso significa
que diferencias[i]>=diferencias[j], porque i estaba en la planta sur, por lo tanto mas a la derecha, por lo tanto mayor
por lo que es imposible que la solucion mejore

Definimos v_1, v_2, ... v_((n-2)/2) como una solucion del problema, donde los v_i son las ciudades que se han asignado
a la planta norte, ordenadas de menor a mayor distancia si tomamos otra solucion v_1,...,v_k,s_k,...,s_n, ahora cambiamos
s_k por v_k, por definicion v_1,...,v_(k-1) son las k-1 menores diferencias norte-sur, y v_k es la k-esima menor, por lo
que podemos asegurar que la diferencia norte-sur de s_k es mayor que la de v_k, entonces si cambiamos v_k por s_k, el nuevo
coste sera, como asignamos v_k a la norte y s_k a la sur:
costeAnterior-distanciaNorte(s_k)+distanciaNorte(v_k)-distanciaSur(v_k)+distanciaSur(s_k)=
costeAnterior+(distanciaNorte(v_k)-distanciaSur(v_k))-(distanciaNorte(s_k)-distanciaSur(v_k))=
costaAnterior+diferencia(v_k)-diferencia(s_k)
Donde diferencia(i) es la diferencia norte-sur de la ciudad i, antes demostramos que diferencia(v_k) < diferencia(v_s), por lo
que el coste ha mejorado, por lo que v_1,...,v_((N-2)/2) es la solucion optima


*/

using ll = long long int;
using vi = std::vector<ll>;
using ii = std::pair<ll, ll>;
using vii = std::vector<ii>;
using Grafo = GrafoValorado<ll>;
using min_q = std::priority_queue<ii, vii, std::greater<ii>>;
using max_q = std::priority_queue<ii, vii, std::less<ii>>;

class Dijkstra
{
public:
    Dijkstra(Grafo const &g, ll orig) : origen(orig),
                                        dist(g.V(), INF), anterior(g.V()), pq(g.V())
    {
        dist[origen] = 0;
        pq.push(origen, 0);
        anterior[origen] = -1;
        while (!pq.empty())
        {
            ll v = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(v))
                relajar(a, v);
        }
    }
    bool hayCamino(ll v) const { return dist[v] != INF; }
    ll distancia(ll v) const { return dist[v]; }

private:
    const ll INF = std::numeric_limits<ll>::max();
    ll origen;
    std::vector<ll> dist;
    std::vector<ll> anterior;
    IndexPQ<ll> pq;
    void relajar(Arista<ll> a, ll v)
    {
        ll w = a.otro(v);
        if (dist[w] > dist[v] + a.valor())
        {
            dist[w] = dist[v] + a.valor();
            anterior[w] = v;
            pq.update(w, dist[w]);
        }
    }
};

// En total coste O(Nlog(M+N))

ll resolver(const Grafo &g)
{
    // coste O(Mlog(N)) para cada uno
    Dijkstra norte(g, 0), sur(g, g.V() - 1);
    vii diferencias(g.V() - 2);
    // Coste O(N)
    for (ll i = 1; i < g.V() - 1; i++)
    {
        diferencias[i - 1] = {norte.distancia(i) - sur.distancia(i), i};
    }
    ll suma = 0;
    // coste O(Nlog(N))
    std::sort(diferencias.begin(), diferencias.end());
    // coste O(N) entre ambos for
    for (ll i = 0; i < diferencias.size() / 2; i++)
    {
        suma += 2 * norte.distancia(diferencias[i].second);
    }
    for (ll i = diferencias.size() / 2; i < diferencias.size(); i++)
    {
        suma += 2 * sur.distancia(diferencias[i].second);
    }
    return suma;
}

bool resuelveCaso()
{
    // LEER DATOS DE ENTRADA
    Grafo g(std::cin, 1);

#ifdef CENT
    if (condition)
        return false;
#endif
#ifdef ILIM
    if (!std::cin)
        return false;
#endif

    ll sol = resolver(g);
    printf("%lld\n", sol);
    return true;
}

//@ </answer>

int main()
{

#ifdef NUMC
    ll n;
    std::cin >> n;
    for (ll i = 0; i < n; i++)
        resuelveCaso();

#endif

#ifndef NUMC
    while (resuelveCaso())
        ;
#endif
}