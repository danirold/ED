/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: DANIEL ROLDAN SERRANO
  Estudiante 2: SERGIO MARTINEZ OLIVERA

  Dad una explicación de la solución y justificad su coste.

  @ </answer> */


  // Añade los include que necesites
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <map>

using namespace std;

// Tipo de datos para representar direcciones
// Para hacer referencia a los elementos de este tipo enumerado se utiliza:
//   Direccion::Norte, Direccion::Sur, etc.
enum class Direccion { Norte, Sur, Este, Oeste };

// Operador para leer una dirección desde un flujo de entrada.
// Ejemplo de uso:
//
// Direccion dir;
// cin >> dir;
//
istream& operator>>(istream& is, Direccion& dir) {
    string palabra; is >> palabra;
    if (palabra == "Norte") dir = Direccion::Norte;
    else if (palabra == "Sur") dir = Direccion::Sur;
    else if (palabra == "Este") dir = Direccion::Este;
    else if (palabra == "Oeste") dir = Direccion::Oeste;
    else throw std::domain_error("Lectura de direccion incorrecta");
    return is;
}

// Implementa a continuación la clase Desierto.
//@ <answer>

class Desierto {
public:

    Desierto() { }

    void anyadir_torre(const string& nombre, int x, int y) {   //O(log n), siendo n el numero de torres
        if (mapa_torres.count(nombre)) {
            throw domain_error("Torre ya existente");
        }
        if (mapa_x.count(x) && mapa_x[x].count(y)) {
            throw domain_error("Posicion ocupada");
        }
        mapa_torres[nombre] = { x,y };
        mapa_x[x][y] = nombre;
        mapa_y[y][x] = nombre;
    }

    void eliminar_torre(const string& nombre) {    //O(log n), siendo n el numero de torres
        if (!mapa_torres.count(nombre)) {
            throw domain_error("Torre no existente");
        }
        pair<int, int> pos = mapa_torres[nombre];
        mapa_torres.erase(nombre);
        mapa_x[pos.first].erase(pos.second);
        mapa_y[pos.second].erase(pos.first);
    }

    pair<bool, string> torre_en_posicion(int x, int y) const {   //O(log n), siendo n el numero de torres
        if (mapa_x.count(x) && mapa_x.at(x).count(y)) {
            return { true, mapa_x.at(x).at(y) };
        }
        else return { false, " " };
    }

    pair<int, int> posicion(const string& nombre) const {   //O(1), acceso de unordered_map
        if (!mapa_torres.count(nombre)) {
            throw domain_error("Torre no existente");
        }
        return mapa_torres.at(nombre);
    }

    string torre_mas_cercana(const string& nombre, const Direccion& dir) const {   //O(log n), siendo n el numero de torres
        if (!mapa_torres.count(nombre)) {
            throw domain_error("Torre no existente");
        }
        string sol = busqueda_torre(nombre, dir);
        return sol;
    }

private:
    // Añade aquí los atributos que conforman la representación
    // interna del TAD
    //
    // También puedes añadir métodos auxiliares privados

    unordered_map<string, pair<int, int>> mapa_torres;
    unordered_map<int, map<int, string>> mapa_x;
    unordered_map<int, map<int, string>> mapa_y;

    string busqueda_torre(const string& nombre, const Direccion& dir) const {  //O(log n), siendo n el numero de torres, por usar find
        if (dir == Direccion::Norte) {     
            pair<int, int> pos = posicion(nombre);
            auto it = mapa_x.at(pos.first).find(pos.second);
            it++;
            if (it == mapa_x.at(pos.first).end()) {
                throw domain_error("No hay torres en esa direccion");
            }
            else {
                return it->second;
            }
        }
        else if (dir == Direccion::Sur) {   
            pair<int, int> pos = posicion(nombre);
            auto it = mapa_x.at(pos.first).find(pos.second);
            if (it == mapa_x.at(pos.first).begin()) {
                throw domain_error("No hay torres en esa direccion");
            }
            else {
                it--;
                return it->second;
            }
        }
        else if (dir == Direccion::Este) {
            pair<int, int> pos = posicion(nombre);
            auto it = mapa_y.at(pos.second).find(pos.first);
            it++;
            if (it == mapa_y.at(pos.second).end()) {
               throw domain_error("No hay torres en esa direccion");
            }
            else {
                return it->second;
            }
        }
        else if (dir == Direccion::Oeste) {
            pair<int, int> pos = posicion(nombre);
            auto it = mapa_y.at(pos.second).find(pos.first);
            if (it == mapa_y.at(pos.second).begin()) {
                throw domain_error("No hay torres en esa direccion");
            }
            else {
                it--;
                return it->second;
            }
        }
    }
};

/*
Utilizamos tres estructuras de datos. Un unordered_map cuyas claves son los nombres de las torres y los valores, sus posiciones (x,y);
otro unordered_map cuyas claves son las componentes x y los valores son maps cuyas claves son las componentes y que tienen las x, y los valores, el nombre de la torre.
y otro analogo a este pero intercambiando las x por las y.
Utilizamos map en los valores para que las posiciones queden ordenadas en ambos ejes, y de ese modo, ayudandonos de iteradores para avanzar o
retroceder, acceder a la mas cercana (si es que existe) por arriba/abajo o dcha/izq.
*/



//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst, nombre; int x, y; Direccion dir;
    cin >> inst;
    if (!cin) return false;
    Desierto desierto;
    while (inst != "FIN") {
        try {
            if (inst == "anyadir_torre") {
                cin >> nombre >> x >> y;
                desierto.anyadir_torre(nombre, x, y);
            }
            else if (inst == "eliminar_torre") {
                cin >> nombre;
                desierto.eliminar_torre(nombre);
            }
            else if (inst == "posicion") {
                cin >> nombre;
                auto [x, y] = desierto.posicion(nombre);
                cout << x << ' ' << y << '\n';
            }
            else if (inst == "torre_en_posicion") {
                cin >> x >> y;
                auto [hay, nombre] = desierto.torre_en_posicion(x, y);
                if (hay) cout << "SI " << nombre << '\n';
                else cout << "NO\n";
            }
            else {
                cin >> nombre >> dir;
                nombre = desierto.torre_mas_cercana(nombre, dir);
                cout << nombre << '\n';
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
        }
        cin >> inst;
    }
    cout << "---\n";
    return true;
}


int main() {
    while (resuelveCaso()) {}
    return 0;
}
