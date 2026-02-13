// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

bool resuelveCaso() {
    int num_lineas;
    cin >> num_lineas;
    cin.ignore(1);

    if (num_lineas == 0)
        return false;

    map<string, vector<int>> mapa;
    string linea; string palabra;
    for (int i = 0; i < num_lineas; ++i) {
        getline(cin, linea); // se lee completamente una línea
        stringstream ss(linea); // para poder extraer de una a una las palabras
        while (ss >> palabra) { // una vuelta por cada palabra de la línea
            // tratar palabra
            if (palabra.size() > 2) {
                for (int j = 0; j < palabra.size(); ++j) palabra[j] = tolower(palabra[j]);
                mapa[palabra].push_back(i + 1);
            }    
        }
    }
    for (pair<string, vector<int>> palabras: mapa) {
        cout << palabras.first << ' ' << palabras.second[0] << ' ';
        for (int i = 1; i < palabras.second.size(); ++i) {
            if (palabras.second[i - 1] != palabras.second[i]) cout << palabras.second[i] << ' ';
        }
        cout << '\n';
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
