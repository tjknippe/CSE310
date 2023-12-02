#include "graph.h"

int main(int argc, char* argv[]) {
    char* graphFilename = argv[1];
    char* direction = argv[2];
    Graph* graph = new Graph();

    if(graph->loadGraph(graphFilename, direction) == false) {
        cout << "Failed to load the graph." << endl;
        return 1;
    }

    while(true) {
        string query;
        cin >> query;

        if(query == "find") {
            int source, destination, flag;
            cin >> source >> destination >> flag;
            graph->runDijkstra(source, destination, flag);
        }
        else if(query == "write") {
            int source, destination;
            cin >> source >> destination;
            graph->writePath(source, destination);
        }
        else if(query == "stop") {
            return 0;
        }
        else {
            cout << "Invalid query. Please use 'find', 'write', or 'stop'." << endl;
        }
    }





}