// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stack>

using namespace std;


bool resuelveCaso() {
    stack <char> pila;
    string linea; 
    getline(cin, linea);


    if (!std::cin)
        return false;

    int i = 0; bool correct = true;
    while (i <= linea.size() && correct) {
        if (linea[i] == '(' || linea[i] == '[' || linea[i] == '{') {
            pila.push(linea[i]);
        }
        else if ((linea[i] == ')' || linea[i] == ']' || linea[i] == '}') && pila.empty()) {
            correct = false;
        }
        else if ((linea[i] == ')' && pila.top() == '(') || (linea[i] == ']' && pila.top() == '[') || (linea[i] == '}' && pila.top() == '{')) {
            pila.pop();
        }
        else if ((linea[i] == ')' && pila.top() != '(') || (linea[i] == ']' && pila.top() != '[') || (linea[i] == '}' && pila.top() != '{')) {
            correct = false;
        }
        ++i;
    }
    
    if (correct && pila.empty()) cout << "SI\n";
    else cout << "NO\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}