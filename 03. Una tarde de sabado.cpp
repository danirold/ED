// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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

    Hora operator + (Hora const& p2) {
        if (this->getSegundos() + p2.segundos >= 60) {
            this->setMinutos(this->getMinutos() + 1);
            if (this->getMinutos() == 60) {
                this->setMinutos(0);
                this->setHoras(this->getHoras() + 1);
            }
        }
        this->setSegundos((this->getSegundos() + p2.segundos) % 60);
        if (this->getMinutos() + p2.minutos >= 60) {
            this->setHoras(this->getHoras() + 1);
        }
        this->setMinutos((this->getMinutos() + p2.minutos) % 60);
        this->setHoras(this->getHoras() + p2.horas);
        return Hora(this->getHoras(), this->getMinutos(), this->getSegundos());
    }
    bool operator == (Hora const& hora2) const {
        if (this->horas == hora2.horas && this->minutos == hora2.minutos && this->segundos == hora2.segundos) return true;
        else return false;
    }
};

class Pelicula {
private:
    Hora hora_inicio; 
    Hora duracion;
    string titulo;

public:
    Hora hora_final;
    Pelicula() {
        this->hora_inicio = Hora();
        this->duracion = Hora();
        this->hora_final = Hora();
        this->titulo = "";
    }

    Pelicula(Hora hora_inicio, Hora duracion, string nombre) {
        this->hora_inicio = hora_inicio;
        this->duracion = duracion;
        this->hora_final = hora_inicio;
        this->titulo = titulo;
    }

    void setHora_inicio(Hora hora_inicio) {
        this->hora_inicio = hora_inicio;
    }
    void setDuracion(Hora duracion) {
        this->duracion = duracion;
    }
    void setTitulo(string titulo) {
        this->titulo = titulo;
    }
    void setHoraFinal() {
        this->hora_final = this->hora_inicio + this->duracion;
    }

    Hora getHoraFinal() {
        return this->hora_final;
    }

    string getTitulo() {
        return this->titulo;
    }

    bool operator < (Pelicula const& p2) {
        if (this->hora_final == p2.hora_final) {
            return this->getTitulo() < p2.titulo;
        }
        return this->getHoraFinal() < p2.hora_final;
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
        << std::setfill('0') << std::setw(2) << hora.getSegundos();
    return out;
}

bool resuelveCaso() {
    int num_peliculas;
    cin >> num_peliculas;

    if (num_peliculas == 0)
        return false;

    vector<Pelicula> peliculas(num_peliculas);
    Hora hora_inicio; Hora duracion; string titulo;
    for (int i = 0; i < num_peliculas; ++i) {
        cin >> hora_inicio;
        peliculas[i].setHora_inicio(hora_inicio);
        cin >> duracion;
        peliculas[i].setDuracion(duracion);
        getline(cin,titulo);
        peliculas[i].setTitulo(titulo);
        peliculas[i].setHoraFinal();
    }

    sort(peliculas.begin(), peliculas.end());
    for (int i = 0; i < peliculas.size(); ++i) {
        cout << peliculas[i].hora_final << peliculas[i].getTitulo() << '\n';
    }

    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}