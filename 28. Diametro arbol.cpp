// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>
#include <tuple>

using namespace std;

template<class T>
class BinTree {
private:
    struct TreeNode {
        T elem;
        TreeNode* left, * right;
        TreeNode(TreeNode* left, const T& elem, TreeNode* right) : elem(elem), left(left), right(right) { }
    };
    TreeNode* root_node;

public:
    BinTree() : root_node(nullptr) { }
    BinTree(const T& elem) : root_node(new TreeNode(nullptr, elem, nullptr)) { }
    BinTree(const BinTree& left, const T& elem, const BinTree& right) : root_node(new TreeNode(left.root_node, elem, right.root_node)) { }

    const T& root() const {
        return root_node->elem;
    }
    BinTree left() const {
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }
    BinTree right() const {
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }
    bool empty() const {
        return root_node == nullptr;
    }
    static void display_node(const TreeNode* root, ostream& out) {
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
    void display(ostream& out) const {
        display_node(root_node, out);
    }
    BinTree<T> read_tree(istream& in) {
        char c;
        in >> c;
        if (c == '.') {
            return BinTree<T>();
        }
        else {
            BinTree<T> left = read_tree(in);
            T elem;
            in >> elem;
            BinTree<T> right = read_tree(in);
            in >> c;
            BinTree<T> result(left, elem, right);
            return result;
        }
    }
};

template<class T>
pair<int, int> diametro(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { 0, 0 };
    }
    else {
        auto [max_izq, act_izq] = diametro(tree.left());
        auto [max_dcha, act_dcha] = diametro(tree.right());
        int maximo = max(max(max_izq, max_dcha), act_izq + act_dcha + 1);
        int actual = 1 + max(act_izq, act_dcha);
        return { maximo, actual };
    }
}

void resuelveCaso() {
    BinTree<char> arbol = arbol.read_tree(cin);
    cout << diametro(arbol).first << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
