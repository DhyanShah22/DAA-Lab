#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Edge {
    char src, dest;
    int weight;
};

struct Graph {
    int V, E;
    struct Edge* edge;
};

struct MinHeapNode {
    char src, dest;
    int weight;
};

struct MinHeap {
    int size;
    int capacity;
    struct MinHeapNode* array;
};

struct MinHeapNode* newMinHeapNode(char src, char dest, int weight) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->src = src;
    node->dest = dest;
    node->weight = weight;
    return node;
}

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

    if (left < minHeap->size && minHeap->array[left].weight < minHeap->array[smallest].weight)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right].weight < minHeap->array[smallest].weight)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[idx], &minHeap->array[smallest]);
        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = &minHeap->array[0];
    struct MinHeapNode* lastNode = &minHeap->array[minHeap->size - 1];
    minHeap->array[0] = *lastNode;
    minHeap->size--;
    minHeapify(minHeap, 0);

    return root;
}

void insertMinHeap(struct MinHeap* minHeap, char src, char dest, int weight) {
    minHeap->size++;
    minHeap->array[minHeap->size - 1] = *newMinHeapNode(src, dest, weight);

    int i = minHeap->size - 1;
    while (i != 0 && minHeap->array[(i - 1) / 2].weight > minHeap->array[i].weight) {
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int find(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    struct Edge result[V];
    int e = 0;
    int i = 0;

    struct MinHeap* minHeap = createMinHeap(graph->E);

    for (i = 0; i < graph->E; ++i) {
        char src, dest;
        int weight;
        printf("Enter edge %d source, destination, and weight: ", i + 1);
        scanf(" %c %c %d", &src, &dest, &weight);
        graph->edge[i] = (struct Edge){src, dest, weight};
        insertMinHeap(minHeap, src, dest, weight);
        insertMinHeap(minHeap, dest, src, weight); // Insert both directions for undirected graph
    }

    int parent[V];
    for (i = 0; i < V; i++)
        parent[i] = -1;

    while (e < V - 1 && !isEmpty(minHeap)) {
        struct MinHeapNode* nextEdge = extractMin(minHeap);

        int x = find(parent, nextEdge->src - 'A');
        int y = find(parent, nextEdge->dest - 'A');

        if (x != y) {
            result[e++] = (struct Edge){nextEdge->src, nextEdge->dest, nextEdge->weight};
            Union(parent, x, y);
        }
    }

    printf("Minimum Spanning Tree (Kruskal's Algorithm):\n");
    for (i = 0; i < e; ++i) {
        printf("Edge %d: %c -- %c\tWeight: %d\n", i + 1, result[i].src, result[i].dest, result[i].weight);
    }
}

int main() {
    printf("Dhyan Shah\n22BCP269\n");
    int V, E;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);

    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (struct Edge*)malloc(E * sizeof(struct Edge));

    kruskalMST(graph);

    free(graph->edge);
    free(graph);

    return 0;
}
