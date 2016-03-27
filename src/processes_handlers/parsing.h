#define PROCESSES_DEFS_FILENAME "processes.csv"

FILE* getProcessesFile() {

  FILE* file;
  if (file = fopen(PROCESSES_DEFS_FILENAME, "r")) {

    printf("Got file %s\n", PROCESSES_DEFS_FILENAME);
    return file;
  }

  printf("File not found");
  exit(1);
  return;
}

process* fillNextProcess(char* line) {

  process* p = malloc(sizeof(process*));

  p->id            = atoi(strtok(line, ","));
  p->arrival_time  = atoi(strtok(NULL, ","));
  p->cpu_cycles    = atoi(strtok(NULL, ","));
  p->memory        = atoi(strtok(NULL, ","));
  p->io_requests   = atoi(strtok(NULL, ","));

  p->io_interval  = (int) floor(p->cpu_cycles / p->io_requests);

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

  queue_cursor* cursor = malloc(sizeof(queue_cursor));

  oneway_list* processes = malloc(sizeof(oneway_list*));
  oneway_list* head = NULL;
  oneway_list* tail = NULL;

  while (true) {

    process* p;
    if ( !(p = getNextProcessDef(file)) ) {

      printf("Got processes defs. Last id: %d\n\n",
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

int getProcessesLength(queue_cursor* processes) {

  int processes_length = 0;
  int* c = &processes_length;
  qc_foreach(processes, &counter, c);

  return processes_length;
}
