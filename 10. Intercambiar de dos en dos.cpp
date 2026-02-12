// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    Node* head;
    int num_elems;

public:
    ListLinkedDouble() {
        head = new Node;
        head->next = nullptr;
        head->prev = nullptr;
        num_elems = 0;
    }

    int size() const { 
        return num_elems; 
    }

    void push_back(const int& elem) {
        Node* last = last_node();
        Node* new_node = new Node{ elem, nullptr, last };
        last->next = new_node;
    }

    Node* last_node() const;
    void swap2by2();
    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    void setNum_Elems(int num_elems) {
        this->num_elems = num_elems;
    }
};

ListLinkedDouble::Node* ListLinkedDouble::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current-> next != nullptr) {
        current = current-> next;
    }
    return current;
}

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

void ListLinkedDouble::swap2by2() {
    if (num_elems != 1) {
        int i = 0;
        Node* previous = head->next;
        while (i < num_elems / 2) {
            Node* current = previous->next;
            if (i == num_elems / 2 - 1) {
                Node* aux = current->next;
                current->prev = previous->prev;
                previous->prev->next = current;
                previous->prev = current;
                current->next = previous;
                if (num_elems % 2 == 0) {
                    previous->next = nullptr;
                }
                else previous->next = aux;

            }
            else {
                Node* aux = current->next;
                current->next = previous;
                current->prev = previous->prev;
                previous->prev->next = current;
                previous->prev = current;
                previous->next = aux;
                aux->prev = previous;
                previous = aux;
            }
            ++i;
        }
    }
}

bool resuelveCaso() {
    int n; cin >> n;

    if (n == 0)
        return false;

    ListLinkedDouble lista;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> valor;
        lista.push_back(valor);
    }

    lista.setNum_Elems(n);

    lista.swap2by2();

    lista.display();

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}
