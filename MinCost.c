#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VERTICES 1000
#define INF 999999

// Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// Structure to represent the graph
struct Graph {
    int V, E;
    struct Edge edges[MAX_VERTICES];
};

// Function to create a graph
void createGraph(struct Graph *graph) {
    printf("Enter the number of vertices (V): ");
    scanf("%d", &graph->V);

    printf("Enter the number of edges (E): ");
    scanf("%d", &graph->E);

    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < graph->E; i++) {
        scanf("%d %d %d", &graph->edges[i].src, &graph->edges[i].dest, &graph->edges[i].weight);
    }
}

// Function to compare two edges based on their weights for sorting
int compareEdges(const void *a, const void *b) {
    return ((struct Edge *)a)->weight - ((struct Edge *)b)->weight;
}

// Function to find the parent of a vertex in the disjoint set
int findParent(int parent[], int vertex) {
    if (parent[vertex] != vertex)
        parent[vertex] = findParent(parent, parent[vertex]);
    return parent[vertex];
}

// Function to perform Union of two subsets
void performUnion(int parent[], int rank[], int x, int y) {
    int rootX = findParent(parent, x);
    int rootY = findParent(parent, y);

    if (rank[rootX] < rank[rootY])
        parent[rootX] = rootY;
    else if (rank[rootX] > rank[rootY])
        parent[rootY] = rootX;
    else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Function to find Minimum Cost Spanning Tree using Kruskal's Algorithm
void kruskalMST(struct Graph *graph) {
    struct Edge result[MAX_VERTICES];
    int parent[MAX_VERTICES], rank[MAX_VERTICES];
    int resultIndex = 0;

    // Sort the edges in non-decreasing order of their weights
    qsort(graph->edges, graph->E, sizeof(struct Edge), compareEdges);

    // Initialize parent array for disjoint set and rank array for union-find
    for (int i = 0; i < graph->V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    // Iterate through all edges and add the ones that don't form a cycle
    for (int i = 0; i < graph->E; i++) {
        int src = graph->edges[i].src;
        int dest = graph->edges[i].dest;

        int rootSrc = findParent(parent, src);
        int rootDest = findParent(parent, dest);

        if (rootSrc != rootDest) {
            result[resultIndex++] = graph->edges[i];
            performUnion(parent, rank, rootSrc, rootDest);
        }
    }

    // Print the Minimum Cost Spanning Tree
    printf("\nMinimum Cost Spanning Tree (Kruskal's Algorithm):\n");
    for (int i = 0; i < resultIndex; i++) {
        printf("%d - %d : %d\n", result[i].src, result[i].dest, result[i].weight);
    }
}

// Function to find the index of the edge with the minimum weight in the given array
int findMinWeightEdge(int key[], bool mstSet[], int V) {
    int minWeight = INF;
    int minWeightIndex = -1;

    for (int v = 0; v < V; v++) {
        if (!mstSet[v] && key[v] < minWeight) {
            minWeight = key[v];
            minWeightIndex = v;
        }
    }

    return minWeightIndex;
}

// Function to find Minimum Cost Spanning Tree using Prim's Algorithm
void primMST(struct Graph *graph) {
    int parent[MAX_VERTICES], key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];
    int src = 0;

    // Initialize key array with INF and mstSet array with false
    for (int v = 0; v < graph->V; v++) {
        key[v] = INF;
        mstSet[v] = false;
    }

    // Start with the first vertex as the source
    key[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < graph->V - 1; count++) {
        int u = findMinWeightEdge(key, mstSet, graph->V);
        mstSet[u] = true;

        // Update the key values and parents of adjacent vertices
        for (int v = 0; v < graph->V; v++) {
            if (graph->edges[v].weight && !mstSet[v] && graph->edges[v].weight < key[v]) {
                parent[v] = u;
                key[v] = graph->edges[v].weight;
            }
        }
    }

    // Print the Minimum Cost Spanning Tree
    printf("\nMinimum Cost Spanning Tree (Prim's Algorithm):\n");
    for (int i = 1; i < graph->V; i++) {
        printf("%d - %d : %d\n", parent[i], i, graph->edges[i].weight);
    }
}

int main() {
    struct Graph graph;
    createGraph(&graph);

    kruskalMST(&graph);
    primMST(&graph);

    return 0;
}
