#define PROCESSES_DEFS_FILENAME "processes.csv"

FILE* getProcessesFile() {

  FILE* file;
  if (file = fopen(PROCESSES_DEFS_FILENAME, "r")) {

    printf("Got file %s\n", PROCESSES_DEFS_FILENAME);
    return file;
  }

  printf("File not found\n");
  exit(1);
  return;
}

/* Process defs assignment
 * Documented at /src/h/process.h */
process* fillNextProcess(char* line) {

  process* p = malloc(sizeof(process));

  p->id            = atoi(strtok(line, ","));
  p->arrival_time  = atoi(strtok(NULL, ","));
  p->cpu_cycles    = atoi(strtok(NULL, ","));
  p->memory        = atoi(strtok(NULL, ","));
  p->io_requests   = atoi(strtok(NULL, ","));

  if (p->cpu_cycles <= 0) {

    printf("Process cpu time must be > than 0.\n");
    exit(1);
    return;
  }

  if (p->io_requests > p->cpu_cycles) {

    printf("IO requests number must be > than total cpu cicles.\n");
    exit(1);
    return;
  }

  p->io_interval    = (int) floor(p->cpu_cycles / p->io_requests);
  p->io_current     = p->io_interval - 1;
  p->io_record_size = IO_DEFAULT_RECORD_SIZE;

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

/* Build processes linked list
 * and assign cursor references */
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

        processes->next = ol_getListNode();
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
