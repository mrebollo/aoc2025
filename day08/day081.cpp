/*
    Advent of code 2025 - Day 8 (1)
    Detect largest components in a circuit
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

#define DEBUG 1


class JunkBox{
private:
    int x,y,z;
public:
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


class Circuit {
            
    private:
        // estructura para los enlaces: (distancia, ptr1, ptr2)
        using Edge = tuple<double, JunkBox*, JunkBox*>; 
        // Max-heap para mantener solo los maxWires enlaces más cortos
        priority_queue<Edge, vector<Edge>, less<Edge>> wire;
        list<JunkBox> boxes;
        int numBoxes;
        int maxWires;
        // inserta las maxWires conexiones más cortasç
        // si hay menos,la inserta, 
        // si hay más y es menor que la mayor, la descarta el top() y la inserta
        void connectBoxes(JunkBox& newBox) {
            if (boxes.size() < 2) return;
            auto it_new = prev(boxes.end());
            for (auto it = boxes.begin(); it != it_new; ++it) {
                double dist = it->distance(*it_new);
                Edge e = {dist, &(*it), &(*it_new)};
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
        void addNeighbour(JunkBox* a, JunkBox* b) {
            a->neig.push_back(b);
            b->neig.push_back(a);
        }
        // DFS recursivo para contar el tamaño de la componente conexa
        int dfs(JunkBox* node, set<JunkBox*>& visited) {
            visited.insert(node);
            int size = 1;
            // Recorre todos los vecinos
            for (JunkBox* neighbor : node->neig) {
                if (visited.find(neighbor) == visited.end()) {
                    size += dfs(neighbor, visited);
                }
            }
            return size;
        }
        // Encuentra los tamaños de todas las componentes conexas y devuelve los 3 mayores
            vector<int> largestComponents() {
                set<JunkBox*> visited; // nodos visitados
                vector<int> cSizes;     //vector con los tamaños de las componentes
                for (auto& box : boxes) {
                    // selecciona un nodo no visitado y hace DFS desde él
                    if (visited.find(&box) == visited.end()) {
                        int compSize = dfs(&box, visited);
                        cSizes.push_back(compSize);
                    }
                }
                // Ordena los tamaños en orden descendente
                sort(cSizes.rbegin(), cSizes.rend());
#ifdef DEBUG
                cout << "Component sizes: ";
                for (int size : cSizes) {
                    cout << size << " ";
                }
                cout << endl;
#endif
                // Se queda con los 3 mayores
                if (cSizes.size() > 3) cSizes.resize(3);
                return cSizes;
            }
            
    public:
        Circuit(int maxWires) : numBoxes(0), maxWires(maxWires) {}
        Circuit() : Circuit(-1) {}

        void addBox(int x, int y, int z) {
            boxes.emplace_back(JunkBox(x, y, z));
            connectBoxes(boxes.back());
            numBoxes++;
        }
        // Crea el circuito a partir de los wire más cortos encontrados
        void connect() {
            while (!wire.empty()) {
                Edge top = wire.top();
                double dist = get<0>(top);
                JunkBox* a = get<1>(top);
                JunkBox* b = get<2>(top);

#ifdef DEBUG
                cout << "Connecting: " << a->print() << " - " << b->print() << " : " << dist << endl;
#endif
                addNeighbour(a, b);
                wire.pop();
            }
        }

        int circuitValue() {
            vector<int> largest = largestComponents();
            int quality = 1;
            for (int size : largest) {
#ifdef DEBUG
                cout << "Component size: " << size << endl;
#endif
                quality *= size;
            }
            return quality;
        }

        void print() {
            cout << "Circuit with " << numBoxes << " boxes and " << maxWires << " wires (showing selected):\n";
            // Mostrar los wires seleccionados
            priority_queue<Edge, vector<Edge>, less<Edge>> tempWire = wire;
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
    Circuit circuit = Circuit(10); 
    ifstream input("test.txt");
    int x, y, z;
    char aux1, aux2;
    while(input >> x >> aux1 >> y >> aux2 >> z) {
        circuit.addBox(x, y, z);
    }
    input.close();
#ifdef DEBUG
    circuit.print();
#endif
    circuit.connect();
#ifdef DEBUG
    circuit.showCircuit();
#endif
    int value = circuit.circuitValue();
    cout << "Circuit value: " << value << endl;
    // Further implementation would go here
    return 0;
}   