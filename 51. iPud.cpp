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
#include <unordered_set>


using namespace std;

class iPud {

public:

    iPud() : lista_reprod(), ya_reprod() {
        duracion_lista = 0;
    }

    void addSong(string S, string A, int D) {
        if (mapa_canciones.count(S)) {
            throw domain_error("addSong");
        }
        mapa_canciones[S] = { A, D, false};
    }

    void addToPlaylist(string S) {
        if (!mapa_canciones.count(S) || mapa_canciones[S].esta) {
            throw domain_error("addToPlayList");
        }
        lista_reprod.push_back(S);
        auto it = lista_reprod.end();
        --it;
        mapa_canciones[S].it_lista_reprod = it;
        mapa_canciones[S].esta = true;
        duracion_lista += mapa_canciones[S].duracion;
    }

    string current() {
        if (lista_reprod.empty()) {
            throw domain_error("current");
        }
        return lista_reprod.front();
    }

    void play() {
        if (lista_reprod.empty()) {
            throw domain_error("No hay canciones en la lista");
        }
        string S = current();
        infoSong& info = mapa_canciones[S];
        lista_reprod.erase(info.it_lista_reprod);
        info.it_lista_reprod = lista_reprod.end();
        info.esta = false;
        duracion_lista -= info.duracion;
        ya_reprod.push_back(S);
        auto it = ya_reprod.end();
        it--;
        info.it_ya_reprod = it;
    }

    int totalTime() {
        return duracion_lista;
    }

    vector<string> recent(int N) {
        if (ya_reprod.empty()) {
            throw domain_error("No hay canciones en la lista");
        }
        vector<string> sol;
        unordered_set<string> canciones;
        if (ya_reprod.size() <= N) {
            auto it = ya_reprod.end();
            it--;
            while (it != ya_reprod.begin()) {
                string song = *it;
                if (!canciones.count(song)) {
                    sol.push_back(song);
                    canciones.insert(song);
                }
                it--;
            }
            string song = *it;
            if (!canciones.count(song)) {
                sol.push_back(song);
                canciones.insert(song);
            }
        }
        else {
            auto it = ya_reprod.end();
            it--;
            int i = 0;
            while (i < N) {
                string song = *it;
                if (!canciones.count(song)) {
                    sol.push_back(song);
                    canciones.insert(song);
                }
                it--;
            }
        }
        return sol;
    }

    void deleteSong(string S) {
        if (!mapa_canciones.count(S)) {
            throw domain_error("deleteSong");
        }
        else {
            if (mapa_canciones[S].it_lista_reprod != lista_reprod.end()) {
                lista_reprod.erase(mapa_canciones[S].it_lista_reprod);
            }
            ya_reprod.erase(mapa_canciones[S].it_ya_reprod);
            mapa_canciones.erase(S);
        }
    }

private:
    int duracion_lista;

    struct infoSong {
        string artista;
        int duracion;
        bool esta;
        list<string>::iterator it_lista_reprod;
        list<string>::iterator it_ya_reprod;
    };

    unordered_map<string, infoSong> mapa_canciones;
    list<string> lista_reprod;
    list<string> ya_reprod;

};


bool resuelveCaso() {
    string operacion, cancion, artista;
    int duracion, N;
    cin >> operacion;
    if (!cin)
        return false;

    iPud iPud;

    while (operacion != "FIN") {
        try {
            if (operacion == "addSong") {
                cin >> cancion >> artista >> duracion;
                iPud.addSong(cancion, artista, duracion);
            }
            else if (operacion == "addToPlaylist") {
                cin >> cancion;
                iPud.addToPlaylist(cancion);
            }
            else if (operacion == "current") {
                string current = iPud.current();
                cout << current << '\n';
            }
            else if (operacion == "play") {
                try {
                    string current = iPud.current();
                    iPud.play();
                    cout << "Sonando " << current << '\n';
                }
                catch (domain_error& e) {
                    cout << "No hay canciones en la lista\n";
                }
            }
            else if (operacion == "totalTime") {
                int totalTime = iPud.totalTime();
                cout << "Tiempo total " << totalTime << '\n';
            }
            else if (operacion == "recent") {
                cin >> N;
                vector<string> v = iPud.recent(N);
                cout << "Las " << v.size() << " mas recientes\n";
                for (string s : v) {
                    cout << "    " << s << '\n';
                }
            }
            else if (operacion == "deleteSong") {
                cin >> cancion;
                iPud.deleteSong(cancion);
            }
        }
        catch (domain_error& e) {
            cout << "ERROR " << e.what() << '\n';
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
