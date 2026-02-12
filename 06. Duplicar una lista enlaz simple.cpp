// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
public:
    ListLinkedSingle() : head(nullptr) { }
    void push_back(const int& elem);
    void duplicate();
    void display() const;
};

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node{ elem, nullptr };
    if (head == nullptr) {
        head = new_node;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void ListLinkedSingle::duplicate() {
    Node* current = head;
    while (current != nullptr) {
        Node* a_duplicar = new Node{current->value, current->next};
        current->next = a_duplicar;
        current = a_duplicar->next;
    }
}

void ListLinkedSingle::display() const {
    cout << "[";
    if (head != nullptr) {
        cout << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            cout << ", " << current->value;
            current = current->next;
        }
    }
    cout << "]";
}

void resuelveCaso() {
    ListLinkedSingle lista;
    int valor;
    cin >> valor;
    while (valor != 0) {
        lista.push_back(valor);
        cin >> valor;
    }
    lista.duplicate();
    lista.display();
    cout << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
