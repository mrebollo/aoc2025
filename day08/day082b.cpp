/*
    Advent of code 2025 - Day 8 (1)
    Generate circuit with one giant component
    = detection of critical link 
    minimum cost spanning tree (MST)
    implementation with DSU (Disjoint Set Union)
*/


#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <cmath>
using namespace std;

//#define DEBUG 1


class JunkBox{
public:
    int x,y,z;
    vector<JunkBox*> neig;
    JunkBox(int x, int y, int z) : x(x), y(y), z(z) {}
    double distance(const JunkBox& other) const {
        double dx = x - other.x;
        double dy = y - other.y;
        double dz = z - other.z;
        return sqrt(dx*dx + dy*dy + dz*dz);
    }
    string print() const {
        return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
    }
};

// estructura para los enlaces: (distancia, ptr1, ptr2)
using Edge = tuple<double, JunkBox*, JunkBox*>; 

class Circuit {            
private:
    // Min-heap para tener la lista de menor a mayor distancia
    priority_queue<Edge, vector<Edge>, greater<Edge>> wire;
    vector<JunkBox*> boxPtrs;
    int numBoxes;
    int maxWires;
    // inserta las maxWires conexiones más cortasç
    // si hay menos,la inserta, 
    // si hay más y es menor que la mayor, la descarta el top() y la inserta
    void connectBoxes(JunkBox* newBox) {
        if (boxPtrs.size() < 2) return;
        for (size_t i = 0; i < boxPtrs.size() - 1; ++i) {
            double dist = boxPtrs[i]->distance(*newBox);
            Edge e = {dist, boxPtrs[i], newBox};
            if (maxWires < 0) {
                wire.push(e); // sin límite
            } else if ((int)wire.size() < maxWires) {
                wire.push(e);
            } else if (dist < get<0>(wire.top())) {
                wire.pop();
                wire.push(e);
            }
        }
    }
   
public:
    Circuit(int maxWires) : numBoxes(0), maxWires(maxWires) {}
    Circuit() : Circuit(-1) {}
    int numNodes() const { return numBoxes;}
    void addBox(int x, int y, int z) {
        JunkBox* newBox = new JunkBox(x, y, z);
        boxPtrs.push_back(newBox);
        connectBoxes(newBox);
        numBoxes++;
    }
    // Devuelve el último enlace que forma el MST
    Edge connect() {
        // Map JunkBox* to index
        unordered_map<JunkBox*, int> boxIndex;
        vector<int> parent(boxPtrs.size());
        for (int i = 0; i < numBoxes; i++) {
            boxIndex[boxPtrs[i]] = i;
            parent[i] = i;
        }
        // find representative of the set
        // función lambda que solo se define para uso local en connect()
        // [&] indica que tiene acceso a las variables de connect por referencia 
        auto find = [&](int x) {
            while (parent[x] != x) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        };
        // unite two sets
        auto unite = [&](int x, int y) {
            // busca los representantes de los conjuntos
            int px = find(x), py = find(y);
            // si no son iguales (pertenece cada uno a un conjunto), los une
            if (px != py) parent[px] = py;
        };
        int components = numBoxes;
        Edge criticalEdge;
        // inicialmente tantos componentes como nodos (todos separados)
        while (!wire.empty() && components > 1) {
            Edge e = wire.top();
            wire.pop();
            JunkBox* a = get<1>(e);
            JunkBox* b = get<2>(e);
            int u = boxIndex[a];
            int v = boxIndex[b];
            // si pertenecen a componentes distintas, los une
            // reduce el número de componentes y guarda el enlace como crítico
            if (find(u) != find(v)) {
                unite(u, v);
                components--;
                criticalEdge = e;
            }
        }
        return criticalEdge;
    }


    void print() {
        cout << "Circuit with " << numBoxes << " boxes and " << maxWires << " wires (showing selected):\n";
        priority_queue<Edge, vector<Edge>, greater<Edge>> tempWire = wire;
        while (!tempWire.empty()) {
            Edge top = tempWire.top();
            double dist = get<0>(top);
            JunkBox* a = get<1>(top);
            JunkBox* b = get<2>(top);
            cout << a->print() << " - " << b->print() << " : " << dist << endl;
            tempWire.pop();
        }
    }

    void showCircuit() {
        for(const auto& box : boxPtrs){
            cout << box->print() << endl;
            for(const auto& neig : box->neig){
                cout << "  -> " << neig->print() << " : " << box->distance(*neig) << endl;
            }
        }
    }
};



int main() {
    Circuit circuit = Circuit(); 
    ifstream input("input.txt");
    int x, y, z;
    char aux1, aux2;
    while(input >> x >> aux1 >> y >> aux2 >> z) {
        circuit.addBox(x, y, z);
    }
    input.close();
#ifdef DEBUG
    circuit.print();
#endif
    Edge edge = circuit.connect();
#ifdef DEBUG
    circuit.showCircuit();
#endif
    long long x1 = get<1>(edge)->x;
    long long x2 = get<2>(edge)->x;
    cout << "x1: " << x1 << ", x2: " << x2 << endl;
    cout << "Circuit value: " << x1 * x2 << endl;
    // Further implementation would go here
    return 0;
}   