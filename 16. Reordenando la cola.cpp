// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;

void resolver(queue <int>& cola) {
    deque <int> aux;
    while (!cola.empty()){
        if (cola.front() >= 0) {
            aux.push_back(cola.front());
        }
        else aux.push_front(cola.front());
        cola.pop();
    }
    while (!aux.empty()) {
        cola.push(aux.front());
        cout << aux.front() << ' ';
        aux.pop_front();
    }
    cout << '\n';
}

bool resuelveCaso() {
    int longitud_cola;
    cin >> longitud_cola;

    if (longitud_cola == 0)
        return false;

    queue <int> cola;  int valor;
    for (int i = 0; i < longitud_cola; ++i) {
        cin >> valor;
        cola.push(valor);
    }

    resolver(cola);

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
