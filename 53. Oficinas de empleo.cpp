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

using namespace std;

// Elige el tipo representante adecuado para el TAD e implementa
// sus operaciones. Puedes añadir métodos o funciones privadas
// si lo consideras conveniente.
//@ <answer>
using empleo = std::string;
using persona = std::string;

class OficinaEmpleo {
public:

    void altaOficina(const persona& p, const empleo& e) {
        if (!empleos.count(e)) {
            list<string> personas;
            empleos.insert({ e, personas });
        }
        if (!personas.count(p) || personas.count(p) && !personas[p].count(e)) {
            empleos[e].push_back(p);
            auto it = empleos[e].end();
            --it;
            personas[p][e] = it;
        }
    }

    persona ofertaEmpleo(const empleo& e) {
        if (!empleos.count(e) || empleos[e].empty()) {
            throw domain_error("No existen personas apuntadas a este empleo");
        }
        string sol = empleos[e].front();
        for (auto [clave, valor] : personas.at(sol)) {
            empleos[clave].erase(valor);
        }
        if (empleos[e].empty()) {
            empleos.erase(e);
        }
        personas.erase(sol);
        return sol;
    }

    vector<empleo> listadoEmpleos(const persona& p) {
        if (!personas.count(p)) {
            throw domain_error("Persona inexistente");
        }
        vector<string> listado_empleos;
        for (auto [clave, valor] : personas[p]) {
            listado_empleos.push_back(clave);
        }
        return listado_empleos;
    }


private:
    unordered_map<empleo, list<persona>> empleos;
    unordered_map<persona, map<empleo, list<persona>::iterator>> personas;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    std::string orden, empleo, persona;
    std::cin >> orden;
    if (!std::cin)
        return false;

    OficinaEmpleo oe;

    while (orden != "FIN") {
        try {
            if (orden == "altaOficina") {
                cin >> persona >> empleo;
                oe.altaOficina(persona, empleo);
            }
            else if (orden == "ofertaEmpleo") {
                cin >> empleo;
                string persona_selec = oe.ofertaEmpleo(empleo);
                cout << empleo << ": " << persona_selec << '\n';
            }
            else if (orden == "listadoEmpleos") {
                cin >> persona;
                vector<string> listado_empleos = oe.listadoEmpleos(persona);
                cout << persona << ": ";
                for (string s : listado_empleos) {
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