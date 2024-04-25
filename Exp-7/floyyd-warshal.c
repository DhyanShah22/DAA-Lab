#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100

void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int dist[V][V];

    // Initialize the solution matrix with the same values as the input graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Updating the solution matrix with shortest paths
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distances
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INT_MAX)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    int graph[MAX_VERTICES][MAX_VERTICES];
    // Initialize graph with INF
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = INT_MAX;

    printf("Enter the edges and their weights (v w c[v][w]):\n");
    for (int i = 0; i < E; i++) {
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        graph[v][w] = weight;
    }

    floydWarshall(graph, V);
    return 0;
}
