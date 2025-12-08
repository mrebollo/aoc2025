/*
    Advent of code 2025 - Day 8 (1)
    Generate circuit with one giant component
    = detection of critical link 
    minumum cost spanning tree (MST)
    there is a greedy algorithm (Prim)
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
    list<JunkBox> boxes;
    int numBoxes;
    int maxWires;
    bool addNeighbour(JunkBox* a, JunkBox* b) {
        if( a->neig.empty() || b->neig.empty()){
            a->neig.push_back(b);
            b->neig.push_back(a);
            return true;
        }
        return false;
    }
   
public:
    Circuit(int maxWires) : numBoxes(0), maxWires(maxWires) {}
    Circuit() : Circuit(-1) {}
    int numNodes() const { return numBoxes;}
    void addBox(int x, int y, int z) {
        boxes.emplace_back(JunkBox(x, y, z));
        numBoxes++;
    }
    // Devuelve el último enlace que forma la MST
    Edge connect() {
        set<JunkBox*> MST;
        // Empezar desde el primer nodo de la lista
        JunkBox* first = &(*boxes.begin());
        MST.insert(first);
        auto connectTo = [&](JunkBox* selected) {
            for(auto& box : boxes){
                if (MST.find(&box) == MST.end() && &box != selected){
                    double dist = selected->distance(box);
                    wire.push({dist, selected, &box});
                }
            }
        };
        connectTo(first);
        Edge criticalEdge;
        double maxWeight = -1.0;
        int numEdges = 0;
        while (!wire.empty() && numEdges < numBoxes) {
            // extraigo el nodo de menor distancia
            Edge top = wire.top(); wire.pop();
            double dist = get<0>(top);
            JunkBox* v = get<2>(top);
            // si no está en el MST, lo añado
            if (MST.count(v) == 0) {
                MST.insert(v);
                numEdges++;
                connectTo(v); //añado sus conexiones
                // el último no es necesariamente el de mayor distancia
                // hay que ir guardándola
                if (dist > maxWeight) {
                    maxWeight = dist;
                    criticalEdge = top;
                }
#ifdef DEBUG
                cout << "Connecting: " << u->print() << " - " << v->print() << " : " << dist << endl;
#endif
            }
        }
        return criticalEdge;
    }


    void print() {
        cout << "Circuit with " << numBoxes << " boxes and " << maxWires << " wires (showing selected):\n";
        // Mostrar los wires seleccionados
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
        for(const auto& box : boxes){
            cout << box.print() << endl;
            for(const auto& neig : box.neig){
                cout << "  -> " << neig->print() << " : " << box.distance(*neig) << endl;
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