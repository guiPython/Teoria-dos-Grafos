# Teoria-dos-Grafos
Repositório de exercícios de Teoria dos Grafos UFABC 2023 Q3

O repositório usa uma lib escrita em C pelos professores Maycon Sambinelli e Carla Negri Lintzmayer, os exercicios foram resolvidos utilizando ela como base.
Algumas modificações foram feitas para que fosse mais facíl manipular digrafos e grafos com ponderados, elas são:
- Adição do atributo peso para toda aresta, quando a informação não é relevante esse atributo foi iniciado com valor 1
- Adição de uma função que adiciona arestas levando em consideração o sentido (digrafos)

Com as modificações as implementações tanto em matriz de adjacencia quanto em lista ligada foram 
modificadas para suportar a adição dos pesos, no caso da matriz cada posição indica o peso da aresta, 
caso seja 0 significa que não temos a aresta, já no caso de lista ligada foi adicionado o atributo
peso em cada nó.

Os exercicios estão com os textos originais e os casos de entrada e saida, caso precise testar 
existem os comandos de compilação no Makefile que geram o binário.
