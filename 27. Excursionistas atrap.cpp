#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>

using namespace std;

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
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

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

template <typename T> int height(const BinTree<T>& tree) {
    if (tree.empty()) {
        return 0;
    }
    else {
        return 1 + std::max(height(tree.left()), height(tree.right()));
    }
}


template <typename T>
std::pair<int, int> excursionistas_rescatados(const BinTree<T>& tree) {
    if (tree.empty()) return{ 0, 0 };

    else {
        auto [equipos_izq, max_izq] = excursionistas_rescatados(tree.left());
        auto [equipos_dcha, max_dcha] = excursionistas_rescatados(tree.right());
        if (equipos_izq == 0 && equipos_dcha == 0 && tree.root() != 0) {
            return { 1, max(max_izq, max_dcha) + tree.root() };
        }
        else {
            return { equipos_izq + equipos_dcha, max(max_izq, max_dcha) + tree.root() };
        }
    }
}


void resuelveCaso() {
    BinTree<int>tree = read_tree<int>(cin);
    pair<int, int> rescate = excursionistas_rescatados(tree);
    cout << rescate.first << ' ' << rescate.second << '\n';
}


int main() {
    int casos; cin >> casos;
    for (int i = 0; i < casos; i++) resuelveCaso();

    return 0;
}