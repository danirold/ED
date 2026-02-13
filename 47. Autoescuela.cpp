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
#include <map>
#include <stdexcept>

using namespace std;

class Autoescuela {

public:
    
    Autoescuela() {}

    void alta(const string& A, const string& P) {
        if (!mapa_alumnos.count(A)) {
            mapa_profes[P][A] = 0;
            mapa_alumnos[A].profesor = P;
            mapa_alumnos[A].puntos = 0;
        }
        else {
            tAlumno& infoAlum = mapa_alumnos[A];
            string profesor = infoAlum.profesor;
            int puntos = infoAlum.puntos;
            mapa_profes[profesor].erase(A);
            mapa_profes[P][A] = puntos;
            mapa_alumnos[A].profesor = P;
            mapa_alumnos[A].puntos = puntos;
        }
    }

    bool es_alumno(const string& A, const string& P) {
        if (!mapa_alumnos.count(A) || !mapa_profes.count(P) || mapa_alumnos[A].profesor != P) {
            return false;
        }
        else return true;
    }

    int puntuacion(const string& A) const {
        if (!mapa_alumnos.count(A)) {
            throw domain_error("ERROR");
        }
        return mapa_alumnos.at(A).puntos;
    }

    void actualizar(const string& A, const int& N) {
        if (!mapa_alumnos.count(A)) {
            throw domain_error("ERROR");
        }
        mapa_alumnos[A].puntos += N;
        string profesor = mapa_alumnos[A].profesor;
        mapa_profes[profesor][A] += N;
    }

    list<string> examen(const string& P, const int& N) {
        list<string> lista_aprob;
        for (auto [clave, valor] : mapa_profes[P]) {
            if (valor >= N) {
                lista_aprob.push_back(clave);
            }
        }
        return lista_aprob;
    }

    void aprobar(const string& A) {
        if (!mapa_alumnos.count(A)) {
            throw domain_error("ERROR");
        }
        string profesor = mapa_alumnos[A].profesor;
        mapa_profes[profesor].erase(A);
        mapa_alumnos.erase(A);
    }

private:
    struct tAlumno {
        int puntos;
        string profesor;
    };

    unordered_map<string, map<string, int>> mapa_profes;
    unordered_map<string, tAlumno> mapa_alumnos;
};


bool resuelveCaso() {
    string alumno, profesor, operacion;
    int puntos;
    cin >> operacion;
    if (!cin)
        return false;

    Autoescuela autoescuela;

    while (operacion != "FIN") {
        try {
            if (operacion == "alta") {
                cin >> alumno >> profesor;
                autoescuela.alta(alumno, profesor);
            }
            else if (operacion == "es_alumno") {
                cin >> alumno >> profesor;
                bool sol = autoescuela.es_alumno(alumno, profesor);
                if (sol) {
                    cout << alumno << " es alumno de " << profesor << '\n';
                }
                else cout << alumno << " no es alumno de " << profesor << '\n';
            }
            else if (operacion == "puntuacion") {
                cin >> alumno;
                int sol = autoescuela.puntuacion(alumno);
                cout << "Puntuacion de " << alumno << ": " << sol << '\n';
            }
            else if (operacion == "actualizar") {
                cin >> alumno >> puntos;
                autoescuela.actualizar(alumno, puntos);
            }
            else if (operacion == "examen") {
                cin >> profesor >> puntos;
                list<string> sol = autoescuela.examen(profesor, puntos);
                cout << "Alumnos de " << profesor << " a examen:\n";
                for (string s : sol) {
                    cout << s << '\n';
                }
            }
            else if (operacion == "aprobar") {
                cin >> alumno;
                autoescuela.aprobar(alumno);
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
