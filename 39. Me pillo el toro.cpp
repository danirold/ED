// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>

using namespace std;

bool resuelveCaso() {
    int num_ejercicios; cin >> num_ejercicios;

    if (num_ejercicios == 0)
        return false;

    map<string, int> mapa; 
    string nombre;
    string resultado;
    cin.ignore(1);
    for (int i = 0; i < num_ejercicios; ++i) {
        getline(cin, nombre);
        getline(cin, resultado);
        if (resultado == "CORRECTO") {
            mapa[nombre]++;
        }
        else if (resultado == "INCORRECTO") {
            mapa[nombre]--;
        }
    }
    for (auto [nombre, nota] : mapa) {
        if (nota != 0) {
            cout << nombre << ", " << nota << '\n';
        }
    }
    cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}