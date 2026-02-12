// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <deque>
#include <stack>
#include <string>

using namespace std;

bool is_vowel(char a) {
    return (a == 'a' || a == 'A' || a == 'e' || a == 'E' || a == 'i' || a == 'I' || a == 'o' || a == 'O' || a == 'u' || a == 'U');
}

bool resuelveCaso() {
    string linea; getline(cin, linea);

    if (!std::cin)
        return false;

    deque<char> cola; stack<char> pila;
    for (int i = 0; i < linea.size(); ++i) {
        if (i % 2 == 1) cola.push_front(linea[i]);
        else pila.push(linea[i]);
    }
    while (!pila.empty()) {
        cola.push_front(pila.top());
        pila.pop();
    }

    deque<char> cola_solucion;
    while (!cola.empty()) {
        while (!cola.empty() && !is_vowel(cola.front())) {
            pila.push(cola.front());
            cola.pop_front();  
        }
        while (!pila.empty()) {
            cola_solucion.push_back(pila.top());
            pila.pop();
        }
        if (!cola.empty()) {
            cola_solucion.push_back(cola.front());
            cola.pop_front();
        }
    }

    while (!cola_solucion.empty()) {
        cout << cola_solucion.front();
        cola_solucion.pop_front();
    }

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}