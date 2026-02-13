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
#include <list>
#include <unordered_map>

  // añade las librerías de la STL que necesites

using namespace std;

using cod_cliente = std::string;
using num_cola = int;


class Supermercado {

public:

    Supermercado() { }

    void setNumCajas(int num_cajas) {
        this->num_cajas = num_cajas;
    }

    void nuevo_cliente(const cod_cliente& c, const num_cola& n) {
        if (clientes.count(c)) {
            throw domain_error("Cliente duplicado");
        }
        if (n >= num_cajas || n < 0) {
            throw domain_error("Cola inexistente");
        }
        colas[n].push_back(c);
        auto it = colas[n].end();
        --it;
        clientes[c] = { n, it };
    }

    void cambiar_cola(const cod_cliente& c, const num_cola& cola) {
        if (cola >= num_cajas || cola < 0) {
            throw domain_error("Cola inexistente");
        }
        if (!clientes.count(c)) {
            throw domain_error("Cliente inexistente");
        }
        if (clientes[c].n != cola) {
            infoCliente& info_cliente = clientes[c];
            colas[info_cliente.n].erase(info_cliente.it);
            colas[cola].push_back(c);
            auto it = colas[cola].end();
            --it;
            clientes[c] = { cola, it };
        }
    }

    num_cola consultar_cliente(const cod_cliente& c) {
        if (!clientes.count(c)) {
            throw domain_error("Cliente inexistente");
        }
        return clientes[c].n;
    }

    int cuantos_en_cola(const num_cola& n) {
        if (n >= num_cajas || n < 0) {
            throw domain_error("Cola inexistente");
        }
        return colas[n].size();
    }

    list<cod_cliente> clientes_en_cola(const num_cola& n) {
        if (n >= num_cajas || n < 0) {
            throw domain_error("Cola inexistente");
        }
        list<cod_cliente> sol;
        for (cod_cliente c : colas[n]) {
            sol.push_front(c);
        }
        return sol;
    }
    

private:
    int num_cajas;
    struct infoCliente {
        num_cola n;
        list<cod_cliente>::iterator it;
    };
    unordered_map<num_cola, list<cod_cliente>> colas;
    unordered_map<cod_cliente, infoCliente> clientes;
};

//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

bool resuelveCaso() {
    int num_cajas; cin >> num_cajas;
    string inst; cin >> inst;
    if (!cin) return false;

    cod_cliente c; num_cola n;

    Supermercado sm;
    sm.setNumCajas(num_cajas);

    while (inst != "FIN") {
        try {
            if (inst == "nuevo_cliente") {
                cin >> c >> n;
                sm.nuevo_cliente(c, n);
            }
            else if (inst == "cambiar_cola") {
                cin >> c >> n;
                sm.cambiar_cola(c, n);
            }
            else if (inst == "consultar_cliente") {
                cin >> c;
                num_cola sol = sm.consultar_cliente(c);
                cout << "El cliente " << c << " esta en la cola " << sol << '\n';
            }
            else if (inst == "cuantos_en_cola") {
                cin >> n;
                int sol = sm.cuantos_en_cola(n);
                cout << "En la cola " << n << " hay " << sol << " clientes\n";
            }
            else if (inst == "clientes_en_cola") {
                cin >> n;
                list<cod_cliente> sol = sm.clientes_en_cola(n);
                cout << "En la cola " << n << " estan: ";
                for (cod_cliente c : sol) {
                    cout << c << ' ';
                }
                cout << '\n';
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
