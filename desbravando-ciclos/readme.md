# Desbravando os Ciclos de Grafolândia

Como você pode ter percebido no problema anterior, a Grafolândia esconde um mistério.

A presença de ciclos nas relações de conflitio entre os habitantes da Grafolândia pode trazer instabilidade e desafios para os mesmos.

Sua missão agora é criar um algoritmo capaz de determinar se Grafolândia está livre de ciclos ou não.

# Entrada
A primeira linha da entrada consiste de dois inteiros V e E, separados por espaço, onde 1 ≤ V ≤ 1000 e 0 ≤ E ≤ V(V - 1)/2, representando o número de habitantes e o número de relações de conflito entre os habitantes da Grafolândia, respectivamente.

Cada habitante é representado por um código numérico entre 0 e V - 1. 

Cada uma das próximas E linhas consiste de um par de inteiros x e y, separados por espaço, onde 0 ≤ x,y ≤ V - 1, que representa a existência de um conflito entre os habitantes de códigos x e y.



# Saída
Se houver ciclos entre as relações da Grafolândia, seu programa deve imprimir "GUERRA!". 

Caso contrário, seu programa deve imprimir "PAZ!".

# Exemplos

### Entrada 1
```
5 4
0 1
0 4
2 4
3 4
```

### Saída 1
```
PAZ!
```

### Entrada 2
```
5 6
0 1
0 4
0 2
2 4
3 1
3 4
```
### Saída 2
```
GUERRA!
```