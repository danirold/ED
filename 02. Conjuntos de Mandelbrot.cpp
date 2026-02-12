// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

using namespace std;

class Complejo {
private:
    double parte_real;
    double parte_imaginaria;

public:
    Complejo() {
        this->parte_real = 0;
        this->parte_imaginaria = 0;
    }

    Complejo(double parte_real, double parte_imaginaria) {
        this->parte_real = parte_real;
        this->parte_imaginaria = parte_imaginaria;
    }

    Complejo operator + (Complejo const& num) {
        return Complejo(this->parte_real + num.parte_real, this->parte_imaginaria + num.parte_imaginaria);
    }

    Complejo operator * (Complejo const& num) {
        double parte_real = (this->parte_real * num.parte_real) - (this->parte_imaginaria * num.parte_imaginaria);
        double parte_imaginaria = (this->parte_real * num.parte_imaginaria) + (this->parte_imaginaria * num.parte_real);
        return Complejo(parte_real, parte_imaginaria);
    }

    double modulo() const {
        return sqrt(this->parte_real * this->parte_real + this->parte_imaginaria * this->parte_imaginaria);
    }
};

void resuelveCaso() {
    double parte_real; double parte_imaginaria;
    cin >> parte_real >> parte_imaginaria;
    Complejo num_complejo(parte_real, parte_imaginaria);
    int num_recurrencia; cin >> num_recurrencia;
    bool parar_recurrencia = false;
    Complejo recurrencia;
    for (int i = 0; i < num_recurrencia && !parar_recurrencia; ++i) {
        recurrencia = recurrencia * recurrencia + num_complejo;
        if (recurrencia.modulo() > 2) parar_recurrencia = true;

    }
    if (parar_recurrencia) cout << "NO\n";
    else cout << "SI\n";
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
