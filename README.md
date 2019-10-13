# Sistemas Operacionais - TP 2 (tp2virtual)

Trabalho prático de implementação de um simulador de memória virtual para a disciplina de Sistemas Operacionais/UFSJ.

## Instalação e uso

``` bash
make
make debug # binario com debug
make clean # remover binario
```

### Uso

``` bash
./tp2virtual [polsub] [arquivo] [pagsize] [memsize]
# [polsub]  Algoritmo de substituição: lru, nru, segunda_chance.
# [arquivo] Caminho para o arquivo log.
# [pagsize] Tamanho de página de memória: 2 a 64.
# [memsize] Tamanho da memória física : 128 a 16384.
```

### Formato de arquivo log

Cada linha contém um endereço de memória de 32 bits, seguido das letras R ou W, indicando um acesso de leitura ou escrita, respectivamente. Exemplo: 

``` text
0785db58 W
000652d8 R
0005df58 W
000652e0 R
0785db50 W
000652e0 R
31308800 R
00062368 R
```

## Acknowledgments

*   [GenericMakefile](https://github.com/mbcrawfo/GenericMakefile) - versionamento e debug definidos em tempo de compilação.
