# Uma Jornada Final na Grafolândia

A Grafolândia, agora plenamente restaurada e envolta em seu esplendor mágico, abre-se diante de seus habitantes com promessas inexploradas e oportunidades cintilantes. As estradas, marcadas por suas propriedades únicas, persistem como trilhas de avanço, tecendo um labirinto fascinante de conexões unidirecionais.

Os habitantes, mergulhados em uma era de paz e harmonia, anseiam por explorar e percorrer os encantos da Grafolândia. Cientes de suas próprias finanças, aspiram a desbravar a terra mágica realizando ocasionais mochilões, o que significa que querem absorver as maravilhas de sua terra ao máximo, mas com gastos mínimos. Isso também significa que, infelizmente, alguns povoados serão inalcançáveis, pois só seria possível chegar até eles de avião.

Sua nobre missão é orientar os habitantes na criação das jornadas mais eficientes pela Grafolândia, utilizando sabiamente as vias encantadas. Dada a localização atual de um habitante, seu desafio é descobrir quais são os menores percursos que ele pode fazer para qualquer outro povoado.

# Entrada
A primeira linha da entrada consiste de dois inteiros V e E, separados por espaço, onde 1 <= V <= 1000 e 0 <= E <= V(V - 1), representando o número de povoados e o número de estradas da Grafolândia, respectivamente.

Cada povoado é representado por um código numérico entre 0 e V - 1.

A próxima linha consiste de um único inteiro s, indicando o povoado do habitante que precisa de ajuda.

Cada uma das próximas E linhas consiste de um trio de números separados por espaços, sendo dois inteiros x y e um número real w, onde 0 <= x, y <= V - 1 e 0 <= w <= 500, que indicam que há uma estrada mágica do povoado x para o povoado y e cujo custo de percurso é w.

# Saída
Seu programa deve imprimir exatamente V linhas, sendo uma para cada povoado da Grafolândia. Na i-ésima linha, imprima:

s-i: perc se for possível ir até o povoado i, substituindo perc pelo menor percurso de s até i, que consiste de uma sequência de povoados separados por espaço (o habitante precisa saber como chegar até i);
s-i: impossivel se não for possível ir de mochilão de s até o povoado i;
s-i: o mais barato eh ficar em casa se i = s
Atenção: o percurso para o povoado i precisa ser impresso antes do percurso para o povoado j, se i < j.

# Exemplos
## Teste 1

### Entrada:
```
8 12
5
1 0 9
1 3 9
2 1 4
2 5 3
2 4 3
3 1 2
3 7 2
3 5 7
4 2 6
4 6 7
5 1 6
6 7 5
```
### Única saída:
```
5-0: 5 1 0
5-1: 5 1
5-2: impossivel
5-3: 5 1 3
5-4: impossivel
5-5: o mais barato eh ficar em casa
5-6: impossivel
5-7: 5 1 3 7
```

## Teste 2
### Entrada:
```
8 12
4
1 0 9
1 3 9
2 1 4
2 5 3
2 4 3
3 1 2
3 7 2
3 5 7
4 2 6
4 6 7
5 1 6
6 7 5
```
### Única saída:
```
4-0: 4 2 1 0
4-1: 4 2 1
4-2: 4 2
4-3: 4 2 1 3
4-4: o mais barato eh ficar em casa
4-5: 4 2 5
4-6: 4 6
4-7: 4 6 7
```
## Teste 3
### Entrada:
```
8 12
6
1 0 9
1 3 9
2 1 4
2 5 3
2 4 3
3 1 2
3 7 2
3 5 7
4 2 6
4 6 7
5 1 6
6 7 5
```
### Única saída:
```
6-0: impossivel
6-1: impossivel
6-2: impossivel
6-3: impossivel
6-4: impossivel
6-5: impossivel
6-6: o mais barato eh ficar em casa
6-7: 6 7
```
## Teste 4
### Entrada:
```
5 7
4
0 2 147.157803960143
1 2 94.4111885495974
1 3 186.479675741142
1 4 231.926045021029
2 3 17.9004480061572
2 4 276.148224952772
3 4 65.7337868609623
```
### Única saída:
```
4-0: impossivel
4-1: impossivel
4-2: impossivel
4-3: impossivel
4-4: o mais barato eh ficar em casa
```