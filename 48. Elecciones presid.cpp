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
#include <unordered_map>
#include <map>

using namespace std;

class ConteoVotos {

public:
    void nuevo_estado(const string& nombre, int num_compromisarios) {
        if (estados.count(nombre)) {
            throw domain_error("Estado ya existente");
        }
        else {
            estados[nombre].num_compromisarios = num_compromisarios;
        }
    }

    void sumar_votos(const string& estado, const string& partido, int num_votos) {
        if (!estados.count(estado)) {
            throw domain_error("Estado no encontrado");
        }
        else {
            InfoEstado& info_estado = estados[estado];
            info_estado.partidos[partido] += num_votos;
            if (info_estado.ganador == "") {
                info_estado.ganador = partido;
                resultado[partido] += info_estado.num_compromisarios;
            }
            else {
                string ganador = estados[estado].ganador;
                if (info_estado.partidos[ganador] < info_estado.partidos[partido]) {
                    info_estado.ganador = partido;
                    resultado[ganador] -= info_estado.num_compromisarios;
                    if (resultado[ganador] == 0) {
                        resultado.erase(ganador);
                    }
                    resultado[partido] += info_estado.num_compromisarios;
                }
            }
        }
    }

    string ganador_en(const string& estado) const {
        if (!estados.count(estado)) {
            throw domain_error("Estado no encontrado");
        }
        else {
            string ganador = estados.at(estado).ganador;
            return ganador;
        }
    }

    vector<pair<string, int>> resultados() const {
        vector<pair<string, int>> sol;
        for (auto [clave, valor] : resultado) {
            sol.push_back({ clave, valor});
        }
        return sol;
    }

private: 
    struct InfoEstado {
        int num_compromisarios;
        string ganador;
        unordered_map<string, int> partidos;
    };

    unordered_map<string, InfoEstado> estados;
    map<string, int> resultado;
};


bool resuelveCaso() {
    string operacion, estado, partido;
    int compromisarios, votos;
    cin >> operacion;
    if (!cin)
        return false;

    ConteoVotos CV;

    while (operacion != "FIN") {
        try {
            if (operacion == "nuevo_estado") {
                cin >> estado >> compromisarios;
                CV.nuevo_estado(estado, compromisarios);
            }
            else if (operacion == "sumar_votos") {
                cin >> estado >> partido >> votos;
                CV.sumar_votos(estado, partido, votos);
            }
            else if (operacion == "ganador_en") {
                cin >> estado;
                auto ganador = CV.ganador_en(estado);
                cout << "Ganador en " << estado << ": " << ganador << '\n';
            }
            else if (operacion == "resultados") {
                for (auto [estado, compromisarios] : CV.resultados()) {
                    cout << estado << ' ' << compromisarios << '\n';
                }
            }
        }
        catch (domain_error& e) {
            cout << e.what() << '\n';
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
