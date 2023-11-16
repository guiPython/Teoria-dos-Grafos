# Desvendando a Magia das Conexões na Grafolândia

À medida que Grafolândia emergiu dos sombrios tempos de guerra, e as conexões mínimas entre os povoados voltaram a ser restabelecidas, as estradas voltaram a ter suas propriedades mágicas: os caminhos só permitem avançar, mas nunca retroceder.

Agora, mais do que nunca, os habitantes anseiam por construir vários caminhos de deslocamento entre os povoados e, certamente, caminhos que os permitam voltar ao seu povoado de origem.

Como várias estradas já estão construídas, é preciso primeiro detectar quais povoados já estão em regiões altamente conectadas, isto é, regiões em que quaisquer dois povoados têm uma estrada que os conectam em ambas as direções. Sua missão agora é detectar onde, no mapa atual, essas regiões já existem.

# Entrada
A primeira linha da entrada consiste de dois inteiros V e E, separados por espaço, onde 1 <= V <= 1000 e 0 <= E <= V(V - 1), representando o número de povoados e o número de estradas que já foram construídas na Grafolândia, respectivamente.

Cada povoado é representado por um código numérico entre 0 e V - 1.

Cada uma das próximas E linhas consiste de um par de números inteiros separados por espaços, x y, onde 0 <= x, y <= V - 1, que indicam que há uma estrada mágica do povoado x para o povoado y.

# Saída
A primeira linha da saída deve ser a frase Ha X regioes altamente conectadas:, onde X deve ser corretamente substituído pela quantidade de regiões altamente conectadas encontradas. Se X = 1, então escreva a frase Ha 1 regiao altamente conectada:.

Não use acentos!

Cada uma das X linhas seguintes deve contar todos os povoados de uma região altamente conectada da Grafolândia, em ordem crescente do código numérico, e separados por espaço, conforme os exemplos abaixo. As regiões em si não têm uma ordem específica.

# Exemplos

## Teste 1
### Entrada:
```
7 15
0 2
0 6
2 3
3 5
4 0
4 1
4 3
4 5
4 6
5 1
5 4
6 0
6 1
6 3
6 4
```
### Possível saída:
```
Ha 2 regioes altamente conectadas:
1 
0 2 3 4 5 6
```

## Teste 2
### Entrada:
```
14 32
1 3
1 5
2 4
2 5
3 1
3 2
3 4
4 0
4 5
5 0
5 1
5 2
5 7
6 7
7 8
7 13
9 8
9 12
9 13
10 8
10 11
10 12
11 12
11 13
12 8
12 10
12 11
13 6
13 7
13 9
13 10
13 11
```
### Possível saída:
```
Ha 4 regioes altamente conectadas:
0 
8 
6 7 9 10 11 12 13 
1 2 3 4 5
```

## Teste 3
### Entrada:
```
5 16
0 1
0 2
0 3
0 4
1 0
1 2
1 4
2 0
2 1
2 4
3 1
3 2
4 0
4 1
4 2
4 3
```
### Única saída possível:
```
Ha 1 regiao altamente conectada:
0 1 2 3 4
```