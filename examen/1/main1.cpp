/*@ <authors>
 *
 * TAIS109 AMAURY ANTONIO VALLE LOPEZ
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Digrafo.h"
#include <vector>
#include <deque>

using namespace std;

// ========================================================================
// Escribe entre las etiquetas answer un comentario general sobre la
// solución, explicando cómo se resuelve el problema y cuál es el coste de
// la solución, en función del tamaño del problema.
// ========================================================================

/*@ <answer>

Para que se cumpla lo que queremos tiene que existir una ordenacion topologica de los vertices, eso significa que tampoco puede haber ciclos,
por lo que para resolver el problema verificamos que el grafo no tenga ciclos a la vez que hacemos una asignacion de numeros a los vertices de modo
que en la ordenacion topologica, los numeros asignados a los vertices se encuentran ordenados de manera creciente

 Coste en tiempo:
 Lo que hacemos es un recorrido en profundidad por lo que el coste esta en O(V+E)

 Coste en espacio adicional:
 El coste en espacio adicional esta en O(V)

 @ </answer> */

 // ========================================================================
 // Escribe el código completo de tu solución debajo de la etiqueta answer
 // ========================================================================
 //@ <answer>

class CicloDirigido {
public:
	CicloDirigido(Digrafo const& g) : visit(g.V(), false),
		apilado(g.V(), false), hayciclo(false), number(g.V()), asg(g.V(), -1) {
		for (int v = 0; v < g.V(); ++v)
			if (!visit[v])
				dfs(g, v);
	}
	bool hayCiclo() const { return hayciclo; }
	std::vector<int> const& asig() const { return asg; }

private:
	int number;
	std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
	std::vector<int> asg; // ant[v] = vértice anterior en el camino a v
	std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
	bool hayciclo;

	void dfs(Digrafo const& g, int v) {
		apilado[v] = true;
		visit[v] = true;
		for (int w : g.ady(v)) {
			if (hayciclo) // si hemos encontrado un ciclo terminamos
				return;
			if (!visit[w]) { // encontrado un nuevo vértice, seguimos
				dfs(g, w);
			}
			else if (apilado[w]) { // hemos detectado un ciclo
				hayciclo = true;
			}
		}
		apilado[v] = false;
		// Hacemos la ordenacion topologica al mismo tiempo que vuscamos los ciclos, cuando un vertice se ha terminado de explorar completamente le asignamos el mayor numero aun no asignado
		asg[v] = number--;
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	Digrafo g(std::cin, 1);

	if (!cin)  // fin de la entrada
		return false;

	// resolver el caso posiblemente llamando a otras funciones
	CicloDirigido cd(g);

	if (cd.hayCiclo()) cout << "NO\n";
	else {
		cout << "SI";
		for (auto x : cd.asig()) std::cout << " " << x;
		cout << "\n";
	}


	// escribir la solución

	return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos1.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	// Resolvemos
	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// system("PAUSE");
#endif
	return 0;
}
