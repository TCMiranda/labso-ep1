## EPI 1 Computer system simulation

### Instruções

O projeto está organizado em

    dist/          // Compilado
    src/           // Fontes

    build.sh       // Compila os fontes de src/ para dist/
    run.sh         // Executa o compilado em dist

    processes.csv  // Arquivo de entrada

Para executar e desenvolver basta

`./build.sh` para compilar
`./run.sh` para executar

Ou ainda `(./build.sh; ./run.sh)` para ambos.

Definições extras sobre o programa, como tamanho da memória em:

    /src/h/simulator_defs.h

### Progresso

#### Carregamento / setup
- [x] Leitura dos eventos
- [x] Enfileiramento dos eventos
- [x] Inicio do loop de eventos

#### Loop
- [x] Validacao do "tempo de chegada"
- [x] Ecaminhamento do evento a fila de entrada
- [ ] Validação da memoria disponivel
- [ ] Carregamento de eventos na fila de entrada em memoria disponivel

#### Execucao
- [ ] Escolha algoritimo de escalonamento
- [ ] Escolha do evento da fila de pronto
- [ ] Execucao do slice definido
- [ ] Validacao do evento
- [ ] Loop
