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

typedef struct Pair {
    int node;
    double weight;
} Pair;

typedef struct Heap {
    int capacity;
    int size;
    int* node_position;
    Pair** pairs;
} Heap;

int min(int a, int b);
int max(int a, int b);

Heap* heap(int size);
Pair* getMin(Heap*);
void heapify(Heap*, int index);
void swap(int index, int other, Pair** items);
void update(Heap*, int node, double weight);
bool isEmpty(Heap);
double weightByIndex(Heap heap, int index);
bool contains(Heap, int node);
void destroy(Heap*);

void prim(Graph g, double** weights);

int main() {
    int vertices, edges, u, v;
    double w;

    scanf("%d %d", &vertices, &edges);
    Graph g = graph(vertices);

    double* weights[vertices];
    for(int i = 0; i < vertices; i++) {
        weights[i] = malloc(sizeof(double) * vertices);
    }

    for(int i = 0; i < edges; i++) {
        scanf("%d %d %lf", &u, &v, &w);
        graph_insert_edge(g, edge(u, v));
        weights[u][v] = w;
        weights[v][u] = w;
    }

    prim(g, weights);
    graph_destroy(g);
    for(int i = 0; i < vertices; i++) free(weights[i]);
    return 0;
}

void prim(Graph g, double** weights) {
    double total = 0.0;
    int order = graph_order(g);
    Heap* h = heap(order);
    int pred[order];
    double weight[order];
    

    for(int i = 0; i < order; i++) {
        pred[i] = -1;
        weight[i] = INFINITY;
    }
    
    weight[0] = 0.0;
    pred[0] = 0;

    while(!isEmpty(*h)) {
        Pair* pair = getMin(h);
        int node = pair->node;
        int degree = graph_vertex_degree(g, node);
        int neighbors[degree];
        graph_neighbors(g, node, neighbors);

        for(int i = 0; i < degree; i++) {
            int neighbor = neighbors[i];
            if(contains(*h, neighbor) && weight[neighbor] > weights[node][neighbor]) {
                pred[neighbor] = node;
                weight[neighbor] = weights[node][neighbor];
                update(h, neighbor, weight[neighbor]);
            }
        }
    }

    for(int i = 0; i < order; i++) total += weight[i];
    printf("%.2f\n", total);

    for(int i = 0; i < order; i++) {
        if(i != pred[i]) printf("%d %d\n", min(i, pred[i]), max(i, pred[i]));
    }

    destroy(h);
}

Pair* pair(int node, double weight) {
    Pair* pair = malloc(sizeof(Pair));
    pair->node = node;
    pair->weight = weight;
    return pair;
}

Heap* heap(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    heap->size = capacity;
    heap->capacity = capacity;
    heap->node_position = malloc(sizeof(int) * capacity);
    heap->pairs = malloc(sizeof(Pair*) * capacity);

    for(int i = 0; i < capacity; i++) {
        heap->node_position[i] = i;
        heap->pairs[i] = pair(i, INFINITY); 
    }

    heap->pairs[0]->weight = 0.0f;
    return heap;
}

Pair* getMin(Heap* heap) {
    if(isEmpty(*heap)) return NULL;
 
    Pair* first = heap->pairs[0];
    Pair* last = heap->pairs[heap->size - 1];
    heap->pairs[0] = last;
 
    heap->node_position[first->node] = heap->size - 1;
    heap->node_position[last->node] = 0;
 
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
        Pair* smallest_pair = heap->pairs[smallest];
        Pair* idx_pair = heap->pairs[idx];
 
        heap->node_position[smallest_pair->node] = idx;
        heap->node_position[idx_pair->node] = smallest;
 
        swap(smallest,idx, heap->pairs);
        heapify(heap, smallest);
    }
}

void update(Heap* heap, int node, double new_weight) {
    int position = heap->node_position[node];
    int parent = (position - 1) / 2;
    heap->pairs[position]->weight = new_weight;

    while(parent >= 0 && weightByIndex(*heap, parent) > new_weight) {
        heap->node_position[node] = parent;
        heap->node_position[heap->pairs[parent]->node] = position;
        swap(parent, position, heap->pairs);
        position = parent;
        parent = (parent - 1) / 2;
    }
}

bool isEmpty(Heap heap) {
    return heap.size == 0;
}

bool contains(Heap heap, int node) {
    int position = heap.node_position[node];
    int heap_size = heap.size;
    return position < heap_size;
}

double weightByIndex(Heap heap, int index) {
    return heap.pairs[index]->weight;
}

void swap(int index, int other, Pair** items) {
    Pair* aux = items[index];
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