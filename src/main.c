#include <headers.h>

int main() {

  queue_cursor* processes = getProcessesList();
  queue_cursor* entry_queue = getEntryQueue();

  while (true) {

    updateEntryQueue(processes, entry_queue);
    forEachCursor(entry_queue, &processPrinter);
    getMemoryMap();

    break;
  }

  printf("\n");
  forEachCursor(processes, &processArrivalTimePrinter);

  printf("\nReset cursor, current id: %d\n", processes->current->process->id);
  printf("End.\n");
  return 0;
}
