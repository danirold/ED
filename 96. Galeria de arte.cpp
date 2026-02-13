/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Nombre y apellidos: Daniel Roldan Serrano

  Da una explicación de la solución y justifica su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>

  // añade las librerías de la STL que necesites

using namespace std;

using artista = std::string;
using obra = std::string;

// Elige el tipo representante adecuado para el TAD GaleriaArte e
// implementa sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente. Justifica la elección de los tipos y el
// coste de las operaciones.
//@ <answer>

class GaleriaArte {

public:

    GaleriaArte() { }

    void nueva_obra(const obra& c, const artista& a, int p) {
        if (obras.count(c)) {
            throw invalid_argument("Obra ya en la galeria");
        }
        obras_orden_antig.push_back(c);
        auto it = obras_orden_antig.end();
        --it;
        obras[c] = { a, p, it };
    }

    void venta_obra(const obra& c) {
        if (!obras.count(c)) {
            throw invalid_argument("Obra no existente");
        }
        InfoObra info_obra = obras[c];
        obras_orden_antig.erase(info_obra.it);
        venta_p_artist[info_obra.a] += info_obra.precio;
        if (venta_p_artist[info_obra.a] > precio_maxima_venta) {
            mas_venden.clear();
            mas_venden.insert(info_obra.a);
            precio_maxima_venta = venta_p_artist[info_obra.a];
        }
        else if (venta_p_artist[info_obra.a] == precio_maxima_venta) {
            mas_venden.insert(info_obra.a);
        }
        obras.erase(c);
    }

    vector<artista> mas_vendidos() const {
        vector<artista> sol;
        for (artista a : mas_venden) {
            sol.push_back(a);
        }
        return sol;
    }

    vector<obra> obras_por_antiguedad(int k) const {
        vector<obra> sol;
        if (k >= obras_orden_antig.size()) {
            for (obra o : obras_orden_antig) {
                sol.push_back(o);
            }
        }
        else {
            auto it = obras_orden_antig.begin();
            for (int i = 0; i < k; ++i) {
                sol.push_back(*it);
                ++it;
            }
        }
        return sol;
    }

private:
    struct InfoObra {
        artista a;
        int precio;
        list<obra>::iterator it;
    };
    unordered_map<obra, InfoObra> obras;
    list<obra> obras_orden_antig;
    unordered_map<artista, int> venta_p_artist;
    set<artista> mas_venden;
    int precio_maxima_venta = 0;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    string inst;
    cin >> inst;
    if (!cin) return false;
    GaleriaArte galeria;
    while (inst != "FIN") {
        try {
            if (inst == "nueva_obra") {
                obra c; artista a; int p;
                cin >> c >> a >> p;
                galeria.nueva_obra(c, a, p);
            }
            else if (inst == "venta_obra") {
                obra c;
                cin >> c;
                galeria.venta_obra(c);
            }
            else if (inst == "mas_vendidos") {
                auto vendidos = galeria.mas_vendidos();
                cout << "Los artistas que mas han vendido son:\n";
                for (auto& a : vendidos) {
                    cout << a << '\n';
                }
            }
            else if (inst == "obras_por_antiguedad") {
                int k;
                cin >> k;
                auto obras = galeria.obras_por_antiguedad(k);
                cout << "Obras mas antiguas en la galeria:\n";
                for (auto& c : obras) {
                    cout << c << '\n';
                }
            }
        }
        catch (exception& e) {
            cout << "ERROR: " << e.what() << '\n';
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
