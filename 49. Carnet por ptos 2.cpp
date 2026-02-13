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

    CarnetPuntos() : mapa_puntos(16) {}

    void nuevo(const string& DNI) {
        if (mapa_personas.count(DNI)) {
            throw domain_error("Conductor duplicado");
        }
        else {
            mapa_puntos[15].push_back(DNI);
            auto it = mapa_puntos[15].end();
            --it;
            mapa_personas[DNI] = { 15, it };
        }
    }

    void quitar(const string& DNI, const int& puntos) {
        if (!mapa_personas.count(DNI)) {
            throw domain_error("Conductor inexistente");
        }
        if (puntos < 0 || puntos > 15) {
            throw domain_error("Puntos no validos");
        }
        else {
            infoPersona& info_persona = mapa_personas[DNI];
            int puntos_antiguos = info_persona.puntos;
            mapa_puntos[puntos_antiguos].erase(info_persona.it);
            if (puntos >= puntos_antiguos) {
                mapa_puntos[0].push_back(DNI);
                auto it = mapa_puntos[0].end();
                --it;
                mapa_personas[DNI] = { 0, it };
            }
            else {
                int puntos_act = puntos_antiguos - puntos;
                mapa_puntos[puntos_act].push_back(DNI);
                auto it = mapa_puntos[puntos_act].end();
                --it;
                mapa_personas[DNI] = { puntos_act, it };
            }
        }
    }

    void recuperar(const string& DNI, const int& puntos) {
        if (!mapa_personas.count(DNI)) {
            throw domain_error("Conductor inexistente");
        }
        else {
            infoPersona& info_persona = mapa_personas[DNI];
            int puntos_antiguos = info_persona.puntos;
            mapa_puntos[puntos_antiguos].erase(info_persona.it);
            if (puntos + puntos_antiguos >= 15) {
                mapa_puntos[15].push_back(DNI);
                auto it = mapa_puntos[15].end();
                --it;
                mapa_personas[DNI] = { 15, it };
            }
            else {
                int puntos_act = puntos_antiguos + puntos;
                mapa_puntos[puntos_act].push_back(DNI);
                auto it = mapa_puntos[puntos_act].end();
                --it;
                mapa_personas[DNI] = { puntos_act, it };
            }
        }
    }

    int consultar(string DNI) const {
        if (!mapa_personas.count(DNI)) {
            throw domain_error("Conductor inexistente");
        }
        else {
            return mapa_personas.at(DNI).puntos;
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

    list<string> lista_por_puntos(int puntos) {
        if (puntos < 0 || puntos > 15) {
            throw domain_error("Puntos no validos");
        }
        list<string> sol;
        for (string s : mapa_puntos[puntos]) {
            sol.push_front(s);
        }
        return sol;
    }

private:
    struct infoPersona {
        int puntos;
        list<string>::iterator it;
    };
    unordered_map<string, infoPersona> mapa_personas;
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
            else if (operacion == "recuperar") {
                cin >> DNI >> puntos;
                CP.recuperar(DNI, puntos);
            }
            else if (operacion == "consultar") {
                cin >> DNI;
                int sol = CP.consultar(DNI);
                cout << "Puntos de " << DNI << ": " << sol << '\n';
            }
            else if (operacion == "lista_por_puntos") {
                cin >> puntos;
                list<string> sol = CP.lista_por_puntos(puntos);
                cout << "Tienen " << puntos << " puntos:";
                for (string s : sol) {
                    cout << ' ' << s;
                }
                cout << '\n';
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
