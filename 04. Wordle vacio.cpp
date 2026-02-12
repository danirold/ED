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
   *  Estudiante 1: DANIEL ROLDAN SERRANO
   *@ </answer> */

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_ELEMS = 2000;

/*@ <answer> */

class Multiconjunto {
public:
    Multiconjunto() {
        num_elems = 0;
    }

    int binarySearch(int nuevo_elem, int ini, int fin) {
        if (ini == fin) return -1;
        else {
            int m = (ini + fin - 1) / 2;
            if (elems[m].valor == nuevo_elem) return m;
            else if (elems[m].valor < nuevo_elem) return binarySearch(nuevo_elem, m + 1, fin);
            else return binarySearch(nuevo_elem, ini, m);
        }
    }

    bool pertenece(int nuevo_elem) {
        return binarySearch(nuevo_elem, 0, num_elems) != -1 && binarySearch(nuevo_elem, 0, num_elems) != num_elems;
    }

    void anyadir(int nuevo_elem) {
        int pos = binarySearch(nuevo_elem, 0, num_elems);
        if (pertenece(nuevo_elem)) {
            elems[num_elems].valor = nuevo_elem;
            elems[num_elems].multiplicidad++;
            num_elems++;
        }
        else {
            elems[pos].multiplicidad++;
        }
    }

    void eliminar(int elemento) {
        int pos = binarySearch(elemento, 0, num_elems);
        if (pertenece(elemento)) {
            if (elems[pos].multiplicidad > 1) {
                elems[pos].multiplicidad--;
            }
            else {
                for (int i = pos; i < num_elems - 1; ++i) {
                    elems[i] = elems[i + 1];
                }
            }
        }
    }

    // Implementa las operaciones necesarias.
    // No olvides el coste!

private:
    struct Elem {
        int valor;
        int multiplicidad;
    };
    Elem elems[MAX_ELEMS];
    int num_elems;
};


// Función que trata un caso de prueba.
// Devuelve false si se ha leído el 0 que marca el fin de la entrada,
// o true en caso contrario.
bool tratar_caso() {
    // Implementar
    int num_elems_secuencia; cin >> num_elems_secuencia;

    if (num_elems_secuencia == 0) return false;

    int dato_leer; Multiconjunto secuencia_correcta; Multiconjunto intento;

    vector<int> datos_leer(num_elems_secuencia);
    for (int i = 0; i < num_elems_secuencia; ++i) {
        cin >> datos_leer[i];
    }
    sort(datos_leer.begin(), datos_leer.end());
    for (int i = 0; i < num_elems_secuencia; ++i) {
        secuencia_correcta.anyadir(datos_leer[i]);
    }

    vector<int> intento_aux(num_elems_secuencia);
    for (int i = 0; i < num_elems_secuencia; ++i) {
        cin >> intento_aux[i];
    }
    sort(intento_aux.begin(), intento_aux.end());
    for (int i = 0; i < num_elems_secuencia; ++i) {
        intento.anyadir(intento_aux[i]);
    }

    return true;
}

/*@ </answer> */

int main() {
    while (tratar_caso()) {}
    return 0;
}
