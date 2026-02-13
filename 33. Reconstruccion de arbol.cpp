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
#include <memory>
#include <cassert>
#include <vector>

/*
  Implementación de la clase BinTree para representar árboles binarios.

  Para realizar este ejercicio no es necesario modificar la clase.
 */

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


using namespace std;
// ----------------------------------------------------------------
// ¡No modificar nada importante por encima de esta línea!

// Implementa a continuación la función pedida. Puedes definir las funciones
// auxiliares que necesites.
//@ <answer>

BinTree<int> reconstruir(vector<int> const& preorden, vector<int> const& inorden) {
    if (preorden.empty()) {
       return BinTree<int>();
    }
    else if (preorden.size() == 1) {
        return BinTree<int>(preorden[0]);
    }
    else {
        vector<int> hijo_izq_inorder;
        int i = 0;
        while (inorden[i] != preorden[0]) {
            hijo_izq_inorder.push_back(inorden[i]);
            ++i;
        }

        vector<int> hijo_dcho_inorder;
        i++;
        int hijo_der = inorden[i];
        while (i < inorden.size()) {
            hijo_dcho_inorder.push_back(inorden[i]);
            ++i;
        }

        vector<int> hijo_izq_preorder;
        i = 1;
        int tam = hijo_izq_inorder.size();
        while (i < 1 + tam){
            hijo_izq_preorder.push_back(preorden[i]);
            ++i;
        }

        vector<int> hijo_der_preorder;
        while (i < preorden.size()) {
            hijo_der_preorder.push_back(preorden[i]);
            ++i;
        }

        return BinTree<int>(reconstruir(hijo_izq_preorder, hijo_izq_inorder), preorden[0], reconstruir(hijo_der_preorder, hijo_dcho_inorder));
    }
}

bool resuelveCaso() {

    // leemos la entrada
    int N;
    cin >> N;
    if (!cin)
        return false;

    vector<int> preorden(N);
    for (int& c : preorden) {
        cin >> c;
    }

    vector<int> inorden(N);
    for (int& c : inorden) {
        cin >> c;
    }

    auto arbol = reconstruir(preorden, inorden);
    cout << arbol << '\n';
    return true;
}

/*@ </answer> */

int main() {


    while (resuelveCaso());

    return 0;
}
