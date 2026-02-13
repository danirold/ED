/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 *              Facultad de Informática
 *         Universidad Complutense de Madrid
 * ---------------------------------------------------
 */

 /*
  * Introduce el nombre y apellidos de los/as componentes del grupo:
  *
  * Estudiante 1: DANIEL ROLDAN SERRANO
  *
  */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <list>
#include <unordered_map>

using namespace std;

class CarnetPuntos {

public:

    CarnetPuntos() : mapa_puntos(16){}

    void nuevo(const string& DNI) {
        if (mapa_personas.count(DNI)) {
            throw domain_error("Conductor duplicado");
        }
        else {
            mapa_personas[DNI] = 15;
            mapa_puntos[15].push_back(DNI);
        }
    }

    void quitar(const string& DNI, const int& puntos) {
        if (!mapa_personas.count(DNI)) {
            throw domain_error("Conductor inexistente");
        }
        else {
            int puntos_antiguos = mapa_personas[DNI];
            mapa_puntos[puntos_antiguos].remove(DNI);
            int puntos_act = max(0, puntos_antiguos - puntos);
            mapa_personas[DNI] = puntos_act;
            mapa_puntos[puntos_act].push_back(DNI);
        }
    }

    int consultar(string DNI) const {
        if (!mapa_personas.count(DNI)) {
            throw domain_error("Conductor inexistente");
        }
        else {
            return mapa_personas.at(DNI);
        }
    }

    int cuantos_con_puntos(int puntos) const {
        if (puntos < 0 || puntos > 15) {
            throw domain_error("Puntos no validos");
        }
        else {
            return mapa_puntos[puntos].size();
        }
    }

private:
    unordered_map<string, int> mapa_personas;
    vector<list<string>> mapa_puntos;
};


bool resuelveCaso() {
    string operacion, DNI;
    int puntos;
    cin >> operacion;
    if (!cin)
        return false;

    CarnetPuntos CP;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo") {
                cin >> DNI;
                CP.nuevo(DNI);
            }
            else if (operacion == "cuantos_con_puntos") {
                cin >> puntos;
                int sol = CP.cuantos_con_puntos(puntos);
                cout << "Con " << puntos << " puntos hay " << sol << '\n';
            }
            else if (operacion == "quitar") {
                cin >> DNI >> puntos;
                CP.quitar(DNI, puntos);
            }
            else if (operacion == "consultar") {
                cin >> DNI;
                int sol = CP.consultar(DNI);
                cout << "Puntos de " << DNI << ": " << sol << '\n';
            }
        }
        catch (domain_error& e) {
            cout << "ERROR: " << e.what() << '\n';
        }
        cin >> operacion;
    }
    cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso()) {}
    return 0;
}
