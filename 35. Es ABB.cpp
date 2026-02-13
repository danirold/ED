/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*
  * MUY IMPORTANTE: Para realizar este ejercicio solo podéis
  * modificar el código contenido entre las etiquetas <answer>
  * y </answer>. Toda modificación fuera de esas etiquetas está
  * prohibida, pues no será corregida.
  *
  * Tampoco esta permitido modificar las líneas que contienen
  * las etiquetas <answer> y </answer>, obviamente :-)
  */

  //@ <answer>
  // Nombre y Apellidos: DANIEL ROLDAN SERRANO
  //@ </answer>

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <vector>

/*
  Implementación de la clase BinTree para representar árboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

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

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const { inorder(root_node, func); }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
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

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void inorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

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
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación la función pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer>

bool resuelveCaso() {

    // leemos la entrada
    char tipo;
    cin >> tipo;
    if (!cin)
        return false;

    if (tipo == 'N') {
        auto arbol = read_tree<int>(cin);
        bool solucion = true;
        if (!arbol.empty()) {
            vector<int> vector;
            arbol.inorder([&vector](int x) {vector.push_back(x); });
            for (int i = 0; i < (vector.size() - 1) && solucion; ++i) {
                if (vector[i] >= vector[i + 1]) solucion = false;
            }
        }
        if (solucion) cout << "SI\n";
        else cout << "NO\n";
    }
    else if (tipo == 'P') {
        auto arbol = read_tree<string>(cin);
        bool solucion = true;
        if (!arbol.empty()) {
            vector<string> vector;
            arbol.inorder([&vector](string x) {vector.push_back(x); });
            for (int i = 0; i < (vector.size() - 1) && solucion; ++i) {
                if (vector[i] >= vector[i + 1]) solucion = false;
            }
        }
        if (solucion) cout << "SI\n";
        else cout << "NO\n";
    }

    return true;
}

/*@ </answer> */

int main() {


    while (resuelveCaso());

    return 0;
}
