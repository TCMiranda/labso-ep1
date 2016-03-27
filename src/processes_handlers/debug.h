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
