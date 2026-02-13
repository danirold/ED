// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <list>
#include <string>

using namespace std;

class Persona {
private:
    int edad;
    string nombre;

public:
    Persona(int edad, string nombre) {
        this->edad = edad;
        this->nombre = nombre;
    }

    int getEdad() {
        return this->edad;
    }
    string getNombre() {
        return this->nombre;
    }
};

template <typename Predicate>
void remove_if(list<Persona> & lista, Predicate pred) {
    auto it = lista.begin();
    while (it != lista.end()) {
        if (pred(*it)) {
            it = lista.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool resuelveCaso() {
    int num_inscritos, edad_minima, edad_maxima;
    cin >> num_inscritos >> edad_minima >> edad_maxima;

    if (num_inscritos == 0 && edad_minima == 0 && edad_maxima == 0)
        return false;

    list<Persona> lista; 

    for (int i = 0; i < num_inscritos; ++i) {
        int edad; cin >> edad;
        string nombre; getline(cin, nombre);
        nombre.erase(0, 1);
        Persona persona(edad, nombre);
        lista.push_back(persona);
    }

    remove_if(lista, [edad_minima, edad_maxima](Persona persona) {return (persona.getEdad() < edad_minima || persona.getEdad() > edad_maxima); });

    while (!lista.empty()) {
        cout << lista.front().getNombre() << '\n';
        lista.pop_front();
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}