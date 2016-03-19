#define PROCESSES_DEFS_FILENAME "processes.csv"

FILE* getProcessesFile() {

  FILE* file;
  if (file = fopen(PROCESSES_DEFS_FILENAME, "r")) {

    printf("Got file %s\n\n", PROCESSES_DEFS_FILENAME);
    return file;
  }

  printf("File not found");
  exit(1);
  return;
}

process* fillNextProcess(char* line) {

  const char* tok;
  process* p = malloc(sizeof(process*));

  p->id           = atoi(strtok(line, ","));
  p->arrival_time = atoi(strtok(NULL, ","));
  p->cpu_cycles   = atoi(strtok(NULL, ","));
  p->memory       = atoi(strtok(NULL, ","));
  p->io           = atoi(strtok(NULL, ","));

  free(line);
  return p;
}

process* getNextProcessDef(FILE* file) {

  char line[1024];
  if ( !fgets(line, 1024, file)
       || ferror(file)
       || feof(file) ) {

    return NULL;
  }

  char* tmp = strdup(line);
  process* p = fillNextProcess(tmp);

  return p;
}

queue_cursor* getProcesses(FILE* file) {

  queue_cursor* cursor = malloc(sizeof(queue_cursor*));

  oneway_list* processes = malloc(sizeof(oneway_list*));
  oneway_list* head = NULL;
  oneway_list* tail = NULL;

  while (true) {

    process* p;
    if ( !(p = getNextProcessDef(file)) ) {

      printf("Finished reading\nLast id: %d\n\n",
             processes->process->id );

      tail = processes;

      break;

    } else {

      /* Assing to current node on the fisrt time,
       * then skip to processes->next */
      if (processes->process) {

        processes->next = getListNode();
        processes = processes->next;
      }

      /* Assign current process to current node */
      processes->process = p;

      /* Assign head item on the first time */
      if (!head) {

        printf("Assign list head\n");
        (head = processes);
      }
    }
  }

  cursor->head = head;
  cursor->tail = tail;
  cursor->current = head;

  return cursor;
}

queue_cursor* getProcessesList() {

  FILE* f = getProcessesFile();

  return getProcesses(f);
}

void printProcess(process* process) {

  printf("Node(%d) {\n  time: %d\n  cpu: %d\n  memory: %d\n  io: %d \n}\n\n",
         process->id,
         process->arrival_time,
         process->cpu_cycles,
         process->memory,
         process->io );

  return;
}

void processDumper(oneway_list* item, void* arg) {

  printProcess(item->process);
}

void processPrinter(oneway_list* item, void* arg) {

  printf("* %d \n", item->process->id);
}

void processArrivalTimePrinter(oneway_list* item, void* arg) {

  printf("* Process %d: %d\n", item->process->id, item->process->arrival_time);
}
