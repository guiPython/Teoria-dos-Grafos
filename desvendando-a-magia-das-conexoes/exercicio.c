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

typedef struct Component {
    int size;
    Vertex* nodes;
} Component;

typedef struct Stack {
    int capacity;
    int size;
    Vertex* items;
} Stack;

typedef struct Dfs {
    int time;
    int* times;
    int* smallest_times;
    bool* in_stack;
    int regions;
    Component** components;
    Stack* stack;
} Dfs;

int min(int a, int b);
int compare(const void* a, const void* b);

Component* component(int capacity);

Stack* stack(int capacity);
bool isEmpty(Stack);
bool isFull(Stack);
void insert(Stack*, Vertex);
int pop(Stack*);
void destroy(Stack*);

Dfs* control(int graphOrder);
void dealloc(Dfs* control);

void dfs(Graph, Vertex, Dfs*);
void tarjan(Graph);

int main() {
    int vertices, edges, u, v;
    scanf("%d %d", &vertices, &edges);
    Graph g = graph(vertices);

    for(int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        digraph_insert_edge(g, edge(u, v, 1));
    }

    tarjan(g);
    graph_destroy(g);
}

void tarjan(Graph graph) {
    int order = graph_order(graph);
    Dfs* result = control(order);
    for(int i = 0; i < order; i++)
        if(result->times[i] == -1) dfs(graph, i, result);

    if(result->regions == 1) printf("Ha 1 regiao altamente conectada:\n");
    else printf("Ha %d regioes altamente conectadas:\n", result->regions);
    
    for(int i = 0; i < result->regions; i++) {
        for(int j = 0; j < result->components[i]->size; j++) {
            printf("%d ", result->components[i]->nodes[j]);
        }
        printf("\n");
    }

    dealloc(result);
}

void dfs(Graph graph, Vertex vertex, Dfs* control) {
    int degree = graph_vertex_degree(graph, vertex);
    int neighbors[degree];
    graph_neighbors(graph, vertex, neighbors);
    
    control->times[vertex] = control->time;
    control->smallest_times[vertex] = control->time;
    control->time++;
    control->in_stack[vertex] = true;
    insert(control->stack, vertex);

    for(int i = 0; i < degree; i++){
        int neighbor = neighbors[i];
        if(control->times[neighbor] == -1) {
            dfs(graph, neighbor, control);
            control->smallest_times[vertex] = min(
                control->smallest_times[neighbor], 
                control->smallest_times[vertex]);
        }

        else if(control->in_stack[neighbor]) {
            control->smallest_times[vertex] = min(
                control->smallest_times[neighbor], 
                control->smallest_times[vertex]);
        }
    }

    if(control->smallest_times[vertex] == control->times[vertex]) {
        Component* c = component(control->stack->size);
        int element;
        do {
            element = pop(control->stack);
            c->nodes[c->size] = element;
            c->size++;
            control->in_stack[element] = false;
        } while(element != vertex);
        control->in_stack[element] = false;
        qsort(c->nodes, c->size, sizeof(int), compare);
        control->components[control->regions] = c;
        control->regions++;
    }
}

Component* component(int capacity) {
    Component* component = malloc(sizeof(Component));
    component->size = 0;
    component->nodes = malloc(sizeof(int) * capacity);
    return component;
}

Dfs* control(int graphOrder) {
    Dfs* dfs = malloc(sizeof(Dfs));
    dfs->time = 0;
    dfs->regions = 0;
    dfs->components = malloc(sizeof(Component*) * graphOrder);
    dfs->times = malloc(sizeof(int) * graphOrder);
    dfs->smallest_times = malloc(sizeof(int) * graphOrder);
    dfs->in_stack = malloc(sizeof(bool) * graphOrder);
    dfs->stack = stack(graphOrder);
    for(int i = 0; i < graphOrder; i++) {
        dfs->times[i] = -1;
        dfs->smallest_times[i] = -1;
        dfs->in_stack[i] = false;
        dfs->components[i] = NULL;
    }
    return dfs;
}

void dealloc(Dfs* control) {
    free(control->times);
    free(control->smallest_times);
    free(control->in_stack);
    for(int i = 0; i < control->regions; i++) 
        free(control->components[i]->nodes);
    free(control->components);
    destroy(control->stack);
    free(control);
}

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

Stack* stack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->size = 0;
    stack->items = malloc(sizeof(int) * capacity);
    return stack;
}

bool isFull(Stack stack) {
    return stack.capacity == stack.size;
}

bool isEmpty(Stack stack) {
    return stack.size == 0;
}

void insert(Stack* stack, int value) {
    if(isFull(*stack)) return;
    stack->items[stack->size] = value;
    stack->size++;
}

int pop(Stack* stack) {
    if(isEmpty(*stack)) return -1;
    stack->size--;
    return stack->items[stack->size];
}

void destroy(Stack* stack) {
    free(stack->items);
    free(stack);
}

/**
 * Find minimum between two numbers.
 */
int min(int a, int b) {
    return (a > b) ? b : a;
}