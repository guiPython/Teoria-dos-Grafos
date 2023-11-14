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

#define NAO_VISITADO 0
#define AZUL 1
#define VERMELHO 2

struct fila {
    int* itens;
    int capacidade;
    int primeiro;
    int ultimo;
    int tamanho;
};

typedef struct fila* Fila;

Fila nova_fila(int tamanho);
void enfilera(Fila, int item);
int desenfilera(Fila);
bool esta_vazia(Fila);
void destroi_fila(Fila);

bool tem_ciclo(Graph);
bool bfs(Graph, Vertex, bool*);

int main() {
    int vertices, arestas, origem, destino;
    scanf("%d %d", &vertices, &arestas);
    Graph grafo = graph(vertices);

    for(int i = 0; i < arestas; i++) {
        scanf("%d %d", &origem, &destino);
        graph_insert_edge(grafo, edge(origem, destino));
    }

    if(tem_ciclo(grafo)) printf("GUERRA!\n");
    else printf("PAZ!\n");
    graph_destroy(grafo);
    return 0;
}

/*
    Chama a busca em largura para todos os vértices do grafo de entrada.
    @param Graph o grafo que vamos verificar se temos ciclo.
    @return true se tem ciclo e false caso contrário.
*/
bool tem_ciclo(Graph graph) {
    int vertices = graph_order(graph);
    bool visitados[vertices];
    for(int i = 0; i < vertices; i++) visitados[i] = false;

    for(int i = 0; i < vertices; i++) {
        if(!visitados[i] && bfs(graph, i, visitados)) return true;
    }
    return false;
}

/*
    Executa uma busca em largura no grafo iniciando pelo vértice desejado 
    modificando o array de visitas dos vértices do grafo.
    @param Graph o grafo que vamos executar a busca.
    @param Vertex o vértice raiz do caminho.
    @param bool* o array de visitas.
    @return true caso um nó seja visitado mais de uma vez por nós distintos, i.e,
    a lista de predecessores para um nó pai contenha um valor diferente do filho que estamos testando,
    caso o vértice não tenha essa caracteristica é retornado false.
*/
bool bfs(Graph grafo, Vertex vertice, bool* visitados) {
    int vertices = graph_order(grafo);
    Fila fila = nova_fila(vertices);
    int predecessores[vertices];

    for(int i = 0; i < vertices; i++) {
        visitados[i] = false;
        predecessores[i] = -1;
    }

    visitados[vertice] = true;
    enfilera(fila, vertice);

    while(!esta_vazia(fila)) {
        Vertex pai = desenfilera(fila);
        int grau = graph_vertex_degree(grafo, pai);
        Vertex filhos[grau];
        graph_neighbors(grafo, pai, filhos);

        for(int i = 0; i < grau; i++) {
            Vertex filho = filhos[i];
            if(!visitados[filho]) {
                visitados[filho] = true;
                enfilera(fila, filho);
                predecessores[filho] = pai;
            } else if(predecessores[pai] != filho) {
                return true;
            }
        }
    }
    destroi_fila(fila);
    return false;
}

/* 
    Implementação de fila com array circular.
    @param int capacidade da fila.
    @return fila criada com a capacidade informada.
*/
Fila nova_fila(int capacidade) {
    Fila fila = malloc(sizeof(Fila));
 
    fila->itens = (int*)malloc(capacidade * sizeof(int));
    fila->capacidade = capacidade;
    fila->primeiro = 0;
    fila->ultimo = -1;
    fila->tamanho = 0;
 
    return fila;
}
 
/*
    Função utilitária para verificar se a queue está vazia ou não
    @param Fila que será verificada.
    @return true caso esteja vazia e false caso não esteja.
*/
bool esta_vazia(Fila fila) {
    return fila->tamanho == 0;
}

/*
    Adiciona um elemento no final da fila aumentando seu tamanho.
    @param Fila que sera adicionado o elemento.
    @param int elemento que será adicionado na fila.
*/
void enfilera(Fila fila, int item) {
    if (fila->tamanho == fila->capacidade)
    {
        printf("A fila está cheia, não foi possivel adicionar o elemento.\n");
        exit(EXIT_FAILURE);
    }
 
    fila->ultimo = (fila->ultimo + 1) % fila->capacidade;
    fila->itens[fila->ultimo] = item;
    fila->tamanho++;
}
 
/* 
    Remove o primeiro elemento da fila diminuindo seu tamanho.
    @param Fila em que será removido o primeiro elemento.
    @return o primeiro item de fila.
*/
int desenfilera(Fila fila) {
    if (esta_vazia(fila)) {
        printf("A fila está vazia, não foi possivel remover o elemento.\n");
        exit(EXIT_FAILURE);
    }

    int primeiro = fila->itens[fila->primeiro];
    
    fila->primeiro = (fila->primeiro + 1) % fila->capacidade;
    fila->tamanho--;
    return primeiro;
}

/*
    Libera a memória alocada dinâmicamente na construção da fila.
    @param Fila que vai ser desalocada.
*/
void destroi_fila(Fila fila) {
    free(fila->itens);
    free(fila);
}