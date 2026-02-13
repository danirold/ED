/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas no
  * será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos: Daniel Roldan Serrano
  //@ </answer>

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream> // stringstream

using namespace std;

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>


void resuelveCaso() {
    map<string, string> mapa; //mapa de -
    string linea; string palabra; string clave;
    getline(cin, linea); int i = 0;
    stringstream ss(linea); // para poder extraer de una a una las palabras
    while (ss >> palabra) { // una vuelta por cada palabra de la línea
        // tratar palabra
        if (i % 2 == 0) {
            clave = palabra;
        }
        else {
            mapa[clave] = palabra;
        }
        ++i;
    }
    map<string, string> aux1; //mapa de +
    map<string, string> aux2; //mapa de *
    getline(cin, linea); i = 0;
    stringstream ss2(linea); // para poder extraer de una a una las palabras
    if (mapa.empty()) {
        while (ss2 >> palabra) {
            if (i % 2 == 0) {
                clave = palabra;
            }
            else {
                aux1[clave] = palabra;
            }
            ++i;
        }
    }
    else {
        while (ss2 >> palabra) { // una vuelta por cada palabra de la línea
            // tratar palabra
            if (i % 2 == 0) {
                clave = palabra;
            }
            else {
                if (mapa.count(clave)) {
                    if (mapa[clave] == palabra) {
                    }
                    else {
                        aux2[clave] = palabra;
                    }
                    mapa.erase(clave);
                }
                else {
                    aux1[clave] = palabra;
                }
            }
            ++i;
        }
    }

    if (mapa.empty() && aux2.empty() && aux1.empty()) {
        cout << "Sin cambios";
    }
    else {
        if (!aux1.empty()) cout << "+ ";
        for (auto [clave, valor] : aux1) {
            cout << clave << ' ';
        }
        if(!mapa.empty()) cout << "\n- ";
        for (auto [clave, valor] : mapa) {
            cout << clave << ' ';
        }
        if(!aux2.empty()) cout << "\n* ";
        for (auto [clave, valor] : aux2) {
            cout << clave << ' ';
        }
    }
    cout << "\n---\n";
}


//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
    int casos;
    cin >> casos;
    cin.ignore(1);
    while (casos--) {
        resuelveCaso();
    }
    return 0;
}