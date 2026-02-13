/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 /

/
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 /

/@ <answer>
  Estudiante 1: Sergio Martinez Olivera
  Estudiante 2: Daniel Roldán Serrano

  Dad una explicación de la solución y justificad el coste del
  algoritmo.

 @ </answer>/
*/


#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
using namespace std;

// ----------------------------------------------------------------
//@ <answer>

/* Utiizamos dos iteradores.Uno que "apunta" al elemento actual y otro al siguiente a este.
* En cada iteracion del bucle comparamos si el valor absoluto de la diferencia de los elementos apuntados por ambos
iteradores distinguiendo tres casos.
En primer lugar, si la diferencia es mayor que uno, anadimos el valor del iterador actual incrementado en 1.
Si la diferencia es 0, eliminamos el elemento repetido
Y, por ultimo, si la diferencia es 1, avanzamos ambos iteradores.
El coste del algoritmo es O(n), siendo n la suma del numero de elementos de la lista inicial mas los elementos introducidos (es decir,
la diferencia en valor absoluto de cada par de elementos de la lista inicial)
*/

void suavizar(list<int> & l) {
  auto it = l.begin();
  auto next = ++l.begin();
  while (next != l.end()){
    int diferencia = abs(*it - *next);
    if (diferencia > 1){
       if (*it > *next) {
           it = l.insert(next, *it - 1);
       }
       else {
           it = l.insert(next, *it + 1);
       }
       diferencia = abs(*it - *next);

    }
    else if (diferencia == 0) {
        next = l.erase(next);
    }
    else {
        it++;
        next++;
    }
  }
}

bool resuelveCaso() {
  int longitud;
  cin >> longitud;
  if (!cin) return false;

  list<int> l;

  for (int i = 0; i < longitud; i++) {
    int x; cin >> x;
    l.push_back(x);
  }

  suavizar(l);

  while (!l.empty()){
    cout << l.front() << ' ';
    l.pop_front();
  }
  cout << '\n';

  // imprimir l

  return true;
}
//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {

  while (resuelveCaso()) { }


  return 0;
}