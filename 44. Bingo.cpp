// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

bool resuelveCaso() {
    int num_participantes; cin >> num_participantes;

    if (num_participantes == 0)
        return false;

    unordered_map<string, int> nombres;
    unordered_map<int, vector<string>> numeros;
    set<string> ganadores;
    string nombre; int num;
    for (int i = 0; i < num_participantes; ++i) {
        cin >> nombre;
        nombres[nombre] = 0;
        cin >> num;
        while (num != 0) {
            nombres[nombre]++;
            numeros[num].push_back(nombre);
            cin >> num;
        }
    }
    bool parar = false;
    while (!parar) {
        cin >> num;
        if (numeros.count(num)) {
            for (int i = 0; i < numeros[num].size(); ++i) {
                nombres[numeros[num][i]]--;
                if (nombres[numeros[num][i]] == 0) {
                    ganadores.insert(numeros[num][i]);
                    parar = true;
                }
            }
        }
    }
    for (auto valor : ganadores) {
        cout << valor << ' ';
    }
    cout << '\n';
    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
