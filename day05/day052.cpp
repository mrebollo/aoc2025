/*
    Advent of Code 2025 - Day 5 (2)
    Calculate the size of the union of intervals
    Use of an interval tree for efficient querying
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
    long long unionSize();
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

// inorder traversal gets intervals ordered by low -> greedy merge
long long IntervalTree::unionSize() {
    // ordered vector of Node*
    vector<Node*> intervals;
    function<void(Node*)> collect = [&](Node* node) {
        if (node == nullptr) return;
        collect(node->left);
        intervals.push_back(node);
        collect(node->right);
    };
    collect(root);  
    /*
        Merge intervals from left to right. 
        Three cases since low1 < low2 always
                      A.              B.          C
        interval 1. [   ]         [      ]    [      ]
        interval 2.        [  ]    [   ]          [     ]
        A) sum size interval 2
        B) do nothing -> eliminate case
        C) sum end2 - end1 
        In all cases, new end = max(end1, end2)
    */
    long long total_size = 0;
    long long current_start = 0, current_end = 0;
    for (auto interval : intervals) {
        if (interval->low > current_end) {
            // Case A
            total_size += (interval->high - interval->low + 1);
            current_end = interval->high;
        } else if (interval->high > current_end) {
            // Case C
            total_size += (interval->high - current_end);
            current_end = interval->high;
        }
    }
    return total_size;
}


int main() {
    ifstream input("input.txt");

    // Read intervals from input
    IntervalTree t;
    long long low, high;
    char bar;
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
    input.close();
    long long union_size = t.unionSize();
    cout << "Union size: " << union_size << endl;   
    return 0;
}