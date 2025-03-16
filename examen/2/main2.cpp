/*@ <authors>
 *
 * TAIS109 AMAURY ANTONIO VALLE LOPEZ
 *
 *@ </authors> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

// ========================================================================
// Escribe entre las etiquetas answer un comentario general sobre la
// solución, explicando cómo se resuelve el problema y cuál es el coste de
// la solución, en función del tamaño del problema.
// ========================================================================

/*@ <answer>

 Explicación:
 Nuestra recurrencia seleccion(i) nos dice la mejor forma de escoger los locales desde el i hasta el N-1 (Los indices de los locales estan entre 0 y N-1), 
 definimos la funcion bloqueo(i), donde bloqueo(i) nos devuelve el indice j > i de la primera posicion que se encuentra a mas de S metros de la posicion i, 
 o devuelve N si no existe tal indice; eso significa que si abrimos un local en la posicion con indice i, sera imposible abrir locales en las posiciones 
 con indices entre i + 1 y j - 1, por lo tanto para calcular seleccion(i), tenemos dos opciones, usar el local i o no usarlo, si no lo usamos entonces somos
 libres de escoger locales a partir del i+1, si lo escogemos, obtenemos su beneficio pero ya no podemos usar los locales que esten a menos de S metros, es 
 decir, somos libres de escoger locales a partir del bloqueo(i)

 Ecuaciones de la recurrencia:
 seleccion(N) = 0
 seleccion(i) = max(seleccion(i + 1), beneficio(i) + seleccion(bloqueo(i)))

 Llamada inicial:
 La primera llamada seria seleccion(0) porque queremos saber la mejor seleccion teniendo en cuenta todas las posiciones

 Aplicación de la programación dinámica:
 Usamos programacion dinamica para almacenar los valores de seleccion(i) de los i mayores para poder reusarlos en el calculo y no tener que recalcularlos

 Coste en tiempo:
 El coste en tiempo es lineal respecto a N

 Coste en espacio adicional:
 El coste en espacio es lineal respecto a N

 @ </answer> */


// ========================================================================
// Escribe el código completo de tu solución debajo de la etiqueta <answer>
// ========================================================================
//@ <answer>


bool resuelveCaso() {

	// leer los datos de la entrada
	int N, S;
	std::cin >> N >> S;

	if (!cin)  // fin de la entrada
		return false;

	// El coste en espacio adicional son solo los vectores seleccion y bloqueo, ambos ocupan espacio lineal respecto a N
	std::vector<int> posicion(N), beneficio(N), seleccion(N + 1), bloqueo(N);
	for (int& x : posicion) std::cin >> x;
	for (int& x : beneficio) std::cin >> x;

	// resolver el caso posiblemente llamando a otras funciones
	int j = 0;
	// Coste lineal respecto a N, los bucles while hacen en total a lo sumo N iteraciones y el for hace N iteraciones
	for (int i = 0; i < N; i++) {
		while (j < N && posicion[j] - posicion[i] < S) j++;
		bloqueo[i] = j;
	}
	seleccion[N] = 0;
	// Coste lineal respecto a N, es un for con cuerpo constante
	for (int i = N - 1; i >= 0; i--) 
		seleccion[i] = std::max(seleccion[i + 1], beneficio[i] + seleccion[bloqueo[i]]);	

	// escribir la solución
	std::cout << seleccion[0] << ":";
	int pos = 0;
	while (pos < N) {
		// Si seleccion(i) es mayor que seleccion(i+1) significa que hemos usado i en la solucion
		if (seleccion[pos] > seleccion[pos + 1]) { std::cout << " " << posicion[pos]; pos = bloqueo[pos]; }
		else pos++;
	}
	std::cout << "\n";

	return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos2.txt");
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
