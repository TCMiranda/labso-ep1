## EPI 1 Computer system simulation

#### [Detalhes da implementação](./docs/main.md)

Nos detalhes da implementação, estão as explicações sobre a estrutura dos códigos fonte. Como foi feita a organização dos arquivos, e a definição das estruturas de dados.

Consta também a forma que foi feita a implementação do loop de eventos, de forma a simular todos os casos de execução de processos em um computador segundo definido no artigo como _BASYS simulator_, processamento, escalonamento, memória, io, etc.

### Instruções

##### O projeto está organizado em

    dist/          // Compilado
    src/           // Fontes

    build.sh       // Compila os fontes de src/ para dist/
    run.sh         // Executa o compilado em dist

    processes.csv  // Arquivo de entrada

##### Para executar e desenvolver basta

`./build.sh` para compilar
`./run.sh` para executar

Ou ainda `(./build.sh; ./run.sh)` para ambos.

##### Extras

Definições extras sobre o programa, como tamanho da memória em:

    /src/h/simulator_defs.h

## Progresso

#### Carregamento / setup
- [x] Inicio do loop de eventos
- [x] Leitura dos eventos
- [x] Enfileiramento dos eventos

#### Loop
- [x] Validacao do "tempo de chegada"
- [x] Ecaminhamento do evento a fila de entrada
- [ ] Definição e escolha da task atual
- [ ] Execução da task atual

#### Carregamento
- [x] Escolha algoritimo de escalonamento
- [x] Escolha do evento da fila de pronto
- [x] Validação da memoria disponivel
- [x] Carregamento do evento escolhido em memoria disponivel
- [ ] Divisão da memória em páginas

#### Execução
- [x] Execução do slice definido - fcfs
- [ ] Execução do slice definido - rr
- [ ] Validação do evento
- [ ] Loop

## etc

    $ gcc --version
    gcc (GCC) 4.9.2 20150212 (Red Hat 4.9.2-6)
    Copyright (C) 2014 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
