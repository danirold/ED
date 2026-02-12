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

    Dad una explicación de la solución y justificad el coste del
    algoritmo.

   *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
using namespace std;

/* ===================================================
 * Implementad aquí debajo vuestro algoritmo
 * ===================================================
 *@ <answer> */

void resolver(vector <int> datos, int k, int N) {
    deque <int> cola_maximos;
    cola_maximos.push_back(datos[0]);
    for (int i = 1; i < k; ++i) {
        while (!cola_maximos.empty() && datos[i] > cola_maximos.back()) cola_maximos.pop_back();
        cola_maximos.push_back(datos[i]);
    }
    cout << cola_maximos.front();
    for (int i = k; i < N; ++i) {
        if (datos[i - k] == cola_maximos.front()) cola_maximos.pop_front();
        while (!cola_maximos.empty() && datos[i] > cola_maximos.back()) cola_maximos.pop_back();
        cola_maximos.push_back(datos[i]);
        cout << ' ' << cola_maximos.front();
    }
    cout << '\n';
}

bool resuelveCaso() {
    // leemos la entrada
    int N, k;
    cin >> N >> k;

    if (!cin)
        return false;

    vector <int> cola(N); int dato;
    for (int i = 0; i < N; ++i) {
        cin >> dato;
        cola[i] = dato;
    }

    resolver(cola, k, N);

    return true;
}

/*@ </answer> */

int main() {

    while (resuelveCaso());
    return 0;
}
