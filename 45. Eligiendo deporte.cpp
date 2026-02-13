/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: DANIEL ROLDAN SERRANO
  Estudiante 2: SERGIO MARTINEZ OLIVERA


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

// Implementa a continuación la función que resuelve un caso de
// prueba. Puedes utilizar otras funciones auxiliares, pon su
// implementación debajo de la etiqueta <answer>.
//@ <answer>

/*
Utilizamos las siguientes estructuras de datos. Un unordered_map<string,int> que almacena los deportes (claves)
con su numero de participantes (valor). Y un unordered_map<string,unordered_set<string>> que almacena los participantes (clave)
y un conjunto de los deportes que practica cada uno (valor).
Hay dos casos a destacar en la lectura de los participantes:
- Cuando un participante repite el mismo deporte no se hace nada
- Cuando un participante hace mas de un deporte, al leer este segundo deporte, restamos uno al numero de participantes del deporte en 
el que ya se habia anadido. Y a partir del tercero, ya no se hace nada.
Luego, para cumplir con las condiciones de salida que nos piden (orden especial), creamos un vector de tSalidas (indicado abajo) copiando los elementos 
de mapa_deportes y lo ordenamos mediante una expresion lambda en la funcion sort.

Respecto al coste, seria O(max(m * n, m log m)), siendo m el numero de deportes, ya que,llamando n al numero de participantes del deporte con más participantes y m al numero de deportes, el coste amortizado del while es m * n, y luego ordenar el vector
tiene coste m log m.
*/

//Utilizamos este struct para ordenar la salida
struct tSalida {
	string deporte;
	int num_partic;
};

bool resuelveCaso() {
	string deporte; cin >> deporte;
	if (!std::cin)
		return false;

	unordered_map<string, int> mapa_deportes;
	unordered_map<string, unordered_set<string>> mapa_participantes;

	while (deporte != "_FIN_") {
		mapa_deportes[deporte] = 0;
		string participante; cin >> participante;
		while (islower(participante[0])) {
			if (!mapa_participantes.count(participante)) {
				mapa_participantes[participante].insert(deporte);
				mapa_deportes[deporte]++;
			}
			else {
				if (mapa_participantes[participante].size() >= 2) {
					mapa_participantes[participante].insert(deporte);
				}
				else {
					if (!mapa_participantes[participante].count(deporte)) {
						mapa_deportes[*mapa_participantes[participante].begin()]--;
						mapa_participantes[participante].insert(deporte);
					}
				}
			}
			cin >> participante;
		}
		deporte = participante;
	}

	vector<tSalida> salida;
	for (auto [clave, valor] : mapa_deportes) {
		tSalida salida1 = { clave, valor };
		salida.push_back(salida1);
	}
	sort(salida.begin(), salida.end(), [](tSalida& deporte1, tSalida& deporte2) {
		if (deporte1.num_partic < deporte2.num_partic) {
			return false;
		}
		else if (deporte1.num_partic > deporte2.num_partic) {
			return true;
		}
		else {
			return deporte1.deporte < deporte2.deporte;
		}
	});

	for (int i = 0; i < salida.size(); ++i) {
		cout << salida[i].deporte << ' ' << salida[i].num_partic << '\n';
	}

	cout << "---\n";
	return true;
}


//@ </answer>
// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

int main() {
	while (resuelveCaso());
	return 0;
}
