// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

bool resuelveCaso() {
    int num_alums; cin >> num_alums;
    int saltar_alums; cin >> saltar_alums;

    if (num_alums == 0 && saltar_alums == 0)
        return false;

    queue <int> cola;
    for (int i = 0; i < num_alums; ++i) {
        cola.push(i + 1);
    }
    int i = 1;
    while (cola.size() != 1) {
        if (i % (saltar_alums + 1) == 0) {
            cola.pop();
        }
        else {
            cola.push(cola.front());
            cola.pop();
        }
        ++i;
    }

    cout << cola.front() << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
