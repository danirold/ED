/*
 * ---------------------------------------------------
 *                ESTRUCTURAS DE DATOS
 * ---------------------------------------------------
 */

 /*@ <answer>

  Introduce el nombre y apellidos de los/as componentes del grupo:

  Estudiante 1: Daniel Roldan Serrano
  Estudiante 2: Sergio Martinez Olivera


  Dad una explicación de la solución y justificad su coste.

  @ </answer> */

#include <iostream>
#include <fstream>
#include <memory>
#include <cassert>
#include <stack>
#include <cctype>
#include <optional>
#include <sstream>
#include <map>
#include <string>

  /*
    Implementación de la clase BinTree para representar árboles binarios.
   */

template<class T>
class BinTree {
public:

    BinTree() : root_node(nullptr) { }

    BinTree(const T& elem) : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) { }

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        :root_node(std::make_shared<TreeNode>(left.root_node, elem, right.root_node)) { }


    bool empty() const {
        return root_node == nullptr;
    }

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

    void display(std::ostream& out) const {
        display_node(root_node, out);
    }

private:
    // Las definiciones de TreeNode y NodePointer dependen recursivamente
    // la una de la otra. Por eso declaro 'struct TreeNode;' antes de NodePointer
    // para que el compilador sepa, cuando analice la definición de NodePointer,
    // que TreeNode va a ser definida más adelante.

    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right) : elem(elem), left(left), right(right) { }

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

/*
 * Operador << para mostrar un árbol por pantalla. No es necesario hacer esto
 * en la práctica, pero os lo dejo por si queréis depurar.
 */
template<typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}


/*
 * Función para leer un árbol binario de la entrada. El formato es el siguiente:
 *
 *  Árbol vacío: .
 *  Árbol no vacío: (i x r)  donde i es la representación del hijo izquierdo
 *                                 x es la raíz
 *                                 r es la representación del hijo derecho
 */
template<typename T>
BinTree<T> read_tree(std::istream& in) {
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

/*
 * Analizador léxico del lenguaje
 */

class Lexer {
public:
    Lexer(std::istream& in) : in(in) { }

    std::string peek() {
        if (next != "") {
            return next;
        }
        else {
            next = read_next();
            return next;
        }
    }

    std::string get() {
        std::string result = peek();
        next = "";
        return result;
    }

private:
    std::istream& in;

    std::string read_next() {
        std::ostringstream result;
        char current;
        in >> current;
        while (iswspace(current)) {
            in >> current;
        }

        if (isdigit(current)) {
            result << current;
            while (isdigit(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (isalpha(current)) {
            result << current;
            while (isalnum(in.peek())) {
                in >> current;
                result << current;
            }
        }
        else if (current == '+' || current == '-' || current == '*' || current == ';' || current == '(' || current == ')') {
            result << current;
        }
        else if (current == ':') {
            result << current;
            in >> current;
            if (current != '=') throw std::domain_error("invalid token: :" + current);
            result << current;
        }
        else {
            throw std::domain_error("invalid_token: " + current);
        }

        return result.str();
    }

private:
    std::string next;
};

/*
 * Analizador sintáctico del lenguaje
 */


class Parser {
public:
    Parser(std::istream& in) : l(in) { }

    BinTree<std::string> parse() {
        return S();
    }

private:
    Lexer l;

    bool is_identifier(const std::string& token) {
        return (!token.empty() && isalpha(token[0]));
    }

    bool is_identifier_or_number(const std::string& token) {
        return (!token.empty() && isalnum(token[0]));
    }

    BinTree<std::string> S() {
        std::string identifier = l.get();
        if (!is_identifier(identifier)) throw std::domain_error("identifier expected, found " + identifier);

        std::string equal = l.get();
        if (equal != ":=") throw std::domain_error(":= expected, found " + equal);

        BinTree<std::string> rhs = E();

        std::string semicolon = l.get();
        if (semicolon != ";") throw std::domain_error("; expected, found " + semicolon);

        return { { identifier }, ":=", rhs };
    }

    BinTree<std::string> E() {
        BinTree<std::string> term = T();
        return Ep(term);
    }

    BinTree<std::string> Ep(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "+" || op == "-") {
            l.get();
            BinTree<std::string> term = T();
            return Ep({ left, op, term });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> T() {
        BinTree<std::string> factor = F();
        return Tp(factor);
    }

    BinTree<std::string> Tp(const BinTree<std::string>& left) {
        std::string op = l.peek();
        if (op == "*") {
            l.get();
            BinTree<std::string> factor = F();
            return Tp({ left, "*", factor });
        }
        else {
            return left;
        }
    }

    BinTree<std::string> F() {
        std::string next = l.get();
        if (is_identifier_or_number(next)) {
            return { next };
        }
        else if (next == "(") {
            BinTree<std::string> inner = E();
            std::string closing = l.get();
            if (closing != ")") throw std::domain_error(") expected, found " + closing);
            return inner;
        }
        else {
            throw std::domain_error("number or identifier expected, found " + next);
        }
    }
};

/*
 * Función que lee una sentencia y devuelve su árbol sintáctico.
 */

BinTree<std::string> parse(std::istream& in) {
    return Parser(in).parse();
}

using namespace std;

/* ======================================================================
 * Escribe tu solución entre las etiquetas "answer" que se muestran a
 * continuación.
 *
 * No es necesario añadir ni modificar ningún método de las clases
 * anteriores, pero puedes implementar las funciones auxiliares
 * que necesites.
 * ====================================================================== */
 /*@ <answer> */

/*
Creamos un mapa en el que las claves van a ser las variables que se utilicen en el programa
y los valores, sus respectivos valores numericos. Para calcular dichos valores, utilizamos una funcion recursiva
en la que si la raiz del arbol es una operacion, realizamos dicha operacion siendo los hijos de la raiz los operandos,
diferenciando si un hijo es un numero o una variable, en este caso, buscaremos su valor en el mapa.

Coste de la solucion: Tenemos un bucle que da M vueltas, siendo M el numero de asignaciones.
El coste de la funcion recursiva calcular() es S * log(N), siendo S el numero maximo de nodos del arbol y N el numero de variables.
Entonces el coste total es M * (S * log(N))
*/

int calcular(BinTree<string> arbol, map<string,int>& mapa) {
    if (arbol.root() == "*") {
        return calcular(arbol.left(), mapa) * calcular(arbol.right(), mapa);
    }
    else if (arbol.root() == "+") {
        return calcular(arbol.left(), mapa) + calcular(arbol.right(), mapa);
    }
    else if (arbol.root() == "-") {
        return calcular(arbol.left(), mapa) - calcular(arbol.right(), mapa);
    }
    else if (isdigit(arbol.root()[0])) {
        return stoi(arbol.root());
    }
    else return mapa[arbol.root()];
}

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    map<string, int> mapa;
    for (int i = 0; i < N; ++i) {
        BinTree<string> arbol = parse(cin);
        int resultado = calcular(arbol.right(), mapa);
        mapa[arbol.left().root()] = resultado;
    }

    for (auto [clave, valor]: mapa) {
        cout << clave << " = " << valor << '\n';
    }

    cout << "---\n";

    return true;
}

/*@ </answer> */

int main() {
    while (resuelveCaso()) {}
    return 0;
}

/*

 3
 x := 3;
 y := 5;
 z := x + y;
 2
 b := 5 + 6 * 3;
 a := b - 1;
 3
 x := 1;
 x := x * 2;
 x := x * 2;
 0
 */
