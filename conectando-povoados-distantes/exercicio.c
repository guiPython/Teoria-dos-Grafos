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

#define NOT_VISITED -1

typedef struct Solution {
    int* pred;
    float weight;
} Solution;

typedef struct Neighbor {
    int vertex;
    float weight;
} Neighbor;

typedef struct Heap {
    int capacity;
    int position;
    Neighbor* neighbors;
} Heap;

Heap* heap(int size);
void swap(int index, int other, int* items);
void insert(Heap* heap, Neighbor neighbor);
void heap_destroy(Heap* heap);

Solution* prim(Graph);
void solution_destroy(Solution*);
void show_solution(Solution);

int main() {
    int vertexes, edges, u, v;
    float w;

    scanf("%d %d", &vertexes, &edges);
    Graph g = graph(vertexes);

    for(int i = 0; i < edges; i++) {
        scanf("%d %d %f", &u, &v, &w);
        graph_insert_edge(g, edgeWithWeight(u, v, w));
    }

    Solution* solution = prim(g);
    show_solution(*solution);

    graph_destroy(g);
    solution_destroy(solution);
    return 0;
}

Solution* prim(Graph g) {
    int visiteds = 0;
    int order = graph_order(g);
    Solution* solution = malloc(sizeof(Solution*));
    solution->pred = malloc(sizeof(int) * order);
    solution->weight = INFINITY;

    for(int i = 0; i <= order; i++) solution->pred[i] = NOT_VISITED;

    while()
}


Heap* heap(int size){
    Heap* heap = malloc(sizeof(Heap));
    heap->capacity = size;
    heap->position = 0;
    heap->neighbors = malloc(sizeof(Neighbor) * size);
    return heap;
}

void insert(Heap* heap, Neighbor neighbor) {
    int position = heap->position;
    heap->neighbors[position] = neighbor;
    int leftChildIndex = 2 * position + 1; 
    int rightChildIndex = 2 * position + 2;
    int childIndex;

    while(leftChildIndex < position) {
        if(rightChildIndex < heap->capacity && 
            heap->neighbors[rightChildIndex].weight < heap->neighbors[leftChildIndex].weight) {
            childIndex = rightChildIndex;
        } else {
            childIndex = leftChildIndex;
        }

        if(heap->neighbors[childIndex].weight > heap->neighbors[position].weight) {
            break;   
        }

        swap(position, childIndex, heap->neighbors);
        position = childIndex;
        leftChildIndex = 2 * position + 1;
        rightChildIndex = 2 * position + 2;
    }
}

void swap(int index, int other, int* items) {
    int aux = items[index];
    items[index] = items[other];
    items[other] = aux;
}

void heap_destroy(Heap* heap) {
    free(heap->neighbors);
    free(heap);
}