/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
    Estudiante 1: Daniel Roldan Serrano
    Estudiante 2: Sergio Martinez Olivera

    Dad una explicación de la solución y justificad el coste del
    algoritmo.

   *@ </answer> */


#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

struct tFecha {
    string fecha;
    int accidentes;
};

void resolver(queue <tFecha> &datos) {
    /*
    Creamos una pila donde introduciremos las fechas y el num de accidentes de cada una.
    Para cada fecha, recorremos la pila hasta encontrar una fecha con un num de accidentes mayor al de la actual, borrando
    aquellas fechas con un numero de accidentes menor, porque ya no seran posibles soluciones para las
    siguientes fechas. Cuando encontramos una fecha con un num de accidentes mayor, mostramos dicha fecha.
    Si se da el caso de que la pila se vacia (o en la primera fecha) esto significa que no hay ninguna fecha que cumpla
    la restriccion, entonces escribimos "NO HAY".
    De este modo, cada fecha entra y/o sale una sola vez en la pila, evitando obtener un orden cuadratico respecto al numero de datos
    */
    stack <tFecha> solucion;
    while (!datos.empty()) {
        while (!solucion.empty() && solucion.top().accidentes <= datos.front().accidentes) {
            solucion.pop();
        }
        if (solucion.empty()) cout << "NO HAY\n";
        else cout << solucion.top().fecha << '\n';
        solucion.push(datos.front());
        datos.pop();
    }
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!cin)
        return false;

    queue <tFecha> datos; tFecha fecha;
    for (int i = 0; i < N; ++i) {
        cin >> fecha.fecha; cin >> fecha.accidentes;
        datos.push(fecha);
    }

    resolver(datos);
    cout << "---\n";

    return true;
}

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {

    while (resuelveCaso());
    return 0;
}
