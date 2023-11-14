# Aventura Bipartida em um Mundo Conectado

Você acaba de ser convocado para uma missão emocionante em um mundo mágico chamado Grafolândia, onde os habitantes são representados por pontos interconectados, criando um intrigante e complexo sistema de relações.

No entanto, há uma particularidade interessante: esses habitantes são divididos em dois clãs rivais, os "Azuis" e os "Vermelhos".

Para manter a paz em Grafolândia, é crucial determinar se as relações entre esses habitantes podem ser classificadas em duas facções distintas, de modo que não haja conflitos internos em cada clã.

Sua tarefa é criar um algoritmo que avalie se Grafolândia pode ser organizada dessa maneira, separando seus habitantes em dois clãs sem que haja conflitos internos.

Você precisa desenvolver uma função que descubra se é possível alcançar essa harmonia.

A paz em Grafolândia depende de você e do sucesso dessa missão. 

Que a sabedoria e a determinação estejam com você!

# Entrada

A primeira linha da entrada consiste de dois inteiros V e E, separados por espaço, onde 1 ≤ V ≤ 1000 e 0 ≤ E ≤ V(V - 1)/2, representando o número de habitantes e o número de relações de conflito entre os habitantes da  Grafolândia, respectivamente.

Cada habitante é representado por um código numérico entre 0 e V - 1.

Cada uma das próximas E linhas consiste de um par de inteiros x e y, separados por espaço, onde 0 ≤ x,y ≤ V - 1, que representa a existência de um conflito  entre os habitantes de códigos x e y.

# Saída

Se for possível dividir a Grafolândia em dois clãs em que não haja conflitos internos, seu programa deve imprimir três linhas: a primeira contendo o texto "PAZ!", e as duas últimas contendo os habitantes de cada clã, separados por  espaço.

Os habitantes devem ser impressos em ordem crescente numérica.

Se não for possível a divisão, seu programa deve imprimir duas linhas: a primeira contendo o texto "GUERRA!" e a última contendo uma sequência de habitantes que comprovem o impedimento da divisão (essa sequência não  necessariamente deve ser em ordem crescente numérica, ela precisa realmente indicar o impedimento).

# Exemplos

### Entrada 1
```
5 5
0 1
0 4
2 4
3 1
3 4
```

### Saída 1
```
PAZ!
0 2 3 
1 4
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
2 0 4 
```
