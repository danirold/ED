#include <iostream>
#include <fstream>
#include <list>
#include <string>
using namespace std;

bool resuelveCaso() {
    string linea;
    getline(cin, linea);
    if (!cin) return false;

    list<char> l;
    auto it = l.begin();

    for (int i = 0; i < linea.size(); i++) {
        if (linea[i] == '-') {
            it = l.begin();
        }
        else if (linea[i] == '+') {
            it = l.end();

        }
        else if (linea[i] == '*') {
            if (it != l.end()) {
                ++it;
            }
        }
        else if (linea[i] == '3') {
            if (it != l.end()) {
                it = l.erase(it);
            }
        }
        else {
            it = l.insert(it, linea[i]);
            ++it;
        }
    }

    while (!l.empty()) {
        cout << l.front();
        l.pop_front();
    }

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso()) {}
    return 0;
}