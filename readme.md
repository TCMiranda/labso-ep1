## EPI 1 Computer system simulation

#### [Detalhes da implementação](./docs/main.md)

Nos detalhes da implementação, estão as explicações sobre a estrutura dos códigos fonte. Como foi feita a organização dos arquivos, e a definição das estruturas de dados.

Consta também a forma que foi feita a implementação do loop de eventos, de forma a simular todos os casos de execução de processos em um computador segundo definido no artigo como _BASYS simulator_, processamento, escalonamento, memória, io, etc.


## Instruções

##### O projeto está organizado em

    dist/          // Compilado
    src/           // Fontes

    build.sh       // Compila os fontes de src/ para dist/
    run.sh         // Executa o compilado e exibe a saida no terminal
    report.sh      // Executa o compilado, salva a saida em ./report.txt e exibe o resultado

    processes.csv  // Arquivo de entrada

#### Para testar e validar os resultados do projeto

Execute `(./build.sh; ./report.sh)` para compilar e ler o report.


##### Para executar e desenvolver, use

`./build.sh` para compilar
`./run.sh` para executar
`./report.sh` para executar com output para `./report.txt` e ler com `more`

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
- [x] Definição e escolha da task atual
- [x] Execução da task atual

#### Carregamento
- [x] Escolha algoritimo de escalonamento
- [x] Escolha do evento da fila de pronto
- [x] Validação da memoria disponivel
- [x] Carregamento do evento escolhido em memoria disponivel
- [x] Validação e alocação de memória em páginas

#### Execução
- [x] Execução do slice definido - fcfs
- [x] Execução do slice definido - rr
- [x] Validação do evento
- [x] Release da CPU
- [x] Release da memória
- [x] Loop

#### IO
- [x] Enviar processos para fila de IO e agendar execução
- [x] Criar fila para interrupção por IO
- [x] Validar entrada de eventos de IO do processo executado
- [x] Reenviar processo a fila de entrada após término do IO

## etc

    $ gcc --version
    gcc (GCC) 4.9.2 20150212 (Red Hat 4.9.2-6)
    Copyright (C) 2014 Free Software Foundation, Inc.
    This is free software; see the source for copying conditions.  There is NO
    warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
