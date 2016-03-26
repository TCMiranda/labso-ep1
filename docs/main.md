## EPI 1 Computer system simulation

##### Detalhes da implementação

O simulador se trata de uma fila de eventos. A cada ciclo, o simulador executa uma tarefa definida anteriormente.

Após cada tarefa executada, o fluxo define o próximo ciclo de execução.

O início do simulador se encontra em `src/main`, onde está definido o método de entrada que guarda as referências das variáveis que compõem o simulador:

    * processes   -> Processes definitions list loaded from disk
    * entry_queue -> Arrived processes queue, updated every loop
    * job_queue   -> Executing processes queue, updated on scheduler call
    * memory      -> Memory map, called on central memory request

    `cycle`       :: Maintains the current CPU cycle
    `schedule`    :: Maintains the next event step

Para o simulador, foram usadas apenas variáveis locais e definições globais.
As difinições estáticas `#define` estão organizadas em `/src/h` junto aos cabeçalhosdos arquivos de estruturas de dados.

Em `/src/h` estão definidos:

    headers.h        -> Agrupamento das bibliotecas e definições de estruturas

    simulator_defs.h -> Definições globais de variáveis de configuração
    queue.h          -> Estruturas e métodos de lista e cursor de fila
    process.h        -> Estrutura da definição de um processo
    memory_map.h     -> Estrutura dos dados de gerenciamento de memória

Os demais arquivos em `/src` definem os métodos das demais etapas do simulador.
O gerenciamento de processos, gerenciamento de memória e escalonador.
