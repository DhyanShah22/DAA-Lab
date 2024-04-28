#include<stdio.h>
#include<limits.h>

#define MAX_VERTICES 100

void floyydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V)
{
    int dist[V][V];
    for(int i =0; i<V;i++){
        for(int j=0; j<V;j++){
            dist[i][j] = graph[i][j];
        }
    }

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

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
    int V,E;
    printf("Enter the Vertices and Edges\n");
    scanf("%d %d",&V, &E);

    int graph[MAX_VERTICES][MAX_VERTICES];
    for(int i=0;i<V;i++){
        for(int j=0;j<V;j++){
            graph[i][j]= INT_MAX;
        }
    }

    printf("Enter the v,w and Vw\n");
    for( int i=0;i<E;i++){
        int v, w, weight;
        scanf("%d %d %d", &v, &w, &weight);
        graph[v][w] = weight;
        }

    floyydWarshall(graph, V);
    return 0;
}