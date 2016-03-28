void counter(oneway_list* item, va_list vas) {

  int* counter = va_arg(vas, int*);
  (*counter)++;
}

void printProcess(process* process) {

  printf("Node(%d) {\n  time: %d\n  cpu: %d\n  memory: %d\n  io: %d \n  io_interval: %d \n  io_current: %d \n}\n\n",
         process->id,
         process->arrival_time,
         process->cpu_cycles,
         process->memory,
         process->io_requests,
         process->io_interval,
         process->io_current );
}

void processDumper(oneway_list* item, va_list vas) {

  printProcess(item->process);
}

void processPrinter(oneway_list* item, va_list vas) {

  printf("%d; ", item->process->id);
}

void processArrivalTimePrinter(oneway_list* item, va_list vas) {

  printf("P(%d: %d); ", item->process->id, item->process->arrival_time);
}

void processStringConcatenator(oneway_list* item, va_list vas) {

  char* formatted = va_arg(vas, char*);
  char* tmp = malloc(sizeof(formatted));

  strcpy(tmp, formatted);
  snprintf(formatted, 20, "%s|%d", tmp, item->process->id);
  free(tmp);
}

char* getFormatterProcesses(queue_cursor* queue) {

  char* formatted = malloc(sizeof(char));

  qc_foreach(queue, &processStringConcatenator, formatted);

  char* tmp = malloc(sizeof(formatted));
  strcpy(tmp, formatted);

  snprintf(formatted, 22, "[%s]", tmp);
  free(tmp);

  return formatted;
}

void printDebugHeaders() {

  printf(" Cycle   Task  ->  % 22s | % 17s | % 17s | % 17s | Output\n",
         "Processes",
         "Entry",
         "Jobs",
         "IO");
}

void printCurrentState(int cycle,
                       event_loop_key current_task,
                       queue_cursor* processes,
                       queue_cursor* entry_queue,
                       queue_cursor* job_queue,
                       queue_cursor* io_queue
                       ) {

  printf("[ % 4d ] % 3d   ->  % 22s | % 17s | % 17s | % 17s | ",
         cycle,
         current_task,
         getFormatterProcesses(processes),
         getFormatterProcesses(entry_queue),
         getFormatterProcesses(job_queue),
         getFormatterProcesses(io_queue));

  fflush(stdout);
}
