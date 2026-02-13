// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG25

#include <iostream>
#include <iomanip>
#include <fstream>
#include <utility>

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
pair<bool, int> es_completo(const BinTree<T>& tree) {
    if (tree.empty()) {
        return {true, 0};
    }
    else {
        pair<bool, int> sol1 = es_completo(tree.left());
        pair<bool, int> sol2 = es_completo(tree.right());
        int height = 1 + max(sol1.second, sol2.second);
        if (tree.left().empty() && tree.right().empty()) return {true, 0};
        else if (tree.left().empty() && !tree.right().empty()) return {false, 0};
        else if (!tree.left().empty() && tree.right().empty()) return {false, 0};
        else {
            return {sol1.first && sol2.first && sol1.second == sol2.second, height};
        }
    }
}

void resuelveCaso() {
    BinTree<char> arbol = arbol.read_tree(cin);
    if (es_completo(arbol).first) {
        cout << "SI";
    }
    else cout << "NO";
    cout << '\n';
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}
