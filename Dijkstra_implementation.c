#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

// Number of vertices in the graph
#define V 6

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the shortest path from source to destination
void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d -> ", j);
}

// Function to print the constructed distance array
void printSolution(int dist[], int parent[], int src) {
    printf("Vertex \t\t Distance from Source \t Path\n");
    for (int i = 0; i < V; i++) {
        printf("%d -> %d \t\t %d \t\t\t %d -> ", src, i, dist[i], src);
        printPath(parent, i);
        printf("\n");
    }
}

// Dijkstra's shortest path algorithm
void dijkstra(int graph[V][V], int src) {
    int dist[V];        // The output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[V];     // sptSet[i] will be true if vertex i is included in the shortest path tree or shortest distance from src to i is finalized
    int parent[V];      // Array to store shortest path tree

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it's not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Print the constructed distance array
    printSolution(dist, parent, src);
}

int main() {
    // Example graph representing flights (adjacency matrix)
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };

    int source = 0; // Source vertex
    dijkstra(graph, source); // Finding shortest path from source

    return 0;
}