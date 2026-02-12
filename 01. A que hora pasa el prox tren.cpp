// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

class Hora {
    int horas;
    int minutos;
    int segundos;

public:
    Hora() {
        this->horas = 0;
        this->minutos = 0;
        this->segundos = 0;
    }

    Hora(int horas, int minutos, int segundos) {
        this->horas = horas;
        this->minutos = minutos;
        this->segundos = segundos;
    }

    bool operator < (Hora const& hora2) const {
        if (this->horas < hora2.horas) return true;
        else if (this->horas == hora2.horas && this->minutos < hora2.minutos) return true;
        else if (this->horas == hora2.horas && this->minutos == hora2.minutos && this->segundos < hora2.segundos) return true;
        else return false;
    }
    void setHoras(int horas) {
        this->horas = horas;
    }
    void setMinutos(int minutos) {
        this->minutos = minutos;
    }
    void setSegundos(int segundos) {
        this->segundos = segundos;
    }
    int getHoras() {
        return this->horas;
    }
    int getMinutos() {
        return this->minutos;
    }
    int getSegundos() {
        return this->segundos;
    }
};

istream& operator >> (istream& in, Hora& h) {
    char aux; int a;
    in >> a;
    h.setHoras(a);
    in >> aux >> a;
    h.setMinutos(a);
    in >> aux >> a;
    h.setSegundos(a);
    return in;
}

ostream& operator << (ostream& out, Hora& hora) {
    out << std::setfill('0') << std::setw(2) << hora.getHoras() << ":" 
        << std::setfill('0') << std::setw(2) << hora.getMinutos() << ":" 
        << std::setfill('0') << std::setw(2) << hora.getSegundos() << '\n';
    return out;
}

int resolver(vector<Hora> const& horas_trenes, int ini, int fin, Hora hora_requerida) {
    if (ini + 1 == fin && !(horas_trenes[ini] < hora_requerida)) return ini;
    else if (ini + 1 == fin) return -1;
    else {
        int m = (ini + fin - 1) / 2;
        if (horas_trenes[m] < hora_requerida) return resolver(horas_trenes, m + 1, fin, hora_requerida);
        else return resolver(horas_trenes, ini, m + 1, hora_requerida);
    }
}

bool resuelveCaso() {
    int num_trenes; int num_horas;
    cin >> num_trenes >> num_horas;

    if (num_trenes == 0 && num_horas == 0)
        return false;

    vector<Hora> horas_trenes(num_trenes);
    for (int i = 0; i < num_trenes; ++i) cin >> horas_trenes[i];

    Hora hora_requerida;
    for (int i = 0; i < num_horas; ++i) {
        cin >> hora_requerida;
        if (resolver(horas_trenes, 0, num_trenes, hora_requerida) == -1) cout << "NO\n";
        else cout << horas_trenes[resolver(horas_trenes, 0, num_trenes, hora_requerida)];
    }

    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}