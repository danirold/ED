// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>

using namespace std;

void resuelveCaso() {
    int num; cin >> num;
    unordered_map<int, int> caps;
    int numero; int longMax = 0; int longAct = 0;
    for (int i = 0; i < num; ++i) {
        cin >> numero;
        if (!caps.count(numero)) {
            longAct++;
            if (longMax < longAct) {
                longMax = longAct;
            }
        }
        else {
            if (i - caps[numero] + 1 <= longAct) {
                longAct = i - caps[numero] + 1;
            }
            else {
                longAct++;
                if (longMax < longAct) {
                    longMax = longAct;
                }
            }
        }
        caps[numero] = i + 1;
    }

    cout << longMax << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
