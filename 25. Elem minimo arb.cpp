// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

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
T valor_min(const BinTree<T>& tree) {
    if (tree.left().empty() && tree.right().empty()) {
        return tree.root();
    }
    else if (tree.left().empty()) {
        return min(valor_min(tree.right()), tree.root());
    }
    else if (tree.right().empty()) {
        return min(valor_min(tree.left()), tree.root());
    }
    else {
        return min(min(valor_min(tree.left()), valor_min(tree.right())), tree.root());
    }
}

bool resuelveCaso() {
    char tipo; cin >> tipo;

    if (!std::cin) 
        return false;

    if (tipo == 'N') {
        BinTree<int> tree = tree.read_tree(cin);
        cout << valor_min(tree);
    }
    else if (tipo == 'P') {
        BinTree<string> tree = tree.read_tree(cin);
        cout << valor_min(tree);
    }

    cout << '\n';

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}