#include <headers.h>

int main() {

  queue_cursor* processes = getProcessesList();
  queue_cursor* entry_queue = getEntryQueue();

  while (true) {

    updateEntryQueue(processes, entry_queue);
    forEachCursor(entry_queue, &processPrinter, NULL);

    break;
  }

  printf("\n");
  forEachCursor(processes, &processArrivalTimePrinter, NULL);

  printf("\nReset cursor, current id: %d\n", processes->current->process->id);
  printf("End.\n");
  return 0;
}
