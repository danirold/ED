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

   /*
    * Implementa las operaciones pedidas en el ejercicio al final de
    * este fichero, entre las etiquetas.
    */

#include <iostream>
#include <cassert>
#include <fstream>


class ListLinkedSingle {
private:
    struct Node {
        int value;
        Node* next;
    };

public:
    ListLinkedSingle() : head(nullptr) { }
    ~ListLinkedSingle() {
        delete_list(head);
    }

    ListLinkedSingle(const ListLinkedSingle& other)
        : head(copy_nodes(other.head)) { }

    void push_front(const int& elem) {
        Node* new_node = new Node;
        new_node->value = elem;
        new_node->next = head;
        head = new_node;
    }

    void push_back(const int& elem);

    void pop_front() {
        assert(head != nullptr);
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }

    void pop_back();

    int size() const;

    bool empty() const {
        return head == nullptr;
    };

    const int& front() const {
        assert(head != nullptr);
        return head->value;
    }

    int& front() {
        assert(head != nullptr);
        return head->value;
    }

    const int& back() const {
        return last_node()->value;
    }

    int& back() {
        return last_node()->value;
    }

    const int& at(int index) const {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    int& at(int index) {
        Node* result_node = nth_node(index);
        assert(result_node != nullptr);
        return result_node->value;
    }

    void display(std::ostream& out) const;
    void display() const {
        display(std::cout);
    }

    // Nuevo método. Debe implementarse abajo
    void merge(ListLinkedSingle& l2);

private:
    Node* head;

    void delete_list(Node* start_node);
    Node* last_node() const;
    Node* nth_node(int n) const;
    Node* copy_nodes(Node* start_node) const;

};

ListLinkedSingle::Node* ListLinkedSingle::copy_nodes(Node* start_node) const {
    if (start_node != nullptr) {
        Node* result = new Node;
        result->value = start_node->value;
        result->next = copy_nodes(start_node->next);
        return result;
    }
    else {
        return nullptr;
    }
}

void ListLinkedSingle::delete_list(Node* start_node) {
    if (start_node != nullptr) {
        delete_list(start_node->next);
        delete start_node;
    }
}

void ListLinkedSingle::push_back(const int& elem) {
    Node* new_node = new Node;
    new_node->value = elem;
    new_node->next = nullptr;
    if (head == nullptr) {
        head = new_node;
    }
    else {
        last_node()->next = new_node;
    }
}

void ListLinkedSingle::pop_back() {
    assert(head != nullptr);
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        Node* previous = head;
        Node* current = head->next;

        while (current->next != nullptr) {
            previous = current;
            current = current->next;
        }

        delete current;
        previous->next = nullptr;
    }
}

int ListLinkedSingle::size() const {
    int num_nodes = 0;

    Node* current = head;
    while (current != nullptr) {
        num_nodes++;
        current = current->next;
    }

    return num_nodes;
}


ListLinkedSingle::Node* ListLinkedSingle::last_node() const {
    assert(head != nullptr);
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

ListLinkedSingle::Node* ListLinkedSingle::nth_node(int n) const {
    assert(0 <= n);
    int current_index = 0;
    Node* current = head;

    while (current_index < n && current != nullptr) {
        current_index++;
        current = current->next;
    }

    return current;
}

void ListLinkedSingle::display(std::ostream& out) const {
    out << "[";
    if (head != nullptr) {
        out << head->value;
        Node* current = head->next;
        while (current != nullptr) {
            out << ", " << current->value;
            current = current->next;
        }
    }
    out << "]";
}

// ----------------------------------------------------------------
// ¡No modificar nada por encima de esta línea!

// Implementa a continuación el método pedido.
//@ <answer>

void ListLinkedSingle::merge(ListLinkedSingle& l2) {//Coste lineal respecto de la suma de los elementos de l1 y l2
    Node* previous = nullptr;
    Node* current1 = head;
    Node* current2 = l2.head;

    if (head == nullptr) {
        head = l2.head;
    }
    else if (current2 == nullptr);
    else {
        while (current2 != nullptr && current1 != nullptr) {
            if (current2->value <= current1->value) {
                Node* aux = current2->next;
                current2->next = current1;
                if (previous == nullptr) {
                    head = current2;
                }
                else {
                    previous->next = current2;
                }
                previous = current2;
                current2 = aux;
            }
            else {
                Node* aux2 = current1;
                current1 = current1->next;
                previous = aux2;
            }
        }
        if (current1 == nullptr) {
            previous->next = current2;
        }
        else if (current2 == nullptr) {
            previous->next = current1;
        }
    }
    l2.head = nullptr;
}

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

using namespace std;

ListLinkedSingle leerLista() {
    ListLinkedSingle lista;
    int n;
    std::cin >> n;
    while (n != 0) {
        lista.push_back(n);
        std::cin >> n;
    }
    return lista;
}

void resuelveCaso() {
    auto lista1 = leerLista();
    auto lista2 = leerLista();

    lista1.merge(lista2);
    lista1.display(); cout << '\n';
}

int main() {


    // Leemos el número de casos de prueba que vendrán a continuación
    int num_casos;
    cin >> num_casos;

    for (int i = 0; i < num_casos; i++) {
        resuelveCaso();
    }

    return 0;
}