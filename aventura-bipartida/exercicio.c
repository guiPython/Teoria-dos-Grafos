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

struct solucao {
    Graph grafo;
    int* cores;
    int qtdConflitantes;
    int* conflitantes;
    bool ehPacifica;
};

struct fila {
    int* itens;
    int capacidade;
    int primeiro;
    int ultimo;
    int tamanho;
};

typedef struct fila* Fila;
typedef struct solucao* Solucao;

Solucao nova_solucao(Graph);
void mostra_solucao(Solucao);
void colore_vertice(Solucao, int pai, int vertice);
void adiciona_conflitante(Solucao, int vizinho);
bool conflitantes_contem(Solucao, int vertice);
void destroi_solucao(Solucao);

Fila nova_fila(int tamanho);
void enfilera(Fila, int item);
int desenfilera(Fila);
bool esta_vazia(Fila);
void destroi_fila(Fila);

void sera_que_vai_ter_guerra(Graph);
void bfs(Solucao, Vertex);

int main() {
    int vertices, arestas, origem, destino;
    scanf("%d %d", &vertices, &arestas);
    Graph grafo = graph(vertices);
    for(int i = 0; i < arestas; i++) {
        scanf("%d %d", &origem, &destino);
        graph_insert_edge(grafo, edge(origem, destino));
    }
    sera_que_vai_ter_guerra(grafo);
    graph_destroy(grafo);
    return 0;
}

/*
    Chama a busca em largura para todos os vértices do grafo de entrada.
    @param Graph o grafo que vamos executar a busca.
*/
void sera_que_vai_ter_guerra(Graph graph) {
    Solucao solucao = nova_solucao(graph);
    int vertices = graph_order(graph);
    for(int i = 0; i < vertices; i++) {
        if(solucao->cores[i] == NAO_VISITADO)
            bfs(solucao, i);
    }
    mostra_solucao(solucao);
    destroi_solucao(solucao);
}

/*
    Executa uma busca em largura no grafo iniciando pelo vértice desejado 
    modificando o array de cores que também funciona como 
    controle de visitas dos vértices do grafo.
    @param Graph o grafo que vamos executar a busca.
    @param Vertex o vértice raiz do caminho.
    @param int* o array de cores.
*/
void bfs(Solucao solucao, Vertex vertice) {
    Fila fila = nova_fila(graph_order(solucao->grafo));
    solucao->cores[vertice] = AZUL;
    enfilera(fila, vertice);
    while(!esta_vazia(fila)) {
        Vertex pai = desenfilera(fila);
        int grau = graph_vertex_degree(solucao->grafo, pai);
        Vertex filhos[grau];
        graph_neighbors(solucao->grafo, pai, filhos);
        for(int i = 0; i < grau; i++) {
            Vertex filho = filhos[i];
            if(solucao->cores[filho] == NAO_VISITADO) {
                colore_vertice(solucao, pai, filho);
                enfilera(fila, filho);
            } else if(solucao->cores[filho] == solucao->cores[pai]) {
                adiciona_conflitante(solucao, pai);
            }
        }
    }
    destroi_fila(fila);
}

/* 
    Implementação da representação de uma solução.
    @param Graph para a busca e criação de partições.
    @return representação de solução com suas caracteristicas.
*/
Solucao nova_solucao(Graph grafo) {
    Solucao solucao = malloc(sizeof(struct solucao));
    int vertices = graph_order(grafo);
    solucao->cores = malloc(vertices * sizeof(int));
    solucao->conflitantes = malloc(vertices * sizeof(int));
    for(int i = 0; i < vertices; i++) {
        solucao->cores[i] = NAO_VISITADO;
        solucao->conflitantes[i] = -1;
    }
    solucao->grafo = grafo;
    solucao->ehPacifica = true;
    solucao->qtdConflitantes = 0;
    return solucao;
}

/*
    Apresenta a solução.
    @param Solucao que será apresentada.
*/
void mostra_solucao(Solucao solucao) {
    if(solucao->ehPacifica) {
        printf("PAZ!\n");
        int vertices = graph_order(solucao->grafo);
        for(int i = 0; i < vertices; i++) {
            if(solucao->cores[i] == AZUL)
                printf("%d ", i);
        }
        printf("\n");
        for(int i = 0; i < vertices; i++) {
            if(solucao->cores[i] == VERMELHO)
                printf("%d ", i);
        }
        printf("\n");
        return;
    }
    printf("GUERRA!\n");
    for(int i = 0; i < solucao->qtdConflitantes; i++) 
        printf("%d ", solucao->conflitantes[i]);
    printf("\n");
}

/*
    Colore um vértice dentro da solução.
    @param Solucao que será modificada.
    @param int pai do vértice que sera colorido.
    @param int vertice que será colorido;
*/
void colore_vertice(Solucao solucao, int pai, int vertice) {
    if(solucao->cores[pai] == AZUL) {
        solucao->cores[vertice] = VERMELHO;
        return;
    }
    solucao->cores[vertice] = AZUL; 
}

/*
    Adiciona um vértice na lista de conflitantes de uma solução 
    caso ele não exista.
    @param Solucao que será modificada.
    @param int vertice que será adicionado;
*/
void adiciona_conflitante(Solucao solucao, int vertice) {
    for(int i = 0; i < solucao->qtdConflitantes; i++) {
        if(solucao->conflitantes[i] == vertice){
            return;
        }
    }
    solucao->ehPacifica = false;
    solucao->conflitantes[solucao->qtdConflitantes] = vertice;
    solucao->qtdConflitantes++;
}

bool conflitantes_contem(Solucao solucao, int vertice) {
    for(int i = 0; i < solucao->qtdConflitantes; i++) {
        if(solucao->conflitantes[i] == vertice){
            return true;
        }
    }
    return false;
}

/*
    Libera a memória alocada dinâmicamente na construção da solução.
    @param Solucao que vai ser desalocada.
*/
void destroi_solucao(Solucao solucao) {
    free(solucao->conflitantes);
    free(solucao->cores);
    free(solucao);
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