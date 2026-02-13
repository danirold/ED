/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */


 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Sergio Martínez Olivera
  Estudiante 2: Daniel Roldán Serrano


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <cassert>
#include <memory>
#include <utility>


  // Clase para representar árboles binarios.
  // No es posible modificar esta clase para el problema de hoy

template <class T> class BinTree {
public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}


using namespace std;


// ----------------------------------------------------------------
// Define aquí la función pedida en el enunciado.
// Puedes definir las funciones auxiliares que necesites, pero siempre
// entre las marcas <answer> y </answer>

//@ <answer>



pair<int, int> salvar(BinTree<char> const& arbol) {
    if (arbol.empty()) {
        return make_pair(0, 0);
    }
    else {

        pair<int, int> left = salvar(arbol.left());
        pair<int, int> right = salvar(arbol.right());
        return make_pair(max(right.second + left.first, left.second + right.first), right.second + left.second + 1);
    }
}

int salvar_arbol(BinTree<char> const& arbol) {
    return salvar(arbol).first;
}

// Indica aquí el coste del algoritmo y las recurrencias planteadas en
// el caso del árbol equilibrado, y en el caso del árbol degenerado.

/* Arbol equlibrado
        c0 si n == 0
T(n) =
        2T(n/2) + c1 si n > 0

    Arbol degenerado
        c0 si n == 0
T(n) =
        T(a) + T(b) + c1 si n > 0 con (a + b + 1) = n
Con esta recurrencia, podemos calcular el coste del algoritmo. Desarrollando la función, en el caso equilibrado, obtenemos O(n), siendo n el
numero de nodos del arbol. En el caso de que el arbol fuera degenerado, el coste también sería O(n), siendo n el numero de nodos.

Hemos resuelto el problema con una función que devuelve un par, siendo el primer elemento del par la solución, es decir, los nodos que se salvan,
y el segundo el número de nodos del árbol. Para ello, desarrollamos una recursión, con el caso base de que el árbol sea vacío, y con el caso recursivo en
el que devolvemos el maximo entre salvar los nodos de la derecha y llamar a la funcion por la izquierda o salvar los nodos de la izquierda y llamar
a la función por la derecha.
*/

//@ </answer>

// ¡No modificar nada debajo de esta línea!
// ----------------------------------------------------------------

void resuelveCaso() {
    BinTree<char> arbol = read_tree<char>(cin);
    assert(!arbol.empty());
    cout << salvar_arbol(arbol) << "\n";
}

int main() {


    int num_casos;
    cin >> num_casos;
    while (num_casos--) {
        resuelveCaso();
    }



    return 0;
}