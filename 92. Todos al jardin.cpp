// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <deque>

using namespace std;

struct tInfoEmpleado {
    int desp_pref;
    bool jefe;
};

bool resuelveCaso() {
    int max_desp, num_emp, num_direc;
    cin >> max_desp >> num_emp >> num_direc;

    if (max_desp == 0 && num_emp == 0 && num_direc == 0)
        return false;

    map<int, deque<tInfoEmpleado> > despachos;
    int i = 0;
    int despacho;
    while (i < num_emp) {
        cin >> despacho;
        if (despachos[despacho].size() < max_desp) {
            tInfoEmpleado t;
            t.desp_pref = despacho;
            t.jefe = false;
            despachos[despacho].push_back(t);
        }
        else {
            tInfoEmpleado t = despachos[despacho].front();
            despachos[despacho].pop_front();
            tInfoEmpleado t2;
            t2.desp_pref = despacho;
            t2.jefe = false;
            despachos[despacho].push_back(t2);
            int j = despacho + 1;
            map<int, deque<tInfoEmpleado> >::iterator it = despachos.find(despacho + 1);
            it++;
            while (it->second.size() >= max_desp) {
                it++;
            }

            despachos[it->first].push_back(t);
        }
        ++i;
    }

    i = 0;
    while (i < num_direc) {
        cin >> despacho;
        if (despachos[despacho].size() == 0) {
            tInfoEmpleado t;
            t.desp_pref = despacho;
            t.jefe = true;
            despachos[despacho].push_back(t);
        }
        else {
            deque<tInfoEmpleado> d = despachos[despacho];
            despachos[despacho].clear();
            tInfoEmpleado t;
            t.desp_pref = despacho;
            t.jefe = true;
            despachos[despacho].push_back(t);
            for (tInfoEmpleado t : d) {
                map<int, deque<tInfoEmpleado> >::iterator it = despachos.find(despacho + 1);
                it++;
                while (it->second.size() >= max_desp) {
                    it++;
                }
                despachos[it->first].push_back(t);
            }
        }
    }

    for (pair<int, deque<tInfoEmpleado> > par : despachos) {
        if (par.second.front().jefe) {
            cout << par.first << " JEFE\n";
        }
        else {
            cout << par.first << " " << par.second.size() << '\n';
        }
    }

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
