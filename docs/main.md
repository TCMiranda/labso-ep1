## EPI 1 Computer system simulation

##### Detalhes da implementação

O simulador se trata de uma fila de eventos. A cada ciclo, o simulador executa uma tarefa definida anteriormente.

Após cada tarefa executada, o fluxo define o próximo ciclo de execução.

O início do simulador se encontra em `src/main`, onde está definido o método de entrada que guarda as referências das variáveis que compõem o simulador:

    * processes   -> Processes definitions list loaded from disk
    * entry_queue -> Arrived processes queue, updated every loop
    * io_lock     -> Represents IO execution resource lock
    * memory      -> Memory map, called on central memory request
    * job_queue   -> Executing processes queue, updated on scheduler call

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


##### Sobre a lista e entrada de processos

Dentre os processos executados dentro do loop de eventos, são também executadas a atualização do tempo de chegada dos processos, e o tempo de espera de uma requisição IO.

Dessa forma, entrada de um processo é simulada pelo deccores dos ciclos do loop de eventos.

O primeiro evento tratado no loop, é referente ao tratamento de um processo que entrou no loop. O processamento de simulação da entrada de um evento ocorre ocasionalmente e variavelmente segundo o algorítmo de escalonamento.

No caso de um algorítimo de processamento assíncrono (mais de um processo sendo executado ao mesmo tempo com a divisão de slices de processamento) a entrada é frequente, e executada a cada release da CPU. Já no caso de um algorítimo sequencial, como o "first come, first served", a entrada de processos é realizada apenas após o termino da execução de um processo e a liberação da CPU. Dessa forma, a fila entrada é avaliada e o próximo processo que reservará a CPU é escolhido.


##### Sobre o tempo de vida de um processo

Os processos seguem o seguinte fluxo:

    Entrada o------------> Alocamento à memória ___
            |                         ^           |
            |                         |           |
            --> Fila para alocamento _|           v
                                                  |
    --- Fila de processos prontos <----------o----o----|
    |                                        |         |
    |                                        v         ^
    ----------> Escalonamento do processo ---o----|    |
                                                  |    |
            ___ Release da CPU - Requisição IO <__|    ^
            |                                          |
            o-------> Lock e execucao de IO ___________|
            |                       ^             |
            |                       |             |
            --> Fila para lock IO __|             v
                                                  |
    ___ Termino da execução e liberação da CPU <---
    |
    |
    --------> Liberação da memória alocada ao processo

Onde cada etapa desse ciclo de vida, está ligada a um evento específico.


##### Sobre os escalonadores

Forão desenvolvidos os algorítimos de escalonamento FCFS (first-come, first-served) e Round-robin.
Cada um dos algorítmos com um foco específico.

O algorítimo FCFS trata os processos como uma fila única e ordenada pela chagada (arival time). Dessa forma, o processo que é escalonado é sempre aquele que chegou primeiro à simulação. O processo escolhido pelo escalonador é executado até atingir uma requisição IO ou ser finalizado. Não existe troca voluntária do processo sendo executado.

Já o algorítmo Round-Robin tem um funcionamento assíncrono. Os processos são interrompidos dado um tempo de processamento determinado. Esse procedimento permite que dois ou mais processos sejam executados em "paralelo". Vale ressaltar que o algorítimo assume um núcleo apenas de processamento, portanto, o paralelismo real não acontece. Porém a troca constante do processo executado permite a simulação do paralelismo, mesmo que em apenas um núcleo.


##### Sobre a simulação de requisições IO

As requisição são feitas em três etapas. Primeira a interrupção do processamento dada a requisição. A requisição envia o processo a uma fila, onde aguardará os recursos de IO. Eventualmente haverá recursos para que o processo seja removido da fila e tenha o controle dos recursos de IO. O processo executa as requisições necessárias e libera os recursos ao término. Com a requisição concluída, o processo volta a fila de processos prontos para ser executados.

------
Tiago de Carvalho Miranda
Nº 8061855
