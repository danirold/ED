// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

bool resuelveCaso() {
    int num_juegos; cin >> num_juegos;
    cin.ignore(1);

    if (!std::cin)
        return false;

    map<string, vector<int>> mapa;
    string linea; string palabra;
    getline(cin, linea); // se lee completamente una línea
    stringstream ss(linea); // para poder extraer de una a una las palabras
    int i = 1;
    while (ss >> palabra) { // una vuelta por cada palabra de la línea
        // tratar palabra
        mapa[palabra].push_back(i);
        ++i;
    }

    int num_preguntas; cin >> num_preguntas;  
    int dias; string titulo;
    for (int i = 0; i < num_preguntas; ++i) {
        cin >> dias >> titulo;
        if (!mapa.count(titulo)) {
            cout << "NO JUEGA\n";
        }
        else if (mapa.count(titulo) && mapa[titulo].size() < dias) {
            cout << "NO JUEGA\n";
        }
        else {
            cout << mapa[titulo][dias - 1] << '\n';
        }
    }

    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}