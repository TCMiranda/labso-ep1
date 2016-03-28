## EPI 1 Computer system simulation

##### Detalhes da implementação

O simulador se trata de uma fila de eventos. A cada ciclo, o simulador executa uma tarefa definida anteriormente.

Após cada tarefa executada, o fluxo define o próximo ciclo de execução.

O início do simulador se encontra em `src/main`, onde está definido o método de entrada que guarda as referências das variáveis que compõem o simulador:

    * processes   -> Processes definitions list loaded from disk
    * entry_queue -> Arrived processes queue, updated every loop
    * job_queue   -> Executing processes queue, updated on scheduler call
    * io_lock     -> Represents IO execution resource lock
    * memory      -> Memory map, called on central memory request

    `cycle`       :: Maintains the current CPU cycle
    `schedule`    :: Maintains the next event step

Para o simulador, foram usadas apenas variáveis locais e definições globais.
As definições estáticas `#define` estão organizadas em `/src/h` junto aos cabeçalhosdos arquivos de estruturas de dados.

Em `/src/h` estão definidos:

    headers.h         -> Agrupamento das bibliotecas e definições de estruturas

    event_loop.h      -> Definições dos métodos de acesso ao event_loop
    event_loop_keys.h -> Definições das chaves de eventos
    io_handling.h     -> Estrutura do simulador de lock de IO
    memory_map.h      -> Estrutura dos dados de gerenciamento de memória
    oneway_list.h     -> Estrutura da lista ligada
    process.h         -> Estrutura da definição de um processo
    queue_cursor.h    -> Estruturas e métodos de lista e cursor de fila
    simulator_defs.h  -> Definições globais de variáveis de configuração

Os demais arquivos em `/src` definem os métodos das demais etapas do simulador.
O gerenciamento de processos, gerenciamento de memória, gerenciamento de IO e escalonador.


##### Sobre o event loop

O event loop (ciclo de eventos) simula a escolha entre as diversas etapas de um computador.
Dentre as taferas executadas, estão entradas de enventos externos, requisições à cpu, etc.

A cada ciclo do loop de eventos, apenas uma tarefa é executada. Esta, pode ou não definir uma próxima tarefa.

As tarefas do ciclo de eventos são:

    DEFAULT_ENTRY    -> 0 : Tarefa padrão (catch all), para entrada de eventos externos
    PROCESSES_ENTRY  -> 1 : Tarefa de entrada de eventos externos, igual a DEFAULT_ENTRY
    MEMORY_REQUEST   -> 2 : Valida os eventos na fila de entrada, solicita a memória e envia a fila de jobs
    CPU_REQUEST      -> 3 : Executa um ciclo do processo atual, e valida interrupções IO
    IO_REQUEST       -> 4 : Tarefa executada em uma interrupção de IO, envia o processo a fila de io
    IO_EXECUTION     -> 5 : Valida o lock de IO e requisita o processamento se disponível
    IO_RELEASE       -> 6 : Termino da execução IO, solta o lock dos recursos e valida a lista de io
    CPU_RELEASE      -> 7 : Termino da execução de um job

A partir do arquivo de configuração dos processos, a lista de processos é criada e a pipeline se inicia.
A loop é executado a fim de receber um processo como entrada externa, carrega-lo em memória, processar as requisições de IO, processar os ciclos de CPU, e terminar sua execução.

O Loop é finalizado no momento em que não existem mais processos aguardando entrada, nem sendo processados.
