// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class ListLinkedDouble {
private:
    struct Node {
        int value;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* last;
    int num_elems;

public:
    ListLinkedDouble() {
        head = new Node;
        head->next = nullptr;
        head->prev = nullptr;
        last = head;
        num_elems = 0;
    }

    void push_back(const int& elem) {
        Node* new_node = new Node{ elem, nullptr, last };
        last->next = new_node;
        this->last = new_node;
        ++num_elems;
    }

    void zip(ListLinkedDouble& other);
    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }
};

void ListLinkedDouble::display(std::ostream& out) const {
    out << "[";
    if (head->next != nullptr) {
        out << head->next->value;
        Node* current = head->next->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

void ListLinkedDouble::zip(ListLinkedDouble& other) {
    if (other.head->next != nullptr) {
        if (head->next == nullptr) {
            head->next = other.head->next;
            other.head->next->prev = head;
            this->last = other.last;
        }
        else {
            Node* current = head->next;
            Node* current2 = other.head->next;
            while (current->next != nullptr && current2 != nullptr) {
                Node* aux2 = current2->next;
                Node* aux = current->next;
                current->next = current2;
                current2->next = aux;
                current2->prev = current;
                aux->prev = current2;
                current = aux;
                current2 = aux2;
            }
            if (current2 != nullptr) {
                current->next = current2;
                current2->prev = current;
                this->last = other.last;
            }
        }
    }
    other.head->next = nullptr;
    other.last = other.head;
    num_elems += other.num_elems;
    other.num_elems = 0;
}

void resuelveCaso() {
    int n; cin >> n;

    ListLinkedDouble lista;
    int valor;
    for (int i = 0; i < n; ++i) {
        cin >> valor;
        lista.push_back(valor);
    }

    cin >> n;
    ListLinkedDouble lista2;
    for (int i = 0; i < n; ++i) {
        cin >> valor;
        lista2.push_back(valor);
    }


    lista.zip(lista2);

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
