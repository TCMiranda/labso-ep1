#include <headers.h>

int main() {

  queue_cursor* processes = getProcessesList();
  queue_cursor* entry_queue = getEntryQueue();
  queue_cursor* job_queue = schl_getJobQueue();

  memory_map* memory = memm_getMemoryMap();

  int cycle = 0;

  while (++cycle) {

    printf("\\_Cycle %d__\\", cycle);

    updateEntryQueue(processes, entry_queue);

    printf("\n[Ready] ");
    qc_foreach(entry_queue, &processPrinter);

    /* GetNextJob and push it to job_queue if not already pushed */
    schl_getNextJob(entry_queue, job_queue, memory);

    printf("\n[Jobs] ");
    qc_foreach(job_queue, &processPrinter);

    printf("\n[Memm] %d-%d=%d",
           memory->max_frames,
           memory->available_frames,
           memory->max_frames - memory->available_frames);

    /* Execute the process */
    schl_executeJob(job_queue);

    printf("\n");
    if (cycle > 3) break;
  }

  printf("\n\\-_\nReset cursor, current id: %d\n",
         processes->current->process->id);
  printf("End.\n");
  return 0;
}
