/******************************************************************************
 *
 * Created by: Carla Negri Lintzmayer
 *             Maycon Sambinelli
 * To be used by our students
 *
 *****************************************************************************/


#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "graph.h"
#include "utils.h"

typedef struct node *link;

struct node {
    Vertex w; 
    Weight weight;
    link next;
};

link list_insert(link head, Vertex w, Weight weight) {
    link p = Malloc(sizeof(*p));
    p->w = w;
    p->next = head;
    p->weight = weight;
    return p;
}

link list_remove(link head, Vertex w) {
    if (head == NULL)
        return NULL;

    if (head->w == w) {
        link p = head->next;
        free(head);
        return p;
    } else {
        head->next = list_remove(head->next, w);
        return head;
    }
}

link list_destroy(link head) {
    if (head) {
        list_destroy(head->next);
        free(head);
    }
    return NULL;
}

struct graph {
    int V;
    int E;
    link *adj;
};

Graph graph(int V) {
    assert(V > 0);

    // http://c-faq.com/aryptr/fn33.html
    Graph G = Malloc(sizeof(*G));

    G->V = V;
    G->E = 0;
    G->adj = Malloc(V * sizeof(link));

    for (Vertex u = 0; u < V; u++)
        G->adj[u] = NULL;
    
    return G;
}

void graph_destroy(Graph G) {
    assert(G);

    for (Vertex u = 0; u < G->V; u++)
        list_destroy(G->adj[u]);
    free(G->adj);
    free(G);
}

int graph_order(Graph G) {
    assert(G);
    return G->V;
}

int graph_num_edges(Graph G) {
    assert(G);
    return G->E;
}

void graph_insert_edge(Graph G, Edge e) {
    assert(G);
    assert(e.u >= 0 && e.u < G->V);
    assert(e.v >= 0 && e.v < G->V);

    G->adj[e.u] = list_insert(G->adj[e.u], e.v, e.weight);
    G->adj[e.v] = list_insert(G->adj[e.v], e.u, e.weight);
    G->E += 1;
}

void digraph_insert_edge(Graph G, Edge e) {
    assert(G);
    assert(e.u >= 0 && e.u < G->V);
    assert(e.v >= 0 && e.v < G->V);

    G->adj[e.u] = list_insert(G->adj[e.u], e.v, e.weight);
    G->E += 1;  
}

void graph_remove_edge(Graph G, Edge e) {
    assert(G);
    assert(e.u >= 0 && e.u < G->V);
    assert(e.v >= 0 && e.v < G->V);

    if (!graph_has_edge(G, e))
        return;

    G->E -= 1;
    G->adj[e.u] = list_remove(G->adj[e.u], e.v);
    G->adj[e.v] = list_remove(G->adj[e.v], e.u);
}

int graph_has_edge(Graph G, Edge e) {
    assert(G);
    assert(e.u >= 0 && e.u < G->V);
    assert(e.v >= 0 && e.v < G->V);

    for (link p = G->adj[e.u]; p != NULL; p = p->next)
        if (p->w == e.v)
            return 1;
    return 0;
}

int graph_edges(Graph G, Edge* edges) {
    assert(G);
    assert(edges);

    int k = 0;
    for (Vertex u = 0; u < G->V; u++)
        for (link p = G->adj[u]; p != NULL; p = p->next) {
            if(p->weight > 0) {
                edges[k] = edge(u, p->w, 1);
                k += 1;
            }
        }
    return k;
}

int graph_vertex_degree(Graph G, Vertex u) {
    assert(G);
    assert(u >= 0 && u < G->V);
    
    int d = 0;
    for (link p = G->adj[u]; p != NULL; p = p->next)
        d += 1;
    return d;
}

int graph_neighbors(Graph G, Vertex u, Vertex* neigh) {
    assert(G);
    assert(u >= 0 && u < G->V);
    assert(neigh);
    
    int k = 0;
    for (link p = G->adj[u]; p != NULL; p = p->next) {
        neigh[k] = p->w;
        k += 1;
    }
    return k;
}

int graph_neighbors_with_weight(Graph G, Vertex u, Pair* pairs) {
    assert(G);
    assert(u >= 0 && u < G->V);
    assert(pairs);
    
    int k = 0;
    for (link p = G->adj[u]; p != NULL; p = p->next) {
        pairs[k] = pair(p->w, p->weight);
        k += 1;
    }
    return k;
}

Graph graph_copy(Graph G) {
    assert(G);

    Graph H = graph(G->V);

    for (Vertex u = 0; u < G->V; u++)
        for (link p = G->adj[u]; p != NULL; p = p->next)
            graph_insert_edge(H, edge(u, p->w, p->weight));

    return H;
}

void graph_print(Graph G) {
    assert(G);

    printf("V: %d, E: %d", G->V, G->E);
    for (Vertex u = 0; u < G->V; u++) {
        printf("%2d: ", u);
        for (link p = G->adj[u]; p != NULL; p = p->next) 
            printf("%d, ", p->w);
        printf("\n");
    }
}


void graph_print_edges(Graph G) {
    assert(G);

    printf("%d %d\n", G->V, G->E);
    for (Vertex u = 0; u < G->V; u++)
        for (link p = G->adj[u]; p != NULL; p = p->next) 
            if (u < p->w)
                printf("%d %d\n", u, p->w);
}