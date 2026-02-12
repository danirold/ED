/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
  * contenidos entre las etiquetas <answer> y </answer>.
  * Toda modificación fuera de esas etiquetas no será corregida.
  */

  /*@ <answer>
   *  Estudiante 1: Sergio Martinez Olivera
   *  Estudiante 2: Daniel Roldan Serrano
   *@ </answer> */


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

const int MAX_RESERVAS = 50000;

/*@ <answer> */

class Teatro {
public:

    // Constructor de la clase
    // Inicializamos el vector de reservas para que tenga longitud MAX_RESERVAS
    // También inicializamos el atributo num_reservas a 0.
    Teatro() : reservas(MAX_RESERVAS), num_reservas(0) { }

    // realizar una nueva reserva, si es posible
    bool nueva_reserva(int inicio, int fin, string nombre) {//En el peor de los casos, cuando ind = 0, tiene O(num_reservas), debido al bucle for marcado con *
        bool sol = true;
        int ind = binarySearch(inicio, 0, num_reservas);
        if (ind == num_reservas - 1 && reservas[ind].inicio <= inicio && reservas[ind].fin >= inicio) sol = false;
        else if (inicio < reservas[ind].inicio&& reservas[ind].inicio <= fin) sol = false;
        else if (inicio < reservas[ind].inicio && reservas[ind].inicio > fin && ind != 0 && reservas[ind - 1].fin >= inicio) sol = false;
        else if (inicio == reservas[ind].inicio) sol = false;

        if (sol) {
            if (ind < num_reservas && reservas[ind].inicio > inicio) {
                for (int j = num_reservas; j > ind; --j) {//*
                    reservas[j] = reservas[j - 1];
                }
                reservas[ind].inicio = inicio;
                reservas[ind].fin = fin;
                reservas[ind].nombre = nombre;
            }
            else {
                reservas[num_reservas].inicio = inicio;
                reservas[num_reservas].fin = fin;
                reservas[num_reservas].nombre = nombre;
            }
            num_reservas++;
        }
        return sol;


    }

    int binarySearch(int num_butaca, int ini, int fin) const {//En todos los casos, el tamaño del vector sobre el que se realiza la busqueda es num_reservas, luego, tiene O(log(num_reservas))
        if (ini + 1 >= fin) return ini;
        else {
            int m = (ini + fin - 1) / 2;

            if (reservas[m].inicio > num_butaca) return binarySearch(num_butaca, ini, m + 1);
            else return binarySearch(num_butaca, m + 1, fin);
        }
    }

    // consultar quién tiene reservada una butaca
    string nombre_reserva(int num_butaca) const {//O(log(num_reservas)), debido a la busqueda binaria realizada, marcada con *
        string sol = "";
        int pos = binarySearch(num_butaca, 0, num_reservas);//*
        if ((pos == num_reservas - 1 || pos == 0) && reservas[pos].inicio <= num_butaca && reservas[pos].fin >= num_butaca) {
            sol = reservas[pos].nombre;
        }
        if (pos > 0 && reservas[pos - 1].inicio <= num_butaca && reservas[pos - 1].fin >= num_butaca) {
            sol = reservas[pos - 1].nombre;
        }
        return sol;
    }

private:
    struct Reserva {
        int inicio;
        int fin;
        string nombre;
    };

    vector<Reserva> reservas;
    int num_reservas;

};

bool tratar_caso() {
    int N, Q;
    cin >> N >> Q;

    if (N == 0 && Q == 0)
        return false;

    Teatro t;

    for (int i = 0; i < N; ++i) {
        int inicio, fin;
        string nombre;
        cin >> inicio >> fin >> nombre;
        if (t.nueva_reserva(inicio, fin, nombre))
            cout << '.';
        else
            cout << 'X';
    }

    cout << '\n';

    for (int i = 0; i < Q; ++i) {
        int num_butaca;
        cin >> num_butaca;
        auto nombre = t.nombre_reserva(num_butaca);
        if (nombre == "")
            cout << "LIBRE\n";
        else
            cout << nombre << "\n";
    }
    cout << "---\n";
    return true;
}

/*@ </answer> */

int main() {
    while (tratar_caso()) {}
    return 0;
}