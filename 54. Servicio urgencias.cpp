/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Daniel Roldan Serrano


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */


#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>

using namespace std;

// Elige el tipo representante adecuado para el TAD e implementa
// sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>
using paciente = std::string;
using gravedad = int;

class Urgencias {
public:

    void nuevo_paciente(const paciente& p, const gravedad& g) {
        if (pacientes.count(p)) {
            throw domain_error("Paciente repetido");
        }
        if (g < 1 || g > 3) {
            throw domain_error("Gravedad incorrecta");
        }
        listas_espera[g].push_back(p);
        auto it = listas_espera[g].end();
        --it;
        pacientes[p] = { g, it };
    }

    gravedad gravedad_actual(const paciente& p) {
        if (!pacientes.count(p)) {
            throw domain_error("Paciente inexistente");
        }
        return pacientes[p].g;
    }

    paciente siguiente() {
        if (listas_espera[1].empty() && listas_espera[2].empty() && listas_espera[3].empty()) {
            throw domain_error("No hay pacientes");
        }
        if (!listas_espera[3].empty()) {
            paciente p = listas_espera[3].front();
            listas_espera[3].erase(pacientes[p].it);
            pacientes.erase(p);
            return p;
        }
        else if (listas_espera[3].empty() && !listas_espera[2].empty()) {
            paciente p = listas_espera[2].front();
            listas_espera[2].erase(pacientes[p].it);
            pacientes.erase(p);
            return p;
        }
        else {
            paciente p = listas_espera[1].front();
            listas_espera[1].erase(pacientes[p].it);
            pacientes.erase(p);
            return p;
        }
    }

    void mejora(paciente p) {
        if (!pacientes.count(p)) {
            throw domain_error("Paciente inexistente");
        }
        int gravedad_paciente = gravedad_actual(p);
        if (gravedad_paciente == 1) {
            pac_recuperados.insert(p);
            listas_espera[1].erase(pacientes[p].it);
            pacientes.erase(p);
        }
        else if (gravedad_paciente == 2) {
            listas_espera[2].erase(pacientes[p].it);
            listas_espera[1].push_front(p);
            auto it = listas_espera[1].begin();
            pacientes[p] = { 1, it };
        }
        else {
            listas_espera[3].erase(pacientes[p].it);
            listas_espera[2].push_front(p);
            auto it = listas_espera[2].begin();
            pacientes[p] = { 2, it };
        }
    }

    list<paciente> recuperados() {
        list<paciente> recuperad;
        for (paciente p : pac_recuperados) {
            recuperad.push_back(p);
        }
        return recuperad;
    }

private:

    struct infoPaciente {
        gravedad g;
        list<paciente>::iterator it;
    };

    unordered_map<paciente, infoPaciente> pacientes;
    unordered_map<gravedad, list<paciente>> listas_espera;
    set<paciente> pac_recuperados;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    std::string paciente, orden;
    int gravedad;
    std::cin >> orden;
    if (!std::cin)
        return false;

    Urgencias urg;

    while (orden != "FIN") {
        try {
            if (orden == "nuevo_paciente") {
                cin >> paciente >> gravedad;
                urg.nuevo_paciente(paciente, gravedad);
            }
            else if (orden == "gravedad_actual") {
                cin >> paciente;
                int gravedad_paciente = urg.gravedad_actual(paciente);
                cout << "La gravedad de " << paciente << " es " << gravedad_paciente << '\n';
            }
            else if (orden == "siguiente") {
                string siguiente = urg.siguiente();
                cout << "Siguiente paciente: " << siguiente << '\n';
            }
            else if (orden == "mejora") {
                cin >> paciente;
                urg.mejora(paciente);
            }
            else if (orden == "recuperados") {
                list<string> recuperados = urg.recuperados();
                cout << "Lista de recuperados: ";
                for (string s : recuperados) {
                    cout << s << ' ';
                }
                cout << '\n';
            }
        }
        catch (std::domain_error& e) {
            std::cout << "ERROR: " << e.what() << '\n';
        }
        std::cin >> orden;
    }
    std::cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}