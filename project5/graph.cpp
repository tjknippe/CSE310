#include "graph.h"
#include "minheap.h"

using namespace std;
const double DOUBLE_MAX = 99999999.0;

Graph::Graph() {
    adjacencyLists = nullptr;
    extractedVertices = nullptr;
    relaxedVertices = nullptr;
    predecessor = nullptr;
    distance = nullptr;

    numVertices = 0;
    numEdges = 0;
    isDirected = false;
    source = 0;
    graphTraversed = false;
    fullTraversal = false; 
    minHeap = MinHeap();
}

Graph::~Graph() {
    delete[] adjacencyLists;
    delete[] extractedVertices;
    delete[] relaxedVertices;
    delete[] predecessor;
    delete[] distance;
}

bool Graph::loadGraph(const string& filename, const string& direction) {
    std::ifstream file;
    file.open(filename);
    if(file.is_open() == false) {
        cout << "Failed to open the graph file." << endl;
        return false;
    }
    string line;
    getline(file, line);
    if(line.empty()) {
        cout << "Input file is empty" << endl;
        return false;
    }

    int n = 0, m = 0;
    std::stringstream ss(line);
    if(ss >> n >> m) {
        numVertices = n + 1;
        numEdges = m;

        adjacencyLists = new Edge*[numVertices];
        for(int i = 0; i < numVertices - 1; i++) {
            adjacencyLists[i] = NULL;
        }

        extractedVertices = new double[numVertices];
        relaxedVertices = new double[numVertices];
        predecessor = new int[numVertices];
        distance = new double[numVertices];
        
        for(int i = 0; i < numVertices - 1; i++) {
            extractedVertices[i] = -1;
            relaxedVertices[i] = -1;
        }
    }
    else {
        cout << "Invalid format for the first line in the input file." << endl;
        return false;
    }
    file.close();
    file.open(filename);
    if(file.is_open() == false) {
        cout << "Failed to reopen the graph file." << endl;
        return false;
    }

    getline(file, line);
    getline(file, line);

    while(line.empty() == false) {
        int edgeId = 0, startNode = 0, endNode = 0;
        double weight = 0;
        std::stringstream ss(line);

        if(ss >> edgeId >> startNode >> endNode >> weight) {
            startNode++;
            endNode++;

            if(startNode > numVertices || endNode > numVertices || startNode < 1 || endNode < 1) {
                cout << "Invalid node IDs in the input file." << endl;
                return false;
            }
            Edge* edge = new Edge();
            edge->destination = endNode;
            edge->weight = weight;

            if(adjacencyLists[startNode] == NULL) {
                adjacencyLists[startNode] = new Edge[numEdges];
            }
            int j = 0;
            while(adjacencyLists[startNode][j].destination != 0) {
                j++;
            }

            adjacencyLists[startNode][j] = *edge;

            if(direction == "undirected") {
                Edge* reverseEdge = new Edge();
                reverseEdge->destination = startNode;
                reverseEdge->weight = weight;

                if(adjacencyLists[endNode] == NULL) {
                    adjacencyLists[endNode] = new Edge[numEdges];
                }
                
                int j = 0;
                while(adjacencyLists[endNode][j].destination != 0) {
                    j++;
                }

                adjacencyLists[endNode][j] = *reverseEdge;

                delete reverseEdge;
            }

            delete edge;
        }
        else {
            cout << "Invalid format for edge in the input file." << endl;
            return false;
        }
        getline(file, line);
    }

    isDirected = (direction == "directed") ? true:false;
    file.close();
    return true;
}

void Graph::runDijkstra(int newSource, int destination, int flag) {
    int n = numVertices;
    int source = newSource;
    graphTraversed = true;
    fullTraversal = true;

    bool* extracted = new bool[n];
    for(int i = 0; i < n - 1; i++) {
        extracted[i] = false;
        extractedVertices[i] = -1;
        relaxedVertices[i] = -1;
        predecessor[i] = -1;
        distance[i] = DOUBLE_MAX;
    }

    extracted[source] = true;

    minHeap.init(n);
    distance[source] = 0;
    minHeap.push(0, source);

    if(flag == 1) {
        cout << "Insert vertext " << source << ", key = " << distance[source] << endl;
    }

    while(minHeap.empty() == false) {
        int u = minHeap.pop();

        extracted[u] = true;
        extractedVertices[u] = distance[u];

        if(flag == 1) {
            cout << "Delete vertex " << u << ", key = " << distance[u] << endl;
        }

        if(u == destination) {
            break;
        }

        if(adjacencyLists[u]) {
            int j = 0;
            while(adjacencyLists[u][j].destination != 0) {
                int v = adjacencyLists[u][j].destination;
                double w = adjacencyLists[u][j].weight;

                if(!extracted[v] && (distance[u] + w < distance[v])) {
                    double oldDistance = distance[v];
                    distance[v] = distance[u] + w;
                    predecessor[v] = u;
                    relaxedVertices[v] = distance[v];

                    if(oldDistance != DOUBLE_MAX && flag == 1) {
                        cout << "Decrease key of vertex " << v << ", from " << oldDistance << " to " << distance[v] << endl;
                    }

                    minHeap.push(distance[v], v);

                    if(flag == 1) {
                        cout << "Insert vertex " << v << ", key = " << distance[v] << endl;
                    }
                }
                j++;
            }
        } 
    }
    while(minHeap.empty() == false) {
        int u = minHeap.pop();
        if(extracted[u] == false) {
            fullTraversal = false;
        }
    }
    delete[] extracted;
}

void Graph::writePath(int s, int d) {
    if(graphTraversed == false) {
        cout << "Error: no path computation done" << endl;
        return;
    }

    if(s != source || d < 1 || d >= numVertices) {
        cout << "Error: invalid source destination pair" << endl;
        return;
    }

    if(extractedVertices[d] != -1) {
        int* path = new int[numVertices];
        int current = d;
        int pathSize = 0;

        while(current != s) {
            path[pathSize] = current;
            current = predecessor[current];
            pathSize++;
        }

        path[pathSize] = s;

        cout << "Shortest path: ";
        for(int i = pathSize; i > 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl << "The path weight is: " << distance[d] << endl;
        delete[] path;
    }
    else if (relaxedVertices[d] != -1) {
        int* path = new int[numVertices];
        int current = d;
        int pathSize = 0;

        while(current != s) {
            path[pathSize] = current;
            current = predecessor[current];
            pathSize++;
        }
        path[pathSize] = s;

        cout << "Path not known to be shortest: ";
        for(int i = pathSize; i > 0; i--) {
            cout << path[i] << " ";
        }
        cout << endl << "The path weight is: " << distance[d] << endl;

        delete[] path;
    }

    else if(fullTraversal == false) {
        cout << "No " << s << "-" << d << " path has been computed, yet." << endl;
    }

    else {
        cout << "No " << s << "-" << d << " path exists." << endl;
    }
}

void Graph::printAdjacencyLists() {
    for(int v = 0; v < numVertices; v++) {
        cout << "Adjacency list for vertec " << v << ": ";

        if(adjacencyLists[v] != NULL) {
            int j = 0;

            while(adjacencyLists[v][j].destination != 0) {
                cout << "(" << adjacencyLists[v][j].destination << ", " << adjacencyLists[v][j].weight << ") ";
                j++;
            }     
        }
        cout << "Predecessor: " << predecessor[v] << endl;
    }
}