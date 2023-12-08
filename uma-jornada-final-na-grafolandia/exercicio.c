/******************************************************************************
 *
 * Criado por: Guilherme Rocha Muzi Franco
 * Disciplina: Teoria dos Grafos 2023 - Q3
 * RA: 11201920623
 *
 *****************************************************************************/
#include "../lib/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Heap {
    int capacity;
    int size;
    int* node_position;
    Pair* pairs;
} Heap;

int min(int a, int b);
int max(int a, int b);

Heap* heap(int size, int source);
Pair getMin(Heap*);
void heapify(Heap*, int index);
void swap(int index, int other, Pair* items);
void update(Heap*, Pair);
bool isEmpty(Heap);
double weightByIndex(Heap heap, int index);
void destroy(Heap*);

void dijkstra(Graph g, int source, int destiny);

int main() {
    int vertices, edges, u, v, povoado;
    int w;

    scanf("%d %d", &vertices, &edges);
    scanf("%d", &povoado);
    Graph g = graph(vertices);

    for(int i = 0; i < edges; i++) {
        scanf("%d %d %d", &u, &v, &w);
        digraph_insert_edge(g, edge(u, v, w));
    }

    for(int i = 0; i < vertices; i++)
        dijkstra(g, povoado, i);

    graph_destroy(g);
    return 0;
}

void dijkstra(Graph g, int source, int destiny) {
    if(source == destiny){
        printf("%d-%d: o mais barato eh ficar em casa\n", 
            source, source);
        return;
    }

    int order = graph_order(g);
    int parents[order];
    double dist[order];
    Heap* h = heap(order, source);
    for(int i = 0; i < order; i++) {
        parents[i] = i;
        dist[i] = INFINITY;
    }

    dist[source] = 0;
    update(h, pair(source, dist[source]));

    while(!isEmpty(*h)) {
        Pair p = getMin(h);
        int node = p.v;
        int degree = graph_vertex_degree(g, node);
        Pair neighbors[degree];
        graph_neighbors_with_weight(g, node, neighbors); 

         for (int i = 0; i < degree; i++) {
            Pair neighbor = neighbors[i];
            if(dist[neighbor.v] > dist[node] + neighbor.weight) {
                dist[neighbor.v] = dist[node] + neighbor.weight;
                parents[neighbor.v] = node; 
                update(h, pair(neighbor.v, dist[neighbor.v]));
            }
        }
    }
    
    if(dist[destiny] == INFINITY) {
        printf("%d-%d: impossivel\n", source, destiny);
        return;
    }

    int path[order];
    int index = 0;
    int aux = destiny;
    printf("%d-%d: %d ", source, destiny, source);
    while(parents[aux] != aux) {
        path[index++] = aux;
        aux = parents[aux];
    }
    for(int i = index - 1; i >= 0; i--) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

Heap* heap(int capacity, int source) {
    Heap* heap = malloc(sizeof(Heap));
    heap->size = capacity;
    heap->capacity = capacity;
    heap->node_position = malloc(sizeof(int) * capacity);
    heap->pairs = malloc(sizeof(Pair) * capacity);

    for(int i = 0; i < capacity; i++) {
        heap->node_position[i] = i;
        heap->pairs[i] = pair(i, INFINITY); 
    }
    return heap;
}

Pair getMin(Heap* heap) {
    Pair first = heap->pairs[0];
    Pair last = heap->pairs[heap->size - 1];
    heap->pairs[0] = last;
 
    heap->node_position[first.v] = heap->size - 1;
    heap->node_position[last.v] = 0;
 
    heap->size--;
    heapify(heap, 0);
 
    return first;
}

void heapify(Heap* heap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < heap->size
        && weightByIndex(*heap, left) < weightByIndex(*heap, smallest))
        smallest = left;
 
    if (right < heap->size
        && weightByIndex(*heap, right) < weightByIndex(*heap, smallest))
        smallest = right;
 
    if (smallest != idx) {
        Pair smallest_pair = heap->pairs[smallest];
        Pair idx_pair = heap->pairs[idx];
 
        heap->node_position[smallest_pair.v] = idx;
        heap->node_position[idx_pair.v] = smallest;
 
        swap(smallest,idx, heap->pairs);
        heapify(heap, smallest);
    }
}

void update(Heap* heap, Pair pair) {
    int position = heap->node_position[pair.v];
    int parent = (position - 1) / 2;
    heap->pairs[position] = pair;

    while(parent >= 0 && weightByIndex(*heap, parent) > pair.weight) {
        heap->node_position[pair.v] = parent;
        heap->node_position[heap->pairs[parent].v] = position;
        swap(parent, position, heap->pairs);
        position = parent;
        parent = (parent - 1) / 2;
    }
}

bool isEmpty(Heap heap) {
    return heap.size == 0;
}

double weightByIndex(Heap heap, int index) {
    return heap.pairs[index].weight;
}

void swap(int index, int other, Pair* items) {
    Pair aux = items[index];
    items[index] = items[other];
    items[other] = aux;
}

void destroy(Heap* heap) {
    free(heap->pairs);
    free(heap->node_position);
    free(heap);
}

/**
 * Find maximum between two numbers.
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Find minimum between two numbers.
 */
int min(int a, int b) {
    return (a > b) ? b : a;
}