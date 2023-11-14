# Conectando Povoados Distantes na Grafolândia

Agora que a Grafolândia emergiu dos sombrios tempos de guerra, o momento é de reconstrução e renovação.

Os cidadãos deste mágico reino enfrentam uma necessidade urgente: restabelecer a intrincada teia de conexões que une os povoados, assegurando que todos estejam interligados.

No entanto, os efeitos devastadores da guerra deixaram os cofres públicos vazios, impondo uma restrição crucial: é vital estabelecer uma única ligação entre quaisquer dois povoados, de forma que no final de todas as obras, os gastos sejam o menor possível.

# Entrada
A primeira linha da entrada consiste de dois inteiros V e E, separados por espaço, onde 1 <= V <= 1000 e 0 <= E <= V(V - 1)/2, representando o número de povoados e o número de estradas que poderiam ser construídas na Grafolândia, respectivamente.

Cada povoado é representado por um código numérico entre 0 e V - 1.

Cada uma das próximas E linhas consiste de um trio de números separados por espaços, sendo dois inteiros x y e um número real w, onde 0 <= x, y <= V - 1 e 0 <= w <= 500, que indicam que a criação de uma estrada entre o povoado x e o povoado y irá custar w aos cofres públicos.

Você pode considerar que as E possibilidades de estradas, se todas escolhidas, certamente conectariam a Grafolândia.

# Saída
Seu programa deve indicar, na primeira linha, o custo mínimo que será cobrado dos cofres públicos para a construção de todas as estradas necessárias para conectar os povoados da Grafolândia, com duas casas decimais.

Nas próximas V - 1 linhas deve imprimir um par x y de inteiros por linha, que indicam que a estrada entre os povoados x e y deve ser construída. Não há uma ordem específica para essa resposta.

# Exemplos

## Teste 1

### Entrada:
```
6 5
0 3 367.115886309872
0 4 324.998711513348
1 2 416.953607385499
1 5 211.701105886336
4 5 258.518695039362
```
### Possível saída:
```
1579.29
1 5
4 5
0 4
0 3
1 2
```

## Teste 2

### Entrada:
```
8 13
0 1 323.812089641324
0 6 302.457182790761
1 3 453.792135601436
1 5 137.644866249893
2 3 41.3104710812971
2 5 193.627634556928
2 6 180.828721298065
2 7 434.499326599484
3 4 83.7306480627169
3 5 369.399542441440
4 5 189.346673631658
4 7 470.732825259378
5 6 178.072698224791
```
### Possível saída:
```
1358.54
2 3
3 4
1 5
5 6
2 6
0 6
2 7
```
## Teste 3

### Entrada:
```
8 8
0 3 8.95038066654014
0 4 151.442836176780
1 4 257.700046974838
1 7 392.469230360402
2 6 206.389384655778
3 5 430.995265493799
3 7 311.969790382856
6 7 86.5411574713376
```

### Possível saída:
```
1453.99
0 3
6 7
0 4
2 6
1 4
3 7
3 5
```
