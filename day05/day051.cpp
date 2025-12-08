/*
    Advent of Code 2025 - Day 5 (1)
    Check if a value belongs to a set of intervals
    Use ogf an interval tree for efficient querying
*/



#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define DEBUG 1

class IntervalTree {
private:
    struct Node {
        long long low, high; // intervalo
        Node *left, *right;
    };
    Node *root;
    Node *newNode(long long low, long long high){
        Node *temp = new Node;
        temp->low = low;
        temp->high = high;
        temp->left = temp->right = nullptr;
        return temp;
    }
    Node* insert(Node *root, long long low, long long high);
    bool inRange(Node *root, long long value);

public:     
    IntervalTree() : root(nullptr) {}
    void insert(long long low, long long high) {
        root = insert(root, low, high);
    }
    bool isFresh(long long ingred) {
        return inRange(root, ingred);
    }
    void print();
};


// Inserción en el árbol, comparando con el límite inferior
IntervalTree::Node* IntervalTree::insert(Node *n, long long low, long long high) {
    // Caso base: árbol vacio -> el nuevo nodo es root
    if (n == nullptr)
         return newNode(low, high);
    // inserta el intervalo en low/high según el valor de low
    if (low < n->low)
        n->left = insert(n->left, low, high);
    else
        n->right = insert(n->right, low, high);
    return n;
}

bool IntervalTree::inRange(Node *n, long long value) {
    if (n == nullptr) return false; // interval not found -> not fresh
    if (value >= n->low && value <= n->high)
        return true; // interval found -> fresh
    // Buscar en ambos subárboles porque los intervalos pueden solaparse
    if (inRange(n->left, value))
        return true;
    return inRange(n->right, value);
}

void IntervalTree::print() {
    // Inorder traversal to print intervals
    function<void(Node*)> inorder = [&](Node* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << "[" << node->low << ", " << node->high << "] ";
        inorder(node->right);
    };
    inorder(root);
    cout << endl;
}
int main() {
    ifstream input("input.txt");

    // Read intervals from input
    IntervalTree t;
    long long low, high;
    string line;
    while (getline(input, line) && !line.empty()){
        size_t dash_pos = line.find('-');
        low = stoll(line.substr(0, dash_pos));
        high = stoll(line.substr(dash_pos + 1));
        t.insert(low, high);
    }
#ifdef DEBUG
    t.print();
#endif
    long long ingred;
    int total_fresh = 0;
    while (input >> ingred){
        bool fresh = t.isFresh(ingred);        
#ifdef DEBUG
        cout << "Ingredient " << ingred << (fresh ? " fresh" : " not fresh") << endl;
#endif
        if (fresh) total_fresh++;
    }
    input.close();
    cout << "Total fresh: " << total_fresh << endl;
    return 0;
}