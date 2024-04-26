#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

struct Edge {
    char src, dest;
    int weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct MinHeapNode {
    char vertex;
    int key;
};

struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode* array;
};

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode*)malloc(capacity * sizeof(struct MinHeapNode));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode* a, struct MinHeapNode* b) {
    struct MinHeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left].key < minHeap->array[smallest].key)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].key < minHeap->array[smallest].key)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

struct MinHeapNode extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode minNode = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return minNode;
}

void decreaseKey(struct MinHeap* minHeap, int v, int key) {
    int i;
    for (i = 0; i < minHeap->size; ++i) {
        if (minHeap->array[i].vertex == v) {
            minHeap->array[i].key = key;
            break;
        }
    }
    while (i && minHeap->array[i].key < minHeap->array[(i - 1) / 2].key) {
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void primMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int parent[V];
    struct MinHeap* minHeap = createMinHeap(V);
    int i;

    for (i = 1; i < V; ++i) {
        parent[i] = -1;
        minHeap->array[i].vertex = i + 'A'; 
        minHeap->array[i].key = INT_MAX;
    }

    minHeap->array[0].vertex = 'A'; 
    minHeap->array[0].key = 0;
    minHeap->size = V;

    while (!isEmpty(minHeap)) {
        struct MinHeapNode minNode = extractMin(minHeap);
        char u = minNode.vertex;
        for (i = 0; i < graph->E; ++i) {
            if (graph->edge[i].src == u || graph->edge[i].dest == u) {
                char v = (graph->edge[i].src == u) ? graph->edge[i].dest : graph->edge[i].src;
                int weight = graph->edge[i].weight;
                int vIdx = v - 'A';
                if (weight < minHeap->array[vIdx].key && minHeap->array[vIdx].key != -1) {
                    parent[vIdx] = u - 'A';
                    decreaseKey(minHeap, v, weight);
                }
            }
        }
    }

    printf("Minimum Spanning Tree (Prim's Algorithm):\n");
    for (i = 1; i < V; ++i)
        printf("Edge %d: %c -- %c\tWeight: %d\n", i, parent[i] + 'A', i + 'A', minHeap->array[i].key);
}

int main() {
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));

    for (int i = 0; i < E; ++i) {
        char src, dest;
        int weight;
        printf("Enter edge %d source, destination, and weight: ", i + 1);
        scanf(" %c %c %d", &src, &dest, &weight);
        graph->edge[i] = (struct Edge){src, dest, weight};
    }

    primMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}
